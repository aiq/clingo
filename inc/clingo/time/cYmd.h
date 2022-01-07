#ifndef CLINGO_TIME_CYMD_H
#define CLINGO_TIME_CYMD_H

#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/time/c_Month.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cYmd
{
   int32_t year;
   c_Month month;
   int8_t day;
};
typedef struct cYmd cYmd;

SLICE_DEF_C_(
   cYmd,             // Type
   cYmdSlice,        // SliceType
   ymd_slice_c,      // FuncName
   cVarYmdSlice,     // VarSliceType
   var_ymd_slice_c   // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

cYmd ymd_c( int64_t year, int64_t month, int64_t day );

/*******************************************************************************
 cmp
*******************************************************************************/

int cmp_ymd_c( cYmd a, cYmd b );

bool ymd_is_valid_c( cYmd ymd );

/*******************************************************************************
 io
*******************************************************************************/

#define read_ymd_c_( Sca, Ymd )                                                \
   read_ymd_c( (Sca), (Ymd), "" )
bool read_ymd_c( cScanner sca[static 1],
                 cYmd ymd[static 1],
                 char const fmt[static 1] );

#define write_ymd_c_( Rec, Ymd )                                               \
   write_ymd_c( (Rec), (Ymd), "" )
bool write_ymd_c( cRecorder rec[static 1],
                  cYmd ymd,
                  char const fmt[static 1] );

#endif
