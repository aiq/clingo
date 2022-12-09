#ifndef CLINGO_INTERN_WRITE_NUM_FORMAT_H
#define CLINGO_INTERN_WRITE_NUM_FORMAT_H

#include "clingo/io/cCell.h"
#include "clingo/io/cScanner.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

#define cWRITE_NUM_VALUE_BUF_SIZE_ 127

struct cWriteNumFormat
{
   bool sign;
   bool memory;
   char type;
   char const* quote;
   char decimal;
   int16_t precision;
   cCell cell;
};
typedef struct cWriteNumFormat cWriteNumFormat;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

bool init_write_int_format_c( cWriteNumFormat numFmt[static 1],
                              char const fmt[static 1] );

bool init_write_float_format_c( cWriteNumFormat numFmt[static 1],
                                char const fmt[static 1] );

void dump_write_num_format_c( cWriteNumFormat const fmt[static 1] );

/*******************************************************************************
 parse
*******************************************************************************/

char parse_int_format_type_c( cScanner* sca );

char parse_float_format_type_c( cScanner* sca );

char const* parse_quote_value_c( cScanner* sca );

bool parse_sign_flag_c( cScanner* sca );

bool parse_memory_flag_c( cScanner* sca );

char parse_decimal_c( cScanner* sca );

int16_t parse_precision_value_c( cScanner* sca );

#endif
