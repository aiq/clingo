#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   cDate date = date_c( 2011, c_Mar, 31 );

   cDate res = add_years_to_date_c( date, 5 );
   expect_at_c_( eq_date_c( res, date_c( 2016, c_Mar, 31 ) ) );

   res = add_years_to_date_c( date, -7 );
   expect_at_c_( eq_date_c( res, date_c( 2004, c_Mar, 31 ) ) );

   return finish_tap_c_();
}
