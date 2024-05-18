#ifndef CLINGO_STRING_CSTRINGBUILDER_H
#define CLINGO_STRING_CSTRINGBUILDER_H

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/string/CString.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

struct cStringBuilder
{
   cRecorder rec;
   int64_t len;
};
typedef struct cStringBuilder cStringBuilder;

struct cStringBuilderMark
{
   int64_t pos;
   int64_t len;
};
typedef struct cStringBuilderMark cStringBuilderMark;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 create
*******************************************************************************/

CLINGO_API
bool init_string_builder_c( cStringBuilder b[static 1], int64_t cap );

CLINGO_API void cleanup_string_builder_c( cStringBuilder b[static 1] );

/*******************************************************************************
 manage
*******************************************************************************/

CLINGO_API void reset_string_builder_c( cStringBuilder b[static 1] );

CLINGO_API
bool resize_string_builder_c( cStringBuilder b[static 1], int64_t cap );

CLINGO_API
int64_t string_builder_byte_length_c( cStringBuilder const b[static 1] );

CLINGO_API int64_t string_builder_cap_c( cStringBuilder const b[static 1] );

CLINGO_API int64_t string_builder_length_c( cStringBuilder const b[static 1] );

CLINGO_API int64_t string_builder_space_c( cStringBuilder const b[static 1] );

/*******************************************************************************
 mark
*******************************************************************************/

CLINGO_API
cStringBuilderMark mark_string_builder_c( cStringBuilder b[static 1] );

CLINGO_API bool reset_string_builder_to_c( cStringBuilder b[static 1],
                                           cStringBuilderMark mark );

/*******************************************************************************
 access
*******************************************************************************/

CLINGO_API cChars built_chars_c( cStringBuilder const b[static 1] );

CLINGO_API char const* built_cstr_c( cStringBuilder const b[static 1] );

CLINGO_API CString* turn_into_string_c( cStringBuilder b[static 1] );

/*******************************************************************************
 append
*******************************************************************************/

CLINGO_API bool append_char_c( cStringBuilder b[static 1], char c );

CLINGO_API bool append_chars_c( cStringBuilder b[static 1], cChars chars );

CLINGO_API inline bool append_cstr_c( cStringBuilder b[static 1],
                                      char const cstr[static 1] )
{
   must_exist_c_( cstr );

   return append_chars_c( b, c_c( cstr ) );
}

CLINGO_API inline bool append_recorded_c( cStringBuilder b[static 1],
                                          cRecorder rec[static 1] )
{
   return append_chars_c( b, recorded_chars_c( rec ) );
}

CLINGO_API bool append_rune_c( cStringBuilder b[static 1], cRune r );

CLINGO_API
bool append_string_c( cStringBuilder b[static 1], CString const* str );

#endif
