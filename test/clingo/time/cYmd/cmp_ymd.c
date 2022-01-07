#include "clingo/lang/expect.h"
#include "clingo/time/cYmd.h"

int main( void )
{
   init_tap_c_();

   cYmd ymd = ymd_c( 2013, c_Apr,  1 );
   cYmd bef = ymd_c( 2013, c_Feb, 18 );
   cYmd aft = ymd_c( 2013, c_Apr,  2 );

   expect_eq_c_( cmp_ymd_c( ymd, ymd ) );
   expect_gt_c_( cmp_ymd_c( ymd, bef ) );
   expect_lt_c_( cmp_ymd_c( ymd, aft ) );

   return finish_tap_c_();
}
