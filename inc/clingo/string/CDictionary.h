#ifndef CLINGO_STRING_CDICTIONARY_H
#define CLINGO_STRING_CDICTIONARY_H

#include "clingo/apidecl.h"
#include "clingo/container/map.h"
#include "clingo/string/CString.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

OBJ_OBJ_MAP_DEF_C_(
   CLINGO_API,       // LibApi
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

#define in_dictionary_c_( Dict, Key )                                          \
   chars_in_dictionary_c( (Dict), c_c( Key) )

#define get_from_dictionary_c_( Dict, Key )                                    \
   get_via_chars_from_dictionary_c( (Dict), c_c( Key ) )

#define remove_from_dictionary_c_( Dict, Key )                                 \
   remove_via_chars_from_dictionary_c( (Dict), c_c( Key ) )

#define set_on_dictionary_c_( Dict, Key, Val )                                 \
   set_via_chars_on_dictionary_c( (Dict), c_c( Key ), c_c( Val ) )

/*******************************************************************************

*******************************************************************************/

CLINGO_API inline bool chars_in_dictionary_c( CDictionary* dict, cChars key )
{
   must_exist_c_( dict );

   CString* keyStr = retain_c( make_string_c( key ) );
   if ( !keyStr ) return false;

   bool ok = in_dictionary_c( dict, keyStr );
   release_c( keyStr );
   return ok;
}

CLINGO_API inline CString* get_via_chars_from_dictionary_c( CDictionary* dict,
                                                 cChars key )
{
   must_exist_c_( dict );

   CString* keyStr = retain_c( make_string_c( key ) );
   if ( !keyStr ) return false;

   CString* result = get_from_dictionary_c( dict, keyStr );
   release_c( keyStr );
   return result;
}

CLINGO_API inline bool remove_via_chars_from_dictionary_c( CDictionary* dict,
                                                           cChars key )
{
   must_exist_c_( dict );

   CString* keyStr = retain_c( make_string_c( key ) );
   if ( !keyStr ) return false;

   bool ok = remove_from_dictionary_c( dict, keyStr );
   release_c( keyStr );
   return ok;
}

CLINGO_API inline bool set_via_chars_on_dictionary_c( CDictionary* dict,
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

#endif
