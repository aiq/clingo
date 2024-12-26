#include "clingo/io/write.h"

#include <ctype.h>
#include <stdio.h>

#include "_/cVaArg.h"
#include "clingo/io/cTape.h"
#include "clingo/io/jot.h"
#include "clingo/io/write_type.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 write
*******************************************************************************/

bool write_list_c( cRecorder rec[static 1], int n, va_list list )
{
   return write_impl_c( rec, n, list );
}

bool write_c( cRecorder rec[static 1], int n, ... )
{
   va_list list;
   va_start( list, n );
   bool res = write_list_c( rec, n, list );
   va_end( list );
   return res;
}

/*******************************************************************************
 write
*******************************************************************************/

bool writeln_list_c( cRecorder rec[static 1], int n, va_list list )
{
   return write_impl_c( rec, n, list ) and
          record_char_c( rec, '\n' );
}

bool writeln_c( cRecorder rec[static 1], int n, ... )
{
   va_list list;
   va_start( list, n );
   bool res = writeln_list_c( rec, n, list );
   va_end( list );
   return res;
}
