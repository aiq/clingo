#include "clingo/lang/expect.h"
#include "clingo/type/int8.h"

int main( void )
{
   init_tap_c_();

   expect_lt_c_( cmp_int8_c( -128, 0 ) );
   expect_lt_c_( cmp_int8_c(   -1, 0 ) );
   expect_eq_c_( cmp_int8_c(    0, 0 ) );
   expect_gt_c_( cmp_int8_c(    1, 0 ) );
   expect_gt_c_( cmp_int8_c(  127, 0 ) );

   return finish_tap_c_();
}
