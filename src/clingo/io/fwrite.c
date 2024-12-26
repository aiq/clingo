#include "clingo/io/fwrite.h"

#include "_/cVaArg.h"
#include "clingo/io/FILE.h"

/*******************************************************************************
********************************************************************* Functions 
********************************************************************************
 fwrite
*******************************************************************************/

bool fwrite_list_c( FILE* file, cErrorStack es[static 1], int n, va_list list )
{
   return fwrite_impl_c( file, es, n, list );
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

bool fwriteln_list_c( FILE* file, cErrorStack es[static 1], int n, va_list list )
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

bool fwriteln_c( FILE* file, cErrorStack es[static 1], int n, ... )
{
   va_list list;
   va_start( list, n );
   bool res = fwriteln_list_c( file, es, n, list );
   va_end( list );
   return res;
}
