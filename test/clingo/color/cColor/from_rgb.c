#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cColor c = from_rgb_c_( 0.271f, 0.416f, 0.651f );
   expect_at_c_( eq_color_c( c, rgb_color_c( 0x456aa6 ) ) );

   return finish_tap_c_();
}