#ifndef CLINGO_INTERN_READ_TIME_UTIL_H
#define CLINGO_INTERN_READ_TIME_UTIL_H

#include "clingo/io/read.h"
#include "clingo/io/read_type.h"
#include "clingo/time/c_Month.h"
#include "clingo/time/c_Weekday.h"
#include "clingo/time/cTzOffset.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 util
*******************************************************************************/

inline bool intl_read_hms_val_c( cScanner sca[static 1],
                                 int8_t val[static 1],
                                 int64_t fmt,
                                 int64_t spaces )
{
   int64_t n = fmt + spaces;
   if ( n != 1 and n != 2 )
      return set_scanner_error_c( sca, c_InvalidReadFormat );

   cScanner* subSca = &sub_scanner_c_( sca, n );
   if ( spaces > 0 )
   {
      move_while_char_c( subSca, ' ' );
   }

   if ( not read_int8_c_( subSca, val ) )
      return false;

   move_scanner_c( sca, subSca->pos );
   return true;
}

inline bool intl_read_xsec_c( cScanner sca[static 1],
                              int32_t val[static 1],
                              int64_t fmt )
{
   if ( on_char_c( sca, '+' ) or on_char_c( sca, '-' ) )
      return set_scanner_error_c( sca, c_NotAbleToReadValue );

   cScanner* subSca = &sub_scanner_c_( sca, fmt );
   int64_t p = subSca->pos;
   if ( not read_int32_c_( subSca, val ) )
      return set_scanner_error_c( sca, c_NotAbleToReadValue );

   int64_t n = fmt - ( subSca->pos - p );
   times_c_( n, i )
   {
      *val *= 10;
   }
   move_scanner_c( sca, subSca->pos );
   return true;
}

inline bool intl_read_time_seperator_c( cScanner sca[static 1],
                                        cScanner fmtSca[static 1] )
{
   char c;
   scan_char_c( fmtSca, &c );
   if ( not move_if_char_c( sca, c ) )
   {
      return set_scanner_error_c( sca, c_InvalidReadFormat );
   }
   return true;
}

/*******************************************************************************
 date
*******************************************************************************/

inline bool intl_read_day_of_year_c( cScanner sca[static 1],
                                     int16_t day[static 1],
                                     int64_t fmt,
                                     int64_t spaces )
{
   int64_t n = fmt + spaces;
   if ( n != 1 and n != 3 )
      return set_scanner_error_c( sca, c_InvalidReadFormat );

   if ( n > sca->space )
      return set_scanner_error_c( sca, c_NotAbleToReadValue );

   cScanner* subSca = &sub_scanner_c_( sca, 3 );
   if ( spaces > 0 )
   {
      move_while_char_c( sca, ' ' );
   }

   if ( not read_int16_c_( subSca, day ) )
      return set_scanner_error_c( sca, c_NotAbleToReadValue );

   move_scanner_c( sca, subSca->pos );
   return true;
}

inline bool intl_read_day_c( cScanner sca[static 1],
                             int8_t day[static 1],
                             int64_t fmt,
                             int64_t spaces )
{
   return intl_read_hms_val_c( sca, day, fmt, spaces );
}

inline bool intl_read_month_c( cScanner sca[static 1],
                               c_Month month[static 1],
                               int64_t fmt,
                               int64_t spaces )
{
   int64_t n = fmt + spaces;
   if ( n == 1 or n == 2 )
   {
      int8_t tmp = 0;
      if ( not intl_read_hms_val_c( sca, &tmp, fmt, spaces ) )
         return false;

      if ( not in_range_c_( c_Jan, tmp, c_Dec ) )
         return set_scanner_error_c( sca, c_NotAbleToReadValue );

      *month = (c_Month)tmp;
   }
   else if ( fmt == 3 and spaces == 0 )
   {
      cVarChars varChars = scalars_c_( 32, char );
      bool res = false;
      for ( c_Month m = c_Jan; m <= c_Dec; ++m )
      {
         cChars cs = as_c_( cChars, get_month_abbrev_c( m, varChars ) );
         if ( move_if_chars_c( sca, cs ) )
         {
            *month = m;
            res = true;
            break;
         }
      }
      if ( not res ) return set_scanner_error_c( sca, c_NotAbleToReadValue );
   }
   else if ( fmt == 4 and spaces == 0 )
   {
      cVarChars varChars = scalars_c_( 32, char );
      bool res = false;
      for ( c_Month m = c_Jan; m <= c_Dec; ++m )
      {
         cChars cs = as_c_( cChars, get_month_name_c( m, varChars ) );
         if ( move_if_chars_c( sca, cs ) )
         {
            *month = m;
            res = true;
            break;
         }
      }
      if ( not res ) return set_scanner_error_c( sca, c_NotAbleToReadValue );
   }
   else
   {
      return set_scanner_error_c( sca, c_InvalidReadFormat );
   }

   return true;
}

