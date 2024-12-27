#include "clingo/lang/expect.h"
#include "clingo/io/write.h"
#include "clingo/time/c_Month.h"
#include "clingo/time/c_Weekday.h"
#include "clingo/time/cDate.h"
#include "clingo/time/CDaySet.h"
#include "clingo/time/cDaytime.h"
#include "clingo/time/cDuration.h"
#include "clingo/time/cHmsn.h"
#include "clingo/time/cMonthDay.h"
#include "clingo/time/cOrdinalDate.h"
#include "clingo/time/cTime.h"
#include "clingo/time/cTzOffset.h"
#include "clingo/time/cWeekDate.h"
#include "clingo/time/cYmd.h"

TEMP_SLICE_C_(
   test,
   {
      cTape tape;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   CDaySet* em2024 = new_day_set_c();
   set_date_period_on_day_set_c( em2024, date_period_c( date_c( 2024, c_Jun, 14 ),
                                                        date_c( 2024, c_Jun, 26 ) ) );
   set_date_period_on_day_set_c( em2024, date_period_c( date_c( 2024, c_Jun, 29 ),
                                                        date_c( 2024, c_Jul,  2 ) ) );
   set_many_on_day_set_c_( em2024, date_c( 2024, c_Jul,  5 ),
                                   date_c( 2024, c_Jul,  6 ),
                                   date_c( 2024, c_Jul,  9 ),
                                   date_c( 2024, c_Jul, 10 ),
                                   date_c( 2024, c_Jul, 14 ) );

   testSlice tests = slice_c_( test,
      t_( month_tape_c_( c_Nov ), "{:MMMM}", "November" ),
      t_( weekday_tape_c_( c_Fri ), "{}", "Fri" ),
      t_( date_tape_c_( date_c( 2013, c_Apr, 1 ) ), "{:YY-MM-DD}", "13-04-01" ),
      t_( day_set_tape_c( em2024 ), "{:zip}", "2024-06-14(13i2z4i2z2i2z2i3z+)" ),
      t_( daytime_tape_c_( daytime_c( 15, 9, 0, 0 ) ), "{:_k:mmAP}", " 3:09PM" ),
      t_( duration_tape_c_( duration_c( 72, 3, 0, 3456789 ) ), "{}", "3d3m3.456789ms" ),
      t_( hmsn_tape_c_( hmsn_c( 18, 3, 12, 10234567 ) ), "{:h:m:s}", "18:3:12" ),
      t_( month_day_tape_c_( month_day_c( 12, 1 ) ), "{:MMM. D}", "Dec. 1" ),
      t_( ordinal_date_tape_c_( ordinal_date_c( 2014, 23 ) ), "{:CCC/YY}", "023/14" ),
      t_( time_tape_c_( make_time_c( 2006, c_Jan, 2, 15, 4, 5, 0, utc_c() ) ), "{:YY.MM.DD hh:mmz}", "06.01.02 15:04Z" ),
      t_( tz_offset_tape_c_( tz_c( +130 ) ), "{:oooo}", "+0130" ),
      t_( week_date_tape_c_( week_date_c( 2001, 7, c_Mon ) ), "{:XX WW EEE}", "01 W7 Mon" ),
      t_( ymd_tape_c_( ymd_c( 1954, c_Aug, 6 ) ), "{:YY/MM/DD}", "54/08/06" )
   );

   for_each_c_( i, test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 1024 );

      bool res = write_c_( rec, t->fmt, t->tape );
      res &= recorded_is_c( rec, t->exp );

      expect_c_( i, res );
   }

   release_all_c_( em2024 );

   return finish_tap_c_();
}