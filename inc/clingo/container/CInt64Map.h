#ifndef CLINGO_CONTAINER_CINT64MAP_H
#define CLINGO_CONTAINER_CINT64MAP_H

#include "clingo/apidecl.h"
#include "clingo/container/map.h"

/*******************************************************************************

*******************************************************************************/

VAL_VAL_MAP_DEF_C_(
   CLINGO_API,    // LibApi
   CInt64Map,     // MapType
   int64_t,       // KeyType
   int64_t,       // ValType
   int64_map_c,   // FuncName
   C_Int64Map     // Meta
)

#endif
