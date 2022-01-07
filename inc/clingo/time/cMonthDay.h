#ifndef CLINGO_TIME_CMONTH_DAY_H
#define CLINGO_TIME_CMONTH_DAY_H

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

SLICE_DEF_C_(
   cMonthDay,              // Type
   cMonthDaySlice,         // SliceType
   month_day_slice_c,      // FuncName
   cVarMonthDaySlice,      // VarSliceType
   var_month_day_slice_c   // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

int cmp_month_day_c( cMonthDay a, cMonthDay b );

cMonthDay month_day_c( int64_t month, int64_t day );

/*******************************************************************************
 io
*******************************************************************************/

#define read_month_day_c_( Sca, Md )                                           \
   read_month_day_c( (Sca), (Md), "" )
bool read_month_day_c( cScanner sca[static 1],
                       cMonthDay md[static 1],
                       char const fmt[static 1] );

#define write_month_day_c_( Rec, Md )                                          \
   write_month_day_c( (Rec), (Md), "" )
bool write_month_day_c( cRecorder rec[static 1],
                        cMonthDay md,
                        char const fmt[static 1] );

#endif
