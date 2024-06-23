#include "clingo/lang/expect.h"
#include "clingo/time/CDaySet.h"

int main( void )
{
   init_tap_c_();

   CDaySet* fullSet = new_day_set_c();

   cDate holiday = date_c( 2014, 12, 1 );
   set_date_period_on_day_set_c( fullSet, sized_date_period_c( holiday, 6 ) );
   set_on_day_set_c( fullSet, date_c( 2014, 12, 9 ) );

   CDaySet* subSet = new_day_set_c();
   set_many_on_day_set_c_( subSet, date_c( 2014, 12, 1 ),
                                   date_c( 2014, 12, 3 ),
                                   date_c( 2014, 12, 5 ),
                                   date_c( 2014, 12, 9 ) );

   expect_at_c_( days_in_day_set_c( fullSet, subSet ) );
   expect_at_c_( not days_in_day_set_c( subSet, fullSet ) );

   CDaySet* emptySet = new_day_set_c();
   expect_at_c_( days_in_day_set_c( fullSet, emptySet ) );

   release_all_c_( fullSet, subSet, emptySet );

   return finish_tap_c_();
}
