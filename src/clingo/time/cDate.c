#include "clingo/time/cDate.h"

#include "_/read_time_util.h"
#include "_/util.h"
#include "_/write_time_util.h"
#include "clingo/lang/algo.h"
#include "clingo/time/C_TimeFormats.h"
#include <time.h>

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

static const int64_t NullDateValue = INT64_MIN;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

cDate local_date_c( void )
{
   struct tm ptm;
   conv_to_local_time( time( NULL ), &ptm );
   return date_c( ptm.tm_year + 1900, ptm.tm_mon + 1, ptm.tm_mday );
}

cDate date_c( int64_t year, int64_t month, int64_t day )
{
   return from_ymd_c( ymd_c( year, month, day ) );
}

cDate null_date_c( void )
{
   return (cDate){ NullDateValue };
}

cDate utc_date_c( void )
{
   struct tm ptm;
   conv_to_utc_time( time( NULL ), &ptm );
   return date_c( ptm.tm_year + 1900, ptm.tm_mon + 1, ptm.tm_mday );
}

/*******************************************************************************
 from
*******************************************************************************/

cDate from_julian_day_c( int64_t jd )
{
   return (cDate){ jd };
}

cDate from_ordinal_date_c( cOrdinalDate od )
{
   cYmd ymd = ymd_from_ordinal_date_c( od );
   return from_ymd_c( ymd );
}

cDate from_week_date_c( cWeekDate wd )
{
   cYmd ymd = ymd_from_week_date_c( wd );
   return from_ymd_c( ymd );
}

cDate from_ymd_c( cYmd ymd )
{
   if ( not ymd_is_valid_c( ymd ) ) return null_date_c();

   int64_t const y = ( ymd.year < 0 ) ? ymd.year + 1
                                      : ymd.year;
   int64_t const m = ymd.month;
   int64_t const d = ymd.day;

   if ( gte_c( cmp_ymd_c( ymd, ymd_c( 1582, c_Oct, 15 ) ) ) )
   {
      // Gregorian calendar starting from October 15, 1582
      // Algorithm from Henry F. Fliegel and Thomas C. Van Flandern
      int64_t a = ( 1461 * ( y + 4800 + ( m - 14 ) / 12 ) ) / 4;
      int64_t b = ( 367 * ( m - 2 - 12 * ( ( m - 14 ) / 12 ) ) ) / 12;
      int64_t c = ( 3 * ( ( y + 4900 + ( m - 14 ) / 12 ) / 100 ) ) / 4;
      return (cDate){ a + b - c + d - 32075 };
   }
   else if ( lte_c( cmp_ymd_c( ymd, ymd_c( 1582, c_Oct, 4 ) ) ) )
   {
      // Julian calendar until October 4, 1582
      // Algorithm from Frequently Asked Questions about Calendars by Claus Toendering
      int64_t const a = ( 14 - m ) / 12;
      int64_t const b = ( 153 * ( m + ( 12 * a ) - 3) + 2 ) / 5;
      int64_t const c = ( y + 4800 - a ) * 1461 / 4;
      return (cDate){ b + c + d - 32083 };
   }
   else
   {
      // the day following October 4, 1582 is October 15, 1582
      return null_date_c();
   }
}

/*******************************************************************************
 as
*******************************************************************************/

int64_t as_julian_day_c( cDate date )
{
    return date._v;
}

cOrdinalDate as_ordinal_date_c( cDate date )
{
   return ordinal_date_from_ymd_c( as_ymd_c( date ) );
}

cWeekDate as_week_date_c( cDate date )
{
   return week_date_from_ymd_c( as_ymd_c( date ) );
}

