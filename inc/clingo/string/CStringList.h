#ifndef CLINGO_STRING_CSTRINGLIST_H
#define CLINGO_STRING_CSTRINGLIST_H

#include "clingo/apidecl.h"
#include "clingo/container/vec.h"
#include "clingo/io/cRecorder.h"
#include "clingo/string/CString.h"
#include "clingo/type/cCharsSlice.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

OBJ_VEC_DEF_C_(
   CLINGO_API,       // LibApi
   CStringList,      // VecType
   CString,          // ObjType
   string_list_c,    // FuncSuffix
   C_StringList      // Meta
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

CLINGO_API bool add_chars_slice_to_string_list_c( CStringList* list, cCharsSlice slice );

CLINGO_API CStringList* from_chars_slice_c( cCharsSlice slice );

/*******************************************************************************

*******************************************************************************/

CLINGO_API inline bool add_chars_to_string_list_c( CStringList* list, cChars val )
{
   must_exist_c_( list );

   CString* valStr = retain_c( make_string_c( val ) );
   if ( valStr == NULL )
   {
      return false;
   }
   bool ok = add_to_string_list_c( list, valStr );
   release_c( valStr );
   return ok;
}

CLINGO_API inline bool add_cstr_to_string_list_c( CStringList* list,
                                                  char const cstr[static 1] )
{
   must_exist_c_( list );
   must_exist_c_( cstr );
   return add_chars_to_string_list_c( list, c_c( cstr ) );
}

CLINGO_API inline bool insert_chars_into_string_list_c( CStringList* list,
                                             int64_t pos,
                                             cChars val )
{
   must_exist_c_( list );

   CString* valStr = retain_c( make_string_c( val ) );
   if ( valStr == NULL )
   {
      return false;
   }
   bool ok = insert_into_string_list_c( list, pos, valStr );
   release_c( valStr );
   return ok;
}

CLINGO_API inline bool insert_cstr_into_string_list_c( CStringList* list,
                                            int64_t pos,
                                            char const cstr[static 1] )
{
   must_exist_c_( list );
   must_exist_c_( cstr );
   return insert_chars_into_string_list_c( list, pos, c_c( cstr ) );
}

CLINGO_API inline bool set_chars_on_string_list_c( CStringList* list,
                                        int64_t pos,
                                        cChars val )
{
   must_exist_c_( list );

   CString* valStr = retain_c( make_string_c( val ) );
   if ( valStr == NULL )
   {
      return false;
   }
   set_on_string_list_c( list, pos, valStr );
   release_c( valStr );
   return true;
}

CLINGO_API inline bool set_cstr_on_string_list_c( CStringList* list,
                                       int64_t pos,
                                       char const cstr[static 1] )
{
   must_exist_c_( list );
   must_exist_c_( list );
   return set_chars_on_string_list_c( list, pos, c_c( cstr ) );
}

/*******************************************************************************

*******************************************************************************/

CLINGO_API int64_t count_string_list_chars_c( CStringList const* list );

CLINGO_API int64_t count_string_list_runes_c( CStringList const* list );

/*******************************************************************************

*******************************************************************************/

#define join_string_list_c_( List, CStr )                                      \
   join_string_list_c( (List), c_c( CStr ) )
CLINGO_API CString* join_string_list_c( CStringList const* list, cChars sep );

CLINGO_API void sort_string_list_c( CStringList* list );

#endif
