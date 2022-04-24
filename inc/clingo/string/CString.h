#ifndef CLINGO_STR_CSTRING_H
#define CLINGO_STR_CSTRING_H

#include "clingo/apidecl.h"
#include "clingo/lang/CObject.h"
#include "clingo/type/char.h"
#include "clingo/type/cRange.h"
#include "clingo/type/cRune.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

CLINGO_API extern cMeta const C_StringMeta;

struct CString;
typedef struct CString CString;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 create
*******************************************************************************/

CLINGO_API CString* adopt_cstr_c( char cstr[static 1] );

CLINGO_API CString* empty_string_c();

CLINGO_API CString* make_string_c( cChars chars );

CLINGO_API CString* new_string_c( char const cstr[static 1] );

CLINGO_API CString* str_c( char const cstr[static 1] );

/*******************************************************************************
 prop
*******************************************************************************/

CLINGO_API bool is_ascii_string_c( CString const* str );

CLINGO_API int64_t string_byte_length_c( CString const* str );

CLINGO_API cChars string_chars_c( CString const* str );

CLINGO_API char const* string_cstr_c( CString const* str );

CLINGO_API bool string_is_empty_c( CString const* str );

CLINGO_API int64_t string_length_c( CString const* str );

/*******************************************************************************
 cmp
*******************************************************************************/

CLINGO_API int cmp_string_c( CString const* a, CString const* b );

CLINGO_API inline bool eq_string_c( CString const* a, CString const* b )
{
   return cmp_string_c( a, b ) == 0;
}

CLINGO_API uint64_t hash_string_c( CString const* str );

CLINGO_API bool string_is_c(  CString const* str, char const cstr[static 1] );

/*******************************************************************************
 sub
*******************************************************************************/

CLINGO_API inline cChars left_string_c( CString const* s, int64_t maxLen )
{
   return left_chars_c( string_chars_c( s ), maxLen );
}

CLINGO_API inline CString* new_left_string_c( CString const* s, int64_t maxLen )
{
   return make_string_c( left_string_c( s, maxLen ) );
}

CLINGO_API inline cChars mid_string_c( CString const* s, int64_t index )
{
   return mid_chars_c( string_chars_c( s ), index );
}

CLINGO_API inline CString* new_mid_string_c( CString const* s, int64_t index )
{
   return make_string_c( mid_string_c( s, index ) );
}

CLINGO_API inline cChars right_string_c( CString const* s, int64_t maxLen )
{
   return right_chars_c( string_chars_c( s ), maxLen );
}

CLINGO_API inline CString* new_right_string_c( CString const* s, int64_t maxLen )
{
   return make_string_c( right_string_c( s, maxLen ) );
}

CLINGO_API inline cChars sub_string_c( CString const* s, int64_t min, int64_t max )
{
   return sub_chars_c( string_chars_c( s ), min, max );
}

CLINGO_API inline CString* new_sub_string_c( CString const* s, int64_t min, int64_t max )
{
   return make_string_c( sub_string_c( s, min, max ) );
}

#endif
