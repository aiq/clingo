#include "clingo/lang/expect.h"
#include "clingo/type/uint8.h"

int main( void )
{
   init_tap_c_();

   expect_lt_c_( cmp_uint8_c(   0, 127 ) );
   expect_lt_c_( cmp_uint8_c( 126, 127 ) );
   expect_eq_c_( cmp_uint8_c( 127, 127 ) );
   expect_gt_c_( cmp_uint8_c( 128, 127 ) );
   expect_gt_c_( cmp_uint8_c( 255, 127 ) );

   return finish_tap_c_();
}
