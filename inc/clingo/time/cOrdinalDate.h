#ifndef CLINGO_TIME_CORDINALDATE_H
#define CLINGO_TIME_CORDINALDATE_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/time/cYmd.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cOrdinalDate
{
   int32_t year;
   int16_t day;
};
typedef struct cOrdinalDate cOrdinalDate;

SLICES_C_(
   cOrdinalDate,     // Type
   cOrdinalDates,    // SliceType
   cVarOrdinalDates  // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API int cmp_ordinal_date_c( cOrdinalDate a, cOrdinalDate b );

CLINGO_API cOrdinalDate ordinal_date_c( int64_t year, int64_t day );

CLINGO_API bool ordinal_date_is_valid_c( cOrdinalDate od );

/*******************************************************************************
 from
*******************************************************************************/

CLINGO_API cOrdinalDate ordinal_date_from_ymd_c( cYmd ymd );

CLINGO_API cYmd ymd_from_ordinal_date_c( cOrdinalDate od );

/*******************************************************************************
 io
*******************************************************************************/

#define read_ordinal_date_c_( Sca, Od )                                        \
   read_ordinal_day_c( (Sca), (Od), "" )
CLINGO_API bool read_ordinal_date_c( cScanner sca[static 1],
                          cOrdinalDate od[static 1], 
                          char const fmt[static 1] );

#define write_ordinal_date_c_( Rec, Od )                                       \
   write_ordinal_date_c( (Rec), (Od), "" )
CLINGO_API bool write_ordinal_date_c( cRecorder rec[static 1],
                           cOrdinalDate od,
                           char const fmt[static 1] );

#define ordinal_date_tape_c_( Od )                                             \
   ordinal_date_tape_c( ref_c_( cOrdinalDate, (Od) ) )
CLINGO_API cTape ordinal_date_tape_c( cOrdinalDate const* od );

#endif
