#include "clingo/lang/expect.h"
#include "clingo/type/cRange.h"

int main( void )
{
   init_tap_c_();

   cRange rng = open_range_c_( -3, 3 );

   expect_at_c_( rng.min == -2 );
   expect_at_c_( rng.max == 2 );

   return finish_tap_c_();
}
