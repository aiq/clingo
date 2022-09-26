#ifndef CLINGO_TIME_CDAYTIME_H
#define CLINGO_TIME_CDAYTIME_H

#include <time.h>

#include "clingo/apidecl.h"
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

SLICES_C_(
   cDaytime,            // Type
   cDaytimeSlice,       // SliceType
   cVarDaytimeSlice     // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define daytime_c_( H, M, S )                                                  \
   daytime_c( (H), (M), (S), 0 )
CLINGO_API cDaytime daytime_c( int64_t h, int64_t m, int64_t s, int64_t n );

CLINGO_API cDaytime local_daytime_c( void );
CLINGO_API cDaytime null_daytime_c( void );
CLINGO_API cDaytime utc_daytime_c( void );

/*******************************************************************************
 from
*******************************************************************************/

CLINGO_API cDaytime from_duration_c( cDuration dur );
CLINGO_API cDaytime from_hmsn_c( cHmsn hmsn );

/*******************************************************************************
 as
*******************************************************************************/

CLINGO_API cDuration as_duration_c( cDaytime dt );
CLINGO_API cHmsn as_hmsn_c( cDaytime dt );

/*******************************************************************************
 add
*******************************************************************************/

CLINGO_API cDaytime add_to_daytime_c( cDaytime dt, cDuration dur );

/*******************************************************************************
 diff
*******************************************************************************/

CLINGO_API cDuration between_daytimes_c( cDaytime a, cDaytime b );

/*******************************************************************************
 cmp
*******************************************************************************/

CLINGO_API int cmp_daytime_c( cDaytime a, cDaytime b );
CLINGO_API bool daytime_is_valid_c( cDaytime dt );
CLINGO_API cDaytime early_daytime_c( cDaytime a, cDaytime b );

CLINGO_API inline bool eq_daytime_c( cDaytime a, cDaytime b )
{
   return ( a._v == b._v );
}

CLINGO_API cDaytime late_daytime_c( cDaytime a, cDaytime b );

/*******************************************************************************
 io
*******************************************************************************/

#define read_daytime_c_( Sca, Daytime )                                        \
   read_daytime_c( (Sca), (Daytime), "" )
CLINGO_API bool read_daytime_c( cScanner sca[static 1],
                     cDaytime dt[static 1],
                     char const fmt[static 1] );

#define write_daytime_c_( Rec, Daytime )                                       \
   write_daytime_c( (Rec), (Daytime), "" )
CLINGO_API bool write_daytime_c( cRecorder rec[static 1],
                      cDaytime dt,
                      char const fmt[static 1] );

#endif