inline bool intl_read_week_c( cScanner sca[static 1],
                              int8_t week[static 1],
                              int64_t fmt )
{
   if ( fmt != 2 and fmt != 3 )
      return set_scanner_error_c( sca, c_InvalidReadFormat );

   cScanner* subSca = &sub_scanner_c_( sca, 3 );

   if ( not move_if_char_c( subSca, 'W' ) )
      return set_scanner_error_c( sca, c_NotAbleToReadValue );

   if ( not read_int8_c_( subSca, week ) )
      return set_scanner_error_c( sca, c_NotAbleToReadValue );

   move_scanner_c( sca, subSca->pos );
   return true;
}

inline bool intl_read_weekday_c( cScanner sca[static 1],
                                 c_Weekday wd[static 1],
                                 int64_t fmt )
{
   if ( fmt == 1 )
   {
      int8_t tmp = 0;
      if ( not intl_read_hms_val_c( sca, &tmp, fmt, 0 ) )
         return false;

      if ( not in_range_c_( c_Mon, tmp, c_Sun ) )
         return set_scanner_error_c( sca, c_NotAbleToReadValue );

      *wd = (c_Weekday)tmp;
   }
   else if ( fmt == 3 )
   {
      cVarChars varChars = scalars_c_( 32, char );
      bool res = false;
      for ( c_Weekday w = c_Mon; w <= c_Sun; ++w )
      {
         cChars cs = as_c_( cChars, get_weekday_abbrev_c( w, varChars ) );
         if ( move_if_chars_c( sca, cs ) )
         {
            *wd = w;
            res = true;
            break;
         }
      }
      if ( not res ) return set_scanner_error_c( sca, c_NotAbleToReadValue );
   }
   else if ( fmt == 4 )
   {
      cVarChars varChars = scalars_c_( 32, char );
      bool res = false;
      for ( c_Weekday w = c_Mon; w <= c_Sun; ++w )
      {
         cChars cs = as_c_( cChars, get_weekday_name_c( w, varChars ) );
         if ( move_if_chars_c( sca, cs ) )
         {
            *wd = w;
            res = true;
            break;
         }
      }
      if ( not res ) return set_scanner_error_c( sca, c_NotAbleToReadValue );
   }
   else
   {
      return set_scanner_error_c( sca, c_InvalidReadFormat );
   }

   return true;
}

inline bool intl_read_year_c( cScanner sca[static 1],
                              int32_t year[static 1],
                              int64_t fmt,
                              int64_t spaces )
{
   int64_t n = fmt + spaces;
   if ( n != 2 and n != 4 )
      return set_scanner_error_c( sca, c_InvalidReadFormat );

   if ( n > sca->space )
      return set_scanner_error_c( sca, c_NotAbleToReadValue );

   cScanner* subSca = &sub_scanner_c_( sca, n );
   if ( spaces > 0 )
   {
      move_while_char_c( subSca, ' ' );
   }

   if ( not read_int32_c_( subSca, year ) )
      return set_scanner_error_c( sca, c_NotAbleToReadValue );

   if ( n == 2 )
   {
      *year = *year + 2000;
   }

   move_scanner_c( sca, subSca->pos );
   return true;
}

/*******************************************************************************
 time
*******************************************************************************/

inline bool intl_read_hour_c( cScanner sca[static 1],
                              int32_t hour[static 1],
                              int64_t fmt,
                              int64_t spaces )
{
   int8_t tmp;
   bool res = intl_read_hms_val_c( sca, &tmp, fmt, spaces );
   *hour = tmp;
   return res;
}

