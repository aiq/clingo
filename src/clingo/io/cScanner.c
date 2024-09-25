#include "clingo/io/cScanner.h"

#include "clingo/io/write.h"
#include "clingo/lang/func.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************

*******************************************************************************/

static bool note_scanner_error( cRecorder rec[static 1], cError const* err )
{
   cScannerError const* data = get_error_data_c( err );
   char const* msg = NULL;
   switch ( data->code )
   {
      #define XMAP_C_( N, I, T ) case N: msg = T;
         cSCANNER_ERROR_CODE_
      #undef XMAP_C_
   }
   if ( msg == NULL )
   {
      return write_c_( rec, "unknown scanner error code: {i64}", data->code );
   }

   return record_chars_c_( rec, msg );
}
cErrorType const C_ScannerError = {
   .desc = stringify_c_( C_ScannerError ),
   .note = &note_scanner_error
};


/*******************************************************************************
 move
*******************************************************************************/

extern inline bool move_scanner_c( cScanner sca[static 1], int64_t offset );
extern inline bool move_scanner_to_c( cScanner sca[static 1], int64_t pos );

extern inline void reset_scanner_c( cScanner sca[static 1] );

/*******************************************************************************
 move if
*******************************************************************************/

bool move_if_byte_c( cScanner sca[static 1], cByte b )
{
   must_exist_c_( sca );

   cByte const* ptr = sca->mem;
   if ( sca->space > 0 and *ptr == b )
   {
      move_scanner_c( sca, 1 );
      return true;
   }

   return false;
}

bool move_if_byte_match_c( cScanner sca[static 1], c_check_byte check )
{
   must_exist_c_( sca );

   cByte const* ptr = sca->mem;
   if ( sca->space > 0 and check( *ptr ) )
   {
      move_scanner_c( sca, 1 );
      return true;
   }

   return false;
}

bool move_if_bytes_c( cScanner sca[static 1], cBytes slice )
{
   must_exist_c_( sca );

   cBytes unscanned = unscanned_bytes_c_( sca );
   if ( bytes_starts_with_c( unscanned, slice ) )
   {
      return move_scanner_c( sca, slice.s );
   }

   return false;
}

bool move_if_any_char_c( cScanner sca[static 1], cChars set )
{
   must_exist_c_( sca );

   char const* ptr = sca->mem;
   if ( sca->space > 0 and find_char_c( set, *ptr ) )
   {
      move_scanner_c( sca, 1 );
      return true;
   }

   return false;
}

bool move_if_char_c( cScanner sca[static 1], char c )
{
   must_exist_c_( sca );

   char const* ptr = sca->mem;
   if ( sca->space > 0 and *ptr == c )
   {
      move_scanner_c( sca, 1 );
      return true;
   }

   return false;
}

bool move_if_char_match_c( cScanner sca[static 1], c_check_char check )
{
   must_exist_c_( sca );

   char const* ptr = sca->mem;
   if ( sca->space > 0 and check( *ptr ) )
   {
      move_scanner_c( sca, 1 );
      return true;
   }

   return false;
}

bool move_if_any_chars_c( cScanner sca[static 1], cCharsSlice slice )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   each_c_( cChars const*, any, slice )
   {
      if ( chars_starts_with_c( unscanned, *any ) )
      {
         return move_scanner_c( sca, any->s );
      }
   }

   return false;
}

bool move_if_chars_c( cScanner sca[static 1], cChars chars )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   if ( chars_starts_with_c( unscanned, chars ) )
   {
      return move_scanner_c( sca, chars.s );
   }

   return false;
}

bool move_if_any_rune_c( cScanner sca[static 1], cChars set )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   cRune tmp = make_rune_c( unscanned );
   if ( rune_is_valid_c( tmp ) and find_rune_c( set, tmp ) )
   {
      move_scanner_c( sca, rune_size_c( tmp ) );
      return true;
   }

   return false;
}