cYmd as_ymd_c( cDate date )
{
   int64_t const jd = date._v;

   int64_t f = jd + 1401; // Julian calendar until October 4, 1582
   if ( jd >= 2299161 ) // Gregorian calendar starting from October 15, 1582
   {
      f += ( ( ( 4 * jd + 274277 ) / 146097 ) * 3 ) / 4 + -38;
   }

   int64_t e = 4 * f + 3;
   int64_t g = ( e % 1461 ) / 4;
   int64_t h = 5 * g + 2;

   int64_t d = ( h % 153 ) / 5 + 1;
   int64_t m = ( ( h / 153 + 2 ) % 12 ) + 1;
   int64_t y = ( e / 1461 ) - 4716 + ( 12 + 2 - m ) / 12;

   return ymd_c( y, m, d );
}

/*******************************************************************************

*******************************************************************************/

bool date_is_valid_c( cDate date )
{
   return date._v != NullDateValue;
}

int64_t date_day_of_year_c( cDate date )
{
   return as_ordinal_date_c( date ).day;
}

c_Weekday date_weekday_c( cDate date )
{
   cYmd ymd = as_ymd_c( date );
   return weekday_c( ymd.year, ymd.month, ymd.day );
}

cDate next_weekday_date_c( cDate date, c_Weekday wd )
{
   c_Weekday curr = date_weekday_c( date );

   int64_t days = ( wd > curr ) ? int64_c_( wd ) - int64_c_( curr )
                                : 7 + ( int64_c_( wd ) - int64_c_( curr ) );

   return add_days_to_date_c( date, days );
}

cDate prev_weekday_date_c( cDate date, c_Weekday wd )
{
   c_Weekday curr = date_weekday_c( date );

   int64_t days = ( wd < curr ) ? int64_c_( wd ) - int64_c_( curr )
                                : -7 + ( int64_c_( wd ) - int64_c_( curr ) );

   return add_days_to_date_c( date, days );
}

/*******************************************************************************

*******************************************************************************/

cDate add_days_to_date_c( cDate date, int64_t days )
{
   int64_t val = NullDateValue;
   iadd64_c( date._v, days, &val );
   return (cDate){ val };
}

cDate add_weeks_to_date_c( cDate date, int64_t weeks )
{
   return add_days_to_date_c( date, 7*weeks );
}

cDate add_months_to_date_c( cDate date, int64_t months )
{
   cYmd ymd = as_ymd_c( date );

   while ( months != 0 )
   {
      if ( months <= -12 )
      {
         ymd.year--;
         months += 12;
      }
      else if ( months >= 12 )
      {
         ymd.year++;
         months -= 12;
      }
      else if ( months < 0 )
      {
         ymd.month += months;
         months = 0;
         if ( ymd.month <= 0 )
         {
            --ymd.year;
            ymd.month += 12;
         }
      }
      else
      {
         ymd.month += months;
         months = 0;
         if ( ymd.month > 12 )
         {
            ++ymd.year;
            ymd.month -= 12;
         }
      }
   }

   int8_t max_days = days_per_month_c_( ymd.month, ymd.year );
   if ( ymd.day > max_days )
   {
      ymd.day = max_days;
   }

   return from_ymd_c( ymd );
}

cDate add_years_to_date_c( cDate date, int64_t years )
{
   cYmd ymd = as_ymd_c( date );
   ymd.year += years;

   int8_t max_days = days_per_month_c_( ymd.month, ymd.year );
   if ( ymd.day > max_days )
   {
      ymd.day = max_days;
   }

   return from_ymd_c( ymd );
}

/*******************************************************************************

*******************************************************************************/

int64_t days_between_dates_c( cDate a, cDate b )
{
   return b._v - a._v;
}

int64_t weeks_between_dates_c( cDate a, cDate b )
{
   return days_between_dates_c( a, b ) / 7;
}

int64_t months_between_dates_c( cDate a, cDate b )
{
   cYmd ay = as_ymd_c( a );
   cYmd by = as_ymd_c( b );

   int64_t months = int64_c_( by.month ) - int64_c_( ay.month );
   int64_t years = by.year - ay.year;

   if ( ( months < 0 ) and ( ay.day < by.day ) )
   {
      months += 1;
   }
   else if ( ( months > 0 ) and ( ay.day > by.day ) )
   {
      months -= 1;
   }

   return months + years * 12;
}

