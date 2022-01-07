#ifndef CLINGO_TIME_CWEEKDAY_H
#define CLINGO_TIME_CWEEKDAY_H

#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/time/c_Month.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 definitions
*******************************************************************************/

#define cWEEKDAY_                                                              \
   cXMAP_( c_Mon, 1 )                                                          \
   cXMAP_( c_Tue, 2 )                                                          \
   cXMAP_( c_Wed, 3 )                                                          \
   cXMAP_( c_Thu, 4 )                                                          \
   cXMAP_( c_Fri, 5 )                                                          \
   cXMAP_( c_Sat, 6 )                                                          \
   cXMAP_( c_Sun, 7 )
 
#define cXMAP_( N, I ) N = I,
enum c_Weekday { cWEEKDAY_ };
#undef cXMAP_

typedef enum c_Weekday c_Weekday;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

inline CONV_C_(
   int64_to_weekday_c,  // FuncName
   int64_t,             // FromType
   c_Weekday,           // ToType
   c_Mon,               // MinValue
   c_Sun                // MaxValue
)

char const* stringify_weekday_c( c_Weekday wd );

inline bool tm_wday_to_weekday_c( int src, c_Weekday dst[static 1] )
{
   if ( not in_range_c_( 0, src, 6 ) ) return false;

   *dst = ( src == 0 ) ? 7
                       : (c_Weekday)src;
   return true;
}

c_Weekday weekday_c( int32_t year, c_Month month, int8_t day );

/*******************************************************************************
 itr
*******************************************************************************/

c_Weekday next_weekday_c( c_Weekday wd );

c_Weekday prev_weekday_c( c_Weekday wd );

/*******************************************************************************
 text
*******************************************************************************/

cVarChars get_weekday_abbrev_c( c_Weekday wd, cVarChars buf );

cVarChars get_weekday_name_c( c_Weekday wd, cVarChars buf );

/*******************************************************************************
 io
*******************************************************************************/

#define read_weekday_c_( Sca, Wd )                                             \
   read_weekday_c( (Sca), (Wd), "" )
bool read_weekday_c( cScanner sca[static 1],
                     c_Weekday wd[static 1],
                     char const fmt[static 1] );

#define write_weekday_c_( Rec, Wd )                                            \
   write_weekday_c( (Rec), (Wd), "" )
bool write_weekday_c( cRecorder rec[static 1],
                      c_Weekday wd,
                      char const fmt[static 1] );

#endif
