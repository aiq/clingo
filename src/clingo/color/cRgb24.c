#include "clingo/color/cRgb24.h"

#include "clingo/io/write.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

SLICE_IMPL_C_(
   cRgb24,            // Type
   cRgb24Slice,       // SliceType
   rgb24_slice_c,     // FuncName
   cVarRgb24Slice,    // VarSliceType
   var_rgb24_slice_c  // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

extern inline bool eq_rgb24_c( cRgb24 a, cRgb24 b );

bool read_rgb24_c( cScanner sca[static 1],
                   cRgb24 rgb[static 1],
                   char const fmt[static 1] )
{
   return false;
}

bool write_rgb24_c( cRecorder rec[static 1],
                    cRgb24 rgb,
                    char const fmt[static 1] )
{
   cChars format = c_c( fmt );

   if ( is_empty_c_( format ) )
   {
      return write_c_( rec,
         "rgb({u8},{u8},{u8})",
         rgb.red, rgb.green, rgb.blue
      );
   }
  /*
  if ( is_empty_c_( format ) or char_slice_is_c( format, "css" ) )
  {
  }
  else if ( char_slice_is_c( format, "dbg" ) )
  {
  }
  else if ( char_slice_is_c( format, "hex" ) )
  {
  }
  */

  return false;
}

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
