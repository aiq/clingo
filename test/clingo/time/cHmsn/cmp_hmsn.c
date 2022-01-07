#include "clingo/lang/expect.h"
#include "clingo/time/cHmsn.h"

int main( void )
{
   init_tap_c_();

   cHmsn hmsn = hms_c( 12, 4, 24 );
   cHmsn before = hms_c( 8, 13, 0 );
   cHmsn after = hms_c( 22, 3, 14 );

   expect_eq_c_( cmp_hmsn_c( hmsn, hmsn ) );
   expect_gt_c_( cmp_hmsn_c( hmsn, before ) );
   expect_lt_c_( cmp_hmsn_c( hmsn, after ) );

   return finish_tap_c_();
}
