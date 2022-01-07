#ifndef CLINGO_CONTAINER_CINT64_SET_H
#define CLINGO_CONTAINER_CINT64_SET_H

#include "clingo/container/set.h"

/*******************************************************************************

*******************************************************************************/

VAL_SET_DEF_C_(
   CInt64Set,     // VecType
   int64_t,       // ValType
   int64_set_c,   // FuncName
   C_Int64SetMeta // Meta
)

#endif
