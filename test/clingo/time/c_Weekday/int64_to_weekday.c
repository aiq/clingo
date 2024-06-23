#include "clingo/lang/expect.h"
#include "clingo/time/c_Weekday.h"

int main( void )
{
   init_tap_c_();

   c_Weekday wd;

   expect_at_c_( int64_to_weekday_c( 1, &wd ) );
   expect_at_c_( wd == c_Mon );

   expect_at_c_( int64_to_weekday_c( 4, &wd ) );
   expect_at_c_( wd == c_Thu );

   expect_at_c_( int64_to_weekday_c( 7, &wd ) );
   expect_at_c_( wd == c_Sun );

   expect_at_c_( !int64_to_weekday_c( 8, &wd ) );

   return finish_tap_c_();
}
