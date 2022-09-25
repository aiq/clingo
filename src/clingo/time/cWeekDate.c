#include "clingo/time/cWeekDate.h"

#include "_/time/read_time_util.h"
#include "_/time/write_time_util.h"
#include "clingo/time/C_TimeFormats.h"
#include "clingo/time/cOrdinalDate.h"
#include "clingo/type/int8.h"
#include "clingo/type/int16.h"
#include "clingo/type/int32.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

int cmp_week_date_c( cWeekDate a, cWeekDate b )
{
   if ( a.year > b.year ) return 1;
   else if ( a.year < b.year ) return -1;

   if ( a.week > b.week ) return 1;
   else if ( a.week < b.week ) return -1;

   if ( a.day > b.day ) return 1;
   else if ( a.day < b.day ) return -1;

   return 0;
}

cWeekDate week_date_c( int64_t year, int64_t week, int64_t day )
{
   cWeekDate wd;
   if ( int64_to_int32_c( year, &(wd.year) ) and
        int64_to_int8_c( week, &(wd.week) ) and
        int64_to_weekday_c( day, &(wd.day) ) )
   {
      return wd;
   }

   return (cWeekDate){ INT32_MIN, INT8_MIN, c_Mon };
}

bool week_date_is_valid_c( cWeekDate wd )
{
   cYmd ymd = ymd_from_week_date_c( wd );
   return ymd_is_valid_c( ymd );
}

/*******************************************************************************
 from
*******************************************************************************/

cWeekDate week_date_from_ymd_c( cYmd ymd )
{
   c_Weekday wd = weekday_c( ymd.year, ymd.month, ymd.day );
   cOrdinalDate od = ordinal_date_from_ymd_c( ymd );
   int64_t const week = ( od.day - int8_c_( wd ) + 10 ) / 7;

   if ( week == 0 )
   {
      cYmd tmpYmd = (cYmd){ ymd.year-1, c_Dec, 28 };
      cWeekDate tmp = week_date_from_ymd_c( tmpYmd );
      return (cWeekDate){ tmp.year, tmp.week, wd };
   }
   else if ( week == 53 )
   {
      c_Weekday firstWd = weekday_c( ymd.year, 1, 1 );
      c_Weekday lastWd = weekday_c( ymd.year, 12, 31 );
      if ( firstWd != c_Thu and lastWd != c_Thu )
      {
         return (cWeekDate){ ymd.year+1, 1, wd };
      }
      return (cWeekDate){ ymd.year, int8_c_( week ), wd };
   }
   else if ( week < 53 )
   {
      return (cWeekDate){ ymd.year, int8_c_( week ), wd };
   }

   return (cWeekDate){ INT32_MIN, INT8_MIN, c_Mon };
}

cYmd ymd_from_week_date_c( cWeekDate wd )
{
   int16_t const woy = wd.week;
   int16_t const dow = int16_c_( wd.day );
   int16_t const dowJan04 = int16_c_( weekday_c( wd.year, 1, 4 ) );

   int16_t doy = ( woy * 7 ) + dow - ( dowJan04 + 3 );

   int32_t year = wd.year;
   if ( doy <= 0 )
   {
      year -= 1;
      doy += days_of_year_c( year );
   }
   else if ( doy > days_of_year_c( wd.year ) )
   {
      doy -= days_of_year_c( year );
      year += 1;
   }

   cOrdinalDate od = (cOrdinalDate){ year, doy };
   return ymd_from_ordinal_date_c( od );
}

/*******************************************************************************
 io
*******************************************************************************/

bool read_week_date_c( cScanner sca[static 1],
                       cWeekDate wd[static 1],
                       char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = C_IsoWeekDate;
   }
   cScanner* fmtSca = &cstr_scanner_c_( fmt );
   int64_t const oldPos = sca->pos;

   cWeekDate tmp = week_date_c( -1, -1, -1 );
   while ( fmtSca->space > 0 )
   {
      bool res = true;
      int64_t mark = fmtSca->pos;
      int64_t spaces = move_while_char_c( fmtSca, '_' ) ? fmtSca->pos - mark
                                                        : 0;

      mark = fmtSca->pos;
      if ( move_while_char_c( fmtSca, 'X' ) )
      {
         res = intl_read_year_c( sca, &tmp.year, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'W' ) )
      {
         res = intl_read_week_c( sca, &tmp.week, fmtSca->pos - mark );
      }
      else if ( move_while_char_c( fmtSca, 'E' ) )
      {
         res = intl_read_weekday_c( sca, &tmp.day, fmtSca->pos - mark );
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
   if ( not week_date_is_valid_c( tmp ) )
   {
      move_scanner_to_c( sca, oldPos );
      return set_scanner_error_c( sca, c_NotAbleToReadValue );
   }

   *wd = tmp;
   return true;
}

bool write_week_date_c( cRecorder rec[static 1],
                        cWeekDate wd,
                        char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = C_IsoWeekDate;
   }
   cScanner* fmtSca = &cstr_scanner_c_( fmt );
   int64_t const oldPos = rec->pos;

   while ( fmtSca->space > 0 )
   {
      bool res = true;
      int64_t mark = fmtSca->pos;
      if ( move_while_char_c( fmtSca, 'E' ) )
      {
         res = intl_write_weekday_c( rec, wd.day, fmtSca->pos - mark );
      }
      else if ( move_while_char_c( fmtSca, 'W' ) )
      {
         res = intl_write_week_c( rec, wd.week, fmtSca->pos - mark );
      }
      else if ( move_while_char_c( fmtSca, 'X' ) )
      {
         res = intl_write_year_c( rec, wd.year, fmtSca->pos - mark );
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
