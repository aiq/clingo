#include "clingo/lang/expect.h"
#include "clingo/type/int32.h"

int main( void )
{
   init_tap_c_();

   expect_lt_c_( cmp_int32_c( -2147483648, 0 ) );
   expect_lt_c_( cmp_int32_c(          -1, 0 ) );
   expect_eq_c_( cmp_int32_c(           0, 0 ) );
   expect_gt_c_( cmp_int32_c(           1, 0 ) );
   expect_gt_c_( cmp_int32_c(  2147483647, 0 ) );

   return finish_tap_c_();
}
