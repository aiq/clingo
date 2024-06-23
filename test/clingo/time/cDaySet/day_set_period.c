#include "clingo/lang/expect.h"
#include "clingo/time/CDaySet.h"

int main( void )
{
   init_tap_c_();

   CDaySet* ds = new_day_set_c();

   set_many_on_day_set_c_( ds, date_c( 2014, 12, 24 ),
                               date_c( 2014, 12, 25 ),
                               date_c( 2014, 12, 26 ),
                               date_c( 2014, 12, 31 ) );

   cDatePeriod period = day_set_period_c( ds );
   cDatePeriod exp = make_date_period_c( 2014, 12, 24, 2014, 12, 31 );
   expect_at_c_( eq_date_period_c( period, exp ) );

   release_c( ds );

   return finish_tap_c_();
}