inline bool intl_read_kitchen_hour_c( cScanner sca[static 1],
                                      int32_t hour[static 1],
                                      int64_t fmt,
                                      int64_t spaces )
{
   int8_t tmp;
   bool res = intl_read_hms_val_c( sca, &tmp, fmt, spaces );
   *hour = tmp;
   return res;
}

inline bool intl_read_min_c( cScanner sca[static 1],
                             int8_t min[static 1],
                             int64_t fmt,
                             int64_t spaces )
{
   return intl_read_hms_val_c( sca, min, fmt, spaces );
}

inline bool intl_read_sec_c( cScanner sca[static 1],
                             int8_t sec[static 1],
                             int64_t fmt,
                             int64_t spaces )
{
   if ( !intl_read_hms_val_c( sca, sec, fmt, spaces ) ) return false;
   return true;
}

inline bool intl_read_isec_c( cScanner sca[static 1],
                              int32_t isec[static 1],
                              int64_t fmt )
{
   if ( fmt != 1 and fmt != 3 )
      return set_scanner_error_c( sca, c_InvalidReadFormat );

   return intl_read_xsec_c( sca, isec, 3 );
}

inline bool intl_read_usec_c( cScanner sca[static 1],
                              int32_t usec[static 1],
                              int64_t fmt )
{
   if ( fmt != 1 and fmt != 3 )
      return set_scanner_error_c( sca, c_InvalidReadFormat );

   return intl_read_xsec_c( sca, usec, 6 );
}

inline bool intl_read_nsec_c( cScanner sca[static 1],
                              int32_t nsec[static 1],
                              int64_t fmt )
{
   if ( fmt != 1 and fmt != 3 )
      return set_scanner_error_c( sca, c_InvalidReadFormat );

   return intl_read_xsec_c( sca, nsec, 9 );
}

inline bool intl_read_ap_c( cScanner sca[static 1],
                            bool pm[static 1] )
{
   if ( move_if_chars_c_( sca, "ap" ) or move_if_chars_c_( sca, "AP" ) )
   {
      *pm = false;
      return true;
   }
   else if ( move_if_chars_c_( sca, "pm" ) or move_if_chars_c_( sca, "PM" ) )
   {
      *pm = true;
      return true;
   }

   return set_scanner_error_c( sca, c_NotAbleToReadValue );
}

inline bool intl_read_offset_c( cScanner sca[static 1],
                                cTzOffset tz[static 1],
                                int64_t fmt,
                                bool z )
{
   if ( z and move_while_char_c( sca, 'Z' ) )
   {
      *tz = tz_c( 0 );
      return true;
   }

   if ( fmt == 1 or fmt == 2 )
   {
      int32_t h;
      {
         cScanner* subSca = &sub_scanner_c_( sca, 3 );
         if ( not read_int32_c_( subSca, &h ) or ( subSca->space > 0 ) )
            return set_scanner_error_c( sca, c_NotAbleToReadValue );

         move_scanner_c( sca, subSca->pos );
      }
      
      int8_t m = 0;
      if ( move_if_char_c( sca, ':' ) )
      {
         cScanner* subSca = &sub_scanner_c_( sca, 2 );
         if ( not read_int8_c_( subSca, &m ) or ( subSca->space > 0 ) )
            return set_scanner_error_c( sca, c_NotAbleToReadValue );

         if ( h < 0 )
         {
            m *= -1;
         }
         move_scanner_c( sca, subSca->pos );
      }
      else if ( fmt == 2 )
      {
         return set_scanner_error_c( sca, c_NotAbleToReadValue );
      }

      *tz = tz_offset_from_duration_c( duration_c( h, m, 0, 0 ) );
      return true;
   }
   else if ( fmt == 4 )
   {
      cScanner* subSca = &sub_scanner_c_( sca, 5 );
      int32_t v;
      if ( not read_int32_c_( subSca, &v ) or ( subSca->space > 0 ) )
         return set_scanner_error_c( sca, c_NotAbleToReadValue );

      move_scanner_c( sca, subSca->pos );
      return true;
   }
   else
   {
      return set_scanner_error_c( sca, c_InvalidReadFormat );
   }

   return set_scanner_error_c( sca, c_NotAbleToReadValue );
}

#endif
