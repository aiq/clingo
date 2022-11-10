#ifndef CLINGO_CONTAINER_CINT64SET_H
#define CLINGO_CONTAINER_CINT64SET_H

#include "clingo/apidecl.h"
#include "clingo/container/set.h"

/*******************************************************************************

*******************************************************************************/

VAL_SET_DEF_C_(
   CLINGO_API,    // LibApi
   CInt64Set,     // VecType
   int64_t,       // ValType
   int64_set_c,   // FuncName
   C_Int64SetMeta // Meta
)

#endif
