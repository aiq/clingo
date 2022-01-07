#include "clingo/lang/expect.h"
#include "clingo/time/cDatePeriod.h"

int main( void )
{
   init_tap_c_();

   cDatePeriod p1 = single_date_period_c( date_c( 2014, 3, 1 ) );
   cDatePeriod p2 = single_date_period_c( date_c( 2014, 3, 10 ) );

   cDatePeriod exp = make_date_period_c( 2014, 3, 1, 2014, 3, 10 );
   expect_c_( eq_date_period_c( unite_date_periods_c( p1, p2 ), exp ) );

   return finish_tap_c_();
}
