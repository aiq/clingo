#include "clingo/color/cRgb24.h"

#include "clingo/io/write.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

extern inline bool eq_rgb24_c( cRgb24 a, cRgb24 b );

/*******************************************************************************
 
*******************************************************************************/

GET_IMAGE_PIXEL_C_( get_rgb24_pixel_c, cRgb24Image, cRgb24 )

IMAGE_HAS_PIXEL_C_( has_rgb24_pixel_c, cRgb24Image )

SET_IMAGE_PIXEL_C_( set_rgb24_pixel_c, cVarRgb24Image, cRgb24 )

/*******************************************************************************
 
*******************************************************************************/

DRAW_IMAGE_LINE_C_( draw_rgb24_line_c, cVarRgb24Image, cRgb24 )

DRAW_IMAGE_RECT_C_( draw_rgb24_rect_c, cVarRgb24Image, cRgb24 )

FILL_IMAGE_RECT_C_( fill_rgb24_rect_c, cVarRgb24Image, cRgb24 )