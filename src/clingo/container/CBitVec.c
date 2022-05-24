#include "clingo/container/CBitVec.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "clingo/io/read_type.h"
#include "clingo/io/write.h"
#include "clingo/io/write_type.h"
#include "clingo/lang/func.h"
#include "clingo/lang/math.h"
#include "clingo/lang/mem.h"
#include "clingo/type/cBytes.h"
#include "clingo/type/uint8.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

struct CBitVec
{
   int64_t numOfBits;
   int64_t numOfBytes;

   cByte* bytes;
   cByte bitMask;
};

static inline void cleanup( void* instance )
{
   CBitVec* vec = instance;
   free( vec->bytes );
}

cMeta const C_BitVecMeta = {
   .desc  =stringify_c_( CBitVec ),
   .cleanup = &cleanup
};

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

// sizeof gives size in bytes (8 bits per byte)
#define BITS_IN_WORD_   8

// word of all 1s
#define WORD_MAX_ byte_c_( 0xff )

cByte bit_mask( int64_t offset )
{
   cByte mask[8] = { 0xff, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe };
   return mask[offset];
}

char x[] = { 1, 2 };

// Index of word
static inline int64_t bytes_index( int64_t b )
{
   return ( b / BITS_IN_WORD_ );
}

static inline uint8_t bytes_offset( int64_t b )
{
   return uint8_c_( b % BITS_IN_WORD_ );
}

// Number of words required to store a given number of bits
static inline int64_t req_num_of_bytes( int64_t b )
{
   return ( b + BITS_IN_WORD_ - 1 ) / BITS_IN_WORD_;
}

static inline void mask_top_byte( CBitVec* vec )
{
   vec->bytes[ vec->numOfBytes - 1 ] &= vec->bitMask;
}

static inline int64_t unused_bits( CBitVec* vec )
{
   return vec->numOfBits % BITS_IN_WORD_;
}

static inline cBytes as_bytes( CBitVec const* vec )
{
   return bytes_c( vec->numOfBytes, vec->bytes );
}

static inline cVarBytes as_var_bytes( CBitVec* vec )
{
   return var_bytes_c( vec->numOfBytes, vec->bytes );
}

// '0' is 0x30 = 0 / '1' is 0x31 = 1
static inline cByte char_as_bit( char c )
{
   if ( c == '0' or c == 'o' )
   {
      return byte_c_( 0 );
   }

   return byte_c_( 1 );
}

static inline bool is_bit_char( char c )
{
   return ( c == '0' or c == 'o' or c == '1' );
}

static inline uint8_t popcount_byte( cByte n )
{
   uint8_t count = 0;    
   while ( n )
   {
      count += n & 0x01 ;    
      n >>= 1 ;
   }
   return count;
}

/*******************************************************************************

*******************************************************************************/

CBitVec* new_bit_vec_c( int64_t n )
{
   must_be_positive_c_( n );

   cObjectInfo const info = default_object_info_c_( &C_BitVecMeta );
   CBitVec* result = alloc_object_c_( CBitVec, &info );

   if( result == NULL )
   {
      return NULL;
   }

   result->numOfBits = n;
   result->numOfBytes = req_num_of_bytes( n );
   result->bytes = alloc_array_c_( result->numOfBytes, cByte );
   result->bitMask = bit_mask( bytes_offset( result->numOfBits ) );

   if( result->bytes == NULL )
   {
      release_c( result );
      return NULL;
   }

   return result;
}

CBitVec* copy_bit_vec_c( CBitVec const* vec )
{
   must_exist_c_( vec );

   size_t size;
   if ( not int64_to_size_c( vec->numOfBytes, &size ) ) return NULL;

   CBitVec* copy = new_bit_vec_c( vec->numOfBits );
   if ( copy == NULL ) return NULL;

   memcpy( copy->bytes, vec->bytes, size );

   return copy;
}

