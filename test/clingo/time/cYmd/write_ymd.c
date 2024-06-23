#include "clingo/io/write.h"
#include "clingo/lang/expect.h"
#include "clingo/lang/locale.h"
#include "clingo/time/cYmd.h"

TEMP_SLICE_C_(
   test,
   {
      cYmd ymd;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   set_locale_c( LC_TIME, "C" ); // For every system the same output

   cYmd ymd = ymd_c( 2013, c_Apr, 1 );
   cYmd yxd = { 2022, c_Dec+1, 7 };
   testSlice tests = slice_c_( test,
      t_( ymd, "YYYYMMDD", "20130401" ),
      t_( ymd, "YY-M-D", "13-4-1" ),
      t_( yxd, "YY-M-D", "22-13-7" )
   );

   each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 32 );

      bool res = write_ymd_c( rec, t->ymd, t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_desc_c_( rec, "test: {s} -> {s}", t->fmt, t->exp );
   }

   return finish_tap_c_();
}
