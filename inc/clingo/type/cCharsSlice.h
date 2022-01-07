#ifndef CLINGO_TYPE_CCHARS_SLICE_H
#define CLINGO_TYPE_CCHARS_SLICE_H

#include "clingo/type/cChars.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

SLICE_DEF_C_(
   cChars,           // Type
   cCharsSlice,      // SliceType
   chars_slice_c,    // FuncName
   cVarCharsSlice,   // VarSliceType
   var_chars_slice_c // VarFuncName
)

CHUNK_DEF_C_(
   cChars,           // Type
   cCharsChunk,      // ChunkType
   cCharsSlice,      // SliceType
   chars_chunk_c,    // FuncName
   cVarCharsChunk,   // VarChunkType
   cVarCharsSlice,   // VarSliceType
   var_chars_chunk_c // VarFuncName
)

WINDOW_DEF_C_(
   cChars,              // Type
   cCharsWindow,        // WindowType
   cCharsSlice,         // SliceType
   chars_window_c,      // FuncName
   cVarCharsWindow,     // VarWindowType
   cVarCharsSlice,      // VarSliceType
   var_chars_window_c   // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

#define cs_c_( ... )                                                           \
   init_chars_slice_c(                                                         \
      (cVarCharsSlice)structs_c_( nargs_c_( __VA_ARGS__ ), cChars ),           \
      nargs_c_( __VA_ARGS__ ),                                                 \
      (char const*[]){ __VA_ARGS__ }                                           \
   )

cCharsSlice init_chars_slice_c( cVarCharsSlice slice,
                                int64_t n,
                                char const* arr[static 1] );

/*******************************************************************************
 algo
*******************************************************************************/

int64_t count_eq_chars_c( cCharsSlice slice, cChars val );

cChars const* find_chars_c( cCharsSlice slice, cChars val );

void qsort_chars_slice_c( cVarCharsSlice slice );

/*******************************************************************************
 prop
*******************************************************************************/

int64_t count_chars_slice_c( cCharsSlice slice );

int64_t count_chars_slice_runes_c( cCharsSlice slice );

/*******************************************************************************
 util
*******************************************************************************/

#define chars_ends_with_any_c_( Chars, ... )                                   \
   chars_ends_with_any_c( (Chars), cs_c_( __VA_ARGS__ ) )
bool chars_ends_with_any_c( cChars chars, cCharsSlice slice );

#define chars_is_any_c_( Chars, ... )                                          \
   chars_is_any_c( (Chars), cs_c_( __VA_ARGS__ ) )
inline bool chars_is_any_c( cChars chars, cCharsSlice slice )
{
   return find_chars_c( slice, chars ) != NULL;
}

#define chars_starts_with_any_c_( Chars, ... )                                 \
   chars_starts_with_any_c( (Chars), cs_c_( __VA_ARGS__ ) )
bool chars_starts_with_any_c( cChars chars, cCharsSlice slice );

#define index_of_any_chars_c_( Chars, ... )                                    \
   index_of_any_chars_c( (Chars), cs_c_( __VA_ARGS__ ) )
int64_t index_of_any_chars_c( cChars chars, cCharsSlice slice );

#define join_chars_slice_c_( Slice, Sep, Buf )                                 \
   join_chars_slice_c( (Slice), c_c( Sep ), (Buf) )
cChars join_chars_slice_c( cCharsSlice slice, cChars sep, cVarChars buf );

#endif
