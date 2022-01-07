#include "clingo/lang/expect.h"
#include "clingo/type/cRange.c"

int main( void )
{
   init_tap_c_();

   cRange range = sized_range_c_( -3, 7 );

   expect_c_( range.min == -3 );
   expect_c_( range.max == 3 );

   return finish_tap_c_();
}
