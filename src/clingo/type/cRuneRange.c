#include "clingo/type/cRuneRange.h"
#include <stdio.h>

/*******************************************************************************
********************************************************************+ Functions
********************************************************************************
 utf8
*******************************************************************************/

extern inline cRuneRange build_rune_range_c( cRune min, cRune max );
extern inline cRuneRange make_rune_range_c( cChars min, cChars max );
extern inline cRuneRange rune_range_c( char const min[static 1],
                                       char const max[static 1] );
extern inline cRuneRange utf16_rune_range_c( uint16_t min, uint16_t max );
extern inline cRuneRange utf32_rune_range_c( uint32_t min, uint32_t max );

/*******************************************************************************
 init
*******************************************************************************/

extern inline bool eq_rune_range_c( cRuneRange a, cRuneRange b );
extern inline bool in_rune_range_c( cRuneRange range, cRune r );
extern inline bool rune_range_is_valid_c( cRuneRange range );
