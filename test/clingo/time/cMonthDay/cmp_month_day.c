#include "clingo/lang/expect.h"
#include "clingo/time/cMonthDay.h"

int main( void )
{
   init_tap_c_();

   cMonthDay a = month_day_c( c_Aug, 6 );
   cMonthDay b = a;
   expect_c_( eq_c( cmp_month_day_c( a, b ) ) );

   b.day = 7;
   expect_c_( diff_c( cmp_month_day_c( a, b ) ) );

   return finish_tap_c_();
}
