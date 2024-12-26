#include "clingo/io/fwrite.h"

#include "_/read_write_util.h"
#include "clingo/io/FILE.h"

/*******************************************************************************
********************************************************************* Functions 
********************************************************************************

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

/*******************************************************************************
 fwrite
*******************************************************************************/

bool fwrite_impl_c( FILE* file,
                    cErrorStack es[static 1],
                    c_get_va_arg getArgFunc,
                    c_write_va_arg writeArgFunc,
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
         if ( not getArgFunc( &list, specifier.type, &arg ) )
         {
            set_recorder_error_c( rec, c_InvalidWriteFormat );
            res = push_recorder_error_c( es, rec );
            break;
         }
         while ( not writeArgFunc( rec, specifier.type, arg, specifier.fmt ) )
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

bool fwrite_list_c( FILE* file, cErrorStack es[static 1], int n, va_list list )
{
   return fwrite_impl_c( file, es, get_va_arg_c, write_va_arg_c, n, list );
}

bool fwrite_c( FILE* file, cErrorStack es[static 1], int n, ... )
{
   va_list list;
   va_start( list, n );
   bool res = fwrite_list_c( file, es, n, list );
   va_end( list );
   return res;
}

/*******************************************************************************
 fwriteln
*******************************************************************************/

bool fwriteln_impl_c( FILE* file,
                      cErrorStack es[static 1],
                      c_get_va_arg getArgFunc,
                      c_write_va_arg writeArgFunc,
                      int n,
                      va_list list )
{
   if ( not fwrite_impl_c( file, es, getArgFunc, writeArgFunc, n, list ) )
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

bool fwriteln_list_c( FILE* file, cErrorStack es[static 1], int n, va_list list )
{
   return fwriteln_impl_c( file, es, get_va_arg_c, write_va_arg_c, n, list );
}

bool fwriteln_c( FILE* file, cErrorStack es[static 1], int n, ... )
{
   va_list list;
   va_start( list, n );
   bool res = fwriteln_list_c( file, es, n, list );
   va_end( list );
   return res;
}
