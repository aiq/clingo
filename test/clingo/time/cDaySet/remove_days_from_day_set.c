#include "clingo/lang/expect.h"
#include "clingo/time/CDaySet.h"

int main( void )
{
   init_tap_c_();

   CDaySet* daySet = new_day_set_c();
   cDatePeriod p1 = sized_date_period_c( date_c( 2014, 12, 1 ), 6 );
   set_date_period_on_day_set_c( daySet, p1 );
   set_on_day_set_c( daySet, date_c( 2014, 12, 9 ) );

   CDaySet* dirty = new_day_set_c();
   set_on_day_set_c( dirty, date_c( 2014, 12, 2 ) );
   cDatePeriod p2 = sized_date_period_c( date_c( 2014, 12, 4 ), 2 );
   set_date_period_on_day_set_c( dirty, p2 );

   remove_days_from_day_set_c( daySet, dirty );
   expect_c_( count_days_c( daySet ) == 4 );
   expect_c_( in_day_set_c( daySet, date_c( 2014, 12, 1 ) ) );
   expect_c_( in_day_set_c( daySet, date_c( 2014, 12, 3 ) ) );
   expect_c_( in_day_set_c( daySet, date_c( 2014, 12, 6 ) ) );
   expect_c_( in_day_set_c( daySet, date_c( 2014, 12, 9 ) ) );

   CDaySet* empty = new_day_set_c();

   remove_days_from_day_set_c( daySet, empty );
   expect_c_( count_days_c( daySet ) == 4 );

   release_all_c_( daySet, dirty, empty );

   return finish_tap_c_();
}
