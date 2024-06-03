#include "clingo/string/CString.h"

#include <string.h>

#include "clingo/lang/func.h"
#include "clingo/type/cRune.h"
#include "clingo/type/uint64.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

struct CString
{
   union
   {
      cChars chars;
      cVarChars varChars;
   };
   int64_t len;
};

static inline void cleanup( void* instance )
{
   CString* str = instance;
   if ( str->varChars.v )
   {
      free( str->varChars.v );
   }
}

cMeta const C_StringMeta = {
   .desc = stringify_c_( CString ),
   .cleanup = &cleanup
};

static cByte emptyStringBuffer[ sizeof_object_c_( CString ) ];
static CString* emptyString = NULL;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

CString* adopt_cstr_c( char cstr[static 1] )
{
   must_exist_c_( cstr );

   cChars chars = c_c( cstr );
   if ( chars.s == 0 )
   {
      return empty_string_c();
   }

   int64_t len = count_runes_c( chars );
   if ( len < 0 )
   {
      return NULL;
   }

   CString* result = new_object_c_( CString, &C_StringMeta );
   if ( result == NULL )
   {
      return NULL;
   }

   result->varChars.v = cstr;
   result->varChars.s = chars.s;
   if ( result->varChars.v == NULL )
   {
      release_c( result );
      return NULL;
   }

   result->len = len;

   return result;
}

/**************************************/

CString* adopt_recorded_c( cRecorder rec[static 1] )
{
   if ( not realloc_recorder_mem_c( rec, rec->pos + 1 ) )
   {
      return NULL;
   }

   int64_t oldPos = rec->pos;
   char* cstr = turn_into_cstr_c( rec );
   CString* res = adopt_cstr_c( cstr );
   if ( res == NULL )
   {
      move_recorder_to_c( rec, oldPos );
      return NULL;
   }

   *rec = null_recorder_c_();
   return res;
}

/**************************************/

CString* empty_string_c( void )
{
   if ( emptyString == NULL )
   {
      cObjectInfo* info = &object_info_c_( &C_StringMeta, 0 );
      emptyString = init_object_c( emptyStringBuffer, info );
      if ( emptyString == NULL )
      {
         return NULL;
      }
      emptyString->chars = (cChars){ 0, "" };
   }
   return emptyString;
}

/**************************************/

CString* new_string_c( char const cstr[static 1] )
{
   return make_string_c( c_c( cstr ) );
}

/**************************************/

CString* make_string_c( cChars chars )
{
   if ( chars.s == 0 )
   {
      return empty_string_c();
   }

   int64_t len = count_runes_c( chars );
   if ( len < 0 )
   {
      return NULL;
   }

   CString* result = new_object_c_( CString, &C_StringMeta );
   if ( result == NULL )
   {
      return NULL;
   }

   result->varChars.v = alloc_array_c_( chars.s + 1, char );
   result->varChars.s = chars.s;
   if ( result->varChars.v == NULL )
   {
      release_c( result );
      return NULL;
   }

   result->varChars.s = set_chars_c( result->varChars, chars );
   result->varChars.v[ chars.s ] = '\0';
   result->len = len;

   return result;
}

/**************************************/

CString* lit_c( char const cstr[static 1] )
{
   must_exist_c_( cstr );

   cChars chars = c_c( cstr );
   if ( chars.s == 0 )
   {
      return empty_string_c();
   }

   int64_t len = count_runes_c( chars );
   if ( len == 0 )
   {
      return NULL;
   }

   cObjectInfo const info = object_info_c_( &C_StringMeta, c_Release );
   CString* result = alloc_object_c_( CString, &info );
   if ( result == NULL )
   {
      return NULL;
   }

   result->chars = chars;
   result->len = len;

   return result;
}

/*******************************************************************************

*******************************************************************************/

bool is_ascii_string_c( CString const* str )
{
   must_exist_c_( str );

   return ( str->chars.s == str->len ) ? true
                                       : false;
}

int64_t string_byte_length_c( CString const* str )
{
   must_exist_c_( str );
   return str->chars.s;
}

cChars sc_c( CString const* str )
{
   must_exist_c_( str );
   return str->chars;
}

char const* scstr_c( CString const* str )
{
   must_exist_c_( str );
   return str->chars.v;
}

bool string_is_empty_c( CString const* str )
{
   must_exist_c_( str );

   return is_empty_c_( str->chars );
}

int64_t string_length_c( CString const* str )
{
   must_exist_c_( str );
   return str->len;
}

/*******************************************************************************
 cmp
*******************************************************************************/

int cmp_string_c( CString const* a, CString const* b )
{
   must_exist_c_( a );
   must_exist_c_( b );

   return cmp_chars_c( a->chars, b->chars );
}

extern inline bool eq_string_c( CString const* a, CString const* b );

uint64_t hash_string_c( CString const* str )
{
   must_exist_c_( str );

   uint64_t hash = 5381;

   char const* itr = begin_c_( str->chars );
   char const* end = end_c_( str->chars );
   for ( ; itr != end; ++itr )
   {
      hash = ( ( hash << 5 ) + hash ) + uint64_c_( *itr );
   }

   return hash;
}

bool string_is_c( CString const* str, char const cstr[static 1] )
{
   must_exist_c_( str );

   return eq_c( cmp_chars_c( str->chars, c_c( cstr ) ) );
}

/*******************************************************************************
 sub
*******************************************************************************/

extern inline cChars left_string_c( CString const* s, int64_t maxLen );
extern inline CString* new_left_string_c( CString const* s, int64_t maxLen );
extern inline cChars mid_string_c( CString const* s, int64_t index );
extern inline CString* new_mid_string_c( CString const* s, int64_t index );
extern inline cChars right_string_c( CString const* s, int64_t maxLen );
extern inline CString* new_right_string_c( CString const* s, int64_t maxLen );
extern inline
cChars sub_string_c( CString const* s, int64_t min, int64_t max );
extern inline
CString* new_sub_string_c( CString const* s, int64_t min, int64_t max );

