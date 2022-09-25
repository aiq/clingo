#ifndef CLINGO_TYPE_CCHARS_H
#define CLINGO_TYPE_CCHARS_H

#include <stdbool.h>
#include <string.h>

#include "clingo/apidecl.h"
#include "clingo/lang/slice.h"
#include "clingo/type/char.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

typedef int ( *c_check_char )( int c );

SLICE_DEF_C_(
   char,       // Type
   cChars,     // SliceType
   cVarChars   // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

CLINGO_API inline cChars c_c( char const cstr[static 1] )
{
   return (cChars){ (int64_t)strlen( cstr ), cstr };
}

#define char_buffer_c_( Size )                                                 \
(                                                                              \
   (cVarChars)scalars_c_( (Size), char )                                       \
)

CLINGO_API bool chars_is_c( cChars chars, char const cstr[static 1] );

#define cstr_is_any_char_c_( Cstr, Set )                                       \
   cstr_is_any_char_c( (Cstr), c_c( Set ) )
CLINGO_API
bool cstr_is_any_char_c( char const cstr[static 1], cChars set );

CLINGO_API
inline bool cstr_is_c( char const cstr[static 1], char const exp[static 1] )
{
   return chars_is_c( c_c( exp ), cstr );
}

CLINGO_API
inline bool cstr_is_char_c( char const cstr[static 1], char c )
{
   return *cstr == c and *(++cstr) == '\0';
}

CLINGO_API bool eq_chars_c( cChars a, cChars b );

#define make_cstr_c_( Buf, Cstr )                                              \
   make_cstr_c( (Buf), c_c( Cstr ) )
CLINGO_API
char* make_cstr_c( cVarChars buf, cChars cs );

/*******************************************************************************
 algo
*******************************************************************************/

#define chars_ends_with_c_( Chars, Cstr )                                      \
   chars_ends_with_c( (Chars), c_c( Cstr ) )
CLINGO_API bool chars_ends_with_c( cChars chars, cChars needle );

#define chars_starts_with_c_( Chars, Cstr )                                    \
   chars_starts_with_c( (Chars), c_c( Cstr ) )
CLINGO_API bool chars_starts_with_c( cChars chars, cChars needle );

#define cmp_chars_c_( Chars, Cstr )                                            \
   cmp_chars_c( (Chars), c_c( Cstr ) )
CLINGO_API int cmp_chars_c( cChars a, cChars b );

CLINGO_API int64_t count_eq_char_c( cChars chars, char val );

#define find_any_char_c_( Chars, Cstr )                                        \
   find_any_char_c( (Chars), c_c( Cstr ) )
CLINGO_API char const* find_any_char_c( cChars chars, cChars set );

CLINGO_API char const* find_char_c( cChars chars, char val );

#define index_of_chars_c_( Chars, Cstr )                                       \
   index_of_chars_c( (Chars), c_c( Cstr ) )
CLINGO_API int64_t index_of_chars_c( cChars chars, cChars sub );

CLINGO_API int64_t insert_char_c( cVarChars chars, int64_t index, char c );

#define insert_chars_c_( Chars, Index, Cstr )                                  \
   insert_chars_c( (Chars), (Index), c_c( Cstr ) )
CLINGO_API int64_t insert_chars_c( cVarChars dst, int64_t index, cChars src );

CLINGO_API void qsort_chars_c( cVarChars chars );

CLINGO_API void reverse_chars_c( cVarChars chars );

CLINGO_API void rotate_chars_c( cVarChars chars, int64_t distance );

#define set_chars_c_( Chars, Cstr )                                            \
   set_chars_c( (Chars), c_c( Cstr ) )
CLINGO_API int64_t set_chars_c( cVarChars dst, cChars src ); 

/*******************************************************************************
 trim
*******************************************************************************/

#define trim_any_char_c_( Chars, Cstr )                                        \
   trim_any_char_c( (Chars), c_c( Cstr ) )
CLINGO_API cChars trim_any_char_c( cChars chars, cChars set );

#define trim_any_char_left_c_( Chars, Cstr )                                   \
   trim_any_char_left_c( (Chars), c_c( Cstr ) )
CLINGO_API cChars trim_any_char_left_c( cChars chars, cChars set );

#define trim_any_char_right_c_( Chars, Cstr )                                  \
   trim_any_char_right_c( (Chars), c_c( Cstr ) )
CLINGO_API cChars trim_any_char_right_c( cChars chars, cChars set );

CLINGO_API cChars trim_char_match_c( cChars chars, c_check_char check );

CLINGO_API cChars trim_char_match_left_c( cChars chars, c_check_char check );

CLINGO_API cChars trim_char_match_right_c( cChars chars, c_check_char check );

#endif
