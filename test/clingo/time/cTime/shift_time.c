#include "clingo/lang/expect.h"
#include "clingo/time/cTime.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      cTime time;
      cTzOffset tz;
      cDate date;
      cDaytime daytime;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( make_time_c( 2021, c_Jun, 12, 21, 0, 0, 0, tz_c( -200 ) ),
          tz_c( +200 ), date_c( 2021, c_Jun, 13 ), daytime_c( 1, 0, 0, 0 ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cTime time = shift_time_c( t->time, t->tz );
      bool res = eq_date_c( get_date_c( time ), t->date ) and
                 eq_daytime_c( get_daytime_c( time ), t->daytime );

      cRecorder* rec = &recorder_c_( 32 );
      write_time_c_( rec, time );
      tap_descf_c( res, "%s", turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}
