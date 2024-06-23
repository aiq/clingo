#include "clingo/lang/expect.h"
#include "clingo/type/cRange.h"

int main( void )
{
   init_tap_c_();

   cRange range = closed_range_c_( -5, 5 );

   expect_at_c_( !in_range_c( range, -6 ) );
   expect_at_c_(  in_range_c( range, -5 ) );
   expect_at_c_(  in_range_c( range, -2 ) );
   expect_at_c_(  in_range_c( range,  0 ) );
   expect_at_c_(  in_range_c( range,  2 ) );
   expect_at_c_(  in_range_c( range,  5 ) );
   expect_at_c_( !in_range_c( range,  6 ) );

   return finish_tap_c_();
}
