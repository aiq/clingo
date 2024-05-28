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
   return (cBytes){ vec->numOfBytes, vec->bytes };
}

static inline cVarBytes as_var_bytes( CBitVec* vec )
{
   return (cVarBytes){ vec->numOfBytes, vec->bytes };
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

   CBitVec* result = new_object_c_( CBitVec, &C_BitVecMeta );

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
      return release_c( result );
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

bool resize_bit_vec_c( CBitVec* vec, int64_t n )
{
   must_be_positive_c_( n );

   int64_t numOfBytes = req_num_of_bytes( n );
   cByte* bytes = realloc_array_c_( vec->bytes, numOfBytes, cByte );
   if ( bytes == NULL ) return false;

   vec->numOfBits = n;
   vec->numOfBytes = numOfBytes;
   vec->bytes = bytes;
   vec->bitMask = bit_mask( bytes_offset( vec->numOfBits ) );

   return true;
}

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

bool set_on_bit_vec_c( CBitVec* vec, int64_t pos, cByte bit )
{
   must_exist_c_( vec );
   must_be_positive_c_( pos );

   if ( pos >= vec->numOfBits )
   {
      if ( byte_as_bit_c( bit ) == 0 ) return true;

      if ( not resize_bit_vec_c( vec, pos+1 ) ) return false;
   }

   cVarBytes bytes = { vec->numOfBytes, vec->bytes };
   set_bytes_bit_c( bytes, pos, bit );
   return true;
}

bool set_range_on_bit_vec_c( CBitVec* vec, cRange range, cByte bit )
{
   must_exist_c_( vec );

   if ( range.max >= vec->numOfBits )
   {
      if ( byte_as_bit_c( bit ) == 0 )
      {
         if ( range.min >= vec->numOfBits ) return true;

         range.max = vec->numOfBits-1;
      }
      else // bit == 1
      {
         if ( not resize_bit_vec_c( vec, range.max+1 ) ) return false;
      }
   }

   cVarBytes bytes = { vec->numOfBytes, vec->bytes };
   set_bytes_bits_c( bytes, range, bit );
   mask_top_byte( vec );
   return true;
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

   shift_bytes_bits_c( as_var_bytes( vec ), offset, fillValue );
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

static inline cRange find_set_range( CBitVec const* vec, int64_t from )
{
   must_exist_c_( vec );

   int64_t beg = find_index_of_bit_c( vec, 1, from );
   if ( beg == -1 ) return (cRange){ 0, -1 };

   int64_t end = find_index_of_bit_c( vec, 0, beg );
   if ( end == -1 ) end = bit_vec_size_c( vec );

   return closed_open_range_c_( beg, end );
}

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
   int64_t const oldPos = rec->pos;
   // --------------------------------------------------------------------- list
   if ( chars_is_c( fmtCs, "list" ) )
   {
      once_c_( xyz )
      {
         cRange rng = find_set_range( vec, 0 );
         bool withSep = false;
         while ( range_is_valid_c( rng ) )
         {
            if ( withSep )
            {
               if ( not record_char_c( rec, ',' ) ) break;
            }
            if ( not write_int64_c_( rec, rng.min ) ) break;

            if ( rng.min != rng.max )
            {
               if ( not record_char_c( rec, '-' ) ) break;
            if ( not write_int64_c_( rec, rng.max ) ) break;
            }

            rng = find_set_range( vec, rng.max+1 );
            withSep = true;
         }

         return true;
      }

      move_recorder_to_c( rec, oldPos );
      return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
   }

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

      move_recorder_to_c( rec, oldPos );
      return false;
   }

   // ---------------------------------------------------------------------- dbg
   if ( chars_is_c( fmtCs, "dbg" ) )
   {
      return write_c_( rec, "{{ .numOfBits={i64}", vec->numOfBits,
                            ", .numOfBytes={i64}", vec->numOfBytes,
                            ", .bitMask={b:b}", vec->bitMask,
                            " }" );
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
         move_recorder_to_c( rec, oldPos );
         return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
      }
   }

   return res;
}

/******************************************************************************/

static inline int64_t count_bit_str( cScanner sca[static 1],
                                      int64_t size[static 1] )
{
   int64_t oldPos = sca->pos;
   int64_t endPos = sca->pos;
   int64_t num = 0;
   while ( true )
   {
      if ( move_if_any_char_c_( sca, "0o1") )
      {
         endPos = sca->pos;
         ++num;
      }
      else if ( move_if_char_match_c( sca, char_is_space_c ) )
      {
         // nothing to do
      }
      else
      {
         break;
      }
   }
   int64_t len = endPos - oldPos;
   *size = num;
   move_scanner_to_c( sca, oldPos );
   return len;
}

static inline void read_bit_str( cScanner sca[static 1], CBitVec* vec )
{
   int64_t i = 0;
   while ( sca->space > 0 )
   {
      char c;
      scan_char_c( sca, &c );
      if ( is_bit_char( c ) )
      {
         if( c == '1' ) // BitVec is 0s by default -- just set the 1s
         {
            set_on_bit_vec_c( vec, i, char_as_bit( c ) );
         }
         ++i;
      }
   }
}

/******************************************************************************/

