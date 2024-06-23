#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      cColor color;
      cColor extra;
      float weight;
      cColor exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_(
         rgb_color_c( 0xff0000 ), rgb_color_c( 0x0000ff ), 0.5f,
         rgb_color_c( 0x800080 )
      ),
      t_(
         rgba_color_c( 0x640000ff ), rgba_color_c( 0x00640080 ), 0.5f,
         rgba_color_c( 0x4b1900c0 )
      ),
      t_(
         rgba_color_c( 0x640000ff ), rgba_color_c( 0x00640080 ), 0.25f,
         rgba_color_c( 0x323200a0 )
      )
   );

   for_each_c_( i, test const*, t, tests )
   {
      cColor mixed = mix_color_c( t->color, t->extra, t->weight );
      bool res = eq_color_c( mixed, t->exp );
      expect_c_( i, res );
   }

   return finish_tap_c_();
}
