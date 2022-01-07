#ifndef CLINGO_TIME_CSTOPWATCH_H
#define CLINGO_TIME_CSTOPWATCH_H

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

cDuration check_stopwatch_c( cStopwatch sw[static 1] );

cDuration reset_stopwatch_c( cStopwatch sw[static 1] );

void start_stopwatch_c( cStopwatch sw[static 1] );

cDuration stop_stopwatch_c( cStopwatch sw[static 1] );

#endif
