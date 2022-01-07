#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   expect_c_( date_weekday_c( date_c( 2012, c_Apr,  8 ) ) == c_Sun );
   expect_c_( date_weekday_c( date_c( 1949, c_May, 23 ) ) == c_Mon );
   expect_c_( date_weekday_c( date_c( 1789, c_Jul, 14 ) ) == c_Tue );
   expect_c_( date_weekday_c( date_c( 1892, c_Jan, 18 ) ) == c_Mon );
   expect_c_( date_weekday_c( date_c( 1989, c_Nov,  9 ) ) == c_Thu );

   return finish_tap_c_();
}
