#ifndef CLINGO_COLOR_CCMYK32_H
#define CLINGO_COLOR_CCMYK32_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/type/uint8.h"
#include "clingo/type/uint32.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cCmyk32
{
   uint8_t cyan;
   uint8_t magenta;
   uint8_t yellow;
   uint8_t key;
};
typedef struct cCmyk32 cCmyk32;

SLICE_DEF_C_(
   cCmyk32,             // Type
   cCmyk32Slice,        // SliceType
   cVarCmyk32Slice      // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define cmyk32_c_( Cyan, Magenta, Yellow, Key )                                \
   ((cCmyk32){ .cyan=(Cyan), .magenta=(Magenta), .yellow=(Yellow), .key=(Key) })

CLINGO_API inline bool eq_cmyk32_c( cCmyk32 a, cCmyk32 b )
{
   return a.cyan    == b.cyan and
          a.magenta == b.magenta and
          a.yellow  == b.yellow and
          a.key     == b.key;
}

#define read_cmyk32_c_( Sca, Cmyk )                                            \
   read_cmyk32_c( (Sca), (Cmyk), "" )
CLINGO_API bool read_cmyk32_c( cScanner sca[static 1],
                               cCmyk32 cmyk[static 1],
                               char const fmt[static 1] );

#define write_cmyk32_c_( Rec, Cmyk )                                           \
   write_cmyk32_c( (Rec), (Cmyk), "" )
CLINGO_API bool write_cmyk32_c( cRecorder rec[static 1],
                                cCmyk32 cmyk,
                                char const fmt[static 1] );

#endif
