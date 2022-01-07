#ifndef CLINGO_TIME_CDURATION_H
#define CLINGO_TIME_CDURATION_H

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

SLICE_DEF_C_(
   cDuration,           // Type
   cDurationSlice,      // SliceType
   duration_slice_c,    // FuncName
   cVarDurationSlice,   // VarSliceType
   var_duration_slice_c // VarFuncName
)

/*******************************************************************************
 definitions
*******************************************************************************/

extern int64_t const C_Week;
extern int64_t const C_Day;
extern int64_t const C_Hour;
extern int64_t const C_Min;
extern int64_t const C_Sec;
extern int64_t const C_Msec;
extern int64_t const C_Usec;
extern int64_t const C_Nsec;

extern cDuration const C_MaxDuration;

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 init
*******************************************************************************/

cDuration duration_c( int64_t h, int64_t m, int64_t s, int64_t n );

cDuration weeks_c( int64_t weeks );
cDuration days_c( int64_t days );
cDuration hours_c( int64_t hours );
cDuration mins_c( int64_t mins );
cDuration secs_c( int64_t secs );
cDuration msecs_c( int64_t msecs );
cDuration usecs_c( int64_t usecs );
cDuration nsecs_c( int64_t nsecs );

inline cDuration null_duration_c( void )
{
   return (cDuration){ ._v = INT64_MIN };
}

/*******************************************************************************
 from
*******************************************************************************/

inline cDuration duration_from_hmsn_c( cHmsn hmsn )
{
   return duration_c( hmsn.hour, hmsn.min, hmsn.sec, hmsn.nsec );
}

cHmsn hmsn_from_duration_c( cDuration dur );

/*******************************************************************************
 conv
*******************************************************************************/

int64_t as_weeks_c( cDuration dur );
int64_t as_days_c( cDuration dur );
int64_t as_hours_c( cDuration dur );
int64_t as_mins_c( cDuration dur );
int64_t as_secs_c( cDuration dur );
int64_t as_msecs_c( cDuration dur );
int64_t as_usecs_c( cDuration dur );
int64_t as_nsecs_c( cDuration dur );

inline int64_t to_time_unit_c( int64_t val, int64_t from, int64_t to )
{
   return ( val * from ) / to;
}

/*******************************************************************************
 overall
*******************************************************************************/

cDuration add_duration_c( cDuration a, cDuration b );

cDuration between_durations_c( cDuration a, cDuration b );

int cmp_duration_c( cDuration a, cDuration b );

inline bool duration_is_valid_c( cDuration dur )
{
   return ( dur._v != INT64_MIN );
}

inline bool eq_duration_c( cDuration a, cDuration b )
{
   return eq_c( cmp_duration_c( a, b ) );
}

inline cDuration invert_duration_c( cDuration dur )
{
   if ( duration_is_valid_c( dur ) )
   {
      return (cDuration){ -1*dur._v };
   }
   return dur;
}

#define truncate_duration_c_( Dur, Fac )                                       \
   trauncate_duration_c( (Dur), (Fac), ref_c_( cDuration, null_duration_c() ) )
cDuration truncate_duration_c( cDuration dur,
                               int64_t fac,
                               cDuration tail[static 1] );

/*******************************************************************************
 io
*******************************************************************************/

#define read_duration_c_( Sca, Dur )                                           \
   read_duration_c( (Sca), (Dur), "" )
bool read_duration_c( cScanner sca[static 1],
                      cDuration dur[static 1],
                      char const fmt[static 1] );

#define write_duration_c_( Rec, Dur )                                          \
   write_duration_c( (Rec), (Dur), "" )
bool write_duration_c( cRecorder rec[static 1],
                       cDuration dur,
                       char const fmt[static 1] );

#endif
