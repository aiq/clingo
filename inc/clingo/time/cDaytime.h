#ifndef CLINGO_TIME_CDAYTIME_H
#define CLINGO_TIME_CDAYTIME_H

#include <time.h>

#include "clingo/time/cDate.h"
#include "clingo/time/cDuration.h"
#include "clingo/time/cTzOffset.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cDaytime
{
   int64_t _v;
};
typedef struct cDaytime cDaytime;

/*******************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   cDaytime,            // Type
   cDaytimeSlice,       // SliceType
   daytime_slice_c,     // FuncSuffix
   cVarDaytimeSlice,    // VarSliceType
   var_daytime_slice_c  // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define daytime_c_( H, M, S )                                                  \
   daytime_c( (H), (M), (S), 0 )
cDaytime daytime_c( int64_t h, int64_t m, int64_t s, int64_t n );

cDaytime local_daytime_c( void );
cDaytime null_daytime_c( void );
cDaytime utc_daytime_c( void );

/*******************************************************************************
 from
*******************************************************************************/

cDaytime from_duration_c( cDuration dur );
cDaytime from_hmsn_c( cHmsn hmsn );

/*******************************************************************************
 as
*******************************************************************************/

cDuration as_duration_c( cDaytime dt );
cHmsn as_hmsn_c( cDaytime dt );

/*******************************************************************************
 add
*******************************************************************************/

cDaytime add_to_daytime_c( cDaytime dt, cDuration dur );

/*******************************************************************************
 diff
*******************************************************************************/

cDuration between_daytimes_c( cDaytime a, cDaytime b );

/*******************************************************************************
 cmp
*******************************************************************************/

int cmp_daytime_c( cDaytime a, cDaytime b );
bool daytime_is_valid_c( cDaytime dt );
cDaytime early_daytime_c( cDaytime a, cDaytime b );

inline bool eq_daytime_c( cDaytime a, cDaytime b )
{
   return ( a._v == b._v );
}

cDaytime late_daytime_c( cDaytime a, cDaytime b );

/*******************************************************************************
 io
*******************************************************************************/

#define read_daytime_c_( Sca, Daytime )                                        \
   read_daytime_c( (Sca), (Daytime), "" )
bool read_daytime_c( cScanner sca[static 1],
                     cDaytime dt[static 1],
                     char const fmt[static 1] );

#define write_daytime_c_( Rec, Daytime )                                       \
   write_daytime_c( (Rec), (Daytime), "" )
bool write_daytime_c( cRecorder rec[static 1],
                      cDaytime dt,
                      char const fmt[static 1] );

#endif
