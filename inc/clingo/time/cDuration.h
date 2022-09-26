#ifndef CLINGO_TIME_CDURATION_H
#define CLINGO_TIME_CDURATION_H

#include "clingo/apidecl.h"
#include "clingo/lang/mem.h"
#include "clingo/time/cHmsn.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cDuration
{
   int64_t _v;
};
typedef struct cDuration cDuration;

/*******************************************************************************
 generated
*******************************************************************************/

SLICES_C_(
   cDuration,           // Type
   cDurationSlice,      // SliceType
   cVarDurationSlice    // VarSliceType
)

/*******************************************************************************
 definitions
*******************************************************************************/

CLINGO_API extern int64_t const C_Week;
CLINGO_API extern int64_t const C_Day;
CLINGO_API extern int64_t const C_Hour;
CLINGO_API extern int64_t const C_Min;
CLINGO_API extern int64_t const C_Sec;
CLINGO_API extern int64_t const C_Msec;
CLINGO_API extern int64_t const C_Usec;
CLINGO_API extern int64_t const C_Nsec;

CLINGO_API extern cDuration const C_MaxDuration;

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 init
*******************************************************************************/

CLINGO_API cDuration duration_c( int64_t h, int64_t m, int64_t s, int64_t n );

CLINGO_API cDuration weeks_c( int64_t weeks );
CLINGO_API cDuration days_c( int64_t days );
CLINGO_API cDuration hours_c( int64_t hours );
CLINGO_API cDuration mins_c( int64_t mins );
CLINGO_API cDuration secs_c( int64_t secs );
CLINGO_API cDuration msecs_c( int64_t msecs );
CLINGO_API cDuration usecs_c( int64_t usecs );
CLINGO_API cDuration nsecs_c( int64_t nsecs );

CLINGO_API inline cDuration null_duration_c( void )
{
   return (cDuration){ ._v = INT64_MIN };
}

/*******************************************************************************
 from
*******************************************************************************/

CLINGO_API inline cDuration duration_from_hmsn_c( cHmsn hmsn )
{
   return duration_c( hmsn.hour, hmsn.min, hmsn.sec, hmsn.nsec );
}

CLINGO_API cHmsn hmsn_from_duration_c( cDuration dur );

/*******************************************************************************
 conv
*******************************************************************************/

CLINGO_API int64_t as_weeks_c( cDuration dur );
CLINGO_API int64_t as_days_c( cDuration dur );
CLINGO_API int64_t as_hours_c( cDuration dur );
CLINGO_API int64_t as_mins_c( cDuration dur );
CLINGO_API int64_t as_secs_c( cDuration dur );
CLINGO_API int64_t as_msecs_c( cDuration dur );
CLINGO_API int64_t as_usecs_c( cDuration dur );
CLINGO_API int64_t as_nsecs_c( cDuration dur );

CLINGO_API inline int64_t to_time_unit_c( int64_t val, int64_t from, int64_t to )
{
   return ( val * from ) / to;
}

/*******************************************************************************
 overall
*******************************************************************************/

CLINGO_API cDuration add_duration_c( cDuration a, cDuration b );

CLINGO_API cDuration between_durations_c( cDuration a, cDuration b );

CLINGO_API int cmp_duration_c( cDuration a, cDuration b );

CLINGO_API inline bool duration_is_valid_c( cDuration dur )
{
   return ( dur._v != INT64_MIN );
}

CLINGO_API inline bool eq_duration_c( cDuration a, cDuration b )
{
   return eq_c( cmp_duration_c( a, b ) );
}

CLINGO_API inline cDuration invert_duration_c( cDuration dur )
{
   if ( duration_is_valid_c( dur ) )
   {
      return (cDuration){ -1*dur._v };
   }
   return dur;
}

#define truncate_duration_c_( Dur, Fac )                                       \
   trauncate_duration_c( (Dur), (Fac), ref_c_( cDuration, null_duration_c() ) )
CLINGO_API cDuration truncate_duration_c( cDuration dur,
                               int64_t fac,
                               cDuration tail[static 1] );

/*******************************************************************************
 io
*******************************************************************************/

#define read_duration_c_( Sca, Dur )                                           \
   read_duration_c( (Sca), (Dur), "" )
CLINGO_API bool read_duration_c( cScanner sca[static 1],
                      cDuration dur[static 1],
                      char const fmt[static 1] );

#define write_duration_c_( Rec, Dur )                                          \
   write_duration_c( (Rec), (Dur), "" )
CLINGO_API bool write_duration_c( cRecorder rec[static 1],
                       cDuration dur,
                       char const fmt[static 1] );

#endif
