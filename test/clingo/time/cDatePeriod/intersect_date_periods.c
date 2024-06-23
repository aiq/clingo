#include "clingo/lang/expect.h"
#include "clingo/time/cDatePeriod.h"

int main( void )
{
   init_tap_c_();

   cDatePeriod p1 = date_period_c( date_c( 2014, 3, 3 ),
                                   date_c( 2014, 3, 9 ) );
   cDatePeriod p2 = date_period_c( date_c( 2014, 3, 7 ),
                                   date_c( 2014, 3, 13 ) );

   cDatePeriod ip = intersect_date_periods_c( p1, p2 );
   expect_at_c_( eq_date_period_c( ip, date_period_c( date_c( 2014, 3, 7 ),
                                                   date_c( 2014, 3, 9 ) ) ) );

   cDatePeriod p3 = single_date_period_c( date_c( 2014, 3, 13 ) );
   cDatePeriod np = intersect_date_periods_c( p1, p3 );
   expect_at_c_( !date_period_is_valid_c( np ) );

   return finish_tap_c_();
}
