#include "clingo/lang/expect.h"
#include "clingo/time/cDaytime.h"

int main( void )
{
   init_tap_c_();

   cDaytime a = daytime_c_( 21, 20, 37 );
   cDaytime b = daytime_c_( 13, 37, 58 );
   cDaytime n = null_daytime_c();

   expect_c_( eq_daytime_c( early_daytime_c( a, b ), b ) );
   expect_c_( eq_daytime_c( early_daytime_c( n, b ), n ) );

   return finish_tap_c_();
}
