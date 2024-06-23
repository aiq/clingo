#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      cColor color;
      cColor other;
      cColor exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cColor base = rgb_color_c( 0xff6600 );
   testSlice tests = slice_c_( test,
      t_( base, rgb_color_c( 0x000000 ), rgb_color_c( 0xff6600 ) ),
      t_( base, rgb_color_c( 0x333333 ), rgb_color_c( 0xcc9933 ) ),
      t_( base, rgb_color_c( 0x666666 ), rgb_color_c( 0x99cc66 ) ),
      t_( base, rgb_color_c( 0x999999 ), rgb_color_c( 0x66ff99 ) ),
      t_( base, rgb_color_c( 0xcccccc ), rgb_color_c( 0x33cccc ) ),
      t_( base, rgb_color_c( 0xffffff ), rgb_color_c( 0x0099ff ) ),
      t_( base, rgb_color_c( 0xff0000 ), rgb_color_c( 0x006600 ) ),
      t_( base, rgb_color_c( 0x00ff00 ), rgb_color_c( 0xff9900 ) ),
      t_( base, rgb_color_c( 0x0000ff ), rgb_color_c( 0xff66ff ) )
   );

   for_each_c_( i, test const*, t, tests )
   {
      cColor neg = negation_color_c( t->color, t->other );
      bool res = eq_color_c( neg, t->exp );
      expect_c_( i, res );
   }

   return finish_tap_c_();
}
