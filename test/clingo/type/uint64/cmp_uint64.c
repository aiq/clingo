#include "clingo/lang/expect.h"
#include "clingo/type/uint64.h"

int main( void )
{
   init_tap_c_();

   expect_lt_c_( cmp_uint64_c(                    0 , 9223372036854775807 ) );
   expect_lt_c_( cmp_uint64_c(  9223372036854775806 , 9223372036854775807 ) );
   expect_eq_c_( cmp_uint64_c(  9223372036854775807 , 9223372036854775807 ) );
   expect_gt_c_( cmp_uint64_c(  9223372036854775808U, 9223372036854775807 ) );
   expect_gt_c_( cmp_uint64_c( 18446744073709551615U, 9223372036854775807 ) );

   return finish_tap_c_();
}
