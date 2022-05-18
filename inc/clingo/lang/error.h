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

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************/

#define cNoError_ 0

struct cErrorNotepad
{
   int64_t pos;
   int64_t space;
   void* mem;
};
typedef struct cErrorNotepad cErrorNotepad;

typedef void cErrorData;

struct cError;
typedef struct cError cError;

typedef bool ( *c_note_error )( cErrorNotepad notepad[static 1],
                                cError const* err );

struct cErrorType
{
   char const* desc;
   c_note_error write;
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
   cError const* last;
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

*******************************************************************************/

CLINGO_API bool push_error_c( cErrorStack stack[static 1],
                              cErrorType const type[static 1],
                              cErrorData const* data,
                              int64_t dataSize );

CLINGO_API bool note_error_c( cErrorNotepad rec[static 1],
                              cError const err[static 1] );

/*******************************************************************************

*******************************************************************************/

CLINGO_API bool push_errno_error_c( cErrorStack stack[static 1],
                                    int number );

CLINGO_API bool note_errno_error_c( cErrorNotepad notepad[static 1],
                                    cError const* data );

#endif
