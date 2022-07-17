#ifndef CLINGO_LANG_ERROR_H
#define CLINGO_LANG_ERROR_H

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "clingo/apidecl.h"
#include "clingo/io/cRecorder.h"
#include "clingo/lang/mem.h"

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

#define QUOTE_LIT_STR_ERROR_TYPE_C_( Type, NoteFunc, WriteText, PushFunc )     \
static bool NoteFunc( cRecorder rec[static 1], cError const* err )             \
{                                                                              \
   must_be_c_( err->type == &Type );                                           \
   cLitStrErrorData const* errd = get_error_data_c( err );                     \
   return write_c_( rec, WriteText, errd->str );                               \
}                                                                              \
cErrorType const Type = {                                                      \
   .desc = stringify_c_( Type ),                                               \
   .note = &NoteFunc                                                           \
};                                                                             \
bool PushFunc( cErrorStack es[static 1], char const str[static 1] )            \
{                                                                              \
   cLitStrErrorData d = { .str=str };                                          \
   return push_error_c( es, &Type, &d, sizeof_c_( cLitStrErrorData ) );        \
}

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************/

#define cNoError_ 0

typedef void cErrorData;

struct cError;
typedef struct cError cError;

typedef bool ( *c_note_error )( cRecorder rec[static 1], cError const* err );

struct cErrorType
{
   char const* desc;
   c_note_error note;
};
typedef struct cErrorType cErrorType;

struct cError
{
   cErrorType const* type;
   cError const* sub;
};

struct cErrorStack
{
   int64_t space;
   void* mem;
   cError const* err;
};
typedef struct cErrorStack cErrorStack;

/*******************************************************************************

*******************************************************************************/

CLINGO_API extern cErrorType const C_ErrnoError;

struct cErrnoErrorData
{
   int number;
};
typedef struct cErrnoErrorData cErrnoErrorData;

CLINGO_API extern cErrorType const C_LitStrError;

struct cLitStrErrorData
{
   char const* str;
};
typedef struct cLitStrErrorData cLitStrErrorData;

CLINGO_API extern cErrorType const C_InvalidInputError;

CLINGO_API extern cErrorType const C_NotEnoughBufferError;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 error
*******************************************************************************/

CLINGO_API
int64_t error_depth_c( cError const* err );

CLINGO_API cErrorData const* get_error_data_c( cError const* err );

#define write_error_c_( Rec, Err )                                             \
   write_error_c( (Rec), (Err), "" )
CLINGO_API bool write_error_c( cRecorder rec[static 1],
                               cError const *err,
                               char const fmt[static 1] );

/*******************************************************************************
 stack
*******************************************************************************/

#define error_stack_c_( Size )                                                 \
(                                                                              \
   (cErrorStack){                                                              \
      .space=(Size),                                                           \
      .mem=stack_mem_c_( Size ),                                               \
      .err=NULL                                                                \
   }                                                                           \
)

#define heap_error_stack_c_( Size )                                            \
(                                                                              \
   (cErrorStack){                                                              \
      .space=(Size),                                                           \
      .mem=alloc_c( Size ),                                                    \
      .err=NULL                                                                \
   }                                                                           \
)

#define make_error_stack_c_( Size, Memory )                                    \
(                                                                              \
   (cErrorStack){                                                              \
      .space=(Size),                                                           \
      .mem=(Memory),                                                           \
      .err=NULL                                                                \
   }                                                                           \
)

CLINGO_API int64_t count_errors_c( cErrorStack es[static 1] );

CLINGO_API void drop_error_c( cErrorStack es[static 1] );

#define push_error_c_( Es, Type )                                              \
   push_error_c( (Es), (Type), NULL, 0 )
CLINGO_API bool push_error_c( cErrorStack es[static 1],
                              cErrorType const type[static 1],
                              cErrorData const* data,
                              int64_t dataSize );

CLINGO_API void reset_error_stack_c( cErrorStack es[static 1] );

/*******************************************************************************
 push error
*******************************************************************************/

CLINGO_API bool push_errno_error_c( cErrorStack es[static 1],
                                    int number );

CLINGO_API bool push_lit_str_error_c( cErrorStack es[static 1],
                                      char const cstr[static 1] );

#endif
