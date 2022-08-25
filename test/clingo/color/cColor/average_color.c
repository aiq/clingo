#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_DEF_C_(
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
      t_( base, rgb_color_c( 0x000000 ), rgb_color_c( 0x803300 ) ),
      t_( base, rgb_color_c( 0x333333 ), rgb_color_c( 0x994d1a ) ),
      t_( base, rgb_color_c( 0x666666 ), rgb_color_c( 0xb36633 ) ),
      t_( base, rgb_color_c( 0x999999 ), rgb_color_c( 0xcc804d ) ),
      t_( base, rgb_color_c( 0xcccccc ), rgb_color_c( 0xe69966 ) ),
      t_( base, rgb_color_c( 0xffffff ), rgb_color_c( 0xffb380 ) ),
      t_( base, rgb_color_c( 0xff0000 ), rgb_color_c( 0xff3300 ) ),
      t_( base, rgb_color_c( 0x00ff00 ), rgb_color_c( 0x80b300 ) ),
      t_( base, rgb_color_c( 0x0000ff ), rgb_color_c( 0x803380 ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cColor avg = average_color_c( t->a, t->b );
      bool res = eq_color_c( avg, t->exp );
      expect_c_( res );
   }

   return finish_tap_c_();
}
