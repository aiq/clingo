#include "clingo/type/char.h"

#include <string.h>

#include "clingo/lang/algo.h"
#include "clingo/lang/func.h"
#include "clingo/type/uint64.h"

#include "clingo/io/print.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall 
*******************************************************************************/

extern inline int cmp_char_c( char a, char b );

/*******************************************************************************
 interpret
*******************************************************************************/

extern inline int8_t dec_char_value_c( char c );
extern inline int8_t hex_char_value_c( char c );
extern inline int8_t oct_char_value_c( char c );

