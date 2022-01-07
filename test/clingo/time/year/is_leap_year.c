#include "clingo/lang/expect.h"
#include "clingo/time/year.h"

int main( void )
{
   init_tap_c_();

   expect_c_( !is_leap_year_c( 1800 ) );
   expect_c_(  is_leap_year_c( 1996 ) );
   expect_c_(  is_leap_year_c( 2000 ) );
   expect_c_( !is_leap_year_c( 2021 ) );

   return finish_tap_c_();
}