CBitVec* bit_vec_from_chars_c( cChars chars )
{
   int64_t count = 0;
   for_each_c_( char const*, c, chars )
   {
      if ( is_bit_char( *c ) )
      {
         ++count;
      }
      else if ( not isspace( *c ) )
      {
         return NULL;
      }
   }

   CBitVec* vec = new_bit_vec_c( count );
   if ( vec == NULL ) return NULL;

   int64_t i = 0;
   for_each_c_( char const*, c, chars )
   {
      if ( is_bit_char( *c ) )
      {
         if( *c == '1' ) // BitVec is 0s by default -- just set the 1s
         {
            set_on_bit_vec_c( vec, i, char_as_bit( *c ) );
         }
         ++i;
      }
   }

   return vec;
}

extern inline CBitVec* bit_vec_from_cstr_c( char const bitstr[static 1] );

/*******************************************************************************

*******************************************************************************/

int64_t bit_vec_size_c( CBitVec const* vec )
{
   must_exist_c_( vec );

   return vec->numOfBits;
}

cByte get_from_bit_vec_c( CBitVec const* vec, int64_t pos )
{
   must_exist_c_( vec );
   must_be_positive_c_( pos );
   must_be_c_( pos < vec->numOfBits );

   cByte const relevantByte = vec->bytes[ bytes_index( pos ) ];
   uint8_t const offset = 7 - bytes_offset( pos );

   return byte_as_bit_c( relevantByte >> offset );
}

int64_t find_index_of_bit_c( CBitVec const* vec,
                             cByte bit,
                             int64_t from )
{
   must_exist_c_( vec );

   bit = byte_as_bit_c( bit );

   for ( int64_t i = from; i < vec->numOfBits; ++i )
   {
      if ( bit == get_from_bit_vec_c( vec, i ) )
      {
         return i;
      }
   }

   return -1;
}

int64_t popcount_bit_vec_c( CBitVec const* vec, cByte bit )
{
   must_exist_c_( vec );

   int64_t numOfBits_set = 0;

   for( int64_t i = 0; i < vec->numOfBytes; i++ )
   {
      if( vec->bytes[ i ] > 0 )
      {
         numOfBits_set += popcount_byte( vec->bytes[ i ] );
      }
   }

   if ( bit == 1 )
   {
      return numOfBits_set;
   }
   else
   {
      return vec->numOfBits - numOfBits_set;
   }
}

int64_t rfind_index_of_bit_c( CBitVec const* vec,
                              cByte bit,
                              int64_t from )
{
   must_exist_c_( vec );

   bit = byte_as_bit_c( bit );

   for ( int64_t i = from; i > -1; i-- )
   {
      if ( bit == get_from_bit_vec_c( vec, i ) )
      {
         return i;
      }
   }

   return -1;
}

/*******************************************************************************

*******************************************************************************/

void set_on_bit_vec_c( CBitVec* vec, int64_t pos, cByte bit )
{
   must_exist_c_( vec );
   must_be_positive_c_( pos );
   must_be_c_( pos < vec->numOfBits );

   cVarBytes bytes = var_bytes_c( vec->numOfBytes, vec->bytes );
   set_bytes_bit_c( bytes, pos, bit );
}

void set_range_on_bit_vec_c( CBitVec* vec, cRange range, cByte bit )
{
   must_exist_c_( vec );

   cVarBytes bytes = var_bytes_c( vec->numOfBytes, vec->bytes );
   set_bytes_bits_c( bytes, range, bit );
   mask_top_byte( vec );
}

/*******************************************************************************

*******************************************************************************/

#define BITOP_FUNC_( Name, Func )                                              \
CBitVec* Name( CBitVec const* a, CBitVec const* b )                            \
{                                                                              \
   must_exist_c_( a );                                                         \
   must_exist_c_( b );                                                         \
                                                                               \
   if ( a->numOfBits != b->numOfBits )                                         \
   {                                                                           \
      return NULL;                                                             \
   }                                                                           \
                                                                               \
   CBitVec* res = new_bit_vec_c( a->numOfBits );                               \
   if ( res == NULL )                                                          \
   {                                                                           \
      return NULL;                                                             \
   }                                                                           \
                                                                               \
   Func( as_bytes( a ), as_bytes( b ), as_var_bytes( res ) );                  \
                                                                               \
   return res;                                                                 \
}

