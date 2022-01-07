#ifndef CLINGO_STR_CSTRING_SET_H
#define CLINGO_STR_CSTRING_SET_H

#include "clingo/container/set.h"
#include "clingo/string/CString.h"

/*******************************************************************************

*******************************************************************************/

OBJ_SET_DEF_C_(
   CStringSet,       // SetType
   CString,          // ObjType
   string_set_c,     // FuncSuffix
   C_StringSetMeta   // Meta
)

/*******************************************************************************
 wrap
*******************************************************************************/

inline bool chars_in_string_set_c( CStringSet* set, cChars val )
{
   must_exist_c_( set );

   CString* valStr = retain_c( make_string_c( val ) );
   if ( !valStr ) return false;

   bool ok = in_string_set_c( set, valStr );
   release_c( set );
   return ok;
}

inline bool remove_chars_from_string_set_c( CStringSet* set, cChars val )
{
   must_exist_c_( set );

   CString* valStr = retain_c( make_string_c( val ) );
   if ( !valStr ) return false;

   bool ok = remove_from_string_set_c( set, valStr );
   release_c( valStr );
   return ok;
}

inline bool set_chars_on_string_set_c( CStringSet* set, cChars val )
{
   must_exist_c_( set );

   CString* valStr = retain_c( make_string_c( val ) );
   if ( !valStr ) return false;

   bool ok = set_on_string_set_c( set, valStr );
   release_c( valStr );
   return ok;
}

#endif
