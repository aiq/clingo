#include "clingo/lang/expect.h"
#include "clingo/time/cTzOffset.h"

TEMP_SLICE_C_(
   test,
   {
      cTzOffset tz;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( tz_c( +430 ), "o", "+04:30" ),
      t_( tz_c( +430 ), "oo", "+04:30" ),
      t_( tz_c( +430 ), "oooo", "+0430" ),
      t_( tz_c( -700 ), "z", "-07" ),
      t_( tz_c( -700 ), "zz", "-07:00" ),
      t_( tz_c( -700 ), "zzzz", "-0700" ),
      t_( tz_c( 0 ), "o", "+00" ),
      t_( tz_c( 0 ), "z", "Z" )
   );

   each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 32 );

      bool res = write_tz_offset_c( rec, t->tz, t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_desc_c_( res, "{s:q} -> {rec}", t->fmt, rec );

   }

   return finish_tap_c_();
}
