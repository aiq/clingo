#include "clingo/type/cByte.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_byte_c( cByte a, cByte b );

/*******************************************************************************
 bit
*******************************************************************************/

extern inline cByte byte_as_bit_c( cByte byte );
extern inline cByte get_byte_bit_c( cByte byte, int64_t pos );
extern inline cByte set_byte_bit_c( cByte byte, int64_t pos, cByte bit );
extern inline cByte toggle_byte_bit_c( cByte byte, int64_t pos );
