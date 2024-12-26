#include "cVaArg.h"

#include "read_write_util.h"
#include "clingo/io/FILE.h"
#include "clingo/io/write_type.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

static bool write_format_text_c( cRecorder rec[static 1],
                                 cScanner sca[static 1] )
{
   while ( true )
   {
      char const* oldStr = sca->mem;
      if ( move_to_char_c( sca, '{' ) )
      {
         cChars cs = atween_c_( oldStr, (char const*)sca->mem );
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
         cChars cs = { sca->space, oldStr };
         move_scanner_c( sca, sca->space );
         return record_chars_c( rec, cs )
            ? true
            : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
      }
   }
}

bool get_va_arg_c( va_list* list, cChars type, cVaArg arg[static 1] )
{
   if ( type.v[0] == 'i' )
   {
      if ( chars_is_c( type, "i8" ) )
      {
         int32_t tmp = va_arg( *list, int32_t );
         arg->i8 = int8_c_( tmp );
         return true;
      }
      else if ( chars_is_c( type, "i16" ) )
      {
         int32_t tmp = va_arg( *list, int32_t );
         arg->i16 = int16_c_( tmp );
         return true;
      }
      else if ( chars_is_c( type, "i32" ) )
      {
         arg->i32 = va_arg( *list, int32_t );
         return true;
      }
      else if ( chars_is_c( type, "i64" ) )
      {
         arg->i64 = va_arg( *list, int64_t );
         return true;
      }
   }
   else if ( type.v[0] == 'u' )
   {
      if ( chars_is_c( type, "u8" ) )
      {
         uint32_t tmp = va_arg( *list, uint32_t );
         arg->u8 = uint8_c_( tmp );
         return true;
      }
      else if ( chars_is_c( type, "u16" ) )
      {
         uint32_t tmp = va_arg( *list, uint32_t );
         arg->u16 = uint16_c_( tmp );
         return true;
      }
      else if ( chars_is_c( type, "u32" ) )
      {
         arg->u32 = va_arg( *list, uint32_t );
         return true;
      }
      else if ( chars_is_c( type, "u64" ) )
      {
         arg->u64 = va_arg( *list, uint64_t );
         return true;
      }
   }
   else if ( chars_is_c( type, "f" ) )
   {
      double tmp = va_arg( *list, double );
      arg->f = float_c_( tmp );
      return true;
   }
   else if ( chars_is_c( type, "d" ) )
   {
      arg->d = va_arg( *list, double );
      return true;
   }
   else if ( chars_is_c( type, "b" ) )
   {
      uint32_t tmp = va_arg( *list, uint32_t );
      arg->b = byte_c_( tmp );
      return true;
   }
   else if ( chars_is_c( type, "c" ) )
   {
      int32_t tmp = va_arg( *list, int32_t );
      arg->c = char_c_( tmp );
      return true;
   }
   else if ( chars_is_c( type, "e" ) )
   {
      arg->e = va_arg( *list, cError const* );
      return true;
   }
   else if ( chars_is_c( type, "r" ) )
   {
      arg->r = va_arg( *list, cRune );
      return true;
   }
   else if ( chars_is_c( type, "bool" ) )
   {
      arg->bool_ = va_arg( *list, int ) != 0;
      return true;
   }
   else if ( chars_is_c( type, "rng" ) )
   {
      arg->rng = va_arg( *list, cRange );
      return true;
   }
   else if ( chars_is_c( type, "s" ) )
   {
      arg->s = va_arg( *list, char const* );
      return true;
   }
   else if ( chars_is_c( type, "bs" ) )
   {
      arg->bs = va_arg( *list, cBytes );
      return true;
   }
   else if ( chars_is_c( type, "cs" ) )
   {
      arg->cs = va_arg( *list, cChars );
      return true;
   }
   else if ( chars_is_c( type, "rec" ) )
   {
      arg->rec = va_arg( *list, cRecorder const* );
      return true;
   }
   else if ( chars_is_c( type, "sca" ) )
   {
      arg->sca = va_arg( *list, cScanner const* );
      return true;
   }
   else if ( chars_is_c( type, "t" ) )
   {
      arg->t = va_arg( *list, cTape );
      return true;
   }

   return false;
}

