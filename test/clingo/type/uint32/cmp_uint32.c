#include "clingo/lang/expect.h"
#include "clingo/type/uint32.h"

int main( void )
{
   init_tap_c_();

   expect_lt_c_( cmp_uint32_c(          0, 2147483647 ) );
   expect_lt_c_( cmp_uint32_c( 2147483646, 2147483647 ) );
   expect_eq_c_( cmp_uint32_c( 2147483647, 2147483647 ) );
   expect_gt_c_( cmp_uint32_c( 2147483648, 2147483647 ) );
   expect_gt_c_( cmp_uint32_c( 4294967295, 2147483647 ) );

   return finish_tap_c_();
}
