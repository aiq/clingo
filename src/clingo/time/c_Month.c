#include "clingo/time/c_Month.h"

#include <stdio.h>
#include <time.h>

#include "_/time/read_time_util.h"
#include "_/time/write_time_util.h"
#include "clingo/io/c_ReadWriteError.h"
#include "clingo/type/int8.h"
#include "clingo/type/int16.h"
#include "clingo/type/int64.h"

static int8_t const DaysPerMonth[ 12 ] = {
//  1   2   3   4   5   6   7   8   9  10  11  12
   31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static int8_t const DaysPerMonthInLeapYear[ 12 ] = {
//  1   2   3   4   5   6   7   8   9  10  11  12
   31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 util
*******************************************************************************/

extern inline bool int64_to_month_c( int64_t src, c_Month month[static 1] );

char const* stringify_month_c( c_Month month )
{
   switch( month ) 
   {
      #define cXMAP_( N, I ) case N: return #N;
         cMONTH_
      #undef cXMAP_
   }
}

/*******************************************************************************
 days
*******************************************************************************/

int8_t days_per_month_c( c_Month month, bool leapYear )
{
   if ( leapYear )
   {
      return DaysPerMonthInLeapYear[ month - 1 ];
   }
   
   return DaysPerMonth[ month - 1 ];
}

int16_t first_month_day_of_year_c( c_Month month, bool leapYear )
{
   cInt8Slice slice = leapYear
      ? int8_slice_c( month - 1, DaysPerMonthInLeapYear )
      : int8_slice_c( month - 1, DaysPerMonth );

   int64_t sum = 0;
   sum_int8_c( slice, &sum );
   return int16_c_( sum + 1 );
}

c_Month first_month_of_quarter_c( c_Month month )
{
   switch( month )
   {
      case c_Jan:
      case c_Feb:
      case c_Mar:
         return c_Jan;
      case c_Apr:
      case c_May:
      case c_Jun:
         return c_Apr;
      case c_Jul:
      case c_Aug:
      case c_Sep:
         return c_Jul;
      case c_Oct:
      case c_Nov:
      case c_Dec:
         return c_Oct;
   }
}

/*******************************************************************************
 itr
*******************************************************************************/

c_Month next_month_c( c_Month month )
{
   return ( month == c_Dec ) ? c_Jan
                             : ++month;
}

c_Month prev_month_c( c_Month month )
{
   return ( month == c_Jan ) ? c_Dec
                             : --month;
}

/*******************************************************************************
 text
*******************************************************************************/

cVarChars get_month_abbrev_c( c_Month month, cVarChars buf )
{
   if ( is_empty_c_( buf ) ) return buf;

   size_t sz;
   if ( not int64_to_size_c( buf.s, &sz ) ) return empty_var_chars_c();

   struct tm t;
   t.tm_mon = int8_c_( month ) - 1;
   size_t len = strftime( buf.v, sz, "%b", &t );
   buf.s = int64_c_( len );
   return buf;
}

cVarChars get_month_name_c( c_Month month, cVarChars buf )
{
   if ( is_empty_c_( buf ) ) return buf;

   size_t sz;
   if ( not int64_to_size_c( buf.s, &sz ) ) return empty_var_chars_c();

   struct tm t;
   t.tm_mon = int8_c_( month ) - 1;
   size_t len = strftime( buf.v, sz, "%B", &t );
   buf.s = int64_c_( len );
   return buf;
}

/*******************************************************************************
 io
*******************************************************************************/

bool read_month_c( cScanner sca[static 1],
                   c_Month month[static 1],
                   char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = "MMM";
   }
   cChars slc = c_c( fmt );
   if ( chars_is_c( slc, "_M" ) )
   {
      return intl_read_month_c( sca, month, 1, 1 );
   }

   int64_t n = count_eq_char_c( slc, 'M' );
   return ( n != slc.s ) ? set_scanner_error_c( sca, c_InvalidFormatString )
                         : intl_read_month_c( sca, month, n, 0 );
}

bool write_month_c( cRecorder rec[static 1],
                    c_Month month,
                    char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = "MMM";
   }
   cChars slc = c_c( fmt );
   if ( chars_is_c( slc, "_M" ) )
   {
      return intl_write_month_c( rec, month, 1, 1 );
   }

   int64_t n = count_eq_char_c( slc, 'M' );
   return ( n != slc.s ) ? set_recorder_error_c( rec, c_InvalidFormatString )
                         : intl_write_month_c( rec, month, n, 0 );
}

