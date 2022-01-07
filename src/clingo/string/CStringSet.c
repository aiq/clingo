#include "clingo/string/CStringSet.h"

/*******************************************************************************

*******************************************************************************/

OBJ_SET_IMPL_C_(
   ,                 // Static
   CStringSet,       // SetType
   cStringSetRow,    // RowType
   CString,          // ObjType
   string_set_c,     // FuncSuffix
   C_StringSetMeta,  // Meta
   hash_string_c,    // HashFunc
   cmp_string_c      // CmpFunc
)

/*******************************************************************************
 wrap
*******************************************************************************/

extern inline bool chars_in_string_set_c( CStringSet* set, cChars val );

extern inline
bool remove_chars_from_string_set_c( CStringSet* set, cChars val );

extern inline bool set_chars_on_string_set_c( CStringSet* set, cChars val );

