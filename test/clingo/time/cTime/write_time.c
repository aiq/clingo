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

   testSlice tests = slice_c_( test,
      t_( make_time_c( 2006, c_Jan, 2, 15, 4, 5, 0, utc_c() ),
          C_Rfc3339Time, "2006-01-02T15:04:05Z" ),
      t_( make_time_c( 2021, c_Jun, 12, 0, 0, 0, 0, utc_c() ),
          "YY.MM.DD", "21.06.12" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 64 );

      bool res = write_time_c( rec, t->time, t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_descf_c( res, "%s -> %s", t->fmt, turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}
