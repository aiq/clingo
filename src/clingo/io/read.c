#include "clingo/io/read.h"

#include <ctype.h>
#include "_/read_write_util.h"
#include "clingo/io/read_type.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

static bool read_format_text_c( cScanner sca[static 1],
                                cScanner fmtSca[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( fmtSca );

   int64_t const scaInitPos = sca->pos;

   while ( true )
   {
      char const* fmtStr = fmtSca->mem;
      if ( move_to_char_c( fmtSca, '{' ) )
      {
         cChars cs = atween_c_( fmtStr, (char const*)fmtSca->mem );
         if ( not move_if_chars_c( sca, cs ) )
         {
            move_scanner_to_c( sca, scaInitPos );
            return false;
         }

         if ( move_if_chars_c_( fmtSca, "{{" ) )
         {
            if ( not move_if_char_c( sca, '{' ) )
            {
               move_scanner_to_c( sca, scaInitPos );
               return false;
            }
         }
         else
         {
            return true;
         }
      }
      else
      {
         cChars cs = unscanned_chars_c_( fmtSca );
         move_scanner_c( fmtSca, fmtSca->space );
         if ( not move_if_chars_c( sca, cs ) )
         {
            move_scanner_to_c( sca, scaInitPos );
            return false;
         }

         return true;
      }
   }
}

/******************************************************************************/

bool read_format_arg_c( cScanner sca[static 1],
                        void* val,
                        cChars type,
                        char const fmt[static 1] )
{
   if ( is_empty_c_( type ) )
   {
      return true;
   }

   if ( type.v[0] == 'i' )
   {
      int64_t tmp;
      if ( chars_is_c( type, "i8" ) )
      {
         int8_t* i8 = val ? val : &tmp;
         return read_int8_c( sca, i8, fmt );
      }
      else if ( chars_is_c( type, "i16" ) )
      {
         int16_t* i16 = val ? val : &tmp;
         return read_int16_c( sca, i16, fmt );
      }
      else if ( chars_is_c( type, "i32" ) )
      {
         int32_t* i32 = val ? val : &tmp;
         return read_int32_c( sca, i32, fmt );
      }
      else if ( chars_is_c( type, "i64" ) )
      {
         int64_t* i64 = val ? val : &tmp;
         return read_int64_c( sca, i64, fmt );
      }
   }
   else if ( type.v[0] == 'u' )
   {
      uint64_t tmp;
      if ( chars_is_c( type, "u8" ) )
      {
         uint8_t* u8 = val ? val : &tmp;
         return read_uint8_c( sca, u8, fmt );
      }
      else if ( chars_is_c( type, "u16" ) )
      {
         uint16_t* u16 = val ? val : &tmp;
         return read_uint16_c( sca, u16, fmt );
      }
      else if ( chars_is_c( type, "u32" ) )
      {
         uint32_t* u32 = val ? val : &tmp;
         return read_uint32_c( sca, u32, fmt );
      }
      else if ( chars_is_c( type, "u64" ) )
      {
         uint64_t* u64 = val ? val : &tmp;
         return read_uint64_c( sca, u64, fmt );
      }
   }
   else if ( chars_is_c( type, "b" ) )
   {
      cByte tmp;
      cByte* b = val ? val : &tmp;
      return read_byte_c( sca, b, fmt );
   }
   else if ( chars_is_c( type, "c" ) )
   {
      char tmp;
      char* c = val ? val : &tmp;
      return read_char_c( sca, c, fmt );
   }
   else if ( chars_is_c( type, "bool" ) )
   {
      bool tmp;
      bool* b = val ? val : &tmp;
      return read_bool_c( sca, b, fmt );
   }
   else if ( chars_is_c( type, "r" ) )
   {
      cRune tmp;
      cRune* r = val ? val : &tmp;
      return read_rune_c( sca, r, fmt );
   }
   else if ( chars_is_c( type, "rng" ) )
   {
      cRange tmp;
      cRange* range = val ? val : &tmp;
      return read_range_c( sca, range, fmt );
   }

   return false;
}

/*******************************************************************************

*******************************************************************************/

bool read_c( cScanner sca[static 1],
             c_read_va_arg read_arg,
             int n,
             ... )
{
   va_list list;
   va_start( list, n );

   cScanner fmtStrSca = null_scanner_c_();
   cReadCommand command;
   reset_read_command_c( &command );
   cReadSpecifier specifier;
   reset_read_specifier_c( &specifier );

   bool res = true;
   int i = 1;
   while ( i <= n )
   {
      res = false;
      // ---------------------------------------------------------------- va_arg
      if ( not is_empty_c_( specifier.type ) )
      {
         void* ptr = specifier.withDst ? va_arg( list, void* )
                                       : NULL;
         if ( not read_arg( sca, ptr, specifier.type, specifier.fmt ) ) break;

         if ( ptr ) ++i;
      }
      else if ( command.op != ' ' )
      {
         if ( not handle_read_command_c( sca, &command ) ) break;
      }
      else if ( fmtStrSca.space == 0 )
      {
         char const* fmtStr = va_arg( list, char const* );
         fmtStrSca = cstr_scanner_c_( fmtStr );
      }

      reset_read_command_c( &command );
      reset_read_specifier_c( &specifier );

      // ---------------------------------------------------------------- scan
      if ( not read_format_text_c( sca, &fmtStrSca ) ) break;

      if ( fmtStrSca.space == 0 )
      {
         ++i;
      }
      else if ( not read_in_read_command_c( &fmtStrSca, &command ) and
                not read_in_read_specifier_c( &fmtStrSca, &specifier ) )
      {
         break;
      }
      res = true;
   }

   va_end( list );
   return res;
}
