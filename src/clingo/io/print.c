#include "clingo/io/print.h"

#include "_/io/read_write_util.h"
#include "clingo/io/FILE.h"
#include "clingo/io/fwrite.h"

/*******************************************************************************
********************************************************************* Functions 
********************************************************************************

*******************************************************************************/

bool print_c( int n, ... )
{
   cErrorStack* es = &error_stack_c_( 64 );
   va_list list;
   va_start( list, n );
   bool res = fwrite_list_c( stdout, es, n, list );
   va_end( list );
   return res;
}

bool println_c( int n, ... )
{
   cErrorStack* es = &error_stack_c_( 64 );
   va_list list;
   va_start( list, n );
   bool res = fwriteln_list_c( stdout, es, n, list );
   va_end( list );
   return res;
}