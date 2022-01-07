#ifndef CLINGO_TIME_YEAR_H
#define CLINGO_TIME_YEAR_H

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

int32_t century_c( int32_t year );

int16_t days_of_year_c( int32_t year );

bool is_leap_year_c( int32_t year );

int32_t year_in_century_c( int32_t year );

#endif
