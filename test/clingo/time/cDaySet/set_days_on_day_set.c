#include "clingo/lang/expect.h"
#include "clingo/time/CDaySet.h"

int main( void )
{
   init_tap_c_();

   CDaySet* daySet = new_day_set_c();
   {
      cDatePeriod tmp = sized_date_period_c( date_c( 2014, 12, 1 ), 6 );
      set_date_period_on_day_set_c( daySet, tmp );
      set_on_day_set_c( daySet, date_c( 2014, 12, 9 ) );
   }

   CDaySet* salt = new_day_set_c();
   {
      set_on_day_set_c( daySet, date_c( 2014, 12, 7 ) );
      cDatePeriod tmp = sized_date_period_c( date_c( 2014, 12, 11 ), 2 );
      set_date_period_on_day_set_c( salt, tmp );
   }

   set_days_on_day_set_c( daySet, salt );
   expect_c_( count_days_c( daySet ) == 10 );
   expect_c_( in_day_set_c( daySet, date_c( 2014, 12,  7 ) ) );
   expect_c_( in_day_set_c( daySet, date_c( 2014, 12, 11 ) ) );
   expect_c_( in_day_set_c( daySet, date_c( 2014, 12, 12 ) ) );


   CDaySet* empty = new_day_set_c();

   set_days_on_day_set_c( daySet, empty );
   expect_c_( count_days_c( daySet ) == 10 );

   release_all_c_( daySet, salt, empty );

   return finish_tap_c_();
}
