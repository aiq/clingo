#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   cDate date = date_c( 2011, c_Mar, 31 );

   cDate res = add_weeks_to_date_c( date, -3 );
   expect_c_( eq_date_c( res, date_c( 2011, c_Mar, 10 ) ) );

   res = add_weeks_to_date_c( date, 52 );
   expect_c_( eq_date_c( res, date_c( 2012, c_Mar, 29 ) ) );

   return finish_tap_c_();
}