static bool write_va_arg_c( cRecorder rec[static 1],
                            cChars type,
                            cVaArg arg,
                            char const fmt[static 1] )
{
   if ( type.v[0] == 'i' )
   {
      if ( chars_is_c( type, "i8" ) )
      {
         return write_int8_c( rec, arg.i8, fmt );
      }
      else if ( chars_is_c( type, "i16" ) )
      {
         return write_int16_c( rec, arg.i16, fmt );
      }
      else if ( chars_is_c( type, "i32" ) )
      {
         return write_int32_c( rec, arg.i32, fmt );
      }
      else if ( chars_is_c( type, "i64" ) )
      {
         return write_int64_c( rec, arg.i64, fmt );
      }
   }
   else if ( type.v[0] == 'u' )
   {
      if ( chars_is_c( type, "u8" ) )
      {
         return write_uint8_c( rec, arg.u8, fmt );
      }
      else if ( chars_is_c( type, "u16" ) )
      {
         return write_uint16_c( rec, arg.u16, fmt );
      }
      else if ( chars_is_c( type, "u32" ) )
      {
         return write_uint32_c( rec, arg.u32, fmt );
      }
      else if ( chars_is_c( type, "u64" ) )
      {
         return write_uint64_c( rec, arg.u64, fmt );
      }
   }
   else if ( chars_is_c( type, "f" ) )
   {
      return write_float_c( rec, arg.f, fmt );
   }
   else if ( chars_is_c( type, "d" ) )
   {
      return write_double_c( rec, arg.d, fmt );
   }
   else if ( chars_is_c( type, "b" ) )
   {
      return write_byte_c( rec, arg.b, fmt );
   }
   else if ( chars_is_c( type, "c" ) )
   {
      return write_char_c( rec, arg.c, fmt );
   }
   else if ( chars_is_c( type, "e" ) )
   {
      return write_error_c( rec, arg.e, fmt );
   }
   else if ( chars_is_c( type, "r" ) )
   {
      return write_rune_c( rec, arg.r, fmt );
   }
   else if ( chars_is_c( type, "bool" ) )
   {
      return write_bool_c( rec, arg.bool_, fmt );
   }
   else if ( chars_is_c( type, "rng" ) )
   {
      return write_range_c( rec, arg.rng, fmt );
   }
   else if ( chars_is_c( type, "s" ) )
   {
      return write_cstr_c( rec, arg.s, fmt );
   }
   else if ( chars_is_c( type, "bs" ) )
   {
      return write_bytes_c( rec, arg.bs, fmt );
   }
   else if ( chars_is_c( type, "cs" ) )
   {
      return write_chars_c( rec, arg.cs, fmt );
   }
   else if ( chars_is_c( type, "rec" ) )
   {
      return write_recorded_c( rec, arg.rec, fmt );
   }
   else if ( chars_is_c( type, "sca" ) )
   {
      return write_unscanned_c( rec, arg.sca, fmt );
   }
   else if ( chars_is_c( type, "t" ) )
   {
      return tape_c_( rec, arg.t, fmt );
   }

   return false;
}

/*******************************************************************************
 write
*******************************************************************************/

