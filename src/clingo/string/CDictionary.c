#include "clingo/string/CDictionary.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

OBJ_OBJ_MAP_IMPL_C_(
   ,                 // Static
   CDictionary,      // MapType
   cDictionaryRow,   // RowType
   CString,          // KeyType
   CString,          // ValType
   dictionary_c,     // FuncSuffix
   C_DictionaryMeta, // Meta
   hash_string_c,    // HashFunc
   cmp_string_c      // CmpFunc
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 wrap
*******************************************************************************/

extern inline bool via_chars_in_dictionary_c( CDictionary* dict, cChars key );

extern inline CString* get_via_chars_from_dictionary_c( CDictionary* dict,
                                                        cChars key );

extern inline bool remove_via_chars_from_dictionary_c( CDictionary* dict,
                                                       cChars key );

extern inline bool set_via_chars_on_dictionary_c( CDictionary* dict,
                                                  cChars key,
                                                  cChars val );
