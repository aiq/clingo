#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cColor c = from_cmyk_c_( 0.58f, 0.36f, 0.0f, 0.35f );
   expect_at_c_( eq_color_c( c, rgb_color_c( 0x466aa6 ) ) );

   return finish_tap_c_();
}