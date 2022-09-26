#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      cColor base;
      cColor dark;
      cColor light;
      float threshold;
      cColor exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_(
         rgb_color_c( 0x222222 ), rgb_color_c( 0x101010 ),
         cCONTRAST_COLOR_LIGHT_, cCONTRAST_COLOR_THRESHOLD_,
         cCONTRAST_COLOR_LIGHT_
      ),
      t_(
         rgb_color_c( 0x222222 ), rgb_color_c( 0x101010 ),
         rgb_color_c( 0xdddddd ), cCONTRAST_COLOR_THRESHOLD_,
         rgb_color_c( 0xdddddd )
      ),
      t_(
         from_hsl_c_( 90.0f, 1.0f, 0.5f ), cCONTRAST_COLOR_DARK_,
         cCONTRAST_COLOR_LIGHT_, 0.4f,
         cCONTRAST_COLOR_DARK_
      ),
      t_(
         from_hsl_c_( 90.0f, 1.0f, 0.5f ), cCONTRAST_COLOR_DARK_,
         cCONTRAST_COLOR_LIGHT_, 0.6f,
         cCONTRAST_COLOR_LIGHT_
      )
   );

   for_each_c_( test const*, t, tests )
   {
      cColor c = contrast_color_c( t->base, t->dark, t->light, t->threshold );
      bool res = eq_color_c( c, t->exp );
      expect_c_( res );
   }

   return finish_tap_c_();
}