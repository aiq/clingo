#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      cColor a;
      cColor b;
      cColor exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cColor base = rgb_color_c( 0xff6600 );
   testSlice tests = slice_c_( test,
      t_( base, rgb_color_c( 0x000000 ), rgb_color_c( 0xff0000 ) ),
      t_( base, rgb_color_c( 0x333333 ), rgb_color_c( 0xff2900 ) ),
      t_( base, rgb_color_c( 0x666666 ), rgb_color_c( 0xff5200 ) ),
      t_( base, rgb_color_c( 0x999999 ), rgb_color_c( 0xff7a00 ) ),
      t_( base, rgb_color_c( 0xcccccc ), rgb_color_c( 0xffa300 ) ),
      t_( base, rgb_color_c( 0xffffff ), rgb_color_c( 0xffcc00 ) ),
      t_( base, rgb_color_c( 0xff0000 ), rgb_color_c( 0xff0000 ) ),
      t_( base, rgb_color_c( 0x00ff00 ), rgb_color_c( 0xffcc00 ) ),
      t_( base, rgb_color_c( 0x0000ff ), rgb_color_c( 0xff0000 ) )
   );

   for_each_c_( i, test const*, t, tests )
   {
      cColor over = overlay_color_c( t->a, t->b );
      bool res = eq_color_c( over, t->exp );
      expect_c_( i, res );
   }

   return finish_tap_c_();
}
