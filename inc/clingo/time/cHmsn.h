#ifndef CLINGO_TIME_CHMSN_H
#define CLINGO_TIME_CHMSN_H

#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cHmsn
{
   int32_t hour;
   int8_t min;
   int8_t sec;
   int32_t nsec;
};
typedef struct cHmsn cHmsn;

/*******************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   cHmsn,            // Type
   cHmsnSlice,       // SliceType
   hmsn_slice_c,     // FuncName
   cVarHmsnSlice,    // VarSliceType
   var_hmsn_slice_c  // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

int cmp_hmsn_c( cHmsn a, cHmsn b );

cHmsn hmsn_c( int64_t hour, int64_t min, int64_t sec, int64_t nsec );

inline cHmsn hms_c( int64_t hour, int64_t min, int64_t sec )
{
   return hmsn_c( hour, min, sec, 0 );
}

bool hmsn_is_valid_c( cHmsn hmsn );

/*******************************************************************************
 io
*******************************************************************************/

#define read_hmsn_c_( Sca, Hmsn )                                              \
   read_hmsn_c( (Sca), (Hmsn), "" )
bool read_hmsn_c( cScanner sca[static 1],
                  cHmsn hmsn[static 1],
                  char const fmt[static 1] );

#define write_hmsn_c_( Rec, Hmsn )                                             \
   write_hmsn_c( (Rec), (Hmsn), "" )
bool write_hmsn_c( cRecorder rec[static 1],
                   cHmsn hmsn,
                   char const fmt[static 1] );

#endif
