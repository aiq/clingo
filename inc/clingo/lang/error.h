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

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************/

#define cNoError_ 0

typedef void cErrorData;

struct cError;
typedef struct cError cError;

typedef bool ( *c_note_error )( cRecorder rec[static 1],
                                cError const* err );

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

/*******************************************************************************

*******************************************************************************/

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

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

CLINGO_API
uint32_t error_depth_c( cError const err[static 1] );

CLINGO_API cErrorData const* get_error_data_c( cError const* err );

CLINGO_API
int fprint_error_c( FILE* output, cError const err[static 1] );

CLINGO_API
inline int print_error_c( cError const err[static 1] )
{
   return fprint_error_c( stdout, err );
}

/*******************************************************************************
 notepad
*******************************************************************************/

CLINGO_API bool note_error_c( cRecorder rec[static 1],
                              cError const *err );

/*******************************************************************************
 stack
*******************************************************************************/

#define error_stack_c_( Size )                                                 \
(                                                                              \
   (cErrorStack){                                                              \
      .space=0,                                                                \
      .mem=(cByte[]){ [(Size)-1]=0 },                                          \
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

CLINGO_API bool push_error_c( cErrorStack stack[static 1],
                              cErrorType const type[static 1],
                              cErrorData const* data,
                              int64_t dataSize );

/*******************************************************************************
 errno
*******************************************************************************/

CLINGO_API bool push_errno_error_c( cErrorStack stack[static 1],
                                    int number );

CLINGO_API bool note_errno_error_c( cRecorder rec[static 1],
                                    cError const* data );

#endif
