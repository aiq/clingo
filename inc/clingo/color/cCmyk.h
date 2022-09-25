#ifndef CLINGO_COLOR_CCMYK_H
#define CLINGO_COLOR_CCMYK_H

#include "clingo/apidecl.h"
#include "clingo/color/cCmyk32.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/type/float.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cCmyk
{
   float cyan;
   float magenta;
   float yellow;
   float key;
};
typedef struct cCmyk cCmyk;

SLICE_DEF_C_(
   cCmyk,            // Type
   cCmykSlice,       // SliceType
   cVarCmykSlice     // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define cmyk_c_( Cyan, Magenta, Yellow, Key )                                  \
   ((cCmyk){ .cyan=(Cyan), .magenta=(Magenta), .yellow=(Yellow), .key=(Key) })

#define eq_cmyk_c_( A, B )                                                     \
   eq_cmyk_c( (A), (B), FLT_EPSILON )
bool eq_cmyk_c( cCmyk a, cCmyk b, float epsilon );

CLINGO_API cCmyk32 cmyk32_from_cmyk_c( cCmyk cmyk );

CLINGO_API cCmyk cmyk_from_cmyk32_c( cCmyk32 color );

#define read_cmyk_c_( Sca, Cmyk )                                              \
   read_cmyk_c( (Sca), (Cmyk), "" )
CLINGO_API bool read_cmyk_c( cScanner sca[static 1],
                             cCmyk cmyk[static 1],
                             char const fmt[static 1] );

#define write_cmyk_c_( Rec, Cmyk )                                             \
   write_cmyk_c( (Rec), (Cmyk), "" )
CLINGO_API bool write_cmyk_c( cRecorder rec[static 1],
                              cCmyk cmyk,
                              char const fmt[static 1] );

#endif
