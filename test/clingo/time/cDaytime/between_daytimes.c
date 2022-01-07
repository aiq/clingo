#include "clingo/lang/expect.h"
#include "clingo/time/cDaytime.h"

int main( void )
{
   init_tap_c_();

   cDaytime a = daytime_c_( 21, 20, 37 );
   cDaytime b = daytime_c_( 13, 37, 58 );

   cDuration dur = duration_c( 7, 42, 39, 0 );
   cDuration rud = invert_duration_c( dur );

   expect_c_( eq_duration_c( between_daytimes_c( a, b ), rud ) );
   expect_c_( eq_duration_c( between_daytimes_c( b, a ), dur ) );

   return finish_tap_c_();
}
