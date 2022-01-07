#include "clingo/container/CInt64Map.h"
#include "clingo/lang/benchmark.h"
#include "clingo/string/CDictionary.h"
#include "clingo/string/CStringList.h"

#include <stdlib.h>
#include <stdint.h>

//******************************************************************** CInt64Map

cBenchmark* make_malloc( int64_t n )
{
   static cBenchmark b = benchmark_c_( "make malloc" );
   b.start = clock();
   int64_t sizeSum = 0;
   times_c_( n, xyz )
   {
      void* ptr = calloc( (unsigned long)next_pow2_int64_c( 64 ), 1 );
      if ( ptr )
      {
         ++sizeSum;
      }
      free( ptr );
   }
   b.end = clock();
   return &b;
}

cBenchmark* make_int64_map( int64_t n )
{
   static cBenchmark b = benchmark_c_( "make int64 map" );
   b.start = clock();
   int64_t sizeSum = 0;
   times_c_( n, xyz )
   {
      CInt64Map* map = new_int64_map_c();
      ++sizeSum;
      release_c( map );
   }
   b.end = clock();
   return &b;
}

cBenchmark* set_int64_map( int64_t n )
{
   static cBenchmark b = benchmark_c_( "set int64 map" );

   cVarInt64Slice ints = heap_slice_c_( n, int64_t );
   srand( 123 );
   times_c_( n, i )
   {
      ints.v[i] = rand();
   }
   CInt64Map* map = new_int64_map_c();

   {
      static cBenchmark bInsert = benchmark_c_( "insert" );
      bInsert.start = clock();
      times_c_( n, i )
      {
         set_on_int64_map_c( map, i, ints.v[i] );
      }
      bInsert.end= clock();
      add_sub_benchmark_c( &b, &bInsert );
   }

   {
      static cBenchmark bRemove = benchmark_c_( "remove" );
      bRemove.start = clock();
      times_c_( n, i )
      {
         remove_from_int64_map_c( map, i );
      }
      bRemove.end = clock();
      add_sub_benchmark_c( &b, &bRemove );
   }

   free( ints.v );
   release_c( map );
   return &b;
}

//****************************************************************** CDictionary

CString* random_string( int64_t len )
{
   cChars charset = c_c( "abcdefghijklmnopqrstuvwxyz"
                          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                          "0123456789,.-#'?!" );

   cVarChars buf = heap_slice_c_( len + 1, char );

   int64_t l = charset.s - 1;
   times_c_( len, i )
   {
      int64_t key = rand() % l;
      buf.v[i] = charset.v[key];
   }
   return adopt_cstr_c( buf.v );
}

cBenchmark* dictionary( int64_t n )
{
   CStringList* list = make_string_list_c( n );
   cVecInfo const* listInfo = info_of_string_list_c( list );

   times_c_( n, i )
   {
      add_to_string_list_c( list, random_string( 10 ) );
   }

   static cBenchmark b = benchmark_c_( "dictionary" );
   b.start = clock();
   CDictionary* dict = new_dictionary_c();
   for ( int64_t i = 0; i < listInfo->count; ++i )
   {
      CString* str = get_from_string_list_c( list, i );
      set_on_dictionary_c( dict, str, str );
   }
   b.end = clock();

   release_all_c_( dict, list );

   return &b;
}

//************************************************************************* main

int main( void )
{
   int64_t const M = 1000*1000;

   static cBenchmark bInt64 = benchmark_c_( "int64 map" );
   {
      add_sub_benchmark_c( &bInt64, make_malloc( 20*M ) );
      add_sub_benchmark_c( &bInt64, make_int64_map( 20*M ) );
      add_sub_benchmark_c( &bInt64, set_int64_map( 20*M ) );
   }
   println_benchmark_c( &bInt64 );

   println_benchmark_c( dictionary( 1*M ) );

   return 0;
}
