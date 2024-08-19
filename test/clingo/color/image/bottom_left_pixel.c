#include "clingo/color/image.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      cPixel a;
      cPixel b;
      cPixel exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( pixel_c_( 100, 200 ), pixel_c_( 500, 600 ), pixel_c_( 100, 600 ) ),
      t_( pixel_c_( 500, 600 ), pixel_c_( 100, 200 ), pixel_c_( 100, 600 ) ),
      t_( pixel_c_( 100, 600 ), pixel_c_( 500, 200 ), pixel_c_( 100, 600 ) ),
      t_( pixel_c_( 500, 200 ), pixel_c_( 100, 600 ), pixel_c_( 100, 600 ) )
   );

   for_each_c_( i, test const*, t, tests )
   {
      cPixel res = bottom_left_pixel_c( t->a, t->b );
      expect_block_c_( i, eq_pixel_c( res, t->exp ))
      {
         tap_exp_line_c_( "{i},{i}", t->exp.x, t->exp.y );
         tap_got_line_c_( "{i},{i}", res.x, res.y );
      }
   }

   return finish_tap_c_();
}