#include "clingo/container/CInt64Map.h"

/*******************************************************************************

*******************************************************************************/

VAL_VAL_MAP_IMPL_C_(
   ,                 // Static
   CInt64Map,        // MapType
   cInt64MapRow,     // RowType
   int64_t,          // KeyType
   int64_t,          // ValType
   int64_map_c,      // FuncName
   C_Int64Map,       // Meta
   hash_int64_c,     // HashFunc
   cmp_int64_c,      // CmpFunc
   do_not_ref_c_     // DoRef
)

