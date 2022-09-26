#include "clingo/lang/expect.h"
#include "clingo/time/cDuration.h"

TEMP_SLICE_C_(
   test,
   {
      cDuration a;
      cDuration b;
      cDuration exp;
      char const* desc;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // days
      t_( duration_c( 22*24, 14, 3, 0 ), days_c( 2 ),
          duration_c( 24*24, 14, 3, 0 ), "add 2d" ),
      t_( duration_c( 22*24, 14, 3, 0 ), days_c( -20 ),
          duration_c( 2*24, 14, 3, 0 ), "add -20d" ),
   // hours
      t_( duration_c( 126, 4, 24, 0 ), hours_c( 1 ),
          duration_c( 127, 4, 24, 0 ), "add 1h" ),
      t_( duration_c( 126, 4, 24, 0 ), hours_c( -5 ),
          duration_c( 121, 4, 24, 0 ), "add -5h" ),
      t_( duration_c( 0, 4, 24, 0 ), hours_c( -10 ),
          duration_c( -9, -55, -36, 0 ), "add -10h" ),
   // mins
      t_( duration_c( 13, 5, 14, 0 ), mins_c( 50 ),
          duration_c( 13, 55, 14, 0 ), "add 50m" ),
      t_( duration_c( 13, 5, 14, 0 ), mins_c( -6 ),
          duration_c( 12, 59, 14, 0 ), "add -6m" ),
      t_( duration_c( 1, 5, 14, 0 ), mins_c( -120 ),
          duration_c( 0, -54, -46, 0 ), "add -120m" ),
   // secs
      t_( duration_c( 1, 4, 24, 0 ), secs_c( 3 ),
          duration_c( 1, 4, 27, 0 ), "add 3s" ),
      t_( duration_c( 1, 0, 24, 0 ), secs_c( -30 ),
          duration_c( 0, 59, 54, 0 ), "add -30s" )
   );

   for_each_c_( test const*, t, tests )
   {
      cDuration dur = add_duration_c( t->a, t->b );

      tap_desc_c( eq_duration_c( dur, t->exp ), t->desc );
   }

   return finish_tap_c_();
}
