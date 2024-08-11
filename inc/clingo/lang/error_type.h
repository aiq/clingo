#ifndef CLINGO_IO_ERRORTYPE_H
#define CLINGO_IO_ERRORTYPE_H

#include "clingo/lang/error.h"

/*******************************************************************************
******************************************************** Code Generation Macros 
*******************************************************************************/

#define SINGLE_ERROR_TYPE_C_( Type, NoteFunc, Note )                           \
static bool NoteFunc( cRecorder rec[static 1], cError const* err )             \
{                                                                              \
   must_be_c_( err->type == &Type );                                           \
   return record_chars_c_( rec, Note );                                        \
}                                                                              \
cErrorType const Type = {                                                      \
   .desc = stringify_c_( Type ),                                               \
   .note = &NoteFunc                                                           \
};

#define QUOTE_LIT_ERROR_TYPE_C_( Type, NoteFunc, WriteText, PushFunc )         \
static bool NoteFunc( cRecorder rec[static 1], cError const* err )             \
{                                                                              \
   must_be_c_( err->type == &Type );                                           \
   cLitErrorData const* errd = get_error_data_c( err );                        \
   return write_c_( rec, WriteText, errd->str );                               \
}                                                                              \
cErrorType const Type = {                                                      \
   .desc = stringify_c_( Type ),                                               \
   .note = &NoteFunc                                                           \
};                                                                             \
bool PushFunc( cErrorStack es[static 1], char const str[static 1] )            \
{                                                                              \
   cLitErrorData d = { .str=str };                                             \
   return push_error_c( es, &Type, &d, sizeof_c_( cLitErrorData ) );           \
}

/*******************************************************************************
************************************************************************* types
********************************************************************************
 basic
*******************************************************************************/

CLINGO_API extern cErrorType const C_ErrnoError;

struct cErrnoErrorData {
   int number;
};
typedef struct cErrnoErrorData cErrnoErrorData;

CLINGO_API bool push_errno_error_c( cErrorStack es[static 1],
                                    int number );

/*******************************************************************************
 
*******************************************************************************/

CLINGO_API extern cErrorType const C_LitError;

struct cLitErrorData {
   char const* str;
};
typedef struct cLitErrorData cLitErrorData;

CLINGO_API bool push_lit_error_c( cErrorStack es[static 1],
                                  char const cstr[static 1] );

/*******************************************************************************
 
*******************************************************************************/

CLINGO_API extern cErrorType const C_TextError;

struct cTextErrorData {
   char const* str;
};
typedef struct cTextErrorData cTextErrorData;

#define push_text_error_c_( Es, ... )                                          \
   push_text_error_c( (Es), nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API bool push_text_error_c( cErrorStack es[static 1],
                                   int n,
                                   ... );

/*******************************************************************************
 
*******************************************************************************/

CLINGO_API extern cErrorType const C_OverflowError;

struct cOverflowErrorData {
   uint8_t op;
   uint64_t a;
   uint64_t b;
};
typedef struct cOverflowErrorData cOverflowErrorData;

CLINGO_API
bool push_iadd8_error_c( cErrorStack es[static 1], int8_t a, int8_t b );
CLINGO_API
bool push_iadd16_error_c( cErrorStack es[static 1], int16_t a, int16_t b );
CLINGO_API
bool push_iadd32_error_c( cErrorStack es[static 1], int32_t a, int32_t b );
CLINGO_API
bool push_iadd64_error_c( cErrorStack es[static 1], int64_t a, int64_t b );

CLINGO_API
bool push_uadd8_error_c( cErrorStack es[static 1], uint8_t a, uint8_t b );
CLINGO_API
bool push_uadd16_error_c( cErrorStack es[static 1], uint16_t a, uint16_t b );
CLINGO_API
bool push_uadd32_error_c( cErrorStack es[static 1], uint32_t a, uint32_t b );
CLINGO_API
bool push_uadd64_error_c( cErrorStack es[static 1], uint64_t a, uint64_t b );

/******************************************************************************/

CLINGO_API
bool push_imul8_error_c( cErrorStack es[static 1], int8_t a, int8_t b );
CLINGO_API
bool push_imul16_error_c( cErrorStack es[static 1], int16_t a, int16_t b );
CLINGO_API
bool push_imul32_error_c( cErrorStack es[static 1], int32_t a, int32_t b );
CLINGO_API
bool push_imul64_error_c( cErrorStack es[static 1], int64_t a, int64_t b );

CLINGO_API
bool push_umul8_error_c( cErrorStack es[static 1], uint8_t a, uint8_t b );
CLINGO_API
bool push_umul16_error_c( cErrorStack es[static 1], uint16_t a, uint16_t b );
CLINGO_API
bool push_umul32_error_c( cErrorStack es[static 1], uint32_t a, uint32_t b );
CLINGO_API
bool push_umul64_error_c( cErrorStack es[static 1], uint64_t a, uint64_t b );

/******************************************************************************/

CLINGO_API
bool push_isub8_error_c( cErrorStack es[static 1], int8_t a, int8_t b );
CLINGO_API
bool push_isub16_error_c( cErrorStack es[static 1], int16_t a, int16_t b );
CLINGO_API
bool push_isub32_error_c( cErrorStack es[static 1], int32_t a, int32_t b );
CLINGO_API
bool push_isub64_error_c( cErrorStack es[static 1], int64_t a, int64_t b );

CLINGO_API
bool push_usub8_error_c( cErrorStack es[static 1], uint8_t a, uint8_t b );
CLINGO_API
bool push_usub16_error_c( cErrorStack es[static 1], uint16_t a, uint16_t b );
CLINGO_API
bool push_usub32_error_c( cErrorStack es[static 1], uint32_t a, uint32_t b );
CLINGO_API
bool push_usub64_error_c( cErrorStack es[static 1], uint64_t a, uint64_t b );

#endif