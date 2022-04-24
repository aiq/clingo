#ifndef CLINGO_TIME_YEAR_H
#define CLINGO_TIME_YEAR_H

#include <stdbool.h>
#include <stdint.h>

#include "clingo/apidecl.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API int32_t century_c( int32_t year );

CLINGO_API int16_t days_of_year_c( int32_t year );

CLINGO_API bool is_leap_year_c( int32_t year );

CLINGO_API int32_t year_in_century_c( int32_t year );

#endif