bool move_if_rune_c( cScanner sca[static 1], cRune r )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   cRune tmp = make_rune_c( unscanned );
   if ( rune_is_valid_c( tmp ) and eq_rune_c( tmp, r ) )
   {
      move_scanner_c( sca, rune_size_c( tmp ) );
      return true;
   }

   return false;
}

bool move_if_rune_match_c( cScanner sca[static 1], c_check_rune check )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   cRune tmp = make_rune_c( unscanned );
   if ( rune_is_valid_c( tmp ) and check( tmp ) )
   {
      move_scanner_c( sca, rune_size_c( tmp ) );
      return true;
   }

   return false;
}

bool move_if_in_range_c( cScanner sca[static 1], cRuneRange range )
{
   must_exist_c_( sca );
   if ( not rune_range_is_valid_c( range ) ) return false;

   cChars unscanned = unscanned_chars_c_( sca );
   cRune tmp = make_rune_c( unscanned );
   if ( rune_is_valid_c( tmp ) and in_rune_range_c( range, tmp ) )
   {
      move_scanner_c( sca, rune_size_c( tmp ) );
      return true;
   }

   return false;
}

/*******************************************************************************
 move to
*******************************************************************************/

bool move_to_byte_c( cScanner sca[static 1], cByte b )
{
   must_exist_c_( sca );

   cBytes unscanned = unscanned_bytes_c_( sca );
   cByte const* ptr = find_byte_c( unscanned, b );
   if ( ptr == NULL )
   {
      return false;
   }

   int64_t offset = index_of_c_( unscanned, ptr );
   return move_scanner_c( sca, offset );
}

bool move_to_byte_match_c( cScanner sca[static 1], c_check_byte check )
{
   must_exist_c_( sca );

   cBytes unscanned = unscanned_bytes_c_( sca );
   cByte const* beg = begin_c_( unscanned );
   cByte const* end = end_c_( unscanned );

   int64_t offset = 0;
   for ( cByte const* itr = beg; itr != end; ++itr, ++offset )
   {
      if ( check( *itr ) )
      {
         return move_scanner_c( sca, offset );
      }
   }

   return false;
}

bool move_to_bytes_c( cScanner sca[static 1], cBytes slice )
{
   must_exist_c_( sca );

   cBytes unscanned = unscanned_bytes_c_( sca );
   int64_t offset = index_of_bytes_c( unscanned, slice );
   if ( offset == -1 )
   {
      return false;
   }

   return move_scanner_c( sca, offset );
}

bool move_to_any_char_c( cScanner sca[static 1], cChars set )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   char const* ptr = find_any_char_c( unscanned, set );
   if ( ptr == NULL )
   {
      return false;
   }

   int64_t offset = index_of_c_( unscanned, ptr );
   return move_scanner_c( sca, offset );
}

bool move_to_char_c( cScanner sca[static 1], char c)
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   char const* ptr = find_char_c( unscanned, c );
   if ( ptr == NULL )
   {
      return false;
   }

   int64_t offset = index_of_c_( unscanned, ptr );
   return move_scanner_c( sca, offset );
}

bool move_to_char_match_c( cScanner sca[static 1], c_check_char check )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   char const* beg = begin_c_( unscanned );
   char const* end = end_c_( unscanned );

   int64_t offset = 0;
   for ( char const* itr = beg; itr != end; ++itr, ++offset )
   {
      if ( check( *itr ) )
      {
         return move_scanner_c( sca, offset );
      }
   }

   return false;
}

bool move_to_any_chars_c( cScanner sca[static 1], cCharsSlice slice )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   int64_t offset = index_of_any_chars_c( unscanned, slice );
   if ( offset == -1 )
   {
      return false;
   }

   return move_scanner_c( sca, offset );
}

bool move_to_chars_c( cScanner sca[static 1], cChars chars )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   int64_t offset = index_of_chars_c( unscanned, chars );
   if ( offset == -1 )
   {
      return false;
   }

   return move_scanner_c( sca, offset );
}

