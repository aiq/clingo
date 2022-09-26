#ifndef CLINGO_TIME_CYMD_H
#define CLINGO_TIME_CYMD_H

#include "clingo/apidecl.h"
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

SLICES_C_(
   cYmd,             // Type
   cYmdSlice,        // SliceType
   cVarYmdSlice      // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

CLINGO_API cYmd ymd_c( int64_t year, int64_t month, int64_t day );

/*******************************************************************************
 cmp
*******************************************************************************/

CLINGO_API int cmp_ymd_c( cYmd a, cYmd b );

CLINGO_API bool ymd_is_valid_c( cYmd ymd );

/*******************************************************************************
 io
*******************************************************************************/

#define read_ymd_c_( Sca, Ymd )                                                \
   read_ymd_c( (Sca), (Ymd), "" )
CLINGO_API bool read_ymd_c( cScanner sca[static 1],
                 cYmd ymd[static 1],
                 char const fmt[static 1] );

#define write_ymd_c_( Rec, Ymd )                                               \
   write_ymd_c( (Rec), (Ymd), "" )
CLINGO_API bool write_ymd_c( cRecorder rec[static 1],
                  cYmd ymd,
                  char const fmt[static 1] );

#endif
