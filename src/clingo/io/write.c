#include "clingo/io/write.h"

#include <ctype.h>
#include <stdio.h>

#include "_/io/read_write_util.h"
#include "clingo/io/jot.h"
#include "clingo/io/write_type.h"

/*******************************************************************************
********************************************************* Types and Definitions
**+*****************************************************************************
 Definitions
*******************************************************************************/

cErrorType const C_WriteError = {
   .desc = stringify_c_( C_WriteError ),
   .note = &note_write_error_c
};

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

static bool write_format_text_c( cRecorder rec[static 1],
                                 cScanner sca[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( sca );

   while ( true )
   {
      char const* oldStr = sca->mem;
      if ( move_to_char_c( sca, '{' ) )
      {
         cChars cs = make_chars_c( oldStr, sca->mem );
         if ( not record_chars_c( rec, cs ) )
         {
            return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
         }

         if ( move_if_chars_c_( sca, "{{" ) )
         {
            if ( not record_char_c( rec, '{' ) )
            {
               return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
            }
         }
         else
         {
            return true;
         }
      }
      else
      {
         cChars cs = chars_c( sca->space, oldStr );
         move_scanner_c( sca, sca->space );
         return record_chars_c( rec, cs )
            ? true
            : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
      }
   }
}

bool write_format_arg_c( cRecorder rec[static 1],
                         va_list* list,
                         cChars type,
                         char const fmt[static 1] )
{
   if ( is_empty_c_( type ) )
   {
      return 0;
   }

   if ( type.v[0] == 'i' )
   {
      if ( chars_is_c( type, "i8" ) )
      {
         int32_t tmp = va_arg( *list, int32_t );
         int8_t i = int8_c_( tmp );
         return write_int8_c( rec, i, fmt );
      }
      else if ( chars_is_c( type, "i16" ) )
      {
         int32_t tmp = va_arg( *list, int32_t );
         int16_t i = int16_c_( tmp );
         return write_int16_c( rec, i, fmt );
      }
      else if ( chars_is_c( type, "i32" ) )
      {
         return write_int32_c( rec, va_arg( *list, int32_t ), fmt );
      }
      else if ( chars_is_c( type, "i64" ) )
      {
         return write_int64_c( rec, va_arg( *list, int64_t ), fmt );
      }
   }
   else if ( type.v[0] == 'u' )
   {
      if ( chars_is_c( type, "u8" ) )
      {
         uint32_t tmp = va_arg( *list, uint32_t );
         uint8_t u = uint8_c_( tmp );
         return write_uint8_c( rec, u, fmt );
      }
      else if ( chars_is_c( type, "u16" ) )
      {
         uint32_t tmp = va_arg( *list, uint32_t );
         uint16_t u = uint16_c_( tmp );
         return write_uint16_c( rec, u, fmt );
      }
      else if ( chars_is_c( type, "u32" ) )
      {
         return write_uint32_c( rec, va_arg( *list, uint32_t ), fmt );
      }
      else if ( chars_is_c( type, "u64" ) )
      {
         return write_uint64_c( rec, va_arg( *list, uint64_t ), fmt );
      }
   }
   else if ( chars_is_c( type, "f" ) )
   {
      double tmp = va_arg( *list, double );
      float f = float_c_( tmp );
      return write_float_c( rec, f, fmt );
   }
   else if ( chars_is_c( type, "d" ) )
   {
      return write_double_c( rec, va_arg( *list, double ), fmt );
   }
   else if ( chars_is_c( type, "b" ) )
   {
      uint32_t tmp = va_arg( *list, uint32_t );
      cByte b = byte_c_( tmp );
      return write_byte_c( rec, b, fmt );
   }
   else if ( chars_is_c( type, "c" ) )
   {
      int32_t tmp = va_arg( *list, int32_t );
      char c = char_c_( tmp );
      return write_char_c( rec, c, fmt );
   }
   else if ( chars_is_c( type, "r" ) )
   {
      return write_rune_c( rec, va_arg( *list, cRune ), fmt );
   }
   else if ( chars_is_c( type, "bool" ) )
   {
      return write_bool_c( rec, va_arg( *list, int ) != 0, fmt );
   }
   else if ( chars_is_c( type, "rng" ) )
   {
      return write_range_c( rec, va_arg( *list, cRange ), fmt );
   }
   else if ( chars_is_c( type, "s" ) )
   {
      return write_cstr_c( rec, va_arg( *list, char const* ), fmt );
   }
   else if ( chars_is_c( type, "bs" ) )
   {
      return write_bytes_c( rec, va_arg( *list, cBytes ), fmt );
   }
   else if ( chars_is_c( type, "cs" ) )
   {
      return write_chars_c( rec, va_arg( *list, cChars ), fmt );
   }
   else if ( chars_is_c( type, "rec" ) )
   {
      return write_recorded_c( rec, va_arg( *list, cRecorder const* ), fmt );
   }

   return false;
}

/*******************************************************************************

*******************************************************************************/

static inline bool write_impl( cRecorder rec[static 1],
                               c_write_va_arg write_arg,
                               int n,
                               va_list list )
{
   cScanner fmtStrSca = null_scanner_c_();

   cWriteSpecifier specifier;
   reset_write_specifier_c( &specifier );

   for ( int i = 0; i < n; ++i )
   {
      if ( is_empty_c_( specifier.type ) )
      {
         char const* fmtStr = va_arg( list, char const* );
         fmtStrSca = cstr_scanner_c_( fmtStr );
      }
      else
      {
         if ( not write_arg( rec, &list, specifier.type, specifier.fmt ) )
         {
            if ( rec->err == cNoError_ )
            {
               set_recorder_error_c( rec, c_InvalidWriteFormat );
            }
            return false;
         }
      }

      write_format_text_c( rec, &fmtStrSca );
      if ( fmtStrSca.space == 0 )
      {
         reset_write_specifier_c( &specifier );
      }
      else if ( not read_in_write_specifier_c( &fmtStrSca, &specifier ) )
      {
         return false;
      }
   }

   return true;
}

bool write_c( cRecorder rec[static 1],
              c_write_va_arg write_arg,
              int n,
              ... )
{
   va_list list;
   va_start( list, n );

   return write_impl( rec, write_arg, n, list );
}

bool writeln_c( cRecorder rec[static 1],
              c_write_va_arg write_arg,
              int n,
              ... )
{
   va_list list;
   va_start( list, n );

   bool ok = write_impl( rec, write_arg, n, list );
   if ( not ok )
   {
      return false;
   }

   if ( not record_endl_c( rec ) )
   {
      return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
   }

   return true;
}

/*******************************************************************************

*******************************************************************************/

bool push_write_error_c( cErrorStack es[static 1], cRecorder rec[static 1] )
{
   return false;
}

bool note_write_error_c( cRecorder rec[static 1], cError const* err )
{
   char const* msg = NULL;
   switch ( rec->err )
   {
      #define XMAP_C_( N, I, T ) case N: msg = T;
         cWRITE_ERROR_CODE_
      #undef XMAP_C_
   }
   if ( msg == NULL ) return false;

   return record_chars_c_( rec, msg );
}
