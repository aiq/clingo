#include "clingo/lang/expect.h"
#include "clingo/type/cRange.h"

int main( void )
{
   init_tap_c_();

   cRange range = { .min = 6, .max = 99 };

   expect_c_( clamp_into_range_c( range, 1 ) == 6 );
   expect_c_( clamp_into_range_c( range, 128 ) == 99 );

   return finish_tap_c_();
}
