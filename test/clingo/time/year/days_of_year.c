#include "clingo/lang/expect.h"
#include "clingo/time/year.h"

int main( void )
{
   init_tap_c_();

   expect_c_( days_of_year_c( 1800 ) == 365 );
   expect_c_( days_of_year_c( 1996 ) == 366 );
   expect_c_( days_of_year_c( 2000 ) == 366 );
   expect_c_( days_of_year_c( 2021 ) == 365 );

   return finish_tap_c_();
}
