#ifndef CLINGO_TIME_CTIME_H
#define CLINGO_TIME_CTIME_H

#include <time.h>

#include "clingo/time/cDate.h"
#include "clingo/time/cDaytime.h"
#include "clingo/time/cDuration.h"
#include "clingo/time/cTimestamp.h"
#include "clingo/time/cTzOffset.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cTime
{
   int64_t _s;
   int32_t _n;
   int32_t _z;
};
typedef struct cTime cTime;

/*******************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   cTime,            // Type
   cTimeSlice,       // SliceType
   time_slice_c,     // FuncName
   cVarTimeSlice,    // VarSliceType
   var_time_slice_c  // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

cTime local_time_c( void );
cTime make_time_c( int64_t year, int64_t month, int64_t day,
                   int64_t hour, int64_t min, int64_t sec, int64_t nsec,
                   cTzOffset tz );
cTime null_time_c( void );
cTime time_c( cDate d, cDaytime dt, cTzOffset tz );
cTime utc_time_c( void );

/*******************************************************************************
 timestamp
*******************************************************************************/

cTimestamp as_timestamp_c( cTime time );
cTime from_timestamp_c( cTimestamp ts );

/*******************************************************************************
 get
*******************************************************************************/

cDate get_date_c( cTime time );
cDaytime get_daytime_c( cTime time );
cHmsn get_hmsn_c( cTime time );
cOrdinalDate get_ordinal_date_c( cTime time );
cTzOffset get_tz_offset_c( cTime time );
cWeekDate get_week_date_c( cTime time );
cYmd get_ymd_c( cTime time );

/*******************************************************************************
 add
*******************************************************************************/

cTime add_to_time_c( cTime time, cDuration dur );
cDuration between_times_c( cTime a, cTime b );
cTime shift_time_c( cTime time, cTzOffset tz );

/*******************************************************************************
 cmp
*******************************************************************************/

int cmp_time_c( cTime a, cTime b );
cTime early_time_c( cTime a, cTime b );

inline bool eq_time_c( cTime a, cTime b )
{
   return eq_c( cmp_time_c( a, b ) );
}

cTime late_time_c( cTime a, cTime b );
bool time_is_valid_c( cTime time );

/*******************************************************************************
 io
*******************************************************************************/

#define read_time_c_( Sca, Date )                                              \
   read_time_c( (Sca), (Date), "" )
bool read_time_c( cScanner sca[static 1],
                  cTime time[static 1],
                  char const fmt[static 1] );

#define write_time_c_( Rec, Date )                                             \
   write_time_c( (Rec), (Date), "" )
bool write_time_c( cRecorder rec[static 1],
                   cTime time,
                   char const fmt[static 1] );

#endif
