#include "clingo/time/cTimestamp.h"

#include <time.h>

#include "clingo/time/cDuration.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 init
*******************************************************************************/

cTimestamp now_c( void )
{
   struct timespec ts;
   timespec_get( &ts, TIME_UTC );
   
   return (cTimestamp){ ts.tv_sec*C_Sec + ts.tv_nsec*C_Nsec };
}

cTimestamp null_timestamp_c( void )
{
   return (cTimestamp){ -1 };
}

cTimestamp unix_timestamp_c( cDuration dur )
{
   return (cTimestamp){ ._v=dur._v };
}

/*******************************************************************************
 unix
*******************************************************************************/

extern inline int64_t timestamp_secs_c( cTimestamp ts );

extern inline int64_t timestamp_msecs_c( cTimestamp ts );

extern inline int64_t timestamp_usecs_c( cTimestamp ts );

extern inline int64_t timestamp_nsecs_c( cTimestamp ts );

/*******************************************************************************
 cmp
*******************************************************************************/

int cmp_timestamp_c( cTimestamp a, cTimestamp b )
{
   return cmp_int64_c( a._v, b._v );
}

extern inline bool eq_timestamp_c( cTimestamp a, cTimestamp b );

bool timestamp_is_valid_c( cTimestamp ts )
{
   return ( ts._v >= 0 );
}

/*******************************************************************************
 diff
*******************************************************************************/

cDuration between_timestamps_c( cTimestamp a, cTimestamp b )
{
   return (cDuration){ b._v - a._v };
}

cDuration since_c( cTimestamp ts );

cDuration until_c( cTimestamp ts );
