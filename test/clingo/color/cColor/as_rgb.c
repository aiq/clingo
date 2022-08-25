#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cRgb rgb = as_rgb_c( rgb_color_c( 0x456aa6 ) );
   cRgb exp = rgb_c_( 0.271f, 0.416f, 0.651f );
   expect_c_( eq_rgb_c( rgb, exp, 0.0005f ) );

   return finish_tap_c_();
}