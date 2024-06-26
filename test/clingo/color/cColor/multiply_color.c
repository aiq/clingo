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
      t_( base, rgb_color_c( 0x000000 ), rgb_color_c( 0x000000 ) ),
      t_( base, rgb_color_c( 0x333333 ), rgb_color_c( 0x331400 ) ),
      t_( base, rgb_color_c( 0x666666 ), rgb_color_c( 0x662900 ) ),
      t_( base, rgb_color_c( 0x999999 ), rgb_color_c( 0x993d00 ) ),
      t_( base, rgb_color_c( 0xcccccc ), rgb_color_c( 0xcc5200 ) ),
      t_( base, rgb_color_c( 0xffffff ), rgb_color_c( 0xff6600 ) ),
      t_( base, rgb_color_c( 0xff0000 ), rgb_color_c( 0xff0000 ) ),
      t_( base, rgb_color_c( 0x00ff00 ), rgb_color_c( 0x006600 ) ),
      t_( base, rgb_color_c( 0x0000ff ), rgb_color_c( 0x000000 ) )
   );

   for_each_c_( i, test const*, t, tests )
   {
      cColor mult = multiply_color_c( t->a, t->b );
      bool res = eq_color_c( mult, t->exp );
      expect_c_( i, res );
   }

   return finish_tap_c_();
}