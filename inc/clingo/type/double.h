#ifndef CLINGO_TYPE_DOUBLE_H
#define CLINGO_TYPE_DOUBLE_H

#include <float.h>

#include "clingo/lang/chunk.h"
#include "clingo/lang/slice.h"
#include "clingo/lang/window.h"
#include "clingo/type/c_ByteOrder.h"
#include "clingo/type/uint64.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

struct cDoubleInfo
{
   uint8_t sign;
   uint16_t exponent;
   uint64_t mantissa;
};
typedef struct cDoubleInfo cDoubleInfo;

SLICE_DEF_C_(
   double,              // Type
   cDoubleSlice,        // SliceType
   double_slice_c,      // FuncName
   cVarDoubleSlice,     // VarSliceType
   var_double_slice_c   // VarFuncName
)

CHUNK_DEF_C_(
   double,              // Type
   cDoubleChunk,        // ChunkType
   cDoubleSlice,        // SliceType
   double_chunk_c,      // FuncName
   cVarDoubleChunk,     // VarChunkType
   cVarDoubleSlice,     // VarSliceType
   var_double_chunk_c   // VarFuncName
)

WINDOW_DEF_C_(
   double,              // Type
   cDoubleWindow,       // WindowType
   cDoubleSlice,        // SliceType
   double_window_c,     // FuncName
   cVarDoubleWindow,    // VarWindowType
   cVarDoubleSlice,     // VarSliceType
   var_double_window_c  // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API inline int cmp_double_c( double a, double b )
{
   return ( a < b ) ? -1
                    : ( a == b ) ? 0
                                 : 1;
}

#define double_c_( Value )                                                     \
(                                                                              \
   (double)(Value)                                                             \
)

CLINGO_API bool double_to_float_c( double d, float f[static 1] );

#define eq_double_c_( D1, D2 )                                                 \
   eq_double_c( (D1), (D2), DBL_EPSILON )
CLINGO_API bool eq_double_c( double d1, double d2, double epsilon );

/*******************************************************************************
 info
*******************************************************************************/

CLINGO_API double build_double_c( cDoubleInfo info );

CLINGO_API cDoubleInfo double_info_c( double d );

/*******************************************************************************
 swap
*******************************************************************************/

CLINGO_API double swap_double_c( double d );
CLINGO_API double swap_double_to_c( double d, c_ByteOrder order );
CLINGO_API double swap_double_from_c( double d, c_ByteOrder order );

/*******************************************************************************
 pack
*******************************************************************************/

CLINGO_API uint64_t pack_double_c( double d );
CLINGO_API double unpack_double_c( uint64_t u );

/*******************************************************************************
 algo
*******************************************************************************/

CLINGO_API double const* find_double_c( cDoubleSlice, double val );

CLINGO_API double const* max_double_c( cDoubleSlice slice );

CLINGO_API double const* min_double_c( cDoubleSlice slice );

CLINGO_API bool prod_double_c( cDoubleSlice slice, double res[static 1] );

CLINGO_API bool sum_double_c( cDoubleSlice slice, double res[static 1] );

#endif
