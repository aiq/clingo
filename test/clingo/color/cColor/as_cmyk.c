#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cCmyk cmyk = as_cmyk_c( rgb_color_c( 0x466aa6 ) );
   cCmyk exp = cmyk_c_( 0.578f, 0.361f, 0.0f, 0.349f );
   expect_c_( eq_cmyk_c( cmyk, exp, 0.0005f ) );

   return finish_tap_c_();
}