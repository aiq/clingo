#include "clingo/lang/expect.h"
#include "clingo/type/int64.h"

int main( void )
{
   init_tap_c_();

   expect_lt_c_( cmp_int64_c( -9223372036854775807-1, 0 ) );
   expect_lt_c_( cmp_int64_c(                     -1, 0 ) );
   expect_eq_c_( cmp_int64_c(                      0, 0 ) );
   expect_gt_c_( cmp_int64_c(                      1, 0 ) );
   expect_gt_c_( cmp_int64_c(    9223372036854775807, 0 ) );

   return finish_tap_c_();
}
