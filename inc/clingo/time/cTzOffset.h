#ifndef CLINGO_TIME_CTZ_OFFSET_H
#define CLINGO_TIME_CTZ_OFFSET_H

#include "clingo/apidecl.h"
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

SLICES_C_(
   cTzOffset,              // Type
   cTzOffsetSlice,         // SliceType
   cVarTzOffsetSlice       // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

CLINGO_API cTzOffset local_c( void );

CLINGO_API cTzOffset null_tz_offset_c( void );

CLINGO_API cTzOffset tz_c( int64_t v );

CLINGO_API cTzOffset utc_c( void );

/*******************************************************************************
 from
*******************************************************************************/

CLINGO_API inline cDuration duration_from_tz_offset_c( cTzOffset tz )
{
   return secs_c( tz._v );
}

CLINGO_API inline cHmsn hmsn_from_tz_offset_c( cTzOffset tz )
{
   cDuration dur = duration_from_tz_offset_c( tz );
   return hmsn_from_duration_c( dur );
}

CLINGO_API inline cTzOffset tz_offset_from_duration_c( cDuration dur )
{
   return (cTzOffset){ (int32_t)as_secs_c( dur ) };
}

CLINGO_API inline cTzOffset tz_offset_from_hmsn_c( cHmsn hmsn )
{
   cDuration dur = duration_from_hmsn_c( hmsn );
   return tz_offset_from_duration_c( dur );
}

/*******************************************************************************
 cmp
*******************************************************************************/

CLINGO_API int cmp_tz_offset_c( cTzOffset a, cTzOffset b );

CLINGO_API inline bool eq_tz_offset_c( cTzOffset a, cTzOffset b )
{
   return eq_c( cmp_tz_offset_c( a, b ) );
}

/*******************************************************************************
 diff
*******************************************************************************/

CLINGO_API cDuration between_tz_offsets_c( cTzOffset a, cTzOffset b );

/*******************************************************************************
 io
*******************************************************************************/

#define read_tz_offset_c_( Sca, Tz )                                           \
   read_tz_offset_c( (Sca), (Tz), "" )
CLINGO_API bool read_tz_offset_c( cScanner sca[static 1],
                       cTzOffset tz[static 1],
                       char const fmt[static 1] );

#define write_tz_offset_c_( Rec, Tz )                                          \
   write_tz_offset_c( (Rec), (Tz), "" )
CLINGO_API bool write_tz_offset_c( cRecorder rec[static 1],
                        cTzOffset tz,
                        char const fmt[static 1] );

#endif
