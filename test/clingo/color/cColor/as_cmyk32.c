#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cCmyk32 cmyk = as_cmyk32_c( rgb_color_c( 0x466aa6 ) );
   cCmyk32 exp = cmyk32_c_( 147, 92, 0, 89 );
   expect_c_( eq_cmyk32_c( cmyk, exp ) );

   return finish_tap_c_();
}