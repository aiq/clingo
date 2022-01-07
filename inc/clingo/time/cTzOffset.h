#ifndef CLINGO_TIME_CTZ_OFFSET_H
#define CLINGO_TIME_CTZ_OFFSET_H

#include "clingo/time/cDuration.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cTzOffset
{
   int32_t _v;
};
typedef struct cTzOffset cTzOffset;

/*******************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   cTzOffset,              // Type
   cTzOffsetSlice,         // SliceType
   tz_offset_slice_c,      // FuncName
   cVarTzOffsetSlice,      // VarSliceType
   var_tz_offset_slice_c   // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

cTzOffset local_c( void );

cTzOffset null_tz_offset_c( void );

cTzOffset tz_c( int64_t v );

cTzOffset utc_c( void );

/*******************************************************************************
 from
*******************************************************************************/

inline cDuration duration_from_tz_offset_c( cTzOffset tz )
{
   return secs_c( tz._v );
}

inline cHmsn hmsn_from_tz_offset_c( cTzOffset tz )
{
   cDuration dur = duration_from_tz_offset_c( tz );
   return hmsn_from_duration_c( dur );
}

inline cTzOffset tz_offset_from_duration_c( cDuration dur )
{
   return (cTzOffset){ (int32_t)as_secs_c( dur ) };
}

inline cTzOffset tz_offset_from_hmsn_c( cHmsn hmsn )
{
   cDuration dur = duration_from_hmsn_c( hmsn );
   return tz_offset_from_duration_c( dur );
}

/*******************************************************************************
 cmp
*******************************************************************************/

int cmp_tz_offset_c( cTzOffset a, cTzOffset b );

inline bool eq_tz_offset_c( cTzOffset a, cTzOffset b )
{
   return eq_c( cmp_tz_offset_c( a, b ) );
}

/*******************************************************************************
 diff
*******************************************************************************/

cDuration between_tz_offsets_c( cTzOffset a, cTzOffset b );

/*******************************************************************************
 io
*******************************************************************************/

#define read_tz_offset_c_( Sca, Tz )                                           \
   read_tz_offset_c( (Sca), (Tz), "" )
bool read_tz_offset_c( cScanner sca[static 1],
                       cTzOffset tz[static 1],
                       char const fmt[static 1] );

#define write_tz_offset_c_( Rec, Tz )                                          \
   write_tz_offset_c( (Rec), (Tz), "" )
bool write_tz_offset_c( cRecorder rec[static 1],
                        cTzOffset tz,
                        char const fmt[static 1] );

#endif
