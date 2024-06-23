#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   cDate a = date_c( 1983, c_Dec, 1 );
   cDate b = date_c( 1982, c_Jan, 3 );

   expect_at_c_( eq_date_c( early_date_c( a, b ), b ) );
   expect_at_c_( eq_date_c( early_date_c( null_date_c(), b ), null_date_c() ) );

   return finish_tap_c_();
}