#define BITOP_ON_FUNC_( Name, Func )                                           \
bool Name( CBitVec* a, CBitVec const* b )                                      \
{                                                                              \
   must_exist_c_( a );                                                         \
   must_exist_c_( b );                                                         \
                                                                               \
   if ( a->numOfBits != b->numOfBits )                                         \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
                                                                               \
   return Func( as_bytes( a ), as_bytes( b ), as_var_bytes( a ) );             \
}

/******************************************************************************/

BITOP_FUNC_( bitand_bit_vec_c, bitand_bytes_c )
BITOP_ON_FUNC_( bitand_on_bit_vec_c, bitand_bytes_c )

BITOP_FUNC_( bitor_bit_vec_c, bitor_bytes_c )
BITOP_ON_FUNC_( bitor_on_bit_vec_c, bitor_bytes_c )

CBitVec* compl_bit_vec_c( CBitVec const* vec )
{
   must_exist_c_( vec );

   CBitVec* res = new_bit_vec_c( vec->numOfBits );
   if ( res == NULL )
   {
      return NULL;
   }

   compl_bytes_c( as_bytes( vec ), as_var_bytes( res ) );
   mask_top_byte( res );

   return res;
}

bool compl_on_bit_vec_c( CBitVec* vec )
{
   must_exist_c_( vec );

   bool res = compl_bytes_c( as_bytes( vec ), as_var_bytes( vec ) );
   mask_top_byte( vec );
   return res;
}

BITOP_FUNC_( xor_bit_vec_c, xor_bytes_c )
BITOP_ON_FUNC_( xor_on_bit_vec_c, xor_bytes_c )

/*******************************************************************************

*******************************************************************************/

void shift_bit_vec_c( CBitVec* vec, int64_t offset, cByte fillValue )
{
   must_exist_c_( vec );
   must_be_c_( offset != INT64_MIN );

   shift_bytes_c( as_var_bytes( vec ), offset, fillValue );
   if ( offset < 0 and unused_bits( vec ) > 0 )
   {
      abs_c_( offset, &offset );
      cRange range = sized_range_c_( vec->numOfBits - offset, offset );
      set_range_on_bit_vec_c( vec, range, fillValue );
   }
   mask_top_byte( vec );
}

/*******************************************************************************

*******************************************************************************/

bool bit_vec_is_c( CBitVec* vec, cChars chars )
{
   must_exist_c_( vec );

   int64_t vecSize = bit_vec_size_c( vec );

   int64_t i = 0;
   for_each_c_( char const*, c, chars )
   {
      if( *c == 'o' or *c == '0' or *c == '1' )
      {
         if ( i >= vecSize ) return false;

         cByte strBit = char_as_bit( *c );
         cByte vecBit = get_from_bit_vec_c( vec, i );
         if ( vecBit != strBit ) return false;

         ++i;
      }
      else if ( not isspace( *c ) )
      {
         return false;
      }
   }

   return ( i == vecSize );
}

int cmp_bit_vec_c( CBitVec const* a, CBitVec const* b )
{
   must_exist_c_( a );
   must_exist_c_( b );

   return cmp_bytes_c( as_bytes( a ), as_bytes( b ) );
}

extern inline bool eq_bit_vec_c( CBitVec const* a, CBitVec const* b );

/*******************************************************************************
 io
*******************************************************************************/

static inline bool write_zip_value( cRecorder rec[static 1],
                                    cByte val,
                                    int64_t n )
{
   if ( n == 1 )
   {
      char c = val ? '+'
                   : '_';
      return record_char_c( rec, c );
   }
   else
   {
      char c = val ? 'i'
                   : 'z';
      return write_int64_c_( rec, n ) and record_char_c( rec, c );
   }
}

