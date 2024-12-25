#include "clingo/io/fwrite.h"

#include "_/read_write_util.h"
#include "clingo/io/FILE.h"

/*******************************************************************************
********************************************************************* Functions 
********************************************************************************

*******************************************************************************/

static bool fwrite_format_text( FILE* file,
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

static void cleanup_fwrite_impl( cRecorder rec[static 1], int64_t initCap )
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
                    c_write_va_arg write_arg,
                    int n,
                    va_list list )
{
   cScanner fmtStrSca = null_scanner_c_();

   cWriteSpecifier specifier;
   reset_write_specifier_c( &specifier );

   int64_t const initCap = 1024;
   cRecorder* rec = &recorder_c_( initCap );
   for ( int i = 0; i < n; ++i )
   {
      if ( is_empty_c_( specifier.type ) )
      {
         char const* fmtStr = va_arg( list, char const* );
         fmtStrSca = cstr_scanner_c_( fmtStr );
      }
      else
      {
         if ( not write_arg( rec, list, specifier.type, specifier.fmt ) )
         {
            if ( rec->err == cNoError_ )
            {
               cleanup_fwrite_impl( rec, initCap );
               return set_recorder_error_c( rec, c_InvalidWriteFormat );
            }
            if ( rec->err == c_NotEnoughRecorderSpace )
            {
               reset_recorder_c( rec );
               int64_t cap = recorder_cap_c( rec );
               if ( cap == initCap )
               {
                  cap *= 2;
                  if ( not alloc_recorder_mem_c( rec, cap ) )
                  {
                     return push_errno_error_c( es, ENOMEM );
                  }
               }
               while ( not write_arg( rec, list, specifier.type, specifier.fmt ) )
               {
                  cap *= 2;
                  if ( not realloc_recorder_mem_c( rec, cap ) )
                  {
                     free_recorder_mem_c( rec );
                     return push_errno_error_c( es, ENOMEM );
                  }
               }
            }
         }
         if ( not fput_chars_c( file, recorded_chars_c( rec ) ) )
         {
            return push_file_error_c( es, file );
         }
      }

      fwrite_format_text( file, &fmtStrSca, es );
      if ( fmtStrSca.space == 0 )
      {
         reset_write_specifier_c( &specifier );
      }
      else if ( not read_in_write_specifier_c( &fmtStrSca, &specifier ) )
      {
         cleanup_fwrite_impl( rec, initCap );
         return false;
      }
      reset_recorder_c( rec );
   }

   cleanup_fwrite_impl( rec, initCap );
   return true;
}

bool fwrite_list_c( FILE* file, cErrorStack es[static 1], int n, va_list list )
{
   return fwrite_impl_c( file, es, write_format_arg_c, n, list );
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
                      c_write_va_arg write_arg,
                      int n,
                      va_list list )
{
   if ( not fwrite_impl_c( file, es, write_arg, n, list ) )
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
   return fwriteln_impl_c( file, es, write_format_arg_c, n, list );
}

bool fwriteln_c( FILE* file, cErrorStack es[static 1], int n, ... )
{
   va_list list;
   va_start( list, n );
   bool res = fwriteln_list_c( file, es, n, list );
   va_end( list );
   return res;
}
