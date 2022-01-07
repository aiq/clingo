#include "clingo/container/CInt64Map.h"
#include "clingo/io/print.h"
#include "clingo/lang/expect.h"

void print_info( cMapInfo const* info )
{
   pjotln_c_( lfjds, 1024,
              "empty: ", map_is_empty_c( info ), " / ",
              "cap: ", map_cap_c( info ), " / ",
              "load: ", map_load_c( info ), " / ",
              "max load: ", info->maxLoad );
}

void print_map( CInt64Map const* map )
{
   int64_t const* key;
   int64_t const* val;
   iterate_map_c_( itr, key, val, map, next_in_int64_map_c )
   {
      cRecorder* rec = &recorder_c_( 128 );
      write_c_( rec, "({i64}/{i64}/{i64}) ", itr, *key, *val );
      print_recorded_c( rec );
   }
   printf( "\n" );
}

int main( void )
{
   init_tap_c_();

   CInt64Map* map = retain_c( make_int64_map_c( 4, 0.5f ) );
   cMapInfo const* info = info_of_int64_map_c( map );
   print_info( info );
   {
      set_on_int64_map_c( map, 123, 1 );
      set_on_int64_map_c( map, 314434, 2 );
      set_on_int64_map_c( map, -3424, 41234 );
      set_on_int64_map_c( map, 1234, 4636 );
      set_on_int64_map_c( map, 3245245, 32566234 );
      set_on_int64_map_c( map, 123, 2 );
   }
   print_info( info_of_int64_map_c( map ) );

   print_map( map );
   require_c_( remove_from_int64_map_c( map, 123 ) );
   print_map( map );

   release_c( map );

   return finish_tap_c_();
}
