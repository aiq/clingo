#include "clingo/lang/expect.h"
#include "clingo/time/CDaySet.h"

int main( void )
{
   init_tap_c_();

   CDaySet* ds = new_day_set_c();

   set_on_day_set_c( ds, date_c( 2014, 12, 24 ) );
   set_on_day_set_c( ds, date_c( 2014, 12, 25 ) );
   set_on_day_set_c( ds, date_c( 2014, 12, 26 ) );

   cDatePeriod holyNight = single_date_period_c( date_c( 2014, 12, 24 ) );
   expect_c_( date_period_in_day_set_c( ds, holyNight ) );

   cDatePeriod holiday = make_date_period_c( 2014, 12, 24, 2014, 12, 26 );
   expect_c_( date_period_in_day_set_c( ds, holiday ) );

   cDatePeriod lastDays = make_date_period_c( 2014, 12, 24, 2014, 12, 31 );
   expect_c_( not date_period_in_day_set_c( ds, lastDays ) );

   release_c( ds );

   return finish_tap_c_();
}
