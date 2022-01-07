#include "clingo/lang/expect.h"
#include "clingo/type/uint16.h"

int main( void )
{
   init_tap_c_();

   expect_lt_c_( cmp_uint16_c(     0, 32767 ) );
   expect_lt_c_( cmp_uint16_c( 32766, 32767 ) );
   expect_eq_c_( cmp_uint16_c( 32767, 32767 ) );
   expect_gt_c_( cmp_uint16_c( 32768, 32767 ) );
   expect_gt_c_( cmp_uint16_c( 65535, 32767 ) );

   return finish_tap_c_();
}
