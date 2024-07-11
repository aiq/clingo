#include "clingo/io/read_type.h"

#include "_/read_num.h"
#include "_/read_write_util.h"
#include "clingo/io/read.h"
#include "clingo/io/write_type.h"

/*******************************************************************************

*******************************************************************************/

bool read_bool_c( cScanner sca[static 1],
                  bool val[static 1],
                  char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( val );
   must_exist_c_( fmt );

   if ( *fmt == '\0' or cstr_is_char_c( fmt, '*' ) )
   {
      if ( move_if_chars_c_( sca, "true" ) or
           move_if_chars_c_( sca, "TRUE" ) or
           move_if_chars_c_( sca, "True" ) )
      {
         *val = true;
         return true;
      }
      else if ( move_if_chars_c_( sca, "false" ) or
                move_if_chars_c_( sca, "FALSE" ) or
                move_if_chars_c_( sca, "False" ) )
      {
         *val = false;
         return true;
      }
   }
   else
   {
      char const* t = cstr_is_char_c( fmt, 'l' )   ? "true" :
                      cstr_is_char_c( fmt, 'U' )   ? "TRUE" :
                      cstr_is_c( fmt, "Cc" )       ? "True" :
                                                     NULL;
      char const* f = cstr_is_char_c( fmt, 'l' )   ? "false" :
                      cstr_is_char_c( fmt, 'U' )   ? "FALSE" :
                      cstr_is_c( fmt, "Cc" )       ? "False" :
                                                     NULL;
      if ( !t or !f )
      {
         return set_scanner_error_c( sca, c_InvalidReadFormat );
      }

      if ( move_if_chars_c_( sca, t ) )
      {
         *val = true;
         return true;
      }
      else if ( move_if_chars_c_( sca, f ) )
      {
         *val = false;
         return true;
      }
      else
      {
         return set_scanner_error_c( sca, c_InvalidReadFormat );
      }
   }

   return set_scanner_error_c( sca, c_NotAbleToReadValue );
}

bool read_byte_c( cScanner sca[static 1],
                  cByte byte[static 1],
                  char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( byte );
   must_exist_c_( fmt );
   
   return read_uint8_c( sca, byte, "x" );
}

bool read_char_c( cScanner sca[static 1],
                  char c[static 1],
                  char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( c );
   must_exist_c_( fmt );

   return scan_char_c( sca, c );
}

bool read_range_c( cScanner sca[static 1],
                   cRange rng[static 1],
                   char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( rng );
   must_exist_c_( fmt );

   int64_t const oldPos = sca->pos;

   once_c_( xyz )
   {
      bool const openBeg = move_if_char_c( sca, '(' );
      bool const closedBeg = move_if_char_c( sca, '[' );
      if ( openBeg == closedBeg )
      {
         break;
      }

      int64_t min;
      if ( not read_int64_c_( sca, &min ) )
      {
         break;
      }

      if ( not move_if_char_c( sca, ',' ) and
           not move_if_char_c( sca, ';' ) and
           not move_if_chars_c_( sca, ".." ) )
      {
         break;
      }

      int64_t max;
      if ( not read_int64_c_( sca, &max ) )
      {
         break;
      }

      bool const openEnd = move_if_char_c( sca, ')' );
      bool const closedEnd = move_if_char_c( sca, ']' );
      if ( openEnd == closedEnd )
      {
         break;
      }

      *rng = ( openBeg and openEnd )   ? open_range_c_( min, max ) :
             ( openBeg and closedEnd ) ? open_closed_range_c_( min, max ) :
             ( closedBeg and openEnd ) ? closed_open_range_c_( min, max ) :
                                         closed_range_c_( min, max );
      return true;
   }

   move_scanner_to_c( sca, oldPos );
   return set_scanner_error_c( sca, c_NotAbleToReadValue );
}

