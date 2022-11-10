#ifndef CLINGO_TYPE_CCHARSSLICE_H
#define CLINGO_TYPE_CCHARSSLICE_H

#include "clingo/apidecl.h"
#include "clingo/type/cChars.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

SLICES_C_(
   cChars,        // Type
   cCharsSlice,   // SliceType
   cVarCharsSlice // VarSliceType
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

CLINGO_API
cCharsSlice init_chars_slice_c( cVarCharsSlice slice,
                                int64_t n,
                                char const* arr[static 1] );

/*******************************************************************************
 algo
*******************************************************************************/

CLINGO_API int64_t count_eq_chars_c( cCharsSlice slice, cChars val );

CLINGO_API cChars const* find_chars_c( cCharsSlice slice, cChars val );

CLINGO_API void qsort_chars_slice_c( cVarCharsSlice slice );

/*******************************************************************************
 prop
*******************************************************************************/

CLINGO_API int64_t count_chars_slice_c( cCharsSlice slice );

CLINGO_API int64_t count_chars_slice_runes_c( cCharsSlice slice );

/*******************************************************************************
 util
*******************************************************************************/

#define chars_ends_with_any_c_( Chars, ... )                                   \
   chars_ends_with_any_c( (Chars), cs_c_( __VA_ARGS__ ) )
CLINGO_API bool chars_ends_with_any_c( cChars chars, cCharsSlice slice );

#define chars_is_any_c_( Chars, ... )                                          \
   chars_is_any_c( (Chars), cs_c_( __VA_ARGS__ ) )
CLINGO_API inline bool chars_is_any_c( cChars chars, cCharsSlice slice )
{
   return find_chars_c( slice, chars ) != NULL;
}

#define chars_starts_with_any_c_( Chars, ... )                                 \
   chars_starts_with_any_c( (Chars), cs_c_( __VA_ARGS__ ) )
CLINGO_API bool chars_starts_with_any_c( cChars chars, cCharsSlice slice );

#define index_of_any_chars_c_( Chars, ... )                                    \
   index_of_any_chars_c( (Chars), cs_c_( __VA_ARGS__ ) )
CLINGO_API int64_t index_of_any_chars_c( cChars chars, cCharsSlice slice );

#define join_chars_slice_c_( Slice, Sep, Buf )                                 \
   join_chars_slice_c( (Slice), c_c( Sep ), (Buf) )
CLINGO_API cChars join_chars_slice_c( cCharsSlice slice, cChars sep, cVarChars buf );

#endif
