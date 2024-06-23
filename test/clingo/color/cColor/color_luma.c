#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      cColor color;
      float exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( from_rgb24_c_( 100, 200, 30 ), 0.65f ),
      t_( cCONTRAST_COLOR_DARK_, 0.0f ),
      t_( cCONTRAST_COLOR_LIGHT_, 1.0f ),
      t_( from_hsl_c_( 90.0f, 1.0f, 0.5f ), 0.82f )
   );

   each_c_( test const*, t, tests )
   {
      float luma = color_luma_c( t->color );
      bool res = eq_float_c( luma, t->exp, 0.005 );
      expect_at_c_( res );
   }

   return finish_tap_c_();
}
