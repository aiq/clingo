#include "clingo/lang/expect.h"
#include "clingo/container/CInt64Map.h"

int main( void )
{
   init_tap_c_();

   CInt64Map* map = retain_c( new_int64_map_c() );
   {
      set_on_int64_map_c( map, 1000, 1 );
      set_on_int64_map_c( map,  100, 2 );
      set_on_int64_map_c( map,   10, 3 );
      set_on_int64_map_c( map,    1, 4 );
   }

   int64_t res = 0;
   int64_t const* key;
   int64_t const* val;
   iterate_map_c_( itr, key, val, map, next_in_int64_map_c )
   {
      res += *key * *val;
   }    
   expect_c_( res == 1234 );

   release_c( map );

   return finish_tap_c_();
}