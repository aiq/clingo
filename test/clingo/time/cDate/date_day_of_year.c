#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( date_day_of_year_c( date_c( 2012, c_Jan,  1 ) ) ==   1 );
   expect_at_c_( date_day_of_year_c( date_c( 2012, c_May,  3 ) ) == 124 );
   expect_at_c_( date_day_of_year_c( date_c( 2012, c_Dec, 31 ) ) == 366 );

   return finish_tap_c_();
}
