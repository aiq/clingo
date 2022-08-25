#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cColor black = rgb_color_c( 0x000000 );
   cColor white = rgb_color_c( 0xffffff );

   expect_c_(  eq_color_c( black, black ) );
   expect_c_( !eq_color_c( black, white ) );

   return finish_tap_c_();
}