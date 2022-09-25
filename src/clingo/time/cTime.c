#include "clingo/time/cTime.h"

#include "_/time/util.h"
#include "_/time/read_time_util.h"
#include "_/time/write_time_util.h"
#include "clingo/time/C_TimeFormats.h"
#include "clingo/type/int32.h"
#include "clingo/io/write.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 definitions
*******************************************************************************/

static cDate const unixEpochDate = { 2440588 };

static int64_t const secsPerDay = 86400;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

cTime local_time_c( void )
{
   struct timespec ts;
   timespec_get( &ts, TIME_UTC );
   time_t offset = local_offset( ts.tv_sec );

   int32_t n;
   if ( not int64_to_int32_c( ts.tv_nsec, &n ) ) return null_time_c();

   int32_t z;
   if ( not int64_to_int32_c( offset, &z ) ) return null_time_c();

   return (cTime){ ts.tv_sec, n, z };
}

cTime make_time_c( int64_t year, int64_t month, int64_t day,
                   int64_t hour, int64_t min, int64_t sec, int64_t nsec,
                   cTzOffset tz )
{
   cDate date = date_c( year, month, day );
   cDaytime daytime = daytime_c( hour, min, sec, nsec );
   return time_c( date, daytime, tz );
}

cTime null_time_c( void )
{
   return (cTime){ INT64_MIN, 0, 0 };
}

cTime time_c( cDate d, cDaytime dt, cTzOffset tz )
{
   int64_t days = days_between_dates_c( unixEpochDate, d );
   int64_t daysSecs;
   if ( not imul64_c( days, secsPerDay, &daysSecs ) ) return null_time_c();

   cDuration daytimeDur = as_duration_c( dt );
   cDuration nsDur;
   cDuration sDur = truncate_duration_c( daytimeDur, C_Sec, &nsDur );

   int64_t s;
   if ( not iadd64_c( daysSecs, as_secs_c( sDur ), &s ) ) return null_time_c();

   int32_t n;
   if ( not int64_to_int32_c( as_nsecs_c( nsDur ), &n ) ) return null_time_c();

   s -= tz._v;

   return (cTime){ s, n, tz._v };
}

cTime utc_time_c( void )
{
   struct timespec ts;
   timespec_get( &ts, TIME_UTC );

   int32_t n;
   if ( not int64_to_int32_c( ts.tv_nsec, &n ) ) return null_time_c();

   return (cTime){ ts.tv_sec, n, 0 };
}

/*******************************************************************************
 timestamp
*******************************************************************************/

cTimestamp as_timestamp_c( cTime time )
{
   cDuration dur = add_duration_c( secs_c( time._s ), nsecs_c( time._n ) );
   return (cTimestamp){ dur._v };
}

cTime from_timestamp_c( cTimestamp ts )
{
   if ( not timestamp_is_valid_c( ts ) ) return null_time_c();

   cDuration nsec;
   cDuration sec = truncate_duration_c( nsecs_c( ts._v ), C_Sec, &nsec );

   int32_t n;
   if ( not int64_to_int32_c( nsec._v, &n ) ) return null_time_c();

   return (cTime){ as_secs_c( sec ), n, 0 };
}

/*******************************************************************************
 get
*******************************************************************************/

cDate get_date_c( cTime time )
{
   time._s += time._z;
   int64_t days = time._s / secsPerDay;
   return add_days_to_date_c( unixEpochDate, days );
}

cDaytime get_daytime_c( cTime time )
{
   time._s += time._z;
   int64_t secs = time._s % secsPerDay;
   cDuration dur = duration_c( 0, 0, secs, time._n );
   return from_duration_c( dur );
}

cHmsn get_hmsn_c( cTime time )
{
   return as_hmsn_c( get_daytime_c( time ) );
}

cOrdinalDate get_ordinal_date_c( cTime time )
{
   return as_ordinal_date_c( get_date_c( time ) );
}

cTzOffset get_tz_offset_c( cTime time )
{
   return (cTzOffset){ time._z };
}

cWeekDate get_week_date_c( cTime time )
{
   return as_week_date_c( get_date_c( time ) );
}

cYmd get_ymd_c( cTime time )
{
   return as_ymd_c( get_date_c( time ) );
}

/*******************************************************************************
 add
*******************************************************************************/

cTime add_to_time_c( cTime time, cDuration dur )
{
   cDuration nsec;
   cDuration sec = truncate_duration_c( dur, C_Sec, &nsec );
   time._s = as_secs_c( sec );

   nsec = add_duration_c( nsec, (cDuration){ time._z } );
   sec = truncate_duration_c( nsec, C_Sec, &nsec );
   time._s = as_secs_c( sec );
   time._n = int32_c_( as_nsecs_c( sec ) );

   return time;
}

cDuration between_times_c( cTime a, cTime b )
{
   a._z = 0;
   b._z = 0;

   cDate aD = get_date_c( a );
   cDate bD = get_date_c( b );
   cDuration days = days_c( days_between_dates_c( aD, bD ) );

   cDaytime aDt = get_daytime_c( a );
   cDaytime bDt = get_daytime_c( b );
   cDuration dur = between_daytimes_c( aDt, bDt );

   return add_duration_c( days, dur );
}

