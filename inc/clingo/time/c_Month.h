#ifndef CLINGO_TIME_CMONTH_H
#define CLINGO_TIME_CMONTH_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/time/year.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 definitions
*******************************************************************************/

#define cMONTH_                                                                \
   cXMAP_( c_Jan, 1 )                                                          \
   cXMAP_( c_Feb, 2 )                                                          \
   cXMAP_( c_Mar, 3 )                                                          \
   cXMAP_( c_Apr, 4 )                                                          \
   cXMAP_( c_May, 5 )                                                          \
   cXMAP_( c_Jun, 6 )                                                          \
   cXMAP_( c_Jul, 7 )                                                          \
   cXMAP_( c_Aug, 8 )                                                          \
   cXMAP_( c_Sep, 9 )                                                          \
   cXMAP_( c_Oct, 10 )                                                         \
   cXMAP_( c_Nov, 11 )                                                         \
   cXMAP_( c_Dec, 12 )

#define cXMAP_( N, I ) N = I,
enum c_Month { cMONTH_ };
#undef cXMAP_

typedef enum c_Month c_Month;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API inline CONV_C_(
   int64_to_month_c, // FuncName
   int64_t,          // FromType
   c_Month,          // ToType
   c_Jan,            // MinValue
   c_Dec             // MaxValue
)

CLINGO_API char const* stringify_month_c( c_Month month );

/*******************************************************************************
 days
*******************************************************************************/

#define days_per_month_c_( Month, Year )                                       \
   days_per_month_c( Month, is_leap_year_c( Year ) )
CLINGO_API int8_t days_per_month_c( c_Month month, bool leapYear );

#define first_month_day_of_year_c_( Month, Year )                              \
   first_month_day_of_year_c( Month, is_leap_year_c( Year ) )
CLINGO_API int16_t first_month_day_of_year_c( c_Month month, bool leapYear );

CLINGO_API c_Month first_month_of_quarter_c( c_Month month );

/*******************************************************************************
 itr
*******************************************************************************/

CLINGO_API c_Month next_month_c( c_Month month );

CLINGO_API c_Month prev_month_c( c_Month month );

/*******************************************************************************
 text
*******************************************************************************/

CLINGO_API cVarChars get_month_abbrev_c( c_Month month, cVarChars buf );

CLINGO_API cVarChars get_month_name_c( c_Month month, cVarChars buf );

/*******************************************************************************
 io
*******************************************************************************/

#define read_month_c_( Sca, Month )                                            \
   read_month_c( (Sca), (Month), "" )
CLINGO_API
bool read_month_c( cScanner sca[static 1],
                   c_Month month[static 1],
                   char const fmt[static 1] );

#define write_month_c_( Rec, Month )                                           \
   write_month_c( (Rec), (Month), "" )
CLINGO_API
bool write_month_c( cRecorder rec[static 1],
                    c_Month month,
                    char const fmt[static 1] );

#endif