bool write_bit_vec_c( cRecorder rec[static 1],
                      CBitVec const* vec,
                      char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( vec );
   must_exist_c_( fmt );

   if ( vec->numOfBits == 0 )
   {
      return record_chars_c_( rec, "'empty'" ) 
                ? true
                : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
   }

   cChars const fmtCs = c_c( fmt );
   cRecordMarker* marker = &record_marker_c_( rec );
   // ---------------------------------------------------------------------- zip
   if ( chars_is_c( fmtCs, "zip" ) )
   {
      once_c_( xyz )
      {
         cByte prevVal = get_from_bit_vec_c( vec, 0 );
         int64_t counter = 1;
         for ( int64_t i = 1; i < vec->numOfBits; ++i )
         {
            cByte currVal = get_from_bit_vec_c( vec, i );

            if ( currVal == prevVal )
            {
               ++counter;
            }
            else
            {
               if ( not write_zip_value( rec, prevVal, counter ) ) break;

               prevVal = currVal;
               counter = 1;
            }
         }
         if ( not write_zip_value( rec, prevVal, counter ) ) break;

         return true;
      }

      undo_record_c( marker );
      return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
   }

   // ---------------------------------------------------------------------- dbg
   if ( chars_is_c( fmtCs, "dbg" ) )
   {
      if ( write_c_( rec, "{{ .numOfBits={i64}", vec->numOfBits,
                          ", .numOfBytes={i64}", vec->numOfBytes,
                          ", .bitMask={b:b}", vec->bitMask,
                          " }" ) )
      {
         return true;
      }
      else
      {
         undo_record_c( marker );
         return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
      }
   }

   // ------------------------------------------------------------------- format
   cScanner* sca = &make_scanner_c_( fmtCs.s, fmtCs.v );

   cChars charSet = c_c( "o1" ); // ----------------------------------- charSet
   move_to_char_c( sca, '/' );
   {
      cChars sub = scanned_chars_c_( sca );
      if ( sub.s == 0 )
      {
         // same as default
      }
      else if ( sub.s == 2 )
      {
         charSet = sub;
      }
      else
      {
         return set_recorder_error_c( rec, c_InvalidWriteFormat );
      }
   }

   int64_t lineLen = 80; // -------------------------------------------- lineLen
   bool tailCount = false;
   if ( move_if_char_c( sca, '/' ) )
   {
      uint16_t tmp = 80;
      if ( read_uint16_c_( sca, &tmp ) != 0 )
      {
         lineLen = int64_c_( tmp );
      }

      tailCount = move_if_char_c( sca, 'c' );
   }

   int64_t chunkLen = 10; // --------------------------------------------- chunk
   if ( move_if_char_c( sca, '/' ) )
   {
      uint8_t tmp = 10;
      if ( not read_uint8_c_( sca, &tmp ) )
      {
         return set_recorder_error_c( rec, c_InvalidWriteFormat );
      }
      chunkLen = int64_c_( tmp );
   }

   if ( sca->space > 0 ) // ------------------------------------------- fullScan
   {
      return set_recorder_error_c( rec, c_InvalidWriteFormat );
   }

   // -------------------------------------------------------------------- write
   int64_t chunkCount = 0;
   int64_t lineCount = 0;
   bool res = true;
   for ( int64_t i = 0; i < vec->numOfBits; ++i )
   {
      bool const lastBit = i == vec->numOfBits-1;

      char c = get_from_bit_vec_c( vec, i ) ? charSet.v[1]
                                            : charSet.v[0];
      res &= record_char_c( rec, c );

      ++chunkCount;
      ++lineCount;
      
      if ( lastBit )
      {
         if ( tailCount )
         {
            res &= record_chars_c_( rec, " | " );
            res &= write_int64_c_( rec, vec->numOfBits );
         }
      }
      else
      {
         if ( lineCount == lineLen )
         {
            if ( tailCount )
            {
               res &= record_chars_c_( rec, " | " );
               res &= write_int64_c_( rec, i+1 );
            }

            res &= record_char_c( rec, '\n' );

            chunkCount = 0;
            lineCount = 0;
         }
         else if ( chunkCount == chunkLen )
         {
            res &= record_char_c( rec, ' ' );
            chunkCount = 0;
         }
      }

      if ( not res )
      {
         undo_record_c( marker );
         return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
      }
   }

   return res;
}

