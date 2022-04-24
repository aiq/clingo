#ifndef CLINGO_STR_CSTRING_BUILDER_H
#define CLINGO_STR_CSTRING_BUILDER_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/string/CString.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

CLINGO_API extern const cMeta C_StringBuilderMeta;

struct CStringBuilder;
typedef struct CStringBuilder CStringBuilder;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 create
*******************************************************************************/

CLINGO_API CStringBuilder* make_string_builder_c( int64_t cap );

CLINGO_API CStringBuilder* new_string_builder_c();

/*******************************************************************************
 manage
*******************************************************************************/

CLINGO_API void reset_string_builder_c( CStringBuilder* builder );

CLINGO_API bool resize_string_builder_c( CStringBuilder* builder, int64_t cap );

CLINGO_API int64_t string_builder_byte_length_c( CStringBuilder const* builder );

CLINGO_API int64_t string_builder_cap_c( CStringBuilder const* builder );

CLINGO_API int64_t string_builder_length_c( CStringBuilder const* builder );

CLINGO_API int64_t string_builder_space_c( CStringBuilder const* builder );

/*******************************************************************************
 access
*******************************************************************************/

CLINGO_API cChars built_chars_c( CStringBuilder const* builder );

CLINGO_API char const* built_cstr_c( CStringBuilder const* builder );

CLINGO_API CString* turn_into_string_c( CStringBuilder* builder );

/*******************************************************************************
 append
*******************************************************************************/

CLINGO_API bool append_char_c( CStringBuilder* builder, char c );

CLINGO_API bool append_chars_c( CStringBuilder* builder, cChars chars );

CLINGO_API inline bool append_cstr_c( CStringBuilder* builder, char const cstr[static 1] )
{
   must_exist_c_( builder );
   must_exist_c_( cstr );

   return append_chars_c( builder, c_c( cstr ) );
}

CLINGO_API inline bool append_recorded_c( CStringBuilder* builder,
                               cRecorder rec[static 1] )
{
   must_exist_c_( builder );
   must_exist_c_( rec );

   return append_chars_c( builder, recorded_chars_c( rec ) );
}

CLINGO_API bool append_rune_c( CStringBuilder* builder, cRune r );

CLINGO_API bool append_string_c( CStringBuilder* builder, CString const* str );

#endif
