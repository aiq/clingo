#ifndef CLINGO_CONTAINER_CINT64_MAP_H
#define CLINGO_CONTAINER_CINT64_MAP_H

#include "clingo/container/map.h"

/*******************************************************************************

*******************************************************************************/

VAL_VAL_MAP_DEF_C_(
   CInt64Map,     // MapType
   int64_t,       // KeyType
   int64_t,       // ValType
   int64_map_c,   // FuncName
   C_Int64MapMeta // Meta
)

#endif
