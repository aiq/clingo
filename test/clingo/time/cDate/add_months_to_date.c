#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   cDate date = date_c( 2011, c_Mar, 31 );

   cDate res = add_months_to_date_c( date, 13 );
   expect_c_( eq_date_c( res, date_c( 2012, c_Apr, 30 ) ) );

   res = add_months_to_date_c( date, -13 );
   expect_c_( eq_date_c( res, date_c( 2010, c_Feb, 28 ) ) );

   return finish_tap_c_();
}
