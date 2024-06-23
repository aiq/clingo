#include "clingo/lang/expect.h"
#include "clingo/container/CInt64Set.h"

int main( void )
{
   init_tap_c_();

   CInt64Set* set = retain_c( new_int64_set_c() );
   {
      set_on_int64_set_c( set, 1000 );
      set_on_int64_set_c( set,  200 );
      set_on_int64_set_c( set,   30 );
      set_on_int64_set_c( set,    4 );
   }

   int64_t res = 0;
   int64_t const* val;
   iterate_set_c_( itr, &val, set, next_in_int64_set_c )
   {
      res += *val;
   }
   expect_at_c_( res == 1234 );

   release_c( set );

   return finish_tap_c_();
}