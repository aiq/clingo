#include "clingo/lang/expect.h"
#include "clingo/type/cRange.h"

int main( void )
{
   init_tap_c_();

   cRange range = closed_range_c_( 18, 25 );
   expect_c_( range_size_c( range ) == 8 );

   range = sized_range_c_( 18, 8 );
   expect_c_( range_size_c( range ) == 8 );

   return finish_tap_c_();
}