static inline int64_t count_list_size( cScanner sca[static 1],
                                       int64_t size[static 1] )
{
   int64_t oldPos = sca->pos;
   int64_t endPos = sca->pos;
   uint32_t num = 0;
   while ( true )
   {
      move_while_char_match_c( sca, char_is_space_c );
      if ( not read_uint32_c_( sca, &num ) ) break;

      endPos = sca->pos;

      move_while_char_match_c( sca, char_is_space_c );
      if ( move_if_char_c( sca, '-' ) )
      {
         move_while_char_match_c( sca, char_is_space_c );
         if ( not read_uint32_c_( sca, &num ) ) break;

         endPos = sca->pos;
      }

      move_while_char_match_c( sca, char_is_space_c );
      if ( not move_if_char_c( sca, ',') ) break;
   }
   int64_t len = endPos - oldPos;
   *size = num;
   move_scanner_to_c( sca, oldPos );
   return len;
}

static inline void read_list( cScanner sca[static 1], CBitVec* vec )
{
   while ( sca->space > 0 )
   {
      uint32_t min = 0;
      move_while_char_match_c( sca, char_is_space_c );
      if ( !read_uint32_c_( sca, &min ) ) must_be_c_( false );

      move_while_char_match_c( sca, char_is_space_c );
      if ( move_if_char_c( sca, '-' ) )
      {
         move_while_char_match_c( sca, char_is_space_c );
         uint32_t max = 0;
         if ( !read_uint32_c_( sca, &max ) ) must_be_c_( false );

         cRange rng = closed_range_c_( min, max );
         set_range_on_bit_vec_c( vec, rng, 1 );
      }
      else
      {
         set_on_bit_vec_c( vec, min, 1 );
      }

      move_while_char_match_c( sca, char_is_space_c );
      move_if_char_c( sca, ',' );
   }
}

/******************************************************************************/

static inline int64_t count_zip_size( cScanner sca[static 1],
                                      int64_t size[static 1] )
{
   int64_t oldPos = sca->pos;
   int64_t n = 0;
   while ( true )
   {
      if ( move_if_any_char_c_( sca, "_+" ) )
      {
         ++n;
      }
      else if ( on_any_char_c_( sca, "123456789" ) )
      {
         int64_t tmpPos = sca->pos;
         int64_t i;
         read_int64_c_( sca, &i );
         if ( not move_if_any_char_c_( sca, "iz" ) )
         {
            move_scanner_to_c( sca, tmpPos );
            break;
         }
         n += i;
      }
      else
      {
         break;
      }
   }
   int64_t len = sca->pos - oldPos;
   *size = n;
   move_scanner_to_c( sca, oldPos );
   return len;
}

static inline void read_zip( cScanner sca[static 1], CBitVec* vec )
{
   int64_t i = 0;
   while ( sca->space > 0 )
   {
      if ( move_if_char_c( sca, '_' ) )
      {
         // 0 must not set
         ++i;
      }
      else if ( move_if_char_c( sca, '+' ) )
      {
         set_on_bit_vec_c( vec, i, 1 );
         ++i;
      }
      else if ( on_any_char_c_( sca, "123456789" ) )
      {
         int64_t num;
         if ( not read_int64_c_( sca, &num ) )
         {
            must_be_c_( false );
         }
         cRange rng = sized_range_c_( i, num );
         i += num;
         if ( move_if_char_c( sca, 'i' ) )
         {
            set_range_on_bit_vec_c( vec, rng, 1 );
         } else if ( move_if_char_c( sca, 'z' ) )
         {
            // 0 must not set
         }
         else
         {
            must_be_c_( false );
         }
      }
      else
      {
         must_be_c_( false );
      }
   }
}

/******************************************************************************/

bool read_bit_vec_c( cScanner sca[static 1],
                     CBitVec* vec[static 1],
                     char const fmt[static 1] )
{
   cChars const fmtCs = c_c( fmt );
   // --------------------------------------------------------------------------
   if ( chars_is_c( fmtCs, "" ) )
   {
      int64_t size;
      int64_t len = count_bit_str( sca, &size );
      if ( size == 0 ) return set_scanner_error_c( sca, c_NotAbleToReadValue );

      cScanner* subSca = &sub_scanner_c_( sca, len );
      *vec = new_bit_vec_c( size );
      if ( vec == NULL )
         return set_scanner_error_c( sca, c_ReadAllocError );

      read_bit_str( subSca, *vec );
      move_scanner_c( sca, len );
      return true;
   }

   // --------------------------------------------------------------------- list
   if ( chars_is_c( fmtCs, "list" ) )
   {
      int64_t size;
      int64_t len = count_list_size( sca, &size );
      if ( size == 0 ) return set_scanner_error_c( sca, c_NotAbleToReadValue );

      cScanner* subSca = &sub_scanner_c_( sca, len );
      *vec = new_bit_vec_c( size );
      if ( vec == NULL )
         return set_scanner_error_c( sca, c_ReadAllocError );

      read_list( subSca, *vec );
      move_scanner_c( sca, len );
      return true;
   }

   // ---------------------------------------------------------------------- zip
   if ( chars_is_c( fmtCs, "zip" ) )
   {
      int64_t size;
      int64_t len = count_zip_size( sca, &size );
      if ( size == 0 ) return set_scanner_error_c( sca, c_NotAbleToReadValue );

      cScanner* subSca = &sub_scanner_c_( sca, len );
      *vec = new_bit_vec_c( size );
      if ( vec == NULL )
         return set_scanner_error_c( sca, c_ReadAllocError );

      read_zip( subSca, *vec );
      move_scanner_c( sca, len );
      return true;
   }

  return set_scanner_error_c( sca, c_InvalidReadFormat );
}