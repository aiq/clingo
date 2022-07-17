#ifndef CLINGO_IO_FWRITE_H
#define CLINGO_IO_FWRITE_H

#include "clingo/io/jot.h"
#include "clingo/io/write.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 fwrite
*******************************************************************************/

CLINGO_API bool fwrite_impl_c( FILE* file,
                               cErrorStack es[static 1],
                               c_write_va_arg write_arg,
                               int n,
                               va_list list );

CLINGO_API
bool fwrite_list_c( FILE* file, cErrorStack es[static 1], int n, va_list list );

#define fwrite_c_( File, Es, ... )                                             \
   fwrite_c( (File), (Es), nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API bool fwrite_c( FILE* file, cErrorStack es[static 1], int n, ... );

/*******************************************************************************
 fwriteln
*******************************************************************************/

CLINGO_API bool fwriteln_impl_c( FILE* file,
                                 cErrorStack es[static 1],
                                 c_write_va_arg write_arg,
                                 int n,
                                 va_list list );

CLINGO_API bool fwriteln_list_c( FILE* file,
                                 cErrorStack es[static 1],
                                 int n,
                                 va_list list );

#define fwriteln_c_( File, Es, ... )                                           \
   fwriteln_c( (File), (Es), nargs_c_( __VA_ARGS__ ), __VA_ARGS__ )
CLINGO_API bool fwriteln_c( FILE* file, cErrorStack es[static 1], int n, ... );

#endif