bool read_rune_c( cScanner sca[static 1],
                  cRune r[static 1],
                  char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( r );
   must_exist_c_( fmt );

   fmt = ( *fmt == '\0' ) ? "s" : fmt;

   int64_t const oldPos = sca->pos;

   once_c_( xdlfjk )
   {
      if ( cstr_is_char_c( fmt, 's' ) )
      {
         if ( not scan_rune_c( sca, r ) ) break;

         return true;
      }
      else if ( cstr_is_char_c( fmt, 'n' ) )
      {
         uint32_t val = 0;
         if ( !move_if_chars_c_( sca, "U+" ) or
              !read_uint32_c( sca, &val, "X" ) )
         {
            break;
         }
         *r = utf32_rune_c( val );
         return true;
      }

      cChars fmtCs = c_c( fmt );
      if ( chars_is_c( fmtCs, "u8" ) )
      {
         cByte a = 0;
         cByte b = 0;
         cByte c = 0;
         cByte d = 0;
         if ( not read_byte_c_( sca, &a ) ) break;

         int8_t len = utf8_length_c( char_c_( a ) );
         if ( len == 0 ) break;

         if ( len > 1 and not read_byte_c_( sca, &b ) ) break;
         if ( len > 2 and not read_byte_c_( sca, &c ) ) break;
         if ( len > 3 and not read_byte_c_( sca, &d ) ) break;

         *r = build_rune_c_( a, b, c, d );
         return true;
      }
      else if ( chars_is_c( fmtCs, "html" ) )
      {
         uint32_t val = 0;
         if ( !move_if_chars_c_( sca, "&#" ) or
              !read_uint32_c_( sca, &val ) or
              !move_if_char_c( sca, ';' ) )
         {
            break;
         }
         *r = utf32_rune_c( val );
         return true;
      }
      else if ( chars_is_c( fmtCs, "htmlx" ) )
      {
         uint32_t val = 0;
         if ( !move_if_chars_c_( sca, "&#x" ) or
              !read_uint32_c( sca, &val, "X" ) or
              !move_if_char_c( sca, ';' ) )
         {
            break;
         }
         *r = utf32_rune_c( val );
         return true;
      }

      return set_scanner_error_c( sca, c_InvalidReadFormat );
   }

   move_scanner_to_c( sca, oldPos );
   return set_scanner_error_c( sca, c_NotAbleToReadValue );
}

/*******************************************************************************

*******************************************************************************/

bool read_double_c( cScanner sca[static 1],
                    double d[static 1],
                    char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( d );
   must_exist_c_( fmt );

   cChars src = unscanned_chars_c_( sca );
   if ( is_empty_c_( src ) )
   {
      return false;
   }

   int64_t res = 0;
   if ( *fmt == '\0' )
   {
      res = parse_dec_double_c( d, src );
   }

   move_scanner_c( sca, res );
   return res;
}

bool read_float_c( cScanner sca[static 1],
                   float f[static 1],
                   char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( f );
   must_exist_c_( fmt );

   cChars src = unscanned_chars_c_( sca );
   if ( is_empty_c_( src ) )
   {
      return 0;
   }

   double tmp = 0.0;
   int64_t res = 0;
   if ( *fmt == '\0' )
   {
      res = parse_dec_double_c( &tmp, src );
   }

   *f = float_c_( tmp );
   move_scanner_c( sca, res );
   return res;
}

/*******************************************************************************

*******************************************************************************/

bool read_int16_c( cScanner sca[static 1],
                   int16_t i16[static 1],
                   char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( i16 );
   must_exist_c_( fmt );

   cChars src = unscanned_chars_c_( sca );
   if ( is_empty_c_( src ) ) return set_scanner_error_c( sca, c_NotAbleToReadValue );

   int64_t tmp = 0;
   int64_t res = parse_int64_c( &tmp, fmt, src, INT16_MAX, INT16_MIN );
   *i16 = int16_c_( tmp );

   return ( res < 0 )  ? set_scanner_error_c( sca, c_InvalidReadFormat ) :
          ( res == 0 ) ? set_scanner_error_c( sca, c_NotAbleToReadValue ) :
                         move_scanner_c( sca, res );
}

bool read_int32_c( cScanner sca[static 1],
                   int32_t i32[static 1],
                   char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( i32 );
   must_exist_c_( fmt );

   cChars src = unscanned_chars_c_( sca );
   if ( is_empty_c_( src ) ) return set_scanner_error_c( sca, c_NotAbleToReadValue );

   int64_t tmp = 0;
   int64_t res = parse_int64_c( &tmp, fmt, src, INT32_MAX, INT32_MIN );
   *i32 = int32_c_( tmp );

   return ( res < 0 )  ? set_scanner_error_c( sca, c_InvalidReadFormat ) :
          ( res == 0 ) ? set_scanner_error_c( sca, c_NotAbleToReadValue ) :
                         move_scanner_c( sca, res );
}

