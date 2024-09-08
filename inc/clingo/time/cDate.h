#ifndef CLINGO_TIME_CDATE_H
#define CLINGO_TIME_CDATE_H

#include "clingo/apidecl.h"
#include "clingo/time/c_Month.h"
#include "clingo/time/c_Weekday.h"
#include "clingo/time/cDuration.h"
#include "clingo/time/cOrdinalDate.h"
#include "clingo/time/cWeekDate.h"
#include "clingo/time/cYmd.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cDate
{
   int64_t _v;
};
typedef struct cDate cDate;

/*******************************************************************************
 generated
*******************************************************************************/

SLICES_C_(
   cDate,      // Type
   cDates,     // SliceType
   cVarDates   // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

CLINGO_API cDate date_c( int64_t year, int64_t month, int64_t day );
CLINGO_API cDate local_date_c( void );
CLINGO_API cDate null_date_c( void );
CLINGO_API cDate utc_date_c( void );

/*******************************************************************************
 from
*******************************************************************************/

CLINGO_API cDate from_julian_day_c( int64_t jd );
CLINGO_API cDate from_ordinal_date_c( cOrdinalDate od );
CLINGO_API cDate from_week_date_c( cWeekDate wd );
CLINGO_API cDate from_ymd_c( cYmd ymd );

/*******************************************************************************
 as
*******************************************************************************/

CLINGO_API int64_t as_julian_day_c( cDate date );
CLINGO_API cOrdinalDate as_ordinal_date_c( cDate date );
CLINGO_API cWeekDate as_week_date_c( cDate date );
CLINGO_API cYmd as_ymd_c( cDate date );

/*******************************************************************************
 prop
*******************************************************************************/

CLINGO_API bool date_is_valid_c( cDate date );
CLINGO_API int64_t date_day_of_year_c( cDate date );
CLINGO_API c_Weekday date_weekday_c( cDate date );
CLINGO_API cDate next_weekday_date_c( cDate date, c_Weekday wd );
CLINGO_API cDate prev_weekday_date_c( cDate date, c_Weekday wd );

/*******************************************************************************
 add
*******************************************************************************/

CLINGO_API cDate add_days_to_date_c( cDate date, int64_t days );
CLINGO_API cDate add_weeks_to_date_c( cDate date, int64_t weeks );
CLINGO_API cDate add_months_to_date_c( cDate date, int64_t months );
CLINGO_API cDate add_years_to_date_c( cDate date, int64_t years );

/*******************************************************************************
 diff
*******************************************************************************/

CLINGO_API int64_t days_between_dates_c( cDate a, cDate b );
CLINGO_API int64_t weeks_between_dates_c( cDate a, cDate b );
CLINGO_API int64_t months_between_dates_c( cDate a, cDate b );
CLINGO_API int64_t years_between_dates_c( cDate a, cDate b );

/*******************************************************************************
 cmp
*******************************************************************************/

CLINGO_API inline int cmp_date_c( cDate a, cDate b )
{
   return cmp_int64_c( a._v, b._v );
}

CLINGO_API cDate early_date_c( cDate a, cDate b );

CLINGO_API inline bool eq_date_c( cDate a, cDate b )
{
   return eq_c( cmp_date_c( a, b ) );
}

CLINGO_API cDate late_date_c( cDate a, cDate b );

/*******************************************************************************
 io
*******************************************************************************/

#define read_date_c_( Sca, Date )                                              \
   read_date_c( (Sca), (Date), "" )
CLINGO_API bool read_date_c( cScanner sca[static 1],
                  cDate date[static 1],
                  char const fmt[static 1] );

#define write_date_c_( Rec, Date )                                             \
   write_date_c( (Rec), (Date), "" )
CLINGO_API bool write_date_c( cRecorder rec[static 1],
                   cDate date,
                   char const fmt[static 1] );

#define date_tape_c_( Date )                                                   \
   date_tape_c( ref_c_( cDate, (Date) ) )
CLINGO_API cTape date_tape_c( cDate const* date );

#endif
