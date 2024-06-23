#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cColor c = from_cmyk32_c_( 148, 92, 0, 89 );
   expect_at_c_( eq_color_c( c, rgb_color_c( 0x466aa6 ) ) );

   return finish_tap_c_();
}