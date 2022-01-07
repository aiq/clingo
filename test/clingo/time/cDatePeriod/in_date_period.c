#include "clingo/lang/expect.h"
#include "clingo/time/cDatePeriod.h"

int main( void )
{
   init_tap_c_();

   cDatePeriod period = date_period_c( date_c( 2014, 3, 3 ),
                                       date_c( 2014, 3, 9 ) );

   expect_c_( !in_date_period_c( period, null_date_c() ) );
   expect_c_( !in_date_period_c( period, date_c( 2014, 3,  2 ) ) );
   expect_c_(  in_date_period_c( period, date_c( 2014, 3,  3 ) ) );
   expect_c_(  in_date_period_c( period, date_c( 2014, 3,  5 ) ) );
   expect_c_(  in_date_period_c( period, date_c( 2014, 3,  9 ) ) );
   expect_c_( !in_date_period_c( period, date_c( 2014, 3, 10 ) ) );

   return finish_tap_c_();
}
