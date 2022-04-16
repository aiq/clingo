#ifndef CLINGO_INTERN_TIME_UTIL_H
#define CLINGO_INTERN_TIME_UTIL_H

#include <time.h>
#include <stdbool.h>

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

inline bool conv_to_local_time( time_t src, struct tm dst[static 1] )
{
#if _WIN32
   return localtime_s( dst, &src ) != 0;
#else
   return localtime_r( &src, dst ) != NULL;
#endif
}

inline bool conv_to_utc_time( time_t src, struct tm dst[static 1] )
{
#if _WIN32
   return gmtime_s( dst, &src ) != 0;
#else
   return gmtime_r( &src, dst ) != NULL;
#endif
}

inline time_t local_offset( time_t t )
{
#if _WIN32
#    define timegm _mkgmtime
#endif
   struct tm x;
   conv_to_local_time( t, &x );
   struct tm y = x;
   return timegm( &x ) - mktime( &y );
}

#endif
