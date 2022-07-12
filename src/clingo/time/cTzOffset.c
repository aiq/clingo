#include "clingo/time/cTzOffset.h"

#include "_/time/read_time_util.h"
#include "_/time/util.h"
#include "_/time/write_time_util.h"
#include "clingo/io/c_ReadWriteError.h"
#include "clingo/type/int32.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICE_IMPL_C_(
   cTzOffset,              // Type
   cTzOffsetSlice,         // SliceType
   tz_offset_slice_c,      // FuncName
   cVarTzOffsetSlice,      // VarSliceType
   var_tz_offset_slice_c   // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

cTzOffset local_c( void )
{
   time_t t = local_offset( time( NULL ) );
   return (cTzOffset){ (int32_t)t };
}

cTzOffset null_tz_offset_c( void )
{
   return (cTzOffset){ INT32_MIN };
}

cTzOffset tz_c( int64_t v )
{
   int64_t h = to_time_unit_c( v / 100, C_Hour, C_Sec );
   int64_t m = to_time_unit_c( v % 100, C_Min, C_Sec );

   int32_t _v;
   if ( not int64_to_int32_c( h+m, &_v ) ) return null_tz_offset_c();

   return (cTzOffset){ _v };
}

cTzOffset utc_c( void )
{
   return (cTzOffset){ 0 };
}

/*******************************************************************************
 from
*******************************************************************************/

extern inline cDuration duration_from_tz_offset_c( cTzOffset tz );
extern inline cHmsn hmsn_from_tz_offset_c( cTzOffset tz );
extern inline cTzOffset tz_offset_from_duration_c( cDuration dur );
extern inline cTzOffset tz_offset_from_hmsn_c( cHmsn hmsn );

/*******************************************************************************
 cmp
*******************************************************************************/

int cmp_tz_offset_c( cTzOffset a, cTzOffset b )
{
   return ( a._v < b._v ) ? -1
                          : ( a._v == b._v ) ? 0
                                             : 1;
}

extern inline bool eq_tz_offset_c( cTzOffset a, cTzOffset b );

/*******************************************************************************
   diff
*******************************************************************************/

cDuration between_tz_offsets_c( cTzOffset a, cTzOffset b )
{
   return between_durations_c( duration_from_tz_offset_c( a ),
                               duration_from_tz_offset_c( b ) );
}

/*******************************************************************************
 io
*******************************************************************************/

/*
   --------------

   Write TimeZoneOffset:
   ---------------------
   o - +01 and +01:30.
   oo - +01:00 and +01:30
   oooo - +0400
//   zzz - CDT
*/

bool read_tz_offset_c( cScanner sca[static 1],
                       cTzOffset tz[static 1],
                       char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = "oo";
   }
   cScanMarker* sm = &scan_marker_c_( &cstr_scanner_c_( fmt ) );
   int64_t const oldPos = sca->pos;

   bool res = true;
   {
      if ( move_while_char_c( sm->x, 'o' ) )
      {
         res = intl_read_offset_c( sca, tz, trace_scan_c_( sm ), false );
      }
      else if ( move_while_char_c( sm->x, 'z' ) )
      {
         res = intl_read_offset_c( sca, tz, trace_scan_c_( sm ), true );
      }
      else
      {
         return set_scanner_error_c( sca, c_InvalidFormatString );
      }
   }
   if ( not res )
   {
      move_scanner_to_c( sca, oldPos );
      return false;
   }

   return true;
}

bool write_tz_offset_c( cRecorder rec[static 1],
                        cTzOffset tz,
                        char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = "oo";
   }
   cScanMarker* sm = &scan_marker_c_( &cstr_scanner_c_( fmt ) );
   cRecordMarker* marker = &record_marker_c_( rec );

   bool res = true;
   {
      if ( move_while_char_c( sm->x, 'o' ) ) //------------------------------- o
      {
         res = intl_write_offset_c( rec, tz, trace_scan_c_( sm ), false );
      }
      else if ( move_while_char_c( sm->x, 'z' ) ) //-------------------------- z
      {
         res = intl_write_offset_c( rec, tz, trace_scan_c_( sm ), true );
      }
      else
      {
         return set_recorder_error_c( rec, c_InvalidFormatString );
      }
   }
   if ( not res )
   {
      undo_record_c( marker );
      return false;
   }

   return true;
}
