#include "clingo/lang/expect.h"
#include "clingo/time/cDatePeriod.h"

int main( void )
{
   init_tap_c_();

   cDatePeriod p1 = date_period_c( date_c( 2014, 3, 3 ),
                                   date_c( 2014, 3, 9 ) );
   cDatePeriod p2 = date_period_c( date_c( 2014, 3, 7 ),
                                   date_c( 2014, 3, 13 ) );
   cDatePeriod p3 = date_period_c( date_c( 2014, 3, 12 ),
                                   date_c( 2014, 3, 20 ) );

   expect_c_(  date_periods_overlap_c( p1, p2 ) );
   expect_c_(  date_periods_overlap_c( p2, p3 ) );
   expect_c_( !date_periods_overlap_c( p1, p3 ) );

   return finish_tap_c_();
}
