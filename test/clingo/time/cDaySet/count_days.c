#include "clingo/lang/expect.h"
#include "clingo/time/CDaySet.h"

int main( void )
{
   init_tap_c_();

   CDaySet* ds = new_day_set_c();

   expect_c_( day_set_is_empty_c( ds ) );
   expect_c_( count_days_c( ds ) == 0 );

   expect_c_( set_on_day_set_c( ds, date_c( 2014, 10, 3 ) ) );

   expect_c_( count_days_c( ds) == 1 );

   release_c( ds );

   return finish_tap_c_();
}
