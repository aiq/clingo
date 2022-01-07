#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   cDate date;
   cYmd res;

   date = date_c( 2011, c_Apr, 24 );
   res = as_ymd_c( date );
   expect_eq_c_( cmp_ymd_c( res, ymd_c( 2011, c_Apr, 24 ) ) );

   date = date_c( 2000, c_Jan, 1 );
   res = as_ymd_c( date );
   expect_eq_c_( cmp_ymd_c( res, ymd_c( 2000, c_Jan, 1 ) ) );

   return finish_tap_c_();
}
