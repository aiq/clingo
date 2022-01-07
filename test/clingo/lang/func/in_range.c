#include "clingo/lang/expect.h"
#include "clingo/lang/func.h"

int main( void )
{
   init_tap_c_();

   expect_c_( !in_range_c_( 0, -10, 5 ) );
   expect_c_(  in_range_c_( 0,   0, 5 ) );
   expect_c_(  in_range_c_( 0,   3, 5 ) );
   expect_c_(  in_range_c_( 0,   5, 5 ) );
   expect_c_( !in_range_c_( 0,  10, 5 ) );

   expect_c_( !in_range_c_( -1.0, -1.5, 1.0 ) );
   expect_c_(  in_range_c_( -1.0, -1.0, 1.0 ) );
   expect_c_(  in_range_c_( -1.0, -0.5, 1.0 ) );
   expect_c_(  in_range_c_( -1.0,  1.0, 1.0 ) );
   expect_c_( !in_range_c_( -1.0,  1.5, 1.0 ) );

   return finish_tap_c_();
}
