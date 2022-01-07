#ifndef CLINGO_LANG_ERROR_H
#define CLINGO_LANG_ERROR_H

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************/

#define cNoError_ 0

struct cError
{
   int code;
   char const* msg;
   struct cError* details;
};
typedef struct cError cError;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define errno_error_c_()                                                       \
(                                                                              \
   (cError){                                                                   \
      .code = errno,                                                           \
      .msg = strerror( errno ),                                                \
      .details = NULL                                                          \
   }                                                                           \
)

#define error_c_( Code, Msg )                                                  \
(                                                                              \
   (cError){                                                                   \
      .code = (Code),                                                          \
      .msg = (Msg),                                                            \
      .details = NULL                                                          \
   }                                                                           \
)

#define no_error_c_()                                                          \
(                                                                              \
   (cError){                                                                   \
      .code = cNoError_,                                                       \
      .msg = "",                                                               \
      .details = NULL                                                          \
   }                                                                           \
)

/*******************************************************************************

*******************************************************************************/

uint32_t error_depth_c( cError const err[static 1] );

int fprint_error_c( FILE* output, cError const err[static 1] );

inline int print_error_c( cError const err[static 1] )
{
   return fprint_error_c( stdout, err );
}

void reset_error_c( cError err[static 1] );

#endif
