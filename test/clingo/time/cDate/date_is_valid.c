#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( !date_is_valid_c( date_c( 2011, c_Feb, 30 ) ) );
   expect_at_c_( !date_is_valid_c( date_c( 2012, 13, 8 ) ) );
   expect_at_c_(  date_is_valid_c( date_c( 2012, c_Apr, 8 ) ) );
   expect_at_c_( !date_is_valid_c( null_date_c() ) );

   return finish_tap_c_();
}
