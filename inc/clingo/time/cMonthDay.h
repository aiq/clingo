#ifndef CLINGO_TIME_CMONTHDAY_H
#define CLINGO_TIME_CMONTHDAY_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/time/c_Month.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cMonthDay
{
   c_Month month;
   int8_t day;
};
typedef struct cMonthDay cMonthDay;

/*******************************************************************************
 generated
*******************************************************************************/

SLICES_C_(
   cMonthDay,              // Type
   cMonthDaySlice,         // SliceType
   cVarMonthDaySlice       // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API int cmp_month_day_c( cMonthDay a, cMonthDay b );

CLINGO_API cMonthDay month_day_c( int64_t month, int64_t day );

/*******************************************************************************
 io
*******************************************************************************/

#define read_month_day_c_( Sca, Md )                                           \
   read_month_day_c( (Sca), (Md), "" )
CLINGO_API bool read_month_day_c( cScanner sca[static 1],
                       cMonthDay md[static 1],
                       char const fmt[static 1] );

#define write_month_day_c_( Rec, Md )                                          \
   write_month_day_c( (Rec), (Md), "" )
CLINGO_API bool write_month_day_c( cRecorder rec[static 1],
                        cMonthDay md,
                        char const fmt[static 1] );

#endif
