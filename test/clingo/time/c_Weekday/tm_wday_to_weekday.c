#include "clingo/lang/expect.h"
#include "clingo/time/c_Weekday.h"

int main( void )
{
   init_tap_c_();

   c_Weekday wd;

   expect_c_( tm_wday_to_weekday_c( 0, &wd ) );
   expect_c_( wd == c_Sun );

   expect_c_( tm_wday_to_weekday_c( 4, &wd ) );
   expect_c_( wd == c_Thu );

   expect_c_( tm_wday_to_weekday_c( 6, &wd ) );
   expect_c_( wd == c_Sat );

   expect_c_( !tm_wday_to_weekday_c( 7, &wd ) );

   return finish_tap_c_();
}
