#include "clingo/lang/expect.h"
#include "clingo/color/cRgb24.h"

int main( void )
{
   init_tap_c_();

   cRgb24 c1 = { 90, 46, 75 };
   cRgb24 c2 = { 87, 75, 25 };

   expect_at_c_(  eq_rgb24_c( c1, c1 ) );
   expect_at_c_( !eq_rgb24_c( c1, c2 ) );

   return finish_tap_c_();
}