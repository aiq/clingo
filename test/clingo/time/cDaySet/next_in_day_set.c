#include "clingo/lang/expect.h"
#include "clingo/time/CDaySet.h"

int main( void )
{
   init_tap_c_();

   CDaySet* daySet = new_day_set_c();
   cDate tmp;

   // try to get the next day in an empty day set
   tmp = next_in_day_set_c( daySet, date_c( 2014, 10, 20 ) );
   expect_c_( not date_is_valid_c( tmp ) );

   set_many_on_day_set_c_( daySet, date_c( 2014, 12, 1 ),
                                   date_c( 2014, 12, 6 ),
                                   date_c( 2014, 12, 7 ),
                                   date_c( 2014, 12, 23 ) );

   tmp = next_in_day_set_c( daySet, date_c( 2014, 10, 20 ) );
   expect_c_( eq_date_c( tmp, date_c( 2014, 12, 1 ) ) );

   tmp = next_in_day_set_c( daySet, date_c( 2014, 12, 1 ) );
   expect_c_( eq_date_c( tmp, date_c( 2014, 12, 6 ) ) );

   tmp = next_in_day_set_c( daySet, date_c( 2014, 12, 6 ) );
   expect_c_( eq_date_c( tmp, date_c( 2014, 12, 7 ) ) );

   tmp = next_in_day_set_c( daySet, date_c( 2014, 12, 7 ) );
   expect_c_( eq_date_c( tmp, date_c( 2014, 12, 23 ) ) );

   tmp = next_in_day_set_c( daySet, date_c( 2014, 12, 13 ) );
   expect_c_( eq_date_c( tmp, date_c( 2014, 12, 23 ) ) );

   tmp = next_in_day_set_c( daySet, date_c( 2014, 12, 23 ) );
   expect_c_( not date_is_valid_c( tmp ) );

   // try to get the next day after an invalid date
   tmp = next_in_day_set_c( daySet, null_date_c() );
   expect_c_( not date_is_valid_c( tmp ) );

   release_c( daySet );

   return finish_tap_c_();
}
