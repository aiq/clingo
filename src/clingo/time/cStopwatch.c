#include "clingo/time/cStopwatch.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

cDuration reset_stopwatch_c( cStopwatch sw[static 1] )
{
   must_exist_c_( sw );
   cDuration res = stop_stopwatch_c( sw );
   sw->start = sw->end;
   sw->end = null_timestamp_c();
   return res;
}

void start_stopwatch_c( cStopwatch sw[static 1] )
{
   must_exist_c_( sw );
   sw->start = now_c();
   sw->end = null_timestamp_c();
}

cDuration stop_stopwatch_c( cStopwatch sw[static 1] )
{
   must_exist_c_( sw );
   sw->end = now_c();
   return between_timestamps_c( sw->start, sw->end );
}

cDuration check_stopwatch_c( cStopwatch sw[static 1] )
{
   must_exist_c_( sw );
   return since_c( sw->start );
}

