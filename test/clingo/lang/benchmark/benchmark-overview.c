#include "clingo/lang/benchmark.h"

cBenchmark* first( int64_t n )
{
   static cBenchmark b = benchmark_c_( "first benchmark" );
   benchmark_scope_c_( b, "first benchmark" );
   {
      
   }
}
