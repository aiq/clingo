#include "clingo/lang/expect.h"
#include "clingo/time/C_TimeFormats.h"
#include "clingo/time/cTime.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      cTime time;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cTime time = make_time_c( 2006, c_Jan, 2, 15, 4, 5, 0, tz_c( -700 ) );
   testSlice tests = slice_c_( test,
   // date
      t_( time, C_DateFormat, "2006.01.02" ),
   // daytime
      t_( time, C_KitchenTime, " 3:04PM" ),
   // time
      t_( time, C_AnsiCTime,        "Mon Jan  2 15:04:05 2006" ),
      t_( time, C_Rfc882Time,       "02 Jan 06 15:04 -0700" ),
      t_( time, C_Rfc1123Time,      "Mon, 02 Jan 2006 15:04:05 -0700" ),
      t_( time, C_Rfc3339Time,      "2006-01-02T15:04:05-07:00" ),
      t_( time, C_Rfc3339TimeNano,  "2006-01-02T15:04:05.0-07:00" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 64 );

      bool res = write_time_c( rec, t->time, t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_descf_c( res, "'%s' -> '%s'", t->fmt, turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}
