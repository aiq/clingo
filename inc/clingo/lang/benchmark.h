#ifndef CLINGO_LANG_BENCHMARK_H
#define CLINGO_LANG_BENCHMARK_H

#include <stdio.h>
#include <time.h>

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************/

struct cBenchmark
{
   char const* label;
   clock_t start;
   clock_t end;
   struct cBenchmark* lastSub;
   struct cBenchmark* prev;
   struct cBenchmark* next;
};
typedef struct cBenchmark cBenchmark;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#define benchmark_c_( Label )                                                  \
(                                                                              \
   (cBenchmark){                                                               \
      .label = (Label),                                                        \
      .start = 0,                                                              \
      .end = 0,                                                                \
      .lastSub = NULL,                                                         \
      .prev = NULL,                                                            \
      .next = NULL                                                             \
   }                                                                           \
)

/*******************************************************************************

*******************************************************************************/

inline void chain_benchmarks_c( cBenchmark prev[static 1],
                                cBenchmark next[static 1] )
{
   prev->next = next;
   next->prev = prev;
}

inline void add_sub_benchmark_c( cBenchmark main[static 1],
                                 cBenchmark sub[static 1] )
{
   cBenchmark* prevSub = main->lastSub;
   if ( prevSub )
   {
      chain_benchmarks_c( prevSub, sub );
   }
   main->lastSub = sub;
}

cBenchmark const* first_sub_benchmark_c( cBenchmark const b[static 1] );

/*******************************************************************************

*******************************************************************************/

inline double measured_secs_c( cBenchmark const b[static 1] )
{
   double durVal = (double)( b->end - b->start ) / CLOCKS_PER_SEC;
   return durVal;
}

double measured_msecs_c( cBenchmark const b[static 1] )
{
   return measured_secs_c( b ) * 1000.0;
}

double measured_usecs_c( cBenchmark const b[static 1] )
{
   return measured_msecs_c( b ) * 1000.0;
}

double measured_nsecs_c( cBenchmark const b[static 1] )
{
   return measured_usecs_c( b ) * 1000.0;
}

/*******************************************************************************

*******************************************************************************/

int fprintln_benchmark_c( FILE* output, cBenchmark const b[static 1] );

inline int println_benchmark_c( cBenchmark const b[static 1] )
{
   return fprintln_benchmark_c( stdout, b );
}

#endif