static bool fwrite_format_text_c( FILE* file,
                                  cScanner sca[static 1],
                                  cErrorStack es[static 1] )
{
   while ( true )
   {
      char const* oldStr = sca->mem;
      if ( move_to_char_c( sca, '{' ) )
      {
         cChars cs = atween_c_( oldStr, (char const*)sca->mem );
         if ( not  fput_chars_c( file, cs ) )
         {
            push_file_error_c( es, file );
            return false;
         }

         if ( move_if_chars_c_( sca, "{{" ) )
         {
            if ( not fput_chars_c( file, c_c( "{" ) ) )
            {
               push_file_error_c( es, file );
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
         cChars cs = { sca->space, oldStr };
         move_scanner_c( sca, sca->space );
         if ( not fput_chars_c( file, cs ) )
         {
            push_file_error_c( es, file );
            return false;
         }
         return true;
      }
   }
}

static void cleanup_fwrite_impl_c( cRecorder rec[static 1], int64_t initCap )
{
   if ( recorder_cap_c( rec ) != initCap )
   {
      free_recorder_mem_c( rec );
   }
}

bool write_impl_c( cRecorder rec[static 1],
                   int n,
                   va_list listArg )
{
   va_list list;
   va_copy( list, listArg );
   cScanner fmtStrSca = null_scanner_c_();

   cWriteSpecifier specifier;
   reset_write_specifier_c( &specifier );

   bool res = true;
   for ( int i = 0; i < n; ++i )
   {
      if ( is_empty_c_( specifier.type ) )
      {
         char const* fmtStr = va_arg( list, char const* );
         fmtStrSca = cstr_scanner_c_( fmtStr );
      }
      else
      {
         cVaArg arg;
         if ( not get_va_arg_c( &list, specifier.type, &arg ) )
         {
            res = set_recorder_error_c( rec, c_InvalidWriteFormat );
            break;
         }
         if ( not write_va_arg_c( rec, specifier.type, arg, specifier.fmt ) )
         {
            res = false;
            break;
         }
      }

      write_format_text_c( rec, &fmtStrSca );
      if ( fmtStrSca.space == 0 )
      {
         reset_write_specifier_c( &specifier );
      }
      else if ( not read_in_write_specifier_c( &fmtStrSca, &specifier ) )
      {
         res = false;
         break;
      }
   }

   va_end( list );
   return res;
}

bool writeln_impl_c( cRecorder rec[static 1],
                     int n,
                     va_list list )
{
   return write_impl_c( rec, n, list ) and
          record_char_c( rec, '\n' );
}

/*******************************************************************************
 fwrite
*******************************************************************************/

bool fwrite_impl_c( FILE* file,
                    cErrorStack es[static 1],
                    int n,
                    va_list listArg )
{
   va_list list;
   va_copy( list, listArg );
   cScanner fmtStrSca = null_scanner_c_();

   cWriteSpecifier specifier;
   reset_write_specifier_c( &specifier );

   int64_t const initCap = 1024;
   cRecorder* rec = &recorder_c_( initCap );
   bool res = true;
   for ( int i = 0; i < n; ++i )
   {
      if ( is_empty_c_( specifier.type ) )
      {
         char const* fmtStr = va_arg( list, char const* );
         fmtStrSca = cstr_scanner_c_( fmtStr );
      }
      else
      {
         reset_recorder_c( rec );
         cVaArg arg;
         if ( not get_va_arg_c( &list, specifier.type, &arg ) )
         {
            set_recorder_error_c( rec, c_InvalidWriteFormat );
            res = push_recorder_error_c( es, rec );
            break;
         }
         while ( not write_va_arg_c( rec, specifier.type, arg, specifier.fmt ) )
         {
            int64_t cap = recorder_cap_c( rec );
            int64_t newCap = cap * 2;
            res = ( cap == initCap ) ? alloc_recorder_mem_c( rec, newCap )
                                     : realloc_recorder_mem_c( rec, newCap );
            if ( not res )
            {
               push_errno_error_c( es, ENOMEM );
               break;
            }
         }
         if ( not fput_chars_c( file, recorded_chars_c( rec ) ) )
         {
            res = push_file_error_c( es, file );
            break;
         }
      }

      fwrite_format_text_c( file, &fmtStrSca, es );
      if ( fmtStrSca.space == 0 )
      {
         reset_write_specifier_c( &specifier );
      }
      else if ( not read_in_write_specifier_c( &fmtStrSca, &specifier ) )
      {
         res = false;
         break;
      }
   }

   va_end( list );
   cleanup_fwrite_impl_c( rec, initCap );
   return res;
}

bool fwriteln_impl_c( FILE* file,
                      cErrorStack es[static 1],
                      int n,
                      va_list list )
{
   if ( not fwrite_impl_c( file, es, n, list ) )
   {
      return false;
   }
   if ( not fput_chars_c( file, c_c( "\n" ) ) )
   {
      push_file_error_c( es, file );
      return false;
   }
   return true;
}