bool move_to_any_rune_c( cScanner sca[static 1], cChars set )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   char const* ptr = find_any_rune_c( unscanned, set );
   if ( ptr == NULL )
   {
      return false;
   }

   int64_t offset = index_of_c_( unscanned, ptr );
   return move_scanner_c( sca, offset );
   return false;
}

bool move_to_rune_c( cScanner sca[static 1], cRune r )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   char const* ptr = find_rune_c( unscanned, r );
   if ( ptr == NULL )
   {
      return false;
   }

   int64_t offset = index_of_c_( unscanned, ptr );
   return move_scanner_c( sca, offset );
}

bool move_to_rune_match_c( cScanner sca[static 1], c_check_rune check )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   cRune r;
   iterate_runes_c_( itr, &r, unscanned )
   {
      if ( check( r ) )
      {
         int64_t offset = index_of_c_( unscanned, itr );
         return move_scanner_c( sca, offset );
      }
   }

   return false;
}

bool move_to_in_range_c( cScanner sca[static 1], cRuneRange range )
{
   must_exist_c_( sca );

   int64_t offset = 0;
   {
      cChars unscanned = unscanned_chars_c_( sca );
      cRune r;
      iterate_runes_c_( itr, &r, unscanned )
      {
         offset = index_of_c_( unscanned, itr );
         if ( in_rune_range_c( range, r ) )
         {
            break;
         }
         offset += rune_size_c( r );
      }
   }

   return move_scanner_c( sca, offset );
}

/*******************************************************************************
 move while
*******************************************************************************/

bool move_while_byte_c( cScanner sca[static 1], cByte b )
{
   must_exist_c_( sca );

   cBytes unscanned = unscanned_bytes_c_( sca );
   cByte const* itr = begin_c_( unscanned );
   cByte const* end = end_c_( unscanned );

   int64_t offset = 0;
   while ( itr < end and *itr == b )
   {
      ++offset;
      ++itr;
   }

   return ( offset > 0 ) ? move_scanner_c( sca, offset )
                         : false;
}

bool move_while_byte_match_c( cScanner sca[static 1], c_check_byte check )
{
   must_exist_c_( sca );

   cBytes unscanned = unscanned_bytes_c_( sca );
   cByte const* itr = begin_c_( unscanned );
   cByte const* end = end_c_( unscanned );

   int64_t offset = 0;
   while ( itr < end and check( *itr ) )
   {
      ++offset;
      ++itr;
   }

   return ( offset > 0 ) ? move_scanner_c( sca, offset )
                         : false;
}

bool move_while_any_char_c( cScanner sca[static 1], cChars set )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   char const* itr = begin_c_( unscanned );
   char const* end = end_c_( unscanned );

   int64_t offset = 0;
   while ( itr < end and find_char_c( set, *itr ) )
   {
      ++offset;
      ++itr;
   }

   return ( offset > 0 ) ? move_scanner_c( sca, offset )
                         : false;
}

bool move_while_char_c( cScanner sca[static 1], char c )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   char const* itr = begin_c_( unscanned );
   char const* end = end_c_( unscanned );

   int64_t offset = 0;
   while ( itr < end and *itr == c )
   {
      ++offset;
      ++itr;
   }

   return ( offset > 0 ) ? move_scanner_c( sca, offset )
                         : false;
}

bool move_while_char_match_c( cScanner sca[static 1], c_check_char check )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   char const* itr = begin_c_( unscanned );
   char const* end = end_c_( unscanned );

   int64_t offset = 0;
   while ( itr < end and check( *itr ) )
   {
      ++offset;
      ++itr;
   }

   return ( offset > 0 ) ? move_scanner_c( sca, offset )
                         : false;
}

