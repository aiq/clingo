#include "clingo/lang/expect.h"
#include "clingo/time/cDatePeriod.h"

int main( void )
{
   init_tap_c_();

   cDatePeriod p1 = date_period_c( date_c( 2014, 2, 27 ),
                                   date_c( 2014, 3, 25 ) );
   expect_c_( date_period_weeks_c( p1 ) == 3 );

   cDatePeriod p2 = date_period_c( date_c( 2014, 2, 27 ),
                                   date_c( 2014, 3, 27 ) );
   expect_c_( date_period_weeks_c( p2 ) == 4 );

   cDatePeriod p3 = date_period_c( date_c( 2014, 2, 27 ),
                                   date_c( 2014, 3, 29 ) );
   expect_c_( date_period_weeks_c( p3 ) == 4 );

   cDatePeriod p4 = single_date_period_c( date_c( 2014, 3, 2 ) );
   expect_c_( date_period_weeks_c( p4 ) == 0 );

   return finish_tap_c_();
}
