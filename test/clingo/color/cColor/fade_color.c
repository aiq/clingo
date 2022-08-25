#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      float alpha;
      float fade;
      float exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 0.5f, 0.1f, 0.6f ),
      t_( 0.5f, -0.1f, 0.4f )
   );

   cColor base = rgb_color_c( 0xaabbcc );
   for_each_c_( test const*, t, tests )
   {
      cColor c = set_color_alpha_c( base, t->alpha );
      c = fade_color_c( c, t->fade );
      float res = color_alpha_c( c );
      expect_c_( eq_float_c( res, t->exp, 0.005f ) );
   }

   return finish_tap_c_();
}