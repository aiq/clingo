#ifndef CLINGO_INTERN_TIME_UTIL_H
#define CLINGO_INTERN_TIME_UTIL_H

#include <time.h>

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#if _WIN32
inline time_t local_offset( time_t t )
{
   struct tm x;
   localtime_s( &x, &t );
   struct tm y = x;
   return _mkgmtime( &x ) - mktime( &y );
}
#else
inline time_t local_offset( time_t t )
{
   struct tm x;
   localtime_r( &t, &x );
   struct tm y = x;
   return timegm( &x ) - mktime( &y );
}
#endif

#endif
