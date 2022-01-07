#ifndef CLINGO_STR_CSTRING_LIST_H
#define CLINGO_STR_CSTRING_LIST_H

#include "clingo/container/vec.h"
#include "clingo/io/cRecorder.h"
#include "clingo/string/CString.h"
#include "clingo/type/cCharsSlice.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

OBJ_VEC_DEF_C_(
   CStringList,      // VecType
   CString,          // ObjType
   string_list_c,    // FuncName
   C_StringListMeta  // Meta
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/


bool add_chars_slice_to_string_list_c( CStringList* list, cCharsSlice slice );

CStringList* from_chars_slice_c( cCharsSlice slice );

/*******************************************************************************

*******************************************************************************/

inline bool add_chars_to_string_list_c( CStringList* list, cChars val )
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

inline bool add_cstr_to_string_list_c( CStringList* list,
                                       char const cstr[static 1] )
{
   must_exist_c_( list );
   must_exist_c_( cstr );
   return add_chars_to_string_list_c( list, c_c( cstr ) );
}

inline bool insert_chars_into_string_list_c( CStringList* list,
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

inline bool insert_cstr_into_string_list_c( CStringList* list,
                                            int64_t pos,
                                            char const cstr[static 1] )
{
   must_exist_c_( list );
   must_exist_c_( cstr );
   return insert_chars_into_string_list_c( list, pos, c_c( cstr ) );
}

inline bool set_chars_on_string_list_c( CStringList* list,
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

inline bool set_cstr_on_string_list_c( CStringList* list,
                                       int64_t pos,
                                       char const cstr[static 1] )
{
   must_exist_c_( list );
   must_exist_c_( list );
   return set_chars_on_string_list_c( list, pos, c_c( cstr ) );
}

/*******************************************************************************

*******************************************************************************/

int64_t count_string_list_chars_c( CStringList const* list );

int64_t count_string_list_runes_c( CStringList const* list );

/*******************************************************************************

*******************************************************************************/

#define join_string_list_c_( List, CStr )                                      \
   join_string_list_c( (List), c_c( CStr ) )
CString* join_string_list_c( CStringList const* list, cChars sep );

#endif
