#include "clingo/lang/expect.h"
#include "clingo/type/cRange.h"

int main( void )
{
   init_tap_c_();

   cRange range = closed_open_range_c_( -3, 3 );

   expect_at_c_( range.min == -3 );
   expect_at_c_( range.max == 2 );

   return finish_tap_c_();
}
