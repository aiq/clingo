#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   cDate date = date_c( 2011, c_Mar, 31 );

   cDate res = add_days_to_date_c( date, 20 );
   expect_at_c_( eq_date_c( res, date_c( 2011, c_Apr, 20 ) ) );

   res = add_days_to_date_c( date, -11 );
   expect_at_c_( eq_date_c( res, date_c( 2011, c_Mar, 20 ) ) );

   return finish_tap_c_();
}
