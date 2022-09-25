#include "clingo/time/cOrdinalDate.h"

#include "_/time/read_time_util.h"
#include "_/time/write_time_util.h"
#include "clingo/type/int16.h"
#include "clingo/type/int32.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

int cmp_ordinal_date_c( cOrdinalDate a, cOrdinalDate b )
{
   if ( a.year > b.year ) return 1;
   else if ( a.day < b.day ) return -1;

   if ( a.day > b.day ) return 1;
   else if ( a.day < b.day ) return -1;

   return 0;
}

cOrdinalDate ordinal_date_c( int64_t year, int64_t day )
{
   cOrdinalDate od;
   if ( int64_to_int32_c( year, &(od.year) ) and
        int64_to_int16_c( day, &(od.day) ) )
   {
      return od;
   }

   return (cOrdinalDate){ INT32_MIN, INT16_MIN };
}

bool ordinal_date_is_valid_c( cOrdinalDate od )
{
   int16_t max = is_leap_year_c( od.year ) ? 366
                                           : 365;

   return in_range_c_( 1, od.day, max );
}

/*******************************************************************************
 from
*******************************************************************************/

cOrdinalDate ordinal_date_from_ymd_c( cYmd ymd )
{
   int16_t day = first_month_day_of_year_c_( ymd.month, ymd.year );
   day += ymd.day;
   day -= 1;

   return (cOrdinalDate){ ymd.year, day };
}

cYmd ymd_from_ordinal_date_c( cOrdinalDate od )
{
   bool const leapYear = is_leap_year_c( od.year );

   c_Month month = c_Jan;
   int16_t monthDays = c_Jan;
   for ( c_Month m = c_Jan; m <= c_Dec; m++ )
   {
      int16_t const tmp = first_month_day_of_year_c( m, leapYear );
      if ( od.day >= tmp )
      {
         month = m;
         monthDays = tmp;
      }
   }

   return ymd_c( od.year, month, od.day - ( monthDays - 1 ) );

}

/*******************************************************************************
 io
*******************************************************************************/

bool read_ordinal_date_c( cScanner sca[static 1],
                          cOrdinalDate od[static 1],
                          char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = "YYYY-CCC";
   }
   cScanMarker* sm = &scan_marker_c_( &cstr_scanner_c_( fmt ) );
   int64_t oldPos = sca->pos;

   cOrdinalDate tmp = ordinal_date_c( -1, -1 );
   while ( sm->x->space > 0 )
   {
      bool res = true;
      int64_t spaces = move_while_char_c( sm->x, '_' ) ? trace_scan_c_( sm )
                                                       : 0;
  
      if ( move_while_char_c( sm->x, 'C' ) ) //------------------------------- C
      {
         int64_t n = trace_scan_c_( sm );
         res = intl_read_day_of_year_c( sca, &tmp.day, n, spaces );
      }
      else if ( move_while_char_c( sm->x, 'Y' ) ) //-------------------------- Y
      {
         res = intl_read_year_c( sca, &tmp.year, trace_scan_c_( sm ), spaces );
      }
      else
      {
         res = intl_read_time_seperator_c( sca, sm->x );
         trace_scan_c_( sm );
      }

      if ( not res )
      {
         move_scanner_to_c( sca, oldPos );
         return false;
      }
   }
   if ( not ordinal_date_is_valid_c( tmp ) )
   {
      move_scanner_to_c( sca, oldPos );
      return false;
   }

   *od = tmp;
   return true;
}

bool write_ordinal_date_c( cRecorder rec[static 1],
                           cOrdinalDate od,
                           char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = "YYYY-CCC";
   }
   cScanMarker* sm = &scan_marker_c_( &cstr_scanner_c_( fmt ) );
   int64_t oldPos = rec->pos;

   while ( sm->x->space > 0 )
   {
      bool res = true;
      int64_t spaces = move_while_char_c( sm->x, '_' ) ? trace_scan_c_( sm )
                                                       : 0;

      if ( move_while_char_c( sm->x, 'C' ) ) //------------------------------- C
      {
         int64_t n = trace_scan_c_( sm );
         res = intl_write_day_of_year_c( rec, od.day, n, spaces );
      }
      else if ( move_while_char_c( sm->x, 'Y' ) ) //-------------------------- Y
      {
         res = intl_write_year_c( rec, od.year, trace_scan_c_( sm ) );
      }
      else
      {
         res = intl_write_time_seperator_c( rec, sm->x );
         trace_scan_c_( sm );
      }

      if ( not res )
      {
         move_recorder_to_c( rec, oldPos );
         return false;
      }
   }

   return true;
}

