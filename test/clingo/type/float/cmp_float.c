#include "clingo/lang/expect.h"
#include "clingo/type/float.h"

int main( void )
{
   init_tap_c_();

   float flt = -213.435f;
   float les = nextafterf( flt, -FLT_MAX );
   float gre = nextafterf( flt, FLT_MAX );

   expect_eq_c_( cmp_float_c( flt, flt ) );
   expect_lt_c_( cmp_float_c( les, flt ) );
   expect_gt_c_( cmp_float_c( gre, flt ) );

   return finish_tap_c_();
}