bool move_while_any_rune_c( cScanner sca[static 1], cChars set )
{
   must_exist_c_( sca );

   int64_t offset = 0;
   {
      cChars unscanned = unscanned_chars_c_( sca );
      cRune r;
      iterate_runes_c_( itr, &r, unscanned )
      {
         offset = index_of_c_( unscanned, itr );
         if ( not find_rune_c( set, r ) )
         {
            break;
         }
         offset += rune_size_c( r );
      }
   }

   return ( offset > 0 ) ? move_scanner_c( sca, offset )
                         : false;
}

bool move_while_rune_c( cScanner sca[static 1], cRune r )
{
   must_exist_c_( sca );

   int64_t offset = 0;
   {
      cChars unscanned = unscanned_chars_c_( sca );
      cRune tmp;
      iterate_runes_c_( itr, &tmp, unscanned )
      {
         offset = index_of_c_( unscanned, itr );
         if ( not eq_rune_c( r, tmp ) )
         {
            break;
         }
         offset += rune_size_c( tmp );
      }
   }

   return ( offset > 0 ) ? move_scanner_c( sca, offset )
                         : false;
}

bool move_while_rune_match_c( cScanner sca[static 1], c_check_rune check )
{
   must_exist_c_( sca );

   int64_t offset = 0;
   {
      cChars unscanned = unscanned_chars_c_( sca );
      cRune r;
      iterate_runes_c_( itr, &r, unscanned )
      {
         offset = index_of_c_( unscanned, itr );
         if ( not check( r ) )
         {
            break;
         }
         offset += rune_size_c( r );
      }
   }
   return ( offset > 0 ) ? move_scanner_c( sca, offset )
                         : false;
}

bool move_while_in_range_c( cScanner sca[static 1], cRuneRange range )
{
   must_exist_c_( sca );

   int64_t offset = 0;
   {
      cChars unscanned = unscanned_chars_c_( sca );
      cRune r;
      iterate_runes_c_( itr, &r, unscanned )
      {
         offset = index_of_c_( unscanned, itr );
         if ( not in_rune_range_c( range, r ) )
         {
            break;
         }
         offset += rune_size_c( r );
      }
   }

   return ( offset > 0 ) ? move_scanner_c( sca, offset )
                         : false;
}

/*******************************************************************************
 error
*******************************************************************************/

extern inline bool set_scanner_error_c( cScanner sca[static 1], int err );

extern inline int clear_scanner_error_c( cScanner sca[static 1] );

/*******************************************************************************
 access
*******************************************************************************/

extern inline cBytes scanned_bytes_c( cScanner const sca[static 1],
                                      int64_t size );
extern inline cChars scanned_chars_c( cScanner const sca[static 1],
                                      int64_t size );
extern inline cBytes unscanned_bytes_c( cScanner const sca[static 1],
                                        int64_t size );
extern inline cChars unscanned_chars_c( cScanner const sca[static 1],
                                        int64_t size );

