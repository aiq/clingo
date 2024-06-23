#include "clingo/lang/expect.h"
#include "clingo/time/CDaySet.h"

#define expect_eq_( A, B )                                                     \
   expect_at_c_( eq_date_c( (A), (B) ) )

int main( void )
{
   init_tap_c_();

   CDaySet* ds = new_day_set_c();

   cDatePeriod holiday = make_date_period_c( 2014, 12, 24, 2014, 12, 27 );
   set_date_period_on_day_set_c( ds, holiday );
   expect_at_c_( count_days_c( ds ) == 4 );
   expect_eq_( first_in_day_set_c( ds ), date_c( 2014, 12, 24 ) );
   expect_eq_( last_in_day_set_c( ds ), date_c( 2014, 12, 27 ) );

   remove_from_day_set_c( ds, date_c( 2014, 12, 27 ) );
   expect_at_c_( count_days_c( ds ) == 3 );
   expect_eq_( first_in_day_set_c( ds ), date_c( 2014, 12, 24 ) );
   expect_eq_( last_in_day_set_c( ds ), date_c( 2014, 12, 26 ) );

   remove_from_day_set_c( ds, date_c( 2014, 12, 25 ) );
   expect_at_c_( count_days_c( ds ) == 2 );
   expect_eq_( first_in_day_set_c( ds ), date_c( 2014, 12, 24 ) );
   expect_eq_( last_in_day_set_c( ds ), date_c( 2014, 12, 26 ) );

   release_c( ds );

   return finish_tap_c_();
}
