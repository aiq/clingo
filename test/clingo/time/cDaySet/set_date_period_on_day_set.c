#include "clingo/lang/expect.h"
#include "clingo/time/CDaySet.h"

int main( void )
{
   init_tap_c_();

   CDaySet* ds = new_day_set_c();

   cDatePeriod holiday = make_date_period_c( 2014, 12, 24, 2014, 12, 26 );
   set_date_period_on_day_set_c( ds, holiday );

   expect_c_( !in_day_set_c( ds, date_c( 2014, 12, 23 ) ) );
   expect_c_(  in_day_set_c( ds, date_c( 2014, 12, 24 ) ) );
   expect_c_(  in_day_set_c( ds, date_c( 2014, 12, 25 ) ) );
   expect_c_(  in_day_set_c( ds, date_c( 2014, 12, 26 ) ) );
   expect_c_( !in_day_set_c( ds, date_c( 2014, 12, 27 ) ) );

   release_c( ds );

   return finish_tap_c_();
}
