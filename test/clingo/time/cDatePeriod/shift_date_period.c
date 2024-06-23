#include "clingo/lang/expect.h"
#include "clingo/time/cDatePeriod.h"

int main( void )
{
   init_tap_c_();

   cDatePeriod prev = sized_date_period_c( date_c( 2014, 2, 24 ), 7 );
   cDatePeriod week = sized_date_period_c( date_c( 2014, 3,  3 ), 7 );
   cDatePeriod next = sized_date_period_c( date_c( 2014, 3, 10 ), 7 );

   expect_at_c_( eq_date_period_c( shift_date_period_c( week,  7 ), next ) );
   expect_at_c_( eq_date_period_c( shift_date_period_c( week, -7 ), prev ) );

   return finish_tap_c_();
}
