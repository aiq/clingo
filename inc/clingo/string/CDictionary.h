#ifndef CLINGO_STR_CDICTIONARY_H
#define CLINGO_STR_CDICTIONARY_H

#include "clingo/container/map.h"
#include "clingo/string/CString.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

OBJ_OBJ_MAP_DEF_C_(
   CDictionary,      // MapType
   CString,          // KeyType
   CString,          // ValType
   dictionary_c,     // FuncSuffix
   C_DictionaryMeta  // Meta
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 wrap
*******************************************************************************/

inline bool chars_in_dictionary_c( CDictionary* dict, cChars key )
{
   must_exist_c_( dict );

   CString* keyStr = retain_c( make_string_c( key ) );
   if ( !keyStr ) return false;

   bool ok = in_dictionary_c( dict, keyStr );
   release_c( keyStr );
   return ok;
}

inline bool cstr_in_dictionary_c( CDictionary* dict,
                                  char const key[static 1] )
{
   must_exist_c_( dict );
   must_exist_c_( key );
   return chars_in_dictionary_c( dict, c_c( key ) );
}

inline CString* get_via_chars_from_dictionary_c( CDictionary* dict,
                                                 cChars key )
{
   must_exist_c_( dict );

   CString* keyStr = retain_c( make_string_c( key ) );
   if ( !keyStr ) return false;

   CString* result = get_from_dictionary_c( dict, keyStr );
   release_c( keyStr );
   return result;
}

inline CString* get_via_cstr_from_dictionary_c( CDictionary* dict,
                                                char const key[static 1] )
{
   must_exist_c_( dict );
   must_exist_c_( key );
   return get_via_chars_from_dictionary_c( dict, c_c( key ) );
}

inline bool remove_via_chars_from_dictionary_c( CDictionary* dict,
                                                cChars key )
{
   must_exist_c_( dict );

   CString* keyStr = retain_c( make_string_c( key ) );
   if ( !keyStr ) return false;

   bool ok = remove_from_dictionary_c( dict, keyStr );
   release_c( keyStr );
   return ok;
}

inline bool remove_via_cstr_from_dictionary_c( CDictionary* dict,
                                               char const key[static 1] )
{
   must_exist_c_( dict );
   must_exist_c_( key );
   return remove_via_chars_from_dictionary_c( dict, c_c( key ) );
}

inline bool set_chars_on_dictionary_c( CDictionary* dict,
                                       cChars key,
                                       cChars val )
{
   must_exist_c_( dict );

   CString* keyStr = retain_c( make_string_c( key ) );
   if ( !keyStr ) return false;

   CString* valStr = retain_c( make_string_c( val ) );
   if ( !valStr )
   {
      release_c( keyStr );
      return false;
   }

   bool ok = set_on_dictionary_c( dict, keyStr, valStr );
   release_c( keyStr );
   release_c( valStr );
   return ok;
}

inline bool set_cstr_on_dictionary_c( CDictionary* dict,
                                      char const key[static 1],
                                      char const val[static 1] )
{
   must_exist_c_( dict );
   must_exist_c_( key );
   must_exist_c_( val );
   return set_chars_on_dictionary_c( dict, c_c( key ), c_c( val ) );
}

#endif
