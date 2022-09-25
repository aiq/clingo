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

cRgb24 get_rgb24_pixel_c( cRgb24Image image, cPixel pixel )
{
   uint8_t const* data = to_pixel_value_c_( image, cRgb24, pixel );
   must_exist_c_( data );

   return rgb24_c_( data[0], data[1], data[2] );
}

void set_rgb24_pixel_c( cVarRgb24Image image,
                        cPixel pixel,
                        cRgb24 rgb )
{
   uint8_t* data = to_var_pixel_value_c_( image, cRgb24, pixel );
   must_exist_c_( data );

   data[0] = rgb.red;
   data[1] = rgb.green;
   data[2] = rgb.blue;
}
