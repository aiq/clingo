#include "clingo/time/year.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

int32_t century_c( int32_t year )
{
   return year / 100;
}

int16_t days_of_year_c( int32_t year )
{
   return is_leap_year_c( year ) ? 366
                                 : 365;
}

bool is_leap_year_c( int32_t year )
{
   if( ( year % 4 == 0 && year % 100 != 0 ) ||
       ( year % 400 == 0 ) )
   {
      return true;
   }
   
   return false;
}

int32_t year_in_century_c( int32_t year )
{
   return year - ( century_c( year ) * 100 );
}
