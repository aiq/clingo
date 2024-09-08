#ifndef CLINGO_TIME_CTIMESTAMP_H
#define CLINGO_TIME_CTIMESTAMP_H

#include "clingo/apidecl.h"
#include "clingo/time/cDuration.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cTimestamp
{
   int64_t _v;
};
typedef struct cTimestamp cTimestamp;

/*******************************************************************************
 generated
*******************************************************************************/

SLICES_C_(
   cTimestamp,    // Type
   cTimestamps,   // SliceType
   cVarTimestamps // VarSliceType
)

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 init
*******************************************************************************/

CLINGO_API cTimestamp now_c( void );

CLINGO_API cTimestamp null_timestamp_c( void );

CLINGO_API cTimestamp unix_timestamp_c( cDuration dur );

/*******************************************************************************
 unix
*******************************************************************************/

CLINGO_API inline int64_t timestamp_secs_c( cTimestamp ts )
{
   return as_secs_c( nsecs_c( ts._v ) );
}

CLINGO_API inline int64_t timestamp_msecs_c( cTimestamp ts )
{
   return as_msecs_c( nsecs_c( ts._v ) );
}

CLINGO_API inline int64_t timestamp_usecs_c( cTimestamp ts )
{
   return as_usecs_c( nsecs_c( ts._v ) );
}

CLINGO_API inline int64_t timestamp_nsecs_c( cTimestamp ts )
{
   return ts._v;
}

/*******************************************************************************
 cmp
*******************************************************************************/

CLINGO_API int cmp_timestamp_c( cTimestamp a, cTimestamp b );

CLINGO_API inline bool eq_timestamp_c( cTimestamp a, cTimestamp b )
{
   return a._v == b._v;
}

CLINGO_API bool timestamp_is_valid_c( cTimestamp ts );

/*******************************************************************************
 diff
*******************************************************************************/

CLINGO_API cDuration between_timestamps_c( cTimestamp a, cTimestamp b );

CLINGO_API inline cDuration since_c( cTimestamp ts )
{
   return between_timestamps_c( ts, now_c() );
}

CLINGO_API inline cDuration until_c( cTimestamp ts )
{
   return between_timestamps_c( now_c(), ts );
}

#endif
