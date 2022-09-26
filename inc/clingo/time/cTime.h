#ifndef CLINGO_TIME_CTIME_H
#define CLINGO_TIME_CTIME_H

#include <time.h>

#include "clingo/apidecl.h"
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

SLICES_C_(
   cTime,            // Type
   cTimeSlice,       // SliceType
   cVarTimeSlice     // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

CLINGO_API cTime local_time_c( void );
CLINGO_API cTime make_time_c( int64_t year, int64_t month, int64_t day,
                   int64_t hour, int64_t min, int64_t sec, int64_t nsec,
                   cTzOffset tz );
CLINGO_API cTime null_time_c( void );
CLINGO_API cTime time_c( cDate d, cDaytime dt, cTzOffset tz );
CLINGO_API cTime utc_time_c( void );

/*******************************************************************************
 timestamp
*******************************************************************************/

CLINGO_API cTimestamp as_timestamp_c( cTime time );
CLINGO_API cTime from_timestamp_c( cTimestamp ts );

/*******************************************************************************
 get
*******************************************************************************/

CLINGO_API cDate get_date_c( cTime time );
CLINGO_API cDaytime get_daytime_c( cTime time );
CLINGO_API cHmsn get_hmsn_c( cTime time );
CLINGO_API cOrdinalDate get_ordinal_date_c( cTime time );
CLINGO_API cTzOffset get_tz_offset_c( cTime time );
CLINGO_API cWeekDate get_week_date_c( cTime time );
CLINGO_API cYmd get_ymd_c( cTime time );

/*******************************************************************************
 add
*******************************************************************************/

CLINGO_API cTime add_to_time_c( cTime time, cDuration dur );
CLINGO_API cDuration between_times_c( cTime a, cTime b );
CLINGO_API cTime shift_time_c( cTime time, cTzOffset tz );

/*******************************************************************************
 cmp
*******************************************************************************/

CLINGO_API int cmp_time_c( cTime a, cTime b );
CLINGO_API cTime early_time_c( cTime a, cTime b );

CLINGO_API inline bool eq_time_c( cTime a, cTime b )
{
   return eq_c( cmp_time_c( a, b ) );
}

CLINGO_API cTime late_time_c( cTime a, cTime b );
CLINGO_API bool time_is_valid_c( cTime time );

/*******************************************************************************
 io
*******************************************************************************/

#define read_time_c_( Sca, Date )                                              \
   read_time_c( (Sca), (Date), "" )
CLINGO_API bool read_time_c( cScanner sca[static 1],
                             cTime time[static 1],
                             char const fmt[static 1] );

#define write_time_c_( Rec, Date )                                             \
   write_time_c( (Rec), (Date), "" )
CLINGO_API bool write_time_c( cRecorder rec[static 1],
                              cTime time,
                              char const fmt[static 1] );

#endif
