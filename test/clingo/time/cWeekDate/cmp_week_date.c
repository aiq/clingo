#include "clingo/lang/expect.h"
#include "clingo/time/cWeekDate.h"

int main( void )
{
   init_tap_c_();

   cWeekDate a = week_date_c( 2014, 31, c_Mon );
   cWeekDate b = week_date_c( 2014, 31, c_Mon );
   cWeekDate c = week_date_c( 2014, 31, c_Fri );

   expect_eq_c_( cmp_week_date_c( a, b ) );
   expect_lt_c_( cmp_week_date_c( a, c ) );

   return finish_tap_c_();
}
