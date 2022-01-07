#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   cDate a = date_c( 1983, c_Dec, 1 );
   cDate b = date_c( 1982, c_Jan, 3 );

   expect_c_( eq_date_c( late_date_c( a, b ), a ) );
   expect_c_( eq_date_c( late_date_c( null_date_c(), a ), a ) );

   return finish_tap_c_();
}
