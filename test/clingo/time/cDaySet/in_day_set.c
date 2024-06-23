#include "clingo/lang/expect.h"
#include "clingo/time/CDaySet.h"

int main( void )
{
   init_tap_c_();

   CDaySet* daySet = new_day_set_c();

   set_on_day_set_c( daySet, date_c( 2014, 2, 27 ) );
   set_on_day_set_c( daySet, date_c( 2014, 2, 13 ) );

   expect_at_c_( in_day_set_c( daySet, date_c( 2014, 2, 27 ) ) );
   expect_at_c_( not in_day_set_c( daySet, date_c( 2014, 2, 26 ) ) );

   release_c( daySet );

   return finish_tap_c_();
}
