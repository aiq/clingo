#include "clingo/container/CInt64Set.h"

/*******************************************************************************

*******************************************************************************/

VAL_SET_IMPL_C_(
   ,                 // Static
   CInt64Set,        // SetType
   cInt64SetRow,     // RowType
   int64_t,          // ObjType
   int64_set_c,      // FuncSuffix
   C_Int64Set,       // Meta
   hash_int64_c,     // HashFunc
   cmp_int64_c,      // CmpFunc
   do_not_ref_c_     // DoRef
)

