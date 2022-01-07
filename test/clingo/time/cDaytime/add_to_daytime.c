#include "clingo/lang/expect.h"
#include "clingo/time/cDaytime.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      cDaytime base;
      cDuration dur;
      cDaytime exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( daytime_c_( 20, 58,  0 ),   hours_c( 7 ), daytime_c_(  3, 58,  0 ) ),
      t_( daytime_c_(  3, 58,  0 ),  mins_c( -49 ), daytime_c_(  3,  9,  0 ) ),
      t_( daytime_c_( 15, 58,  0 ),    mins_c( 2 ), daytime_c_( 16,  0,  0 ) ),
      t_( daytime_c_( 16,  0,  0 ), mins_c( -100 ), daytime_c_( 14, 20,  0 ) ),
      t_( daytime_c_( 10, 39, 44 ),   secs_c( 23 ), daytime_c_( 10, 40,  7 ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cDaytime dt = add_to_daytime_c( t->base, t->dur );
      bool res = eq_daytime_c( dt, t->exp );
  
      cHmsn t = as_hmsn_c( dt ); 
      tap_descf_c( res, "%d:%d:%d", t.hour, t.min, t.sec );
   }

   return finish_tap_c_();
}
