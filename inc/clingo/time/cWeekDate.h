#ifndef CLINGO_TIME_CWEEKDATE_H
#define CLINGO_TIME_CWEEKDATE_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/io/cTape.h"
#include "clingo/time/c_Weekday.h"
#include "clingo/time/cYmd.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cWeekDate
{
   int32_t year;
   int8_t week;
   c_Weekday day;
};
typedef struct cWeekDate cWeekDate;

/*******************************************************************************
 generated
*******************************************************************************/

SLICES_C_(
   cWeekDate,     // Type
   cWeekDates,    // SliceType
   cVarWeekDates  // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API int cmp_week_date_c( cWeekDate a, cWeekDate b );

CLINGO_API cWeekDate week_date_c( int64_t year, int64_t week, int64_t day );

CLINGO_API bool week_date_is_valid_c( cWeekDate wd );

/*******************************************************************************
 from
*******************************************************************************/

CLINGO_API cWeekDate week_date_from_ymd_c( cYmd ymd );

CLINGO_API cYmd ymd_from_week_date_c( cWeekDate wd );

/*******************************************************************************
 io
*******************************************************************************/

#define read_week_date_c_( Sca, Wd )                                           \
   read_week_date_c( (Sca), (Wd), "" )
CLINGO_API bool read_week_date_c( cScanner sca[static 1],
                       cWeekDate wd[static 1],
                       char const fmt[static 1] );

#define write_week_date_c_( Rec, Wd )                                          \
   write_week_date_c( (Rec), (Wd), "" )
CLINGO_API bool write_week_date_c( cRecorder rec[static 1],
                        cWeekDate wd,
                        char const fmt[static 1] );

#define week_date_tape_c_( Wd )                                                \
   week_date_tape_c( ref_c_( cWeekDate, (Wd) ) )
CLINGO_API cTape week_date_tape_c( cWeekDate const* wd );

#endif
