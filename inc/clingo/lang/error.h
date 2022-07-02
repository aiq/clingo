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

CLINGO_API extern cErrorType const C_TextError;

struct cTextErrorData
{
   cChars text;
};
typedef struct cTextErrorData cTextErrorData;

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
      .space=0,                                                                \
      .mem=stack_mem_c_( Size ),                                               \
      .err=NULL                                                                \
   }                                                                           \
)

#define heap_error_stack_c_( Size )                                            \
(                                                                              \
   (cErrorStack){                                                              \
      .space=0,                                                                \
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

#define push_text_error_c_( Es, Text )                                         \
   push_text_error_c( (Es), c_c( Text ) )
CLINGO_API bool push_text_error_c( cErrorStack es[static 1],
                                   cChars text );

#endif
