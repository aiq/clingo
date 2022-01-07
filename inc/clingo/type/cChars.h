#ifndef CLINGO_TYPE_CCHARS_H
#define CLINGO_TYPE_CCHARS_H

#include <stdbool.h>
#include <string.h>

#include "clingo/lang/chunk.h"
#include "clingo/lang/slice.h"
#include "clingo/lang/window.h"
#include "clingo/type/char.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

typedef int ( *c_check_char )( int c );

SLICE_DEF_C_(
   char,       // Type
   cChars,     // SliceType
   chars_c,    // FuncName
   cVarChars,  // VarSliceType
   var_chars_c // VarFuncName
)

CHUNK_DEF_C_(
   char,             // Type
   cCharChunk,       // ChunkType
   cChars,           // SliceType
   char_chunk_c,     // FuncName
   cVarCharChunk,    // VarChunkType
   cVarChars,        // VarSliceType
   var_char_chunk_c  // VarFuncName
)

WINDOW_DEF_C_(
   char,             // Type
   cCharWindow,      // WindowType
   cChars,           // SliceType
   char_window_c,    // FuncName
   cVarCharWindow,   // VarWindowType
   cVarChars,        // VarSliceType
   var_char_window_c // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

inline cChars c_c( char const cstr[static 1] )
{
   return chars_c( (int64_t)strlen( cstr ), cstr );
}

#define char_buffer_c_( Size )                                                 \
(                                                                              \
   (cVarChars)scalars_c_( (Size), char )                                       \
)

bool chars_is_c( cChars chars, char const cstr[static 1] );

#define cstr_is_any_char_c_( Cstr, Set )                                       \
   cstr_is_any_char_c( (Cstr), c_c( Set ) )
bool cstr_is_any_char_c( char const cstr[static 1], cChars set );

inline bool cstr_is_c( char const cstr[static 1], char const exp[static 1] )
{
   return chars_is_c( c_c( exp ), cstr );
}

inline bool cstr_is_char_c( char const cstr[static 1], char c )
{
   return *cstr == c and *(++cstr) == '\0';
}

bool eq_chars_c( cChars a, cChars b );

#define make_cstr_c_( Buf, Cstr )                                              \
   make_cstr_c( (Buf), c_c( Cstr ) )
char* make_cstr_c( cVarChars buf, cChars cs );

/*******************************************************************************
 algo
*******************************************************************************/

#define chars_ends_with_c_( Chars, Cstr )                                      \
   chars_ends_with_c( (Chars), c_c( Cstr ) )
bool chars_ends_with_c( cChars chars, cChars needle );

#define chars_starts_with_c_( Chars, Cstr )                                    \
   chars_starts_with_c( (Chars), c_c( Cstr ) )
bool chars_starts_with_c( cChars chars, cChars needle );

#define cmp_chars_c_( Chars, Cstr )                                            \
   cmp_chars_c( (Chars), c_c( Cstr ) )
int cmp_chars_c( cChars a, cChars b );

int64_t count_eq_char_c( cChars chars, char val );

#define find_any_char_c_( Chars, Cstr )                                        \
   find_any_char_c( (Chars), c_c( Cstr ) )
char const* find_any_char_c( cChars chars, cChars set );

char const* find_char_c( cChars chars, char val );

#define index_of_chars_c_( Chars, Cstr )                                       \
   index_of_chars_c( (Chars), c_c( Cstr ) )
int64_t index_of_chars_c( cChars chars, cChars sub );

#define set_chars_c_( Chars, Cstr )                                            \
   set_chars_c( (Chars), c_c( Cstr ) )

int64_t insert_char_c( cVarChars chars, int64_t index, char c );

#define insert_chars_c_( Chars, Index, Cstr )                                  \
   insert_chars_c( (Chars), (Index), c_c( Cstr ) )
int64_t insert_chars_c( cVarChars dst, int64_t index, cChars src );

void qsort_chars_c( cVarChars chars );

void reverse_chars_c( cVarChars chars );

void rotate_chars_c( cVarChars chars, int64_t distance );

/*******************************************************************************
 trim
*******************************************************************************/

#define trim_any_char_c_( Chars, Cstr )                                        \
   trim_any_char_c( (Chars), c_c( Cstr ) )
cChars trim_any_char_c( cChars chars, cChars set );

#define trim_any_char_left_c_( Chars, Cstr )                                   \
   trim_any_char_left_c( (Chars), c_c( Cstr ) )
cChars trim_any_char_left_c( cChars chars, cChars set );

#define trim_any_char_right_c_( Chars, Cstr )                                  \
   trim_any_char_right_c( (Chars), c_c( Cstr ) )
cChars trim_any_char_right_c( cChars chars, cChars set );

cChars trim_char_match_c( cChars chars, c_check_char check );

cChars trim_char_match_left_c( cChars chars, c_check_char check );

cChars trim_char_match_right_c( cChars chars, c_check_char check );

#endif
