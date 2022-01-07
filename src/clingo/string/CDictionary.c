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

extern inline bool chars_in_dictionary_c( CDictionary* dict, cChars key );

extern inline bool cstr_in_dictionary_c( CDictionary* dict,
                                         char const key[static 1] );

extern inline CString* get_via_chars_from_dictionary_c( CDictionary* dict,
                                                        cChars key );

extern inline
CString* get_via_cstr_from_dictionary_c( CDictionary* dict,
                                         char const key[static 1] );

extern inline bool remove_via_chars_from_dictionary_c( CDictionary* dict,
                                                       cChars key );

extern inline
bool remove_via_cstr_from_dictionary_c( CDictionary* dict,
                                        char const key[static 1] );

extern inline bool set_chars_on_dictionary_c( CDictionary* dict,
                                              cChars key,
                                              cChars val );

extern inline bool set_cstr_on_dictionary_c( CDictionary* dict,
                                             char const key[static 1],
                                             char const val[static 1] );

