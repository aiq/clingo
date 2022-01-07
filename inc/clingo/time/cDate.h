#ifndef CLINGO_TIME_CDATE_H
#define CLINGO_TIME_CDATE_H

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

SLICE_DEF_C_(
   cDate,            // Type
   cDateSlice,       // SliceType
   date_slice_c,     // FuncName
   cVarDateSlice,    // VarSliceType
   var_date_slice_c  // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

cDate date_c( int64_t year, int64_t month, int64_t day );
cDate local_date_c( void );
cDate null_date_c( void );
cDate utc_date_c( void );

/*******************************************************************************
 from
*******************************************************************************/

cDate from_julian_day_c( int64_t jd );
cDate from_ordinal_date_c( cOrdinalDate od );
cDate from_week_date_c( cWeekDate wd );
cDate from_ymd_c( cYmd ymd );

/*******************************************************************************
 as
*******************************************************************************/

int64_t as_julian_day_c( cDate date );
cOrdinalDate as_ordinal_date_c( cDate date );
cWeekDate as_week_date_c( cDate date );
cYmd as_ymd_c( cDate date );

/*******************************************************************************
 prop
*******************************************************************************/

bool date_is_valid_c( cDate date );
int64_t date_day_of_year_c( cDate date );
c_Weekday date_weekday_c( cDate date );
cDate next_weekday_date_c( cDate date, c_Weekday wd );
cDate prev_weekday_date_c( cDate date, c_Weekday wd );

/*******************************************************************************
 add
*******************************************************************************/

cDate add_days_to_date_c( cDate date, int64_t days );
cDate add_weeks_to_date_c( cDate date, int64_t weeks );
cDate add_months_to_date_c( cDate date, int64_t months );
cDate add_years_to_date_c( cDate date, int64_t years );

/*******************************************************************************
 diff
*******************************************************************************/

int64_t days_between_dates_c( cDate a, cDate b );
int64_t weeks_between_dates_c( cDate a, cDate b );
int64_t months_between_dates_c( cDate a, cDate b );
int64_t years_between_dates_c( cDate a, cDate b );

/*******************************************************************************
 cmp
*******************************************************************************/

inline int cmp_date_c( cDate a, cDate b )
{
   return cmp_int64_c( a._v, b._v );
}

cDate early_date_c( cDate a, cDate b );

inline bool eq_date_c( cDate a, cDate b )
{
   return eq_c( cmp_date_c( a, b ) );
}

cDate late_date_c( cDate a, cDate b );

/*******************************************************************************
 io
*******************************************************************************/

#define read_date_c_( Sca, Date )                                              \
   read_date_c( (Sca), (Date), "" )
bool read_date_c( cScanner sca[static 1],
                  cDate date[static 1],
                  char const fmt[static 1] );

#define write_date_c_( Rec, Date )                                             \
   write_date_c( (Rec), (Date), "" )
bool write_date_c( cRecorder rec[static 1],
                   cDate date,
                   char const fmt[static 1] );

#endif
