#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   cDate res = from_ymd_c( ymd_c( 2012, c_Apr, 8 ) );
   expect_c_( eq_date_c( res, date_c( 2012, c_Apr, 8 ) ) );

   return finish_tap_c_();
}
