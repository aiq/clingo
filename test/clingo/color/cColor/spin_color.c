#include "clingo/color/cColor.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      cColor color;
      float angle;
      cColor exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( from_hsl_c_( 10.0f, 0.9f, 0.5f ), 20.0f, rgb_color_c( 0xf27f0d ) ),
      t_( from_hsl_c_( 10.0f, 0.9f, 0.5f ), -20.0f, rgb_color_c( 0xf20d33 ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cColor spinned = spin_color_c( t->color, t->angle );
      bool res = eq_color_c( spinned, t->exp );
      expect_c_( res );
   }

   return finish_tap_c_();
}
