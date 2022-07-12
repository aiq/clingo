#include "clingo/time/c_Weekday.h"

#include <time.h>

#include "_/time/read_time_util.h"
#include "_/time/write_time_util.h"
#include "clingo/type/int8.h"
#include "clingo/type/int16.h"
#include "clingo/type/int64.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 util
*******************************************************************************/

extern inline bool int64_to_weekday_c( int64_t src, c_Weekday wd[static 1] );

const char* stringify_weekday_c( c_Weekday wd )
{
   switch( wd ) 
   {
      #define cXMAP_( N, I ) case N: return #N;
         cWEEKDAY_
      #undef cXMAP_
   }
}

extern inline bool tm_wday_to_weekday_c( int src, c_Weekday wd[static 1] );

/*******************************************************************************
 itr
*******************************************************************************/

c_Weekday next_weekday_c( c_Weekday wd )
{
   return ( wd == c_Sun ) ? c_Mon
                          : ++wd;
}

c_Weekday prev_weekday_c( c_Weekday wd )
{
   return ( wd == c_Mon ) ? c_Sun
                          : --wd;
}

/*******************************************************************************
 text 
*******************************************************************************/

cVarChars get_weekday_abbrev_c( c_Weekday wd, cVarChars buf )
{
   if ( is_empty_c_( buf ) ) return buf;

   size_t sz;
   if ( not int64_to_size_c( buf.s, &sz ) ) return empty_var_chars_c();

   struct tm t;
   t.tm_wday = wd % 7;
   size_t len = strftime( buf.v, sz, "%a", &t );
   buf.s = int64_c_( len );
   return buf;
}

cVarChars get_weekday_name_c( c_Weekday wd, cVarChars buf )
{
   if ( is_empty_c_( buf ) ) return buf;

   size_t sz;
   if ( not int64_to_size_c( buf.s, &sz ) ) return empty_var_chars_c();

   struct tm t;
   t.tm_wday = wd % 7;
   size_t len = strftime( buf.v, sz, "%A", &t );
   buf.s = int64_c_( len );
   return buf;
}

c_Weekday weekday_c( int32_t year, c_Month month, int8_t day )
{
   int32_t const dayNum = day % 7;

   int32_t const monthNums[ 12 ] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };
   int32_t const monthNum = monthNums[ month - 1 ];

   int32_t const yearTmp = year - century_c( year ) * 100;
   int32_t const yearNum = ( yearTmp + ( yearTmp / 4 ) ) % 7;

   int32_t centuryNum = ( 3 - ( century_c( year ) % 4 ) ) * 2;

   int32_t leapNum = 0;
   if ( is_leap_year_c( year ) && ( month < c_Mar ) )
   {
      leapNum = 6;
   }

   int tmp = ( dayNum + monthNum + yearNum + centuryNum + leapNum ) % 7;
   c_Weekday res;
   tm_wday_to_weekday_c( tmp, &res );
   return res;
}

/*******************************************************************************
 io
*******************************************************************************/

bool read_weekday_c( cScanner sca[static 1],
                     c_Weekday wd[static 1],
                     char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = "EEE";
   }
   cChars slc = c_c( fmt );
   int64_t n = count_eq_char_c( slc, 'E' );
   return ( n != slc.s ) ? set_scanner_error_c( sca, c_InvalidFormatString )
                         : intl_read_weekday_c( sca, wd, n );
}

bool write_weekday_c( cRecorder rec[static 1],
                      c_Weekday wd,
                      char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = "EEE";
   }
   cChars slc = c_c( fmt );
   int64_t n = count_eq_char_c( slc, 'E' );
   return ( n != slc.s ) ? set_recorder_error_c( rec, c_InvalidFormatString )
                         : intl_write_weekday_c( rec, wd, n );
}
