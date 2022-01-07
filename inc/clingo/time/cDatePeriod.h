#ifndef CLINGO_TIME_CDATE_PERIOD_H
#define CLINGO_TIME_CDATE_PERIOD_H

#include "clingo/time/cDate.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cDatePeriod
{
   cDate first;
   cDate last;
};
typedef struct cDatePeriod cDatePeriod;

/*******************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   cDatePeriod,            // Type
   cDatePeriodSlice,       // SliceType
   date_period_slice_c,    // FuncName
   cVarDatePeriodSlice,    // VarSliceType
   var_date_period_slice_c // VarFuncName
)

/*******************************************************************************
 init
*******************************************************************************/

inline cDatePeriod date_period_c( cDate first, cDate last )
{
   return (cDatePeriod){ .first = first, .last = last };
}

cDatePeriod determine_date_period_c( cDateSlice slice );

inline cDatePeriod make_date_period_c( int64_t y1, int64_t m1, int64_t d1,
                                       int64_t y2, int64_t m2, int64_t d2 )
{
   return date_period_c( date_c( y1, m1, d1 ), date_c( y2, m2, d2 ) );
}

inline cDatePeriod null_date_period_c()
{
   return date_period_c( null_date_c(), null_date_c() );
}

inline cDatePeriod single_date_period_c( cDate date )
{
   return date_period_c( date, date );
}

inline cDatePeriod sized_date_period_c( cDate begin, int64_t days )
{
   return date_period_c( begin, add_days_to_date_c( begin, days - 1 ) );
}

/*******************************************************************************
 length
*******************************************************************************/

int64_t date_period_days_c( cDatePeriod dp );

int64_t date_period_weeks_c( cDatePeriod dp );

/*******************************************************************************
 overall
*******************************************************************************/

inline bool date_period_is_valid_c( cDatePeriod dp )
{
   if ( date_is_valid_c( dp.first ) and date_is_valid_c( dp.last ) )
   {
      return lte_c( cmp_date_c( dp.first, dp.last ) );
   }

   return false;
}

inline bool eq_date_period_c( cDatePeriod a, cDatePeriod b )
{
   return eq_date_c( a.first, b.first ) and
          eq_date_c( a.last, b.last );
}

inline bool in_date_period_c( cDatePeriod dp, cDate date )
{
   return in_range_c_( dp.first._v, date._v, dp.last._v );
}

cDatePeriod resize_date_period_c( cDatePeriod dp, int64_t days );

cDatePeriod shift_date_period_c( cDatePeriod dp, int64_t days );

/*******************************************************************************
 set
*******************************************************************************/

bool date_periods_overlap_c( cDatePeriod a, cDatePeriod b );

cDatePeriod intersect_date_periods_c( cDatePeriod a, cDatePeriod b );

bool is_sub_date_period_c( cDatePeriod dp, cDatePeriod sub );

cDatePeriod unite_date_periods_c( cDatePeriod a, cDatePeriod b );

#endif
