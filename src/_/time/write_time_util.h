#ifndef CLINGO_INTERN_WRITE_TIME_UTIL_H
#define CLINGO_INTERN_WRITE_TIME_UTIL_H

#include "clingo/io/c_ImpExpError.h"
#include "clingo/io/write.h"
#include "clingo/io/write_type.h"
#include "clingo/time/c_Month.h"
#include "clingo/time/c_Weekday.h"
#include "clingo/time/cTzOffset.h"
#include "clingo/time/cYmd.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 util
*******************************************************************************/

inline bool intl_write_xsec_c( cRecorder rec[static 1],
                               int64_t val,
                               bool trim,
                               char const fmt[static 1] )
{
   cRecorder* r = &recorder_c_( 32 );
   recordf_c( r, fmt, val );
   cChars cs = recorded_chars_c( r );
   if ( trim )
   {
      cs = trim_any_char_right_c_( cs, "0" );
      if ( is_empty_c_( cs ) )
      {
         cs = c_c( "0" );
      }
   }
   return record_chars_c( rec, cs )
      ? true
      : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

inline bool intl_write_time_seperator_c( cRecorder rec[static 1],
                                         cScanner fmtSca[static 1] )
{
   char c;
   scan_char_c( fmtSca, &c );
   if ( not record_char_c( rec, c ) )
   {
      return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
   }
   return true;
}

/*******************************************************************************
 date
*******************************************************************************/

inline bool intl_write_day_c( cRecorder rec[static 1],
                              int8_t day,
                              int64_t fmt,
                              int64_t spaces )
{
   bool res = false;
   if ( fmt == 1 and spaces == 0 )
   {
      res = recordf_c( rec, "%d", day );
   }
   else if ( fmt == 2 and spaces == 0 )
   {
      res = recordf_c( rec, "%02d", day );
   }
   else if ( fmt == 1 and spaces == 1 )
   {
      res = recordf_c( rec, "% 2d", day );
   }
   else
   {
      return set_recorder_error_c( rec, c_InvalidFormatString );
   }

   return res ? true
              : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

inline bool intl_write_day_of_year_c( cRecorder rec[static 1],
                                      int16_t dayOfYear,
                                      int64_t fmt,
                                      int64_t spaces )
{
   bool res = false;
   if ( fmt == 1 and spaces == 0 )
   {
      res = recordf_c( rec, "%d", dayOfYear );
   }
   else if ( fmt == 1 and spaces == 2 )
   {
      res = recordf_c( rec, "% 3d", dayOfYear );
   }
   else if ( fmt == 3 and spaces == 0 )
   {
      res = recordf_c( rec, "%03d", dayOfYear );
   }
   else
   {
      return set_recorder_error_c( rec, c_InvalidFormatString );
   }

   return res ? true
              : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

inline bool intl_write_month_c( cRecorder rec[static 1],
                                c_Month month,
                                int64_t fmt,
                                int64_t spaces )
{
   cVarChars buf = scalars_c_( 32, char );
   bool res = false;
   if ( fmt == 1 and spaces == 0 )
   {
      res = recordf_c( rec, "%d", month );
   }
   else if ( fmt == 2 and spaces == 0 )
   {
      res = recordf_c( rec, "%02d", month );
   }
   else if ( fmt == 1 and spaces == 1 )
   {
      res = recordf_c( rec, "% 2d", month );
   }
   else if ( fmt == 3 and spaces == 0 )
   {
      buf = get_month_abbrev_c( month, buf );
      res = record_mem_c( rec, buf.s, buf.v );
   }
   else if ( fmt == 4 and spaces == 0 )
   {
      buf = get_month_name_c( month, buf );
      res = record_mem_c( rec, buf.s, buf.v );
   }
   else
   {
      return set_recorder_error_c( rec, c_InvalidFormatString );
   }

   return res ? true
              : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

inline bool intl_write_week_c( cRecorder rec[static 1],
                               int64_t week,
                               int64_t fmt )
{
   bool res = false;
   switch ( fmt )
   {
      case 2:
         res = recordf_c( rec, "W%d", week );
         break;
      case 3:
         res = recordf_c( rec, "W%02d", week );
         break;
      default:
         return set_recorder_error_c( rec, c_InvalidFormatString );
   }
   return res ? true
              : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

inline bool intl_write_weekday_c( cRecorder rec[static 1],
                                  c_Weekday wd,
                                  int64_t fmt )
{
   cVarChars buf = scalars_c_( 32, char );

   bool res = false;
   switch ( fmt )
   {
      case 1:
         res = recordf_c( rec, "%d", wd );
         break;
      case 3:
         buf = get_weekday_abbrev_c( wd, buf );
         res = record_mem_c( rec, buf.s, buf.v );
         break;
      case 4:
         buf = get_weekday_name_c( wd, buf );
         res = record_mem_c( rec, buf.s, buf.v );
         break;
      default:
         return set_recorder_error_c( rec, c_InvalidFormatString );
   }
   return res ? true
              : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

inline bool intl_write_year_c( cRecorder rec[static 1],
                               int32_t year,
                               int64_t fmt )
{
   bool res = false;
   switch ( fmt )
   {
      case 2:
         res = recordf_c( rec, "%02d", year_in_century_c( year ) );
         break;
      case 4:
         res = recordf_c( rec, "%04d", year );
         break;
      default:
         return set_recorder_error_c( rec, c_InvalidFormatString );
   }
   return res ? true
              : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

/*******************************************************************************
 time
*******************************************************************************/

inline bool intl_write_hour_c( cRecorder rec[static 1],
                               int32_t hour,
                               int64_t fmt,
                               int64_t spaces )
{
   bool res = false;
   if ( fmt == 1 and spaces == 0 )
   {
      res = recordf_c( rec, "%d", hour );
   }
   else if ( fmt == 2 and spaces == 0 )
   {
      res = recordf_c( rec, "%02d", hour );
   }
   else if ( fmt == 1 and spaces == 1 )
   {
      res = recordf_c( rec, "% 2d", hour );
   }
   else
   {
      return set_recorder_error_c( rec, c_InvalidFormatString );
   }

   return res ? true
              : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

inline bool intl_write_kitchen_hour_c( cRecorder rec[static 1],
                                       int32_t hour,
                                       int64_t fmt,
                                       int64_t spaces )
{
   return intl_write_hour_c( rec, hour % 12, fmt, spaces );
}

inline bool intl_write_min_c( cRecorder rec[static 1],
                              int32_t min,
                              int64_t fmt,
                              int64_t spaces )
{
   return intl_write_hour_c( rec, min, fmt, spaces );
}

inline bool intl_write_sec_c( cRecorder rec[static 1],
                              int32_t sec,
                              int64_t fmt,
                              int64_t spaces )
{
   return intl_write_hour_c( rec, sec, fmt, spaces );
}

inline bool intl_write_msec_c( cRecorder rec[static 1],
                               int64_t msec,
                               int64_t fmt )
{
   if ( fmt != 1 and fmt != 3 )
      return set_recorder_error_c( rec, c_InvalidFormatString );

   return intl_write_xsec_c( rec, msec, ( fmt == 1 ), "%03d" );
}

inline bool intl_write_usec_c( cRecorder rec[static 1],
                               int64_t usec,
                               int64_t fmt )
{
   if ( fmt != 1 and fmt != 3 )
      return set_recorder_error_c( rec, c_InvalidFormatString );

   return intl_write_xsec_c( rec, usec, ( fmt == 1 ), "%06d" );
}

inline bool intl_write_nsec_c( cRecorder rec[static 1],
                               int64_t nsec,
                               int64_t fmt )
{
   if ( fmt != 1 and fmt != 3 )
      return set_recorder_error_c( rec, c_InvalidFormatString );

   return intl_write_xsec_c( rec, nsec, ( fmt == 1 ), "%09d" );
}

inline bool intl_write_offset_c( cRecorder rec[static 1],
                                 cTzOffset tz,
                                 int64_t fmt,
                                 bool z )
{
   cHmsn t = hmsn_from_tz_offset_c( tz );
   char sign = ( t.hour < 0 ) ? '-'
                            : '+';
   if ( not iabs32_c( t.hour, &(t.hour) ) )
      return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
   if ( not iabs8_c( t.min, &(t.min) ) )
      return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );

   bool res = false;
   if ( z and t.hour == 0 and t.min == 0 )
   {
      res = record_char_c( rec, 'Z' );
   }
   else if ( fmt == 1 and t.min == 0 )
   {
      res = recordf_c( rec, "%c%02d", sign, t.hour );
   }
   else if ( fmt == 1 and t.min != 0 )
   {
      res = recordf_c( rec, "%c%02d:%02d", sign, t.hour, t.min );
   }
   else if ( fmt == 2 )
   {
      res = recordf_c( rec, "%c%02d:%02d", sign, t.hour, t.min );
   }
   else if ( fmt == 4 )
   {
      res = recordf_c( rec, "%c%02d%02d", sign, t.hour, t.min );
   }
   else
   {
      return set_recorder_error_c( rec, c_InvalidFormatString );
   }

   return res ? true
              : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

#endif
