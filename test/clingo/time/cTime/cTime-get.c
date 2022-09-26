#include "clingo/lang/expect.h"
#include "clingo/time/cTime.h"

TEMP_SLICE_C_(
   test,
   {
      cTime time;
      cDate date;
      cDaytime daytime;
      cTzOffset tz;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( make_time_c( 2009, c_Nov, 10, 23, 12, 48, 123, utc_c() ),
          date_c( 2009, c_Nov, 10 ), daytime_c( 23, 12, 48, 123 ), utc_c() ),
      t_( make_time_c( 1983, c_Dec,  1,  2, 34, 56,   0, tz_c( +400 ) ),
          date_c( 1983, c_Dec, 1 ), daytime_c(  2, 34, 56, 0 ), tz_c( +400 ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 32 );

      cDate date = get_date_c( t->time );
      write_date_c_( rec, date );
      tap_descf_c( eq_date_c( date, t->date ), turn_into_cstr_c( rec ) );

      cDaytime dt = get_daytime_c( t->time );
      write_daytime_c_( rec, dt );
      tap_descf_c( eq_daytime_c( dt, t->daytime ), turn_into_cstr_c( rec ) );

      cTzOffset tz = get_tz_offset_c( t->time );
      write_tz_offset_c_( rec, tz );
      tap_descf_c( eq_tz_offset_c( tz, t->tz ), turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}