bool read_int64_c( cScanner sca[static 1],
                   int64_t i64[static 1],
                   char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( i64 );
   must_exist_c_( fmt );

   cChars src = unscanned_chars_c_( sca );
   if ( is_empty_c_( src ) ) return set_scanner_error_c( sca, c_NotAbleToReadValue );

   int64_t res = parse_int64_c( i64, fmt, src, INT64_MAX, INT64_MIN );

   return ( res < 0 )  ? set_scanner_error_c( sca, c_InvalidReadFormat ) :
          ( res == 0 ) ? set_scanner_error_c( sca, c_NotAbleToReadValue ) :
                         move_scanner_c( sca, res );
}

bool read_int8_c( cScanner sca[static 1],
                  int8_t i8[static 1],
                  char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( i8 );
   must_exist_c_( fmt );

   cChars src = unscanned_chars_c_( sca );
   if ( is_empty_c_( src ) ) return set_scanner_error_c( sca, c_NotAbleToReadValue );

   int64_t tmp = 0;
   int64_t res = parse_int64_c( &tmp, fmt, src, INT8_MAX, INT8_MIN );
   *i8 = int8_c_( tmp );

   return ( res < 0 )  ? set_scanner_error_c( sca, c_InvalidReadFormat ) :
          ( res == 0 ) ? set_scanner_error_c( sca, c_NotAbleToReadValue ) :
                         move_scanner_c( sca, res );
}

/*******************************************************************************

*******************************************************************************/

bool read_uint16_c( cScanner sca[static 1],
                    uint16_t u16[static 1],
                    char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( u16 );
   must_exist_c_( fmt );

   cChars src = unscanned_chars_c_( sca );
   if ( is_empty_c_( src ) ) return set_scanner_error_c( sca, c_NotAbleToReadValue );

   uint64_t tmp = 0;
   int64_t res = parse_uint64_c( &tmp, fmt, src, UINT16_MAX );
   *u16 = uint16_c_( tmp );

   return ( res < 0 )  ? set_scanner_error_c( sca, c_InvalidReadFormat ) :
          ( res == 0 ) ? set_scanner_error_c( sca, c_NotAbleToReadValue ) :
                         move_scanner_c( sca, res );
}

bool read_uint32_c( cScanner sca[static 1],
                    uint32_t u32[static 1],
                    char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( u32 );
   must_exist_c_( fmt );

   cChars src = unscanned_chars_c_( sca );
   if ( is_empty_c_( src ) ) return set_scanner_error_c( sca, c_NotAbleToReadValue );

   uint64_t tmp = 0;
   int64_t res = parse_uint64_c( &tmp, fmt, src, UINT32_MAX );
   *u32 = uint32_c_( tmp );

   return ( res < 0 )  ? set_scanner_error_c( sca, c_InvalidReadFormat ) :
          ( res == 0 ) ? set_scanner_error_c( sca, c_NotAbleToReadValue ) :
                         move_scanner_c( sca, res );
}

bool read_uint64_c( cScanner sca[static 1],
                    uint64_t u64[static 1],
                    char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( u64 );
   must_exist_c_( fmt );

   cChars src = unscanned_chars_c_( sca );
   if ( is_empty_c_( src ) ) return set_scanner_error_c( sca, c_NotAbleToReadValue );

   uint64_t tmp = 0;
   int64_t res = parse_uint64_c( &tmp, fmt, src, UINT64_MAX );
   *u64 = tmp;

   return ( res < 0 )  ? set_scanner_error_c( sca, c_InvalidReadFormat ) :
          ( res == 0 ) ? set_scanner_error_c( sca, c_NotAbleToReadValue ) :
                         move_scanner_c( sca, res );
}

bool read_uint8_c( cScanner sca[static 1],
                   uint8_t u8[static 1],
                   char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( u8 );
   must_exist_c_( fmt );

   cChars src = unscanned_chars_c_( sca );
   if ( is_empty_c_( src ) ) return set_scanner_error_c( sca, c_NotAbleToReadValue );

   uint64_t tmp = 0;
   int64_t res = parse_uint64_c( &tmp, fmt, src, UINT8_MAX );
   *u8 = uint8_c_( tmp );

   return ( res < 0 )  ? set_scanner_error_c( sca, c_InvalidReadFormat ) :
          ( res == 0 ) ? set_scanner_error_c( sca, c_NotAbleToReadValue ) :
                         move_scanner_c( sca, res );
}

/*******************************************************************************

*******************************************************************************/

bool read_chars_c( cScanner sca[static 1],
                   cChars chars[static 1],
                   char const fmt[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( chars );
   must_exist_c_( fmt );

   char const* beg = sca->mem;
   if ( not read_c_( sca, fmt ) )
   {
      return false;
   }
   *chars = (cChars)atween_c_( beg, (char const*)sca->mem );

   return true;
}