bool unscanned_is_c( cScanner const sca[static 1], char const cstr[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( cstr );

   return chars_is_c( unscanned_chars_c_( sca ), cstr );
}

/*******************************************************************************
 on
*******************************************************************************/

extern inline bool on_byte_c( cScanner sca[static 1], cByte b );
extern inline bool on_bytes_c( cScanner sca[static 1], cBytes slice );
extern inline bool on_any_char_c( cScanner sca[static 1], cChars set );
extern inline bool on_char_c( cScanner sca[static 1], char c );
extern inline bool on_chars_c( cScanner sca[static 1], cChars chars );
extern inline bool on_rune_c( cScanner sca[static 1], cRune r );

/*******************************************************************************
 view
*******************************************************************************/

extern inline cBytes view_bytes_c( cScanner sca[static 1], int64_t size );
extern inline cChars view_chars_c( cScanner sca[static 1], int64_t size );

char const* view_cstr_c( cScanner sca[static 1] )
{
   must_exist_c_( sca );

   if ( sca->space == 0 )
   {
      return NULL;
   }

   cChars chars = unscanned_chars_c_( sca );
   char const* beg = begin_c_( chars );
   char const* end = end_c_( chars );
   for ( char const* itr = beg; itr < end; ++itr )
   {
      if ( *itr == '\0' )
      {
         char const* res = sca->mem;
         int64_t const idx = index_of_c_( chars, itr );
         int64_t const size = idx + 1;
         sca->pos += size;
         sca->space -= size;
         sca->mem += size;
         return res;
      }
   }

   return NULL;
}

cChars view_pad_c( cScanner sca[static 1], char pad )
{
   must_exist_c_( sca );

   if ( sca->space == 0 )
   {
      return (cChars)empty_c_();
   }

   cChars chars = unscanned_chars_c_( sca );
   char const* itr = begin_c_( chars );
   char const* end = end_c_( chars );
   while ( *itr == pad and itr < end )
   {
      ++itr;
   }

   void const* tmp = itr;
   int64_t const offset = tmp - sca->mem;
   move_scanner_c( sca, offset );

   return (cChars){ offset, begin_c_( chars ) };
}

cChars view_runes_c( cScanner sca[static 1], int64_t size )
{
   must_exist_c_( sca );

   cChars unscanned = unscanned_chars_c_( sca );
   cChars res = left_runes_c( unscanned, size );
   if ( count_runes_c( res ) != size )
   {
      return (cChars)empty_c_();
   }

   move_scanner_c( sca, res.s );
   return res;
}

/*******************************************************************************
 scan
*******************************************************************************/

#define SCAN_FUNC_IMPL_( Type, FuncName )                                      \
bool FuncName( cScanner sca[static 1], Type val[static 1] )                    \
{                                                                              \
   must_exist_c_( sca );                                                       \
   must_exist_c_( val );                                                       \
                                                                               \
   int64_t const size = sizeof_c_( Type );                                     \
   if ( size > sca->space )                                                    \
   {                                                                           \
      return set_scanner_error_c( sca, c_IncompleteScanValue );                \
   }                                                                           \
                                                                               \
   Type const* ptr = sca->mem;                                                 \
   *val = *ptr;                                                                \
   sca->pos += size;                                                           \
   sca->space -= size;                                                         \
   sca->mem += size;                                                           \
   return true;                                                                \
}

SCAN_FUNC_IMPL_( cByte,    scan_byte_c )
SCAN_FUNC_IMPL_( char,     scan_char_c )

bool scan_rune_c( cScanner sca[static 1], cRune r[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( r );

   if ( sca->space == 0 )
   {
      return set_scanner_error_c( sca, c_EndOfScanner );
   }

   char const* ptr = sca->mem;

   int64_t len = utf8_length_c( *ptr );
   if ( len > sca->space )
   {
      return set_scanner_error_c( sca, c_IncompleteScanValue );
   }

   *r = rune_c( ptr );
   sca->pos += len;
   sca->space -= len;
   sca->mem += len;
   return true;
}

SCAN_FUNC_IMPL_( int8_t,   scan_int8_c )
SCAN_FUNC_IMPL_( int16_t,  scan_int16_c )
SCAN_FUNC_IMPL_( int32_t,  scan_int32_c )
SCAN_FUNC_IMPL_( int64_t,  scan_int64_c )

SCAN_FUNC_IMPL_( uint8_t,  scan_uint8_c )
SCAN_FUNC_IMPL_( uint16_t, scan_uint16_c )
SCAN_FUNC_IMPL_( uint32_t, scan_uint32_c )
SCAN_FUNC_IMPL_( uint64_t, scan_uint64_c )

SCAN_FUNC_IMPL_( float,    scan_float_c )
SCAN_FUNC_IMPL_( double,   scan_double_c )

SCAN_FUNC_IMPL_( void*,    scan_pointer_c )

/*******************************************************************************
 error
*******************************************************************************/

bool push_scanner_error_c( cErrorStack es[static 1],
                           cScanner const sca[static 1] )
{
   cScannerError e = { .code=sca->err };
   return push_error_c( es, &C_ScannerError, &e, sizeof_c_( cScannerError ) );
}
