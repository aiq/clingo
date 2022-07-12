#include "clingo/time/cHmsn.h"

#include "_/time/read_time_util.h"
#include "_/time/write_time_util.h"
#include "clingo/time/cDuration.h"
#include "clingo/time/C_TimeFormats.h"
#include "clingo/type/int8.h"
#include "clingo/type/int32.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

SLICE_IMPL_C_(
   cHmsn,            // Type
   cHmsnSlice,       // SliceType
   hmsn_slice_c,     // FuncName
   cVarHmsnSlice,    // VarSliceType
   var_hmsn_slice_c  // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

cHmsn hmsn_c( int64_t hour, int64_t min, int64_t sec, int64_t nsec )
{
   cHmsn res;
   if ( int64_to_int32_c( hour, &(res.hour) ) and
        int64_to_int8_c( min, &(res.min) ) and
        int64_to_int8_c( sec, &(res.sec) ) and
        int64_to_int32_c( nsec, &(res.nsec) ) )
   {
      return res;
   }

   return (cHmsn){ INT32_MIN, INT8_MIN, INT8_MIN, INT32_MIN };
}

extern inline cHmsn hms_c( int64_t hour, int64_t min, int64_t sec );

/*******************************************************************************
 cmp
*******************************************************************************/

int cmp_hmsn_c( cHmsn a, cHmsn b )
{
   if ( !hmsn_is_valid_c( a ) ) return -1;
   if ( !hmsn_is_valid_c( b ) ) return 1;

   if ( a.hour > b.hour ) return 1;
   else if ( a.hour < b.hour ) return -1;

   if ( a.min > b.min ) return 1;
   else if ( a.min < b.min ) return -1;

   if ( a.sec > b.sec ) return 1;
   else if ( a.sec < b.sec ) return -1;

   if ( a.nsec > b.nsec ) return 1;
   else if ( a.nsec < b.nsec ) return -1;

   return 0;
}

bool hmsn_is_valid_c( cHmsn hmsn )
{
   if ( not in_range_c_( -59, hmsn.min, 59 ) ) return false;

   if ( not in_range_c_( -59, hmsn.sec, 59 ) ) return false;

   if ( not in_range_c_( -999999999, hmsn.nsec, 999999999 ) ) return false;

   return true;
}

/*******************************************************************************
 io
*******************************************************************************/

bool read_hmsn_c( cScanner sca[static 1],
                  cHmsn hmsn[static 1],
                  char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = C_DaytimeFormat;
   }
   cScanMarker* sm = &scan_marker_c_( &cstr_scanner_c_( fmt ) );
   int64_t oldPos = sca->pos;

   cHmsn tmp = hmsn_c( 0, 0, 0, 0 );
   bool pm = false;
   while ( sm->x->space > 0 )
   {
      bool res = true;
      int64_t spaces = move_while_char_c( sm->x, '_' ) ? trace_scan_c_( sm )
                                                       : 0;

      if ( move_while_char_c( sm->x, 'h' ) ) //------------------------------- h
      {
         res = intl_read_hour_c( sca, &tmp.hour, trace_scan_c_( sm ), spaces );
      }
      else if ( move_while_char_c( sm->x, 'k' ) ) //-------------------------- k
      {
         int64_t n = trace_scan_c_( sm );
         res = intl_read_kitchen_hour_c( sca, &tmp.hour, n, spaces );
      }
      else if ( move_while_char_c( sm->x, 'm' ) ) //-------------------------- m
      {
         res = intl_read_min_c( sca, &tmp.min, trace_scan_c_( sm ), spaces );
      }
      else if ( move_while_char_c( sm->x, 's' ) ) //-------------------------- s
      {
         res = intl_read_sec_c( sca, &tmp.sec, trace_scan_c_( sm ), spaces );
      }
      else if ( move_while_char_c( sm->x, 'i' ) ) //-------------------------- i
      {
         res = intl_read_isec_c( sca, &tmp.nsec, trace_scan_c_( sm ) );
         tmp.nsec *= 1000*1000;
      }
      else if ( move_while_char_c( sm->x, 'u' ) ) //-------------------------- u
      {
         res = intl_read_usec_c( sca, &tmp.nsec, trace_scan_c_( sm ) );
         tmp.nsec *= 1000;
      }
      else if ( move_while_char_c( sm->x, 'n' ) ) //-------------------------- n
      {
         res = intl_read_nsec_c( sca, &tmp.nsec, trace_scan_c_( sm ) );
      }
      else if ( move_if_chars_c_( sm->x, "ap" ) or
                move_if_chars_c_( sm->x, "AP" ) )
      {
         res = intl_read_ap_c( sca, &pm );
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
   // closing modifictaions and checks
   if ( pm )
   {
      tmp.hour += 12;
   }
   if ( not hmsn_is_valid_c( tmp ) )
   {
      move_scanner_to_c( sca, oldPos );
      return set_scanner_error_c( sca, c_NotAbleToReadValue );
   }

   *hmsn = tmp;
   return true;
}

bool write_hmsn_c( cRecorder rec[static 1],
                   cHmsn hmsn,
                   char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = C_DaytimeFormat;
   }
   cScanMarker* sm = &scan_marker_c_( &cstr_scanner_c_( fmt ) );
   int64_t oldPos = rec->pos;

   while ( sm->x->space > 0 )
   {
      bool res = true;
      int64_t spaces = move_while_char_c( sm->x, '_' ) ? trace_scan_c_( sm )
                                                       : 0;

      if ( move_while_char_c( sm->x, 'h' ) ) //------------------------------- h
      {
         res = intl_write_hour_c( rec, hmsn.hour, trace_scan_c_( sm ), spaces );
      }
      else if ( move_while_char_c( sm->x, 'k' ) ) //-------------------------- k
      {
         int64_t n = trace_scan_c_( sm );
         res = intl_write_kitchen_hour_c( rec, hmsn.hour, n, spaces );
      }
      else if ( move_while_char_c( sm->x, 'm' ) ) //-------------------------- m
      {
         res = intl_write_min_c( rec, hmsn.min, trace_scan_c_( sm ), spaces );
      }
      else if ( move_while_char_c( sm->x, 's' ) ) //-------------------------- s
      {
         res = intl_write_sec_c( rec, hmsn.sec, trace_scan_c_( sm ), spaces );
      }
      else if ( move_while_char_c( sm->x, 'i' ) ) //-------------------------- i
      {
         int64_t const msecs = to_time_unit_c( hmsn.nsec, C_Nsec, C_Msec );
         res = intl_write_msec_c( rec, msecs, trace_scan_c_( sm ) );
      }
      else if ( move_while_char_c( sm->x, 'u' ) ) //-------------------------- u
      {
         int64_t const usecs = to_time_unit_c( hmsn.nsec, C_Nsec, C_Usec );
         res = intl_write_usec_c( rec, usecs, trace_scan_c_( sm ) );
      }
      else if ( move_while_char_c( sm->x, 'n' ) ) //-------------------------- n
      {
         res = intl_write_nsec_c( rec, hmsn.nsec, trace_scan_c_( sm ) );
      }
      else if ( move_if_chars_c_( sm->x, "ap" ) ) //------------------------- ap
      {
         char const* val = ( hmsn.hour >= 12 ) ? "pm"
                                               : "am";
         res = record_chars_c_( rec, val );
      }
      else if ( move_if_chars_c_( sm->x, "AP" ) ) //------------------------- AP
      {
         char const* val = ( hmsn.hour >= 12 ) ? "PM"
                                               : "AM";
         res = record_chars_c_( rec, val );
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
