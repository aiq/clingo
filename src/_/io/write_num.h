#ifndef CLINGO_INTERN_IO_WRITE_NUM_H
#define CLINGO_INTERN_IO_WRITE_NUM_H

#include <inttypes.h>

#include "clingo/io/cCell.h"
#include "clingo/io/cRecorder.h"

/*******************************************************************************

*******************************************************************************/

bool write_float_num_c( cRecorder rec[static 1],
                        double d,
                        char const fmt[static 1] );

/*******************************************************************************

*******************************************************************************/

uint64_t plusval_c( int64_t val );

int64_t write_bin_c( uint64_t val, bool upper, cVarChars buf );

int64_t write_hex_c( uint64_t val, bool upper, cVarChars buf );

int64_t write_oct_c( uint64_t val, cVarChars buf );

#endif
