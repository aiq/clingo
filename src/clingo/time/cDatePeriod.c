#include "clingo/time/cDatePeriod.h"

#include "clingo/lang/func.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

extern inline cDatePeriod date_period_c( cDate first, cDate last );

cDatePeriod determine_date_period_c( cDates slice )
{
   if ( is_empty_c_( slice ) ) return null_date_period_c();

   cDate first = first_c_( slice );
   cDate last = first;

   each_c_( cDate const*, d, slice )
   {
      first = early_date_c( first, *d );
      last = late_date_c( last, *d );
   }

   return date_period_c( first, last );
}

extern inline cDatePeriod
make_date_period_c( int64_t y1, int64_t m1, int64_t d1,
                    int64_t y2, int64_t m2, int64_t d2 );

extern inline cDatePeriod null_date_period_c();

extern inline cDatePeriod single_date_period_c( cDate date );

extern inline cDatePeriod sized_date_period_c( cDate begin, int64_t days );

/*******************************************************************************
 length
*******************************************************************************/

int64_t date_period_days_c( cDatePeriod dp )
{
   if ( date_period_is_valid_c( dp ) )
   {
      return days_between_dates_c( dp.first, dp.last ) + 1;
   }

   return 0;
}

int64_t date_period_weeks_c( cDatePeriod dp )
{
   return date_period_days_c( dp ) / 7;
}

/*******************************************************************************
 overall
*******************************************************************************/

extern inline bool date_period_is_valid_c( cDatePeriod dp );

extern inline bool eq_date_period_c( cDatePeriod a, cDatePeriod b );

extern inline bool in_date_period_c( cDatePeriod dp, cDate date );

cDatePeriod resize_date_period_c( cDatePeriod dp, int64_t days )
{
   dp.first = add_days_to_date_c( dp.first, -days );
   dp.last = add_days_to_date_c( dp.last, days );
   return dp;
}

cDatePeriod shift_date_period_c( cDatePeriod dp, int64_t days )
{
   dp.first = add_days_to_date_c( dp.first, days );
   dp.last = add_days_to_date_c( dp.last, days );
   return dp;
}

/*******************************************************************************
 set
*******************************************************************************/

bool date_periods_overlap_c( cDatePeriod a, cDatePeriod b )
{
   cDatePeriod intersection = intersect_date_periods_c( a, b );
   return date_period_days_c( intersection ) != 0;
}

cDatePeriod intersect_date_periods_c( cDatePeriod a, cDatePeriod b )
{
   if ( not date_period_is_valid_c( a ) or
        not date_period_is_valid_c( b ) ) return null_date_period_c();

   cDate first = late_date_c( a.first, b.first );
   cDate last = early_date_c( a.last, b.last );
   return date_period_c( first, last ); 
}

bool is_sub_date_period_c( cDatePeriod dp, cDatePeriod sub )
{
   return in_date_period_c( dp, sub.first ) and
          in_date_period_c( dp, sub.last );
}

cDatePeriod unite_date_periods_c( cDatePeriod a, cDatePeriod b )
{
   if ( not date_period_is_valid_c( a ) ) return b;
   if ( not date_period_is_valid_c( b ) ) return a;

   cDate first = early_date_c( a.first, b.first );
   cDate last = late_date_c( a.last, b.last );
   return date_period_c( first, last );
}
