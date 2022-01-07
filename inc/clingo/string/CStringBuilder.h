#ifndef CLINGO_STR_CSTRING_BUILDER_H
#define CLINGO_STR_CSTRING_BUILDER_H

#include "clingo/io/cRecorder.h"
#include "clingo/string/CString.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

extern const cMeta C_StringBuilderMeta;

struct CStringBuilder;
typedef struct CStringBuilder CStringBuilder;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 create
*******************************************************************************/

CStringBuilder* make_string_builder_c( int64_t cap );

CStringBuilder* new_string_builder_c();

/*******************************************************************************
 manage
*******************************************************************************/

void reset_string_builder_c( CStringBuilder* builder );

bool resize_string_builder_c( CStringBuilder* builder, int64_t cap );

int64_t string_builder_byte_length_c( CStringBuilder const* builder );

int64_t string_builder_cap_c( CStringBuilder const* builder );

int64_t string_builder_length_c( CStringBuilder const* builder );

int64_t string_builder_space_c( CStringBuilder const* builder );

/*******************************************************************************
 access
*******************************************************************************/

cChars built_chars_c( CStringBuilder const* builder );

char const* built_cstr_c( CStringBuilder const* builder );

CString* turn_into_string_c( CStringBuilder* builder );

/*******************************************************************************
 append
*******************************************************************************/

bool append_char_c( CStringBuilder* builder, char c );

bool append_chars_c( CStringBuilder* builder, cChars chars );

inline bool append_cstr_c( CStringBuilder* builder, char const cstr[static 1] )
{
   must_exist_c_( builder );
   must_exist_c_( cstr );

   return append_chars_c( builder, c_c( cstr ) );
}

inline bool append_recorded_c( CStringBuilder* builder,
                               cRecorder rec[static 1] )
{
   must_exist_c_( builder );
   must_exist_c_( rec );

   return append_chars_c( builder, recorded_chars_c( rec ) );
}

bool append_rune_c( CStringBuilder* builder, cRune r );

bool append_string_c( CStringBuilder* builder, CString const* str );

#endif
