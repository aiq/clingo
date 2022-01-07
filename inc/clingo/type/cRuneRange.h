#ifndef CLINGO_LANG_CRUNE_RANGE_H
#define CLINGO_LANG_CRUNE_RANGE_H

#include "clingo/type/cRune.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cRuneRange
{
   cRune min;
   cRune max;
};
typedef struct cRuneRange cRuneRange;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

inline cRuneRange build_rune_range_c( cRune min, cRune max )
{
   return (cRuneRange){ .min = min, .max = max };
}

inline cRuneRange make_rune_range_c( cChars min, cChars max )
{
   return build_rune_range_c( make_rune_c( min ), make_rune_c( max ) );
}

inline cRuneRange rune_range_c( char const min[static 1],
                                char const max[static 1] )
{
   return build_rune_range_c( rune_c( min ), rune_c( max ) );
}

inline cRuneRange utf16_rune_range_c( uint16_t min, uint16_t max )
{
   return build_rune_range_c( utf16_rune_c( min ), utf16_rune_c( max ) );
}

inline cRuneRange utf32_rune_range_c( uint32_t min, uint32_t max )
{
   return build_rune_range_c( utf32_rune_c( min ), utf32_rune_c( max ) );
}

/*******************************************************************************
 overall
*******************************************************************************/

inline bool eq_rune_range_c( cRuneRange a, cRuneRange b )
{
   return eq_rune_c( a.min, b.min ) and eq_rune_c( a.max, b.max );
}

#define in_rune_range_c_( Range, Cstr )                                        \
   in_rune_range_c( (Range), rune_c( Cstr ) )
inline bool in_rune_range_c( cRuneRange range, cRune r )
{
   return in_range_c_( range.min.ctrl, r.ctrl, range.max.ctrl );
}

inline bool rune_range_is_valid_c( cRuneRange range )
{
   return lte_c( cmp_rune_c( range.min, range.max ) );
}

#endif