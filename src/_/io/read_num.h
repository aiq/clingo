#ifndef CLINGO_INTERN_IO_READ_NUM_H
#define CLINGO_INTERN_IO_READ_NUM_H

#include <inttypes.h>
#include <iso646.h>

#include "clingo/lang/func.h"
#include "clingo/type/cChars.h"

/*******************************************************************************

*******************************************************************************/

int64_t parse_dec_int64_c( int64_t* n,
                           cChars src,
                           int64_t max,
                           int64_t min );

int64_t parse_hex_int64_c( int64_t* n,
                           cChars src,
                           int64_t max,
                           int64_t min );

int64_t parse_oct_int64_c( int64_t* n,
                           cChars src,
                           int64_t max,
                           int64_t min );

int64_t parse_bin_int64_c( int64_t* n,
                           cChars src,
                           int64_t max,
                           int64_t min );

int64_t parse_int64_c( int64_t* n,
                       char const format[static 1],
                       cChars src,
                       int64_t max,
                       int64_t min );

/*******************************************************************************

*******************************************************************************/

int64_t parse_dec_uint64_c( uint64_t* n,
                            cChars src,
                            uint64_t max );

int64_t parse_hex_uint64_c( uint64_t* n,
                            cChars src,
                            uint64_t max );

int64_t parse_oct_uint64_c( uint64_t* n,
                            cChars src,
                            uint64_t max );

int64_t parse_bin_uint64_c( uint64_t* n,
                            cChars src,
                            uint64_t max );

int64_t parse_uint64_c( uint64_t* n,
                        char const format[static 1],
                        cChars src,
                        uint64_t max );

/*******************************************************************************

*******************************************************************************/

int64_t parse_dec_double_c( double* d, cChars src );

#endif
