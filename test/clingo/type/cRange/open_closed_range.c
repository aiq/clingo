#include "clingo/lang/expect.h"
#include "clingo/type/cRange.h"

int main( void )
{
   init_tap_c_();

   cRange range = open_closed_range_c_( -3, 3 );

   expect_c_( range.min == -2 );
   expect_c_( range.max == 3 );

   return finish_tap_c_();
}
