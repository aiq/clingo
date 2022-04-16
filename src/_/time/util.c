#include "_/time/util.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

extern inline bool conv_to_local_time( time_t src, struct tm dst[static 1] );

extern inline bool conv_to_utc_time( time_t src, struct tm dst[static 1] );

extern inline time_t local_offset( time_t t );
