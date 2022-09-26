#include "clingo/lang/expect.h"
#include "clingo/time/cDuration.h"

TEMP_SLICE_C_(
   test,
   {
      cDuration dur;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cDuration dur = duration_c( 72, 3, 0, 3456789 );
   cDuration max = C_MaxDuration;

   testSlice tests = slice_c_( test,
      t_( dur, "", "3d3m3.456789ms" ),
      t_( dur, "WWDDHHMMSS.I", "0W3D0H3M0.003S" ),
      t_( dur, "WW DD HH MM SS.I", "0W 3D 0H 3M 0.003S" ),
      t_( dur, "hmss.n", "72h3m0.003456789s" ),
      t_( dur, "ww", "0w" ),
      t_( dur, "w", "" ),
      t_( max, "wwddhhmmss.n", "15250w1d23h47m16.854775807s" ),
      t_( invert_duration_c( max ), "", "-15250w1d23h47m16.854775807s" ),
      t_( max, "w", "15250w" ),
      t_( max, "d", "106751d" ),
      t_( max, "h", "2562047h" ),
      t_( max, "m", "153722867m" ),
      t_( max, "s", "9223372036s" ),
      t_( max, "ss.i", "9223372036.854s" ),
      t_( max, "ss.u", "9223372036.854775s" ),
      t_( max, "ss.n", "9223372036.854775807s" ),
      t_( max, "*U", "9223372036.854775807S" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 64 );

      bool res = write_duration_c( rec, t->dur, t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_descf_c( res, "'%s' -> '%s'", t->fmt, turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}
