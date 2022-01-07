#include "clingo/lang/benchmark.h"

#include <iso646.h>
#include "clingo/lang/func.h"

/*******************************************************************************
********************************************************************* Functions
*******************************************************************************/

extern inline void add_sub_benchmark_c( cBenchmark main[static 1],
                                        cBenchmark sub[static 1] );

extern inline void chain_benchmarks_c( cBenchmark prev[static 1],
                                       cBenchmark next[static 1] );

cBenchmark const* first_sub_benchmark_c( cBenchmark const b[static 1] )
{
   cBenchmark const* first = b->lastSub;

   while ( first )
   {
      if ( first->prev == NULL ) break;

      first = first->prev;
   }

   return first;
}

/*******************************************************************************

*******************************************************************************/

extern inline double measured_secs_c( cBenchmark const b[static 1] );
extern inline double measured_msecs_c( cBenchmark const b[static 1] );
extern inline double measured_usecs_c( cBenchmark const b[static 1] );
extern inline double measured_nsecs_c( cBenchmark const b[static 1] );

/*******************************************************************************

*******************************************************************************/

static int print_dur( FILE* output, cBenchmark const b[static 1] )
{
   if ( b->start == 0 or b->end == 0 )
   {
      return 0;
   }
   double durVal = (double)( b->end - b->start ) / CLOCKS_PER_SEC;
   if ( durVal > 1.0 )
   {
      return fprintf( output, "\t\t%fs", durVal );
   }
   else
   {
      durVal *= 1000.0;
      if ( durVal > 1.0 )
      {
         return fprintf( output, "\t\t%fms", durVal );
      }
      durVal *= 1000.0;
      if ( durVal > 1.0 )
      {
         return fprintf( output, "\t\t%fµs", durVal );
      }
      durVal *= 1000.0;
      if ( durVal > 1.0 )
      {
         return fprintf( output, "\t\t%fns", durVal );
      }
   }
   return fprintf( output, "0.0" );
}

static int print_line( FILE* output, cBenchmark const b[static 1], int level )
{
   int res = 0;
   int tmpRes = 0;

   times_c_( level, xyz )
   {
      tmpRes = fprintf( output, "\t" );
      if ( tmpRes < 0 ) return tmpRes;
      else res += tmpRes;
   }
      
   tmpRes = fprintf( output, "%s", b->label );
   if ( tmpRes < 0 ) return tmpRes;
   else res += tmpRes;

   tmpRes = print_dur( output, b );
   if ( tmpRes < 0 ) return tmpRes;
   else res += tmpRes;

   tmpRes = fprintf( output, "\n" );
   if ( tmpRes < 0 ) return tmpRes;
   else res += tmpRes;

   return res;
}

static int print_impl( FILE* output, cBenchmark const b[static 1], int level )
{
   int res = 0;

   while ( b )
   {
      int tmpRes = print_line( output, b, level );
      if ( tmpRes < 0 ) return tmpRes;
      else res += tmpRes;

      if ( b->lastSub )
      {
         cBenchmark const* first = first_sub_benchmark_c( b );
         tmpRes = print_impl( output, first, level + 1 );
         if ( tmpRes < 0 ) return tmpRes;
         else res += tmpRes;
      }
      b = b->next;
   }

   return res;
}

int fprintln_benchmark_c( FILE* output, cBenchmark const b[static 1] )
{
   return print_impl( output, b, 0 );
}

extern inline int println_benchmark_c( cBenchmark const b[static 1] );
