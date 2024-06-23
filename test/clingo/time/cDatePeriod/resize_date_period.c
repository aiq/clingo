#include "clingo/lang/expect.h"
#include "clingo/time/cDatePeriod.h"

int main( void )
{
   init_tap_c_();

   cDatePeriod period = make_date_period_c( 2014, 11, 9, 2014, 11, 16 );

   cDatePeriod bigger = make_date_period_c( 2014, 11, 2, 2014, 11, 23 );
   expect_at_c_( eq_date_period_c( resize_date_period_c( period, 7 ), bigger ) );

   cDatePeriod smaller = make_date_period_c( 2014, 11, 10, 2014, 11, 15 );
   expect_at_c_( eq_date_period_c( resize_date_period_c( period, -1 ), smaller ) );

   return finish_tap_c_();
}
