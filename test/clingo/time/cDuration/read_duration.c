#include "clingo/io/read.h"
#include "clingo/lang/expect.h"
#include "clingo/time/cDuration.h"

TEMP_SLICE_C_(
   test,
   {
      char const* str;
      char const* fmt;
      cDuration exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "3d3m3.456789ms", "", duration_c( 72, 3, 0, 3456789 ) ),
      t_( "3d3m0.3456789s", "", duration_c( 72, 3, 0, 345678900 ) ),
      t_( "0W3D0H3M0.3S", "WDHM*U", duration_c( 72, 3, 0, 300000000 ) ),
      t_( "0W 3D 0H 3M 0.3S", "WW DD HH MM *U", duration_c( 72, 3, 0, 300000000 ) ),
      t_( "72h3m3.5s", "hm", duration_c( 72, 3, 0, 0 ) ),
      t_( "3s", "", secs_c( 3 ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->str );

      cDuration dur;
      bool res = read_duration_c( sca, &dur, t->fmt );
      res &= eq_c( cmp_duration_c( dur, t->exp ) );

      cRecorder* rec = &recorder_c_( 32 );
      write_duration_c_( rec, dur );
      tap_descf_c( res, "%s -> %s", t->fmt, turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}