cTime shift_time_c( cTime time, cTzOffset tz )
{
   time._z = tz._v;
   return time;
}

/*******************************************************************************
 cmp
*******************************************************************************/

int cmp_time_c( cTime a, cTime b )
{
   return ( a._s != b._s ) ? cmp_int64_c( a._s, b._s )
                           : cmp_int32_c( a._n, b._n );
}

cTime early_time_c( cTime a, cTime b )
{
   return lt_c( cmp_time_c( a, b ) ) ? a
                                     : b;
}

extern inline bool eq_time_c( cTime a, cTime b );

cTime late_time_c( cTime a, cTime b )
{
   return gt_c( cmp_time_c( a, b ) ) ? a
                                     : b;
}

bool time_is_valid_c( cTime time )
{
   return diff_c(cmp_time_c(time, null_time_c()));
}

/*******************************************************************************
 io
*******************************************************************************/

bool read_time_c( cScanner sca[static 1],
                  cTime time[static 1],
                  char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = C_TimeFormat;
   }
   cScanner* fmtSca = &cstr_scanner_c_( fmt );
   int64_t const oldPos = sca->pos;

   cOrdinalDate od = ordinal_date_c( -1, -1 );
   cWeekDate wd = week_date_c( -1, -1, -1 );
   cYmd ymd = ymd_c( -1, -1, -1 );
   cHmsn hmsn = hmsn_c( 0, 0, 0, 0 );
   cTzOffset tz = utc_c();
   bool pm = false;
   while ( fmtSca->space > 0 )
   {
      bool res = true;
      int64_t mark = sca->pos;
      int64_t spaces = move_while_char_c( fmtSca, '_' ) ? fmtSca->pos - mark
                                                        : 0;

      mark = sca->pos;
      if ( move_while_char_c( fmtSca, 'C' ) ) //------------------------------ C
      {
         int64_t n = fmtSca->pos - mark;
         res = intl_read_day_of_year_c( sca, &od.day, n, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'D' ) ) //------------------------- D
      {
         res = intl_read_day_c( sca, &ymd.day, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'E' ) ) //------------------------- E
      {
         res = intl_read_weekday_c( sca, &wd.day, fmtSca->pos - mark );
      }
      else if ( move_while_char_c( fmtSca, 'M' ) ) //------------------------- M
      {
         res = intl_read_month_c( sca, &ymd.month, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'W' ) ) //------------------------- W
      {
         res = intl_read_week_c( sca, &wd.week, fmtSca->pos - mark );
      }
      else if ( move_while_char_c( fmtSca, 'X' ) ) //------------------------- X
      {
         res = intl_read_year_c( sca, &wd.year, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'Y' ) ) //------------------------- Y
      {
         res = intl_read_year_c( sca, &ymd.year, fmtSca->pos - mark, spaces );
         od.year = ymd.year;
      }
      else if ( move_while_char_c( fmtSca, 'h' ) ) //------------------------- h
      {
         res = intl_read_hour_c( sca, &hmsn.hour, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'k' ) ) //------------------------- k
      {
         int64_t n = fmtSca->pos - mark;
         res = intl_read_kitchen_hour_c( sca, &hmsn.hour, n, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'm' ) ) //------------------------- m
      {
         res = intl_read_min_c( sca, &hmsn.min, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 's' ) ) //------------------------- s
      {
         res = intl_read_sec_c( sca, &hmsn.sec, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'i' ) ) //------------------------- i
      {
         res = intl_read_isec_c( sca, &hmsn.nsec, fmtSca->pos - mark );
         hmsn.nsec *= 1000*1000;
      }
      else if ( move_while_char_c( fmtSca, 'u' ) ) //------------------------- u
      {
         res = intl_read_usec_c( sca, &hmsn.nsec, fmtSca->pos - mark );
         hmsn.nsec *= 1000;
      }
      else if ( move_while_char_c( fmtSca, 'n' ) ) //------------------------- n
      {
         res = intl_read_nsec_c( sca, &hmsn.nsec, fmtSca->pos - mark );
      }
      else if ( move_if_chars_c_( fmtSca, "ap" ) or
                move_if_chars_c_( fmtSca, "AP" ) )
      {
         res = intl_read_ap_c( sca, &pm );
      }
      else if ( move_while_char_c( fmtSca, 'o' ) ) //------------------------- o
      {
         res = intl_read_offset_c( sca, &tz, fmtSca->pos - mark, false );
      }
      else if ( move_while_char_c( fmtSca, 'z' ) ) //------------------------- z
      {
         res = intl_read_offset_c( sca, &tz, fmtSca->pos - mark, true );
      }
      else
      {
         res = intl_read_time_seperator_c( sca, fmtSca );
      }

      if ( not res )
      {
         move_scanner_to_c( sca, oldPos );
         return false;
      }
   }
   if ( pm )
   {
      hmsn.hour += 12;
   }
   bool hmsnOk = hmsn_is_valid_c( hmsn );
   if ( ymd_is_valid_c( ymd ) and hmsnOk )
   {
      *time = time_c( from_ymd_c( ymd ), from_hmsn_c( hmsn ), tz );
   }
   else if ( week_date_is_valid_c( wd ) and hmsnOk )
   {
      *time = time_c( from_week_date_c( wd ), from_hmsn_c( hmsn ), tz );
   }
   else if ( ordinal_date_is_valid_c( od ) and hmsnOk )
   {
      *time = time_c( from_ordinal_date_c( od ), from_hmsn_c( hmsn ), tz );
   }
   else
   {
      move_scanner_to_c( sca, oldPos );
      return set_scanner_error_c( sca, c_NotAbleToReadValue );
   }

   return true;
}

