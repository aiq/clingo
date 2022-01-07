#include "clingo/container/CByteVec.h"
#include "clingo/container/CInt64Vec.h"
#include "clingo/lang/benchmark.h"

cBenchmark* run_int64_vec( int64_t n )
{
   static cBenchmark b = benchmark_c_( "run int64 vec" );
   b.start = clock();
   {
      CInt64Vec* vec = new_int64_vec_c();
      times_c_( n, i )
      {
         add_to_int64_vec_c( vec, i );
      }
      release_c( vec );
   }
   b.end = clock();
   return &b;
}

cBenchmark* run_byte_vec( int64_t n )
{
   static cBenchmark b = benchmark_c_( "run byte vec" );
   b.start = clock();
   {
      CByteVec* vec = new_byte_vec_c();
      cByte byte = 0xbe;
      times_c_( n, i )
      {
         add_to_byte_vec_c( vec, byte );
      }
      release_c( vec );
   }
   b.end = clock();

   return &b;
}

int main( void )
{
   int64_t const M = 1000*1000;

   println_benchmark_c( run_int64_vec( 100*M ) );
   println_benchmark_c( run_byte_vec( 100*M ) );

   return 0;
}
