#include "clingo/lang/expect.h"
#include "clingo/time/cDatePeriod.h"

int main( void )
{
   init_tap_c_();

   cDatePeriod p1 = sized_date_period_c( date_c( 2013, 2, 17 ), 10 );
   expect_at_c_( date_period_days_c( p1 ) == 10 );

   cDatePeriod p2 = single_date_period_c( date_c( 2013, 2, 17 ) );
   expect_at_c_( date_period_days_c( p2 ) == 1 );

   cDatePeriod p3 = date_period_c( date_c( 2015, 12, 24 ),
                                   date_c( 2015, 12, 26 ) );
   expect_at_c_( date_period_days_c( p3 ) == 3 );

   return finish_tap_c_();
}