bool write_time_c( cRecorder rec[static 1],
                   cTime time,
                   char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = C_TimeFormat;
   }
   cScanner* fmtSca = &cstr_scanner_c_( fmt );
   int64_t const oldPos = rec->pos;

   cHmsn hmsn = get_hmsn_c( time );
   cYmd ymd = get_ymd_c( time );
   cOrdinalDate od = ordinal_date_from_ymd_c( ymd );
   cWeekDate wd = week_date_from_ymd_c( ymd );
   while ( fmtSca->space > 0 )
   {
      bool res = true;
      int64_t mark = fmtSca->pos;
      int64_t spaces = move_while_char_c( fmtSca, '_' ) ? fmtSca->pos - mark
                                                        : 0;

      mark = fmtSca->pos;
      if ( move_while_char_c( fmtSca, 'C' ) ) //------------------------------ C
      {
         int64_t n = fmtSca->pos - mark;
         res = intl_write_day_of_year_c( rec, od.day, n, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'D' ) ) //------------------------- D
      {
         res = intl_write_day_c( rec, ymd.day, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'E' ) ) //------------------------- E
      {
         res = intl_write_weekday_c( rec, wd.day, fmtSca->pos - mark );
      }
      else if ( move_while_char_c( fmtSca, 'M' ) ) //------------------------- M
      {
         res = intl_write_month_c( rec, ymd.month, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'W' ) ) //------------------------- W
      {
         res = intl_write_week_c( rec, wd.week, fmtSca->pos - mark );
      }
      else if ( move_while_char_c( fmtSca, 'X' ) ) //------------------------- X
      {
         res = intl_write_year_c( rec, wd.year, fmtSca->pos - mark );
      }
      else if ( move_while_char_c( fmtSca, 'Y' ) ) //------------------------- Y
      {
         res = intl_write_year_c( rec, ymd.year, fmtSca->pos - mark );
      }
      else if ( move_while_char_c( fmtSca, 'h' ) ) //------------------------- h
      {
         res = intl_write_hour_c( rec, hmsn.hour, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'k' ) ) //------------------------- k
      {
         int64_t n = fmtSca->pos - mark;
         res = intl_write_kitchen_hour_c( rec, hmsn.hour, n, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'm' ) ) //------------------------- m
      {
         res = intl_write_min_c( rec, hmsn.min, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 's' ) ) //------------------------- s
      {
         res = intl_write_sec_c( rec, hmsn.sec, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'i' ) ) //------------------------- i
      {
         int64_t const msecs = to_time_unit_c( hmsn.nsec, C_Nsec, C_Msec );
         res = intl_write_msec_c( rec, msecs, fmtSca->pos - mark );
      }
      else if ( move_while_char_c( fmtSca, 'u' ) ) //------------------------- u
      {
         int64_t const usecs = to_time_unit_c( hmsn.nsec, C_Nsec, C_Usec );
         res = intl_write_usec_c( rec, usecs, fmtSca->pos - mark );
      }
      else if ( move_while_char_c( fmtSca, 'n' ) ) //------------------------- n
      {
         res = intl_write_nsec_c( rec, hmsn.nsec, fmtSca->pos - mark );
      }
      else if ( move_if_chars_c_( fmtSca, "ap" ) ) //------------------------ ap
      {
         char const* val = ( hmsn.hour >= 12 ) ? "pm"
                                               : "am";
         res = record_chars_c_( rec, val );
      }
      else if ( move_if_chars_c_( fmtSca, "AP" ) ) //------------------------ AP
      {
         char const* val = ( hmsn.hour >= 12 ) ? "PM"
                                               : "AM";
         res = record_chars_c_( rec, val );
      }
      else if ( move_while_char_c( fmtSca, 'o' ) ) //------------------------- o
      {
         int64_t n = fmtSca->pos - mark;
         res = intl_write_offset_c( rec, get_tz_offset_c( time ), n, false );
      }
      else if ( move_while_char_c( fmtSca, 'z' ) ) //------------------------- z
      {
         int64_t n = fmtSca->pos - mark;
         res = intl_write_offset_c( rec, get_tz_offset_c( time ), n , true );
      }
      else
      {
         res = intl_write_time_seperator_c( rec, fmtSca );
      }

      if ( not res )
      {
         move_recorder_to_c( rec, oldPos );
         return false;
      }
   }

   return true;
}
