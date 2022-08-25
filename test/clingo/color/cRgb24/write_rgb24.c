#include "clingo/lang/expect.h"
#include "clingo/color/cRgb24.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      cRgb24 rgb;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cRgb24 rgb = rgb24_c_( 108, 75, 54 );
   testSlice tests = slice_c_( test,
      t_( rgb, "", "{108;75;54}" ),
      t_( rgb, "dbg", "{ .red=108, .green=75, .blue=54 }" ),
      t_( rgb, "css", "#6C4B36" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 32 );

      bool res = write_rgb24_c( rec, t->rgb, t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_descf_c( res, "test: '%s' -> '%s'", t->fmt, turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}