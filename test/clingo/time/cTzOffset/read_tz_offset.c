#include "clingo/lang/expect.h"
#include "clingo/time/cTzOffset.h"

TEMP_SLICE_C_(
   test,
   {
      char const* str;
      char const* fmt;
      cTzOffset exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "+04:30", "o", tz_c( +430 ) ),
      t_( "+04:30", "oo", tz_c( +430 ) ),
      t_( "+0430", "oooo", tz_c( +430 ) ),
      t_( "-07", "z", tz_c( -700 ) ),
      t_( "-07:00", "zz", tz_c( -700 ) ),
      t_( "-0700", "zzzz", tz_c( -700 ) ),
      t_( "+00", "o", tz_c( 0 ) ),
      t_( "Z", "z", tz_c( 0 ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->str );

      cTzOffset tz;
      bool res = read_tz_offset_c( sca, &tz, t->fmt );
      res &= eq_c( cmp_tz_offset_c( tz, t->exp ) );

      tap_descf_c( res, "test: %s with %s", t->str, t->fmt );
   }

   return finish_tap_c_();
}
