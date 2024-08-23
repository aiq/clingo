#include "clingo/io/write_type.h"

#include <stdio.h>

#include "_/WRITE_INT.h"
#include "_/WRITE_UINT.h"
#include "_/write_num.h"
#include "clingo/io/read_type.h"
#include "clingo/io/write.h"

/*******************************************************************************

*******************************************************************************/

bool write_bool_c( cRecorder rec[static 1],
                   bool val,
                   char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( fmt );

   char const* txt = "";
   if ( *fmt == '\0' or cstr_is_char_c( fmt, 'l' ) )
   {
      txt = val ? "true"
                : "false";
   }
   else if ( cstr_is_char_c( fmt, 'U' ) )
   {
      txt = val ? "TRUE"
                : "FALSE";
   }
   else if ( chars_is_c( c_c( fmt ), "Cc" ) )
   {
      txt = val ? "True"
                : "False";
   }
   else
   {
      return set_recorder_error_c( rec, c_InvalidWriteFormat );
   }

   return record_chars_c_( rec, txt )
      ? true
      : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

bool write_byte_c( cRecorder rec[static 1],
                   cByte byte,
                   char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( fmt );

   if ( *fmt == '\0' or cstr_is_char_c( fmt, 'x' ) )
   {
      return write_uint8_c( rec, byte, "x(2>0)" );
   }
   else if ( cstr_is_char_c( fmt, 'X' ) )
   {
      return write_uint8_c( rec, byte, "X(2>0)" );
   }
   else if ( cstr_is_char_c( fmt, 'b' ) )
   {
      return write_uint8_c( rec, byte, "b(8>o)" );
   }
   else if ( cstr_is_char_c( fmt, 'B' ) )
   {
      return write_uint8_c( rec, byte, "B(8>0)" );
   }

   return set_recorder_error_c( rec, c_InvalidWriteFormat );
}

bool write_char_c( cRecorder rec[static 1],
                   char c,
                   char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( fmt );

   bool recRes = true;

   if ( *fmt == '\0' or cstr_is_char_c( fmt, 'c' ) )
   {
      recRes = record_char_c( rec, c );
   }
   else if ( cstr_is_char_c( fmt, 'q' ) )
   {
      recRes = record_char_c( rec, '\'' ) and
               record_char_c( rec, c ) and
               record_char_c( rec, '\'' );
   }
   else if ( cstr_is_char_c( fmt, 'Q' ) )
   {
      recRes = record_char_c( rec, '"' ) and
               record_char_c( rec, c ) and
               record_char_c( rec, '"' );
   }
   else
   {
      return set_recorder_error_c( rec, c_InvalidWriteFormat );
   }

   return recRes
      ? true
      : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

bool write_error_c( cRecorder rec[static 1],
                    cError const *err,
                    char const fmt[static 1] )
{
   if ( err == NULL ) return record_chars_c_( rec, "no error" );

   bool res = err->type->note( rec, err );
   err = err->sub;
   while ( res and err != NULL )
   {
      res &= record_chars_c_( rec, ": " );
      res &= err->type->note( rec, err );
      err = err->sub;
   }
   return res;
}

bool write_range_c( cRecorder rec[static 1],
                    cRange rng,
                    char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( fmt );
  
   cScanner* sca = &cstr_scanner_c_( fmt );

   if ( unscanned_is_c( sca, "dbg" ) )
   {
      return write_c_( rec, "{{ .min={i64}, .max={i64} }", rng.min, rng.max );
   }

   char const* fmtStr = "[{i64}{s}{i64}]";
   if ( sca->space != 0 )
   {
      if ( move_if_chars_c_( sca, "co" ) )
      {
         fmtStr = "[{i64}{s}{i64})";
         rng = closed_open_range_c_( rng.min, rng.max );
      }
      else if ( move_if_chars_c_( sca, "oc" ) )
      {
         fmtStr = "({i64}{s}{i64}]";
         rng = open_closed_range_c_( rng.min, rng.max );
      }
      else if ( move_if_char_c( sca, 'c' ) )
      {
         // same as default
      }
      else if ( move_if_char_c( sca, 'o' ) )
      {
         fmtStr = "({i64}{s}{i64})";
         rng = open_range_c_( rng.min, rng.max );
      }
   }

   char const* delimiter = "..";
   if ( move_if_char_c( sca, '/' ) )
   {
      if ( move_if_char_c( sca, ',' ) )
      {
         delimiter = ",";
      }
      else if ( move_if_char_c( sca, ';' ) )
      {
         delimiter = ";";
      }
      else if ( move_if_char_c( sca, '|' ) )
      {
         delimiter = "|";
      }
      else if ( move_if_chars_c_( sca, ".." ) )
      {
         // same as default
      }
      else
      {
         return set_recorder_error_c( rec, c_InvalidWriteFormat );
      }
   }

   if ( sca->space > 0 )
   {
      return set_recorder_error_c( rec, c_InvalidWriteFormat );
   }

   return write_c_( rec, fmtStr, rng.min, delimiter, rng.max );
}

bool write_rune_c( cRecorder rec[static 1],
                   cRune rune,
                   char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( fmt );

   fmt = ( *fmt == '\0' ) ? "s" : fmt;

   int64_t const oldPos = rec->pos;
   once_c_( xaskldj )
   {
      if ( cstr_is_any_char_c_( fmt, "qQs" ) )
      {
         cChars cs = { rune_size_c( rune ), rune.c };
         return write_chars_c( rec, cs, fmt );
      }
      else if ( cstr_is_char_c( fmt, 'n' ) )
      {
         uint32_t const u32 = rune_code_c( rune );
         if ( u32 > 0xFFFF )
         {
            if ( !record_chars_c_( rec, "U+" ) or
                 !write_uint32_c( rec, u32, "X" ) )
               break;
         }
         else
         {
            if ( !record_chars_c_( rec, "U+" ) or
                 !write_uint32_c( rec, u32, "X(4>0)" ) )
               break;
         }
         return true;
      }

      cChars fmtCs = c_c( fmt );
      if ( chars_is_c( fmtCs, "u8" ) )
      {
         int8_t n = rune_size_c( rune );
         for ( int8_t i = 0; i < n; ++i )
         {
            if ( not write_byte_c_( rec, rune.b[i] ) ) break;
         }
         return true;
      }
      else if ( chars_is_c( fmtCs, "html" ) )
      {
         uint32_t const u32 = rune_code_c( rune );
         if ( !record_chars_c_( rec, "&#" ) or
              !write_uint32_c_( rec, u32 ) or
              !record_char_c( rec, ';' ) )
            break;

         return true;
      }
      else if ( chars_is_c( fmtCs, "htmlx" ) )
      {
         uint32_t const u32 = rune_code_c( rune );
         if ( !record_chars_c_( rec, "&#x" ) or
              !write_uint32_c( rec, u32, "X" ) or
              !record_char_c( rec, ';' ) )
            break;

         return true;
      }

      return set_recorder_error_c( rec, c_InvalidWriteFormat );
   }

   move_recorder_to_c( rec, oldPos );
   return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

bool write_tape_c( cRecorder rec[static 1],
                   cTape tape,
                   char const fmt[static 1] )
{
   return tape_c_( rec, tape, fmt );
}

/*******************************************************************************

*******************************************************************************/

bool write_double_c( cRecorder rec[static 1],
                     double d,
                     char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( fmt );

   if ( *fmt == '\0' )
   {
      fmt = "g.17";
   }
   else if ( chars_is_c( c_c( fmt ), "dbg" ) )
   {
      cDoubleInfo i = double_info_c( d );
      int64_t const oldPos = rec->pos;
      bool ok = write_c_( rec, "{{ .sign={u8:x}", i.sign,
                               ", .exponent={u16:x}", i.exponent,
                               ", .mantissa={u64:x} }", i.mantissa );
      if ( not ok )
      {
         move_recorder_to_c( rec, oldPos );
      }
      return ok;
   }

   return write_float_num_c( rec, d, fmt );
}

bool write_float_c( cRecorder rec[static 1],
                    float f,
                    char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( fmt );

   if ( *fmt == '\0' )
   {
      fmt = "g.9";
   }
   else if ( chars_is_c( c_c( fmt ), "dbg" ) )
   {
      cFloatInfo i = float_info_c( f );
      int64_t const oldPos = rec->pos;
      bool ok = write_c_( rec, "{{ .sign={u8:x}", i.sign,
                               ", .exponent={u8:x}", i.exponent,
                               ", .mantissa={u32:x} }", i.mantissa );
      if ( not ok )
      {
         move_recorder_to_c( rec, oldPos );
      }
      return ok;
   }

   return write_float_num_c( rec, f, fmt );
}

/*******************************************************************************

*******************************************************************************/

WRITE_INT_C_(
   int16_t,
   write_int16_c,
   PRIi16,
   uint16_t
)

WRITE_INT_C_(
   int32_t,
   write_int32_c,
   PRIi32,
   uint32_t
)

WRITE_INT_C_(
   int64_t,
   write_int64_c,
   PRIi64,
   uint64_t
)

WRITE_INT_C_(
   int8_t,
   write_int8_c,
   PRIi8,
   uint8_t
)

/*******************************************************************************

*******************************************************************************/

WRITE_UINT_C_(
   uint16_t,
   write_uint16_c,
   PRIu16
)

WRITE_UINT_C_(
   uint32_t,
   write_uint32_c,
   PRIu32
)

WRITE_UINT_C_(
   uint64_t,
   write_uint64_c,
   PRIu64
)

WRITE_UINT_C_(
   uint8_t,
   write_uint8_c,
   PRIu8
)

/*******************************************************************************

*******************************************************************************/

bool write_bytes_c( cRecorder rec[static 1],
                    cBytes slice, 
                    char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( fmt );

   cScanner* sca = &cstr_scanner_c_( fmt );

   char const* fmtStr = "x"; // ----------------------------------------- fmtStr
   if ( move_if_char_c( sca, 'x' ) )
   {
      // same as default
   }
   else if ( move_if_char_c( sca, 'X' ) )
   {
      fmtStr = "X";
   }

   int64_t lineLen = 24; // -------------------------------------------- lineLen
   bool tailCount = false;
   if ( move_if_char_c( sca, '/' ) )
   {
      uint16_t tmp = 24;
      if ( read_uint16_c_( sca, &tmp ) != 0 )
      {
         lineLen = int64_c_( tmp );
      }

      tailCount = move_if_char_c( sca, 'c' );
   }

   int64_t chunkLen = 1; // --------------------------------------------- chunk
   if ( move_if_char_c( sca, '/' ) )
   {
      uint8_t tmp = 1;
      if ( read_uint8_c_( sca, &tmp ) == 0 )
      {
         return set_recorder_error_c( rec, c_InvalidWriteFormat );
      }
      chunkLen = int64_c_( tmp );
   }

   if ( sca->space != 0 )
   {
      return set_recorder_error_c( rec, c_InvalidWriteFormat );
   }

   int64_t const oldPos = rec->pos;
   once_c_( xyz )
   {
      int64_t chunkCount = 0;
      int64_t lineCount = 0;
      for ( int64_t i = 0; i < slice.s; ++i )
      {
         bool const lastByte = i == slice.s-1;

         if ( not write_byte_c( rec, slice.v[i], fmtStr ) ) break;

         ++chunkCount;
         ++lineCount;
     
         if ( lastByte )
         {
            if ( tailCount )
            {
               if ( !record_chars_c_( rec, " | " ) or
                    !write_int64_c_( rec, slice.s ) )
                  break;
            }
         }
         else
         {
            if ( lineCount == lineLen )
            {
               if ( tailCount )
               {
                  if ( !record_chars_c_( rec, " | " ) or
                       !write_int64_c_( rec, i+1 ) )
                     break;
               }

               if ( not record_char_c( rec, '\n' ) ) break;

               chunkCount = 0;
               lineCount = 0;
            }
            else if ( chunkCount == chunkLen )
            {
               if ( not record_char_c( rec, ' ' ) ) break;

               chunkCount = 0;
            }
         }
      }

      return true;
   }

   move_recorder_to_c( rec, oldPos );
   return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

static inline bool record_escaped_char( cRecorder rec[static 1], char c )
{
   switch ( c )
   {
      case '\r': return record_chars_c_( rec, "\\r" ); // Carriage Return
      case '\t': return record_chars_c_( rec, "\\t" ); // Horzontal Tab
      case '\\': return record_chars_c_( rec, "\\\\" ); // Backslash
      case '\n': return record_chars_c_( rec, "\\n" ); // Newline
      case '\"': return record_chars_c_( rec, "\\\"" ); // Double quotation mark
      default: return record_char_c( rec, c );
   }
}

bool write_chars_c( cRecorder rec[static 1],
                    cChars chars,
                    char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( fmt );

   if ( *fmt == '\0' )
   {
      fmt = "s";
   }
   if ( not cstr_is_any_char_c_( fmt, "qQes" ) )
   {
      return set_recorder_error_c( rec, c_InvalidWriteFormat );
   }

   int64_t const oldPos = rec->pos;

   once_c_( xyz )
   {
      if ( cstr_is_char_c( fmt, 'q' ) )
      {
         if ( !record_char_c( rec, '\'' ) or
              !record_chars_c( rec, chars ) or
              !record_char_c( rec, '\'' ) )
            break;
      }
      else if ( cstr_is_char_c( fmt, 'Q' ) )
      {
         if ( !record_char_c( rec, '"' ) or
              !record_chars_c( rec, chars ) or
              !record_char_c( rec, '"' ) )
            break;
      }
      else if ( cstr_is_char_c( fmt, 'e' ) )
      {
         if ( not record_char_c( rec, '"' ) ) break;

         each_c_( char const*, c, chars )
         {
            if ( not record_escaped_char( rec, *c ) ) break;
         }
         if ( not record_char_c( rec, '"' ) ) break;
      }
      else if ( cstr_is_char_c( fmt, 's' ) )
      {
         if ( not record_chars_c( rec, chars ) ) break;
      }

      return true;
   }

   move_recorder_to_c( rec, oldPos );
   return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

bool write_cstr_c( cRecorder rec[static 1],
                   char const cstr[static 1],
                   char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( cstr );
   must_exist_c_( fmt );

   return write_chars_c( rec, c_c( cstr ), fmt );
}

bool write_recorded_c( cRecorder rec[static 1],
                       cRecorder const src[static 1],
                       char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( src );
   must_exist_c_( fmt );

   cScanner* sca = &cstr_scanner_c_( fmt );

   if ( sca->space == 0 or
        move_if_chars_c( sca, c_c( "cs" ) ) )
   {
      move_if_char_c( sca, '/' );
      return write_chars_c( rec, recorded_chars_c( src ), sca->mem );
   }
   else if ( move_if_chars_c( sca, c_c( "bs" ) ) )
   {
      move_if_char_c( sca, '/' );
      return write_bytes_c( rec, recorded_bytes_c( src ), sca->mem );
   }

   return set_recorder_error_c( rec, c_InvalidWriteFormat );
}

bool write_unscanned_c( cRecorder rec[static 1],
                        cScanner const sca[static 1],
                        char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( sca );
   must_exist_c_( fmt );

   cScanner* fmtSca = &cstr_scanner_c_( fmt );

   if ( fmtSca->space == 0 or
        move_if_chars_c( fmtSca, c_c( "cs" ) ) )
   {
      move_if_char_c( fmtSca, '/' );
      return write_chars_c( rec, unscanned_chars_c_( sca ), fmtSca->mem );
   }
   else if ( move_if_chars_c( fmtSca, c_c( "bs" ) ) )
   {
      move_if_char_c( fmtSca, '/' );
      return write_bytes_c( rec, unscanned_bytes_c_( sca ), fmtSca->mem );
   }

   return set_recorder_error_c( rec, c_InvalidWriteFormat );
}