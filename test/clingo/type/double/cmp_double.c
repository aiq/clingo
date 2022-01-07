#include "clingo/lang/expect.h"
#include "clingo/type/double.h"

int main( void )
{
   init_tap_c_();

   double dbl = 3.14;
   double les = nextafter( dbl, -DBL_MAX );
   double gre = nextafter( dbl, DBL_MAX );

   expect_eq_c_( cmp_double_c( dbl, dbl ) );
   expect_lt_c_( cmp_double_c( les, dbl ) );
   expect_gt_c_( cmp_double_c( gre, dbl ) );

   return finish_tap_c_();
}
