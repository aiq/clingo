#include "clingo/string/CStringList.h"

#include "clingo/io/cRecorder.h"
#include "clingo/io/write.h"
#include "clingo/lang/mem.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

OBJ_VEC_IMPL_C_(
   ,//optional       // Static
   CStringList,      // VecType
   CString,          // ObjType
   string_list_c,    // FuncName
   C_StringListMeta  // Meta
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

bool add_chars_slice_to_string_list_c( CStringList* list, cCharsSlice slice )
{
   must_exist_c_( list );

   CString** arr = alloc_array_c_( slice.s, CString* );
   if ( arr == NULL ) return false;

   int64_t n = 0;
   bool ok = true;
   for_each_c_( cChars const*, chars, slice )
   {
      CString* str = retain_c( make_string_c( *chars ) );
      ok = ( str != NULL );
      if ( not ok ) break;

      arr[n] = str;
      ++n;
   }
   if ( ok )
   {
      ok = add_array_to_string_list_c( list, n, arr );
   }
   for ( int64_t i = 0; i < n; ++i )
   {
      release_c( arr[i] );
   }
   free( arr );

   return ok;
}

CStringList* from_chars_slice_c( cCharsSlice slice )
{
   CStringList* list = make_string_list_c( slice.s );
   if ( list == NULL ) return NULL;

   if ( not add_chars_slice_to_string_list_c( list, slice ) )
   {
      release_c( list );
      return NULL;
   }

   return list;
}

/*******************************************************************************

*******************************************************************************/

extern inline bool add_chars_to_string_list_c( CStringList* list, cChars val );

extern inline bool add_cstr_to_string_list_c( CStringList* list,
                                              char const cstr[static 1] );

extern inline bool insert_chars_into_string_list_c( CStringList* list,
                                                    int64_t pos,
                                                    cChars val );

extern inline bool insert_cstr_into_string_list_c( CStringList* list,
                                                   int64_t pos,
                                                   char const cstr[static 1] );

extern inline bool set_chars_on_string_list_c( CStringList* list,
                                               int64_t pos,
                                               cChars val );

extern inline bool set_cstr_on_string_list_c( CStringList* list,
                                              int64_t pos,
                                              char const cstr[static 1] );

/*******************************************************************************

*******************************************************************************/

int64_t count_string_list_chars_c( CStringList const* list )
{
   must_exist_c_( list );

   cVecInfo const* info = info_of_string_list_c( list );

   int64_t result = 0;
   for ( int64_t i = 0; i < info->count; ++i )
   {
      CString const* str = get_from_string_list_c( list, i );
      result += scs_c( str ).s;
   }

   return result;
}

int64_t count_string_list_runes_c( CStringList const* list )
{
   must_exist_c_( list );

   cVecInfo const* info = info_of_string_list_c( list );

   int64_t result = 0;
   for ( int64_t i = 0; i < info->count; ++i )
   {
      CString const* str = get_from_string_list_c( list, i );
      result += string_length_c( str );
   }

   return result;
 }

/*******************************************************************************

*******************************************************************************/

CString* join_string_list_c( CStringList const* list, cChars sep )
{
   must_exist_c_( list );

   cVecInfo const* info = info_of_string_list_c( list );
   if ( info->count == 0 )
   {
      return empty_string_c();
   }

   // determine full length of string result

   int64_t const strLen = count_string_list_chars_c( list );
   int64_t const sepLen = ( info->count - 1 ) * sep.s;

   // create recorder
   int64_t const memSize = strLen + sepLen + 1;
   cRecorder* rec = &dyn_recorder_c_( memSize );
   if ( rec->mem == NULL )
   {
      return NULL;
   }

   // record the result
   CString const* first = get_from_string_list_c( list, 0 );
   record_chars_c( rec, scs_c( first ) );
   for ( int64_t i = 1; i < info->count; ++i )
   {
      record_chars_c( rec, sep );
      CString const* str = get_from_string_list_c( list, i );
      record_chars_c( rec, scs_c( str ) );
   }

   return adopt_cstr_c( turn_into_cstr_c( rec ) );
}

