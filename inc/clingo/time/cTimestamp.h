#ifndef CLINGO_TIME_CTIMESTAMP_H
#define CLINGO_TIME_CTIMESTAMP_H

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

SLICE_DEF_C_(
   cTimestamp,             // Type
   cTimestampSlice,        // SliceType
   timestamp_slice_c,      // FuncName
   cVarTimestampSlice,     // VarSliceType
   var_timestamp_slice_c   // VarFuncName
)

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 init
*******************************************************************************/

cTimestamp now_c( void );

cTimestamp null_timestamp_c( void );

/*******************************************************************************
 cmp
*******************************************************************************/

int cmp_timestamp_c( cTimestamp a, cTimestamp b );

inline bool eq_timestamp_c( cTimestamp a, cTimestamp b )
{
   return a._v == b._v;
}

bool timestamp_is_valid_c( cTimestamp ts );

/*******************************************************************************
 diff
*******************************************************************************/

cDuration between_timestamps_c( cTimestamp a, cTimestamp b );

inline cDuration since_c( cTimestamp ts )
{
   return between_timestamps_c( ts, now_c() );
}

inline cDuration until_c( cTimestamp ts )
{
   return between_timestamps_c( now_c(), ts );
}

#endif