int64_t years_between_dates_c( cDate a, cDate b )
{
   cYmd ay = as_ymd_c( a );
   cYmd by = as_ymd_c( b );

   int64_t years = by.year - ay.year;

   if ( ( years < 0 ) and ( ay.month < by.month ) and ( ay.day < by.day ) )
   {
      years += 1;
   }
   else if ( ( years > 0 ) and ( ay.month > by.month ) && ( ay.day < by.day ) )
   {
      years -= 1;
   }

   return years;
}

/*******************************************************************************

*******************************************************************************/

extern inline int cmp_date_c( cDate a, cDate b );

extern inline bool eq_date_c( cDate a, cDate b );

cDate early_date_c( cDate a, cDate b )
{
   return lt_c( cmp_date_c( a, b ) ) ? a
                                     : b;
}

cDate late_date_c( cDate a, cDate b )
{
   return gt_c( cmp_date_c( a, b ) ) ? a
                                     : b;
}

/*******************************************************************************

   Write Date:
   -----------

   Month based:

   D - the day as number without a leading zero (1-31)
   DD - the day as number with a leading zero (01-31)
   DDD - the abbrevated day name (Mon - Sun). Uses QDate::shortDayName().
   DDDD - the long day name (Monday - Sunday). Uses QDate::longDayName().
   M - the month as number without a leading zero (1-12)
   MM - the month as number with a leading zero (01-12)
   MMM - the abbrevated month name (Jan - Dec). Uses QDate::shortMonthName().
   MMMM - the long month name (January - December). Uses QDate::longMonthName().
   YY - the year as two digit number (00-99)
   YYYY - the year as four digit number (0000-9999)

   Week based:

   E - one digit day of week, from 1 to 7 where 1 is Monday and 7 is Sunday
   EEE - Fri.
   EEEE - Friday
   WW - Week of Year W0 - W53
   WWW - Week of Year W00 - W53
   XX - 
   XXXX - 

   Ordinal based:

   C - 0 - 366
   CCC - 000 - 366
   YY - the year as two digit number (00-99)
   YYYY - the year as four digit number (0000-9999)

*******************************************************************************/

bool read_date_c( cScanner sca[static 1],
                  cDate date[static 1],
                  char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = C_DateFormat;
   }
   cScanner* fmtSca = &cstr_scanner_c_( fmt );
   int64_t const oldPos = fmtSca->pos;

   cOrdinalDate od = ordinal_date_c( -1, -1 );
   cWeekDate wd = week_date_c( -1, -1, -1 );
   cYmd ymd = ymd_c( -1, -1, -1 );
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
   if ( ymd_is_valid_c( ymd ) )
   {
      *date = from_ymd_c( ymd );
   }
   else if ( week_date_is_valid_c( wd ) )
   {
      *date = from_week_date_c( wd );
   }
   else if ( ordinal_date_is_valid_c( od ) )
   {
      *date = from_ordinal_date_c( od );
   }
   else
   {
      move_scanner_to_c( sca, oldPos );
      return set_scanner_error_c( sca, c_NotAbleToReadValue );
   }

   return true;
}

bool write_date_c( cRecorder rec[static 1],
                   cDate date,
                   char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = C_DateFormat;
   }
   cScanner* fmtSca = &cstr_scanner_c_( fmt );
   int64_t const oldPos = rec->pos;

   cOrdinalDate od = as_ordinal_date_c( date );
   cWeekDate wd = as_week_date_c( date );
   cYmd ymd = as_ymd_c( date );
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

static TAPE_C_( tape_func, cDate, write_date_c, do_deref_c_ )
cTape date_tape_c( cDate const* date )
{
   return (cTape){ .i=date, .f=tape_func };
}
