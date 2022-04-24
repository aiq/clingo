#ifndef CLINGO_TIME_CSTOPWATCH_H
#define CLINGO_TIME_CSTOPWATCH_H

#include "clingo/apidecl.h"
#include "clingo/time/cTimestamp.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cStopwatch
{
   cTimestamp start;
   cTimestamp end;
};
typedef struct cStopwatch cStopwatch;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API cDuration check_stopwatch_c( cStopwatch sw[static 1] );

CLINGO_API cDuration reset_stopwatch_c( cStopwatch sw[static 1] );

CLINGO_API void start_stopwatch_c( cStopwatch sw[static 1] );

CLINGO_API cDuration stop_stopwatch_c( cStopwatch sw[static 1] );

#endif
