#include "clingo/lang/expect.h"
#include "clingo/type/cRange.h"

int main( void )
{
   init_tap_c_();

   cRange range = closed_range_c_( 0, 9 );

   cRange next = shift_range_c( range, range_size_c( range ) );
   expect_at_c_( next.min == 10 );
   expect_at_c_( next.max == 19 );

   cRange prev = shift_range_c( range, -1 * range_size_c( range ) );
   expect_at_c_( prev.min == -10 );
   expect_at_c_( prev.max == -1 );

   return finish_tap_c_();
}
