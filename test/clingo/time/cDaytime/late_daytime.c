#include "clingo/lang/expect.h"
#include "clingo/time/cDaytime.h"

int main( void )
{
   init_tap_c_();

   cDaytime a = daytime_c_( 21, 20, 37 );
   cDaytime b = daytime_c_( 13, 37, 58 );
   cDaytime n = null_daytime_c();

   expect_at_c_( eq_daytime_c( late_daytime_c( a, b ), a ) );
   expect_at_c_( eq_daytime_c( late_daytime_c( n, b ), b ) );

   return finish_tap_c_();
}
