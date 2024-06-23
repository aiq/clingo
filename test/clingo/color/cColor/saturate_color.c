#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      cColor color;
      float amount;
      cColor exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( from_hsl_c_( 90.0f, 0.9f, 0.5f ), 0.1f, rgb_color_c( 0x80ff00 ) )
   );

   for_each_c_( i, test const*, t, tests )
   {
      cColor saturated = saturate_color_c( t->color, t->amount );
      bool res = eq_color_c( saturated, t->exp );
      expect_c_( i, res );
   }

   return finish_tap_c_();
}
