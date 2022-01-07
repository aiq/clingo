#include "clingo/lang/error.h"

/*******************************************************************************
********************************************************************* Functions
*******************************************************************************/

uint32_t error_depth_c( cError const err[static 1] )
{
   uint32_t res = 0;

   while ( err )
   {
      res += 1;
      err = err->details;
   }

   return res;
}

int fprint_error_c( FILE* output, cError const err[static 1] )
{
   int res = 0;

   while ( err )
   {
      cError const* curr = err;
      err = curr->details;
      char const* fmtStr = err ? "%s: "
                               : "%s";

      int tmpRes = fprintf( output, fmtStr, curr->msg );
      if ( tmpRes < 0 )
      {
         return tmpRes;
      }
      res += tmpRes;
   }

   return res;
}

extern inline int print_error_c( cError const err[static 1] );

void reset_error_c( cError err[static 1] )
{
   while ( err )
   {
      cError* curr = err;
      err = curr->details;

      curr->code = cNoError_;
      curr->msg = "";
      curr->details = NULL;
   }
}
