#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   cDate date = date_c( 2008, c_Sep, 26 );
   cWeekDate res = as_week_date_c( date );
   expect_eq_c_( cmp_week_date_c( res, week_date_c( 2008, 39, c_Fri ) ) );

   return finish_tap_c_();
}
