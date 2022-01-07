#include "clingo/lang/expect.h"
#include "clingo/type/int16.h"

int main()
{
   init_tap_c_();

   expect_lt_c_( cmp_int16_c( -32768, 0 ) );
   expect_lt_c_( cmp_int16_c(     -1, 0 ) );
   expect_eq_c_( cmp_int16_c(      0, 0 ) );
   expect_gt_c_( cmp_int16_c(      1, 0 ) );
   expect_gt_c_( cmp_int16_c(  32767, 0 ) );

   return finish_tap_c_();
}
