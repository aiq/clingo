#ifndef CLINGO_COLOR_CRGB24_H
#define CLINGO_COLOR_CRGB24_H

#include "clingo/apidecl.h"
#include "clingo/color/image.h"
#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/type/uint8.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cRgb24
{
   uint8_t red;
   uint8_t green;
   uint8_t blue;
};
typedef struct cRgb24 cRgb24;

SLICES_C_(
   cRgb24,           // Type
   cRgb24Slice,      // SliceType
   cVarRgb24Slice    // VarSliceType
)

IMAGES_C_(
   cRgb24Image,   // ImageType
   cVarRgb24Image // VarImageType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 
*******************************************************************************/

#define rgb24_c_( Red, Green, Blue )                                           \
   ((cRgb24){ .red=(Red), .green=(Green), .blue=(Blue) })

CLINGO_API inline bool eq_rgb24_c( cRgb24 a, cRgb24 b )
{
   return a.red   == b.red and
          a.green == b.green and
          a.blue  == b.blue;
}

/*******************************************************************************
 
*******************************************************************************/

#define heap_var_rgb24_image_c_( W, H )                                        \
(                                                                              \
   (cVarRgb24Image){                                                           \
      .w=(W),                                                                  \
      .h=(H),                                                                  \
      .data=alloc_image_data_c( (W), (H), sizeof_c_( cRgb24 ) )                \
   }                                                                           \
)

CLINGO_API cRgb24 get_rgb24_pixel_c( cRgb24Image image, cPixel pixel );

CLINGO_API bool has_rgb24_pixel_c( cRgb24Image image, cPixel pixel );

CLINGO_API bool set_rgb24_pixel_c( cVarRgb24Image image,
                                   cPixel pixel,
                                   cRgb24 rgb );

/*******************************************************************************
 
*******************************************************************************/

CLINGO_API bool draw_rgb24_line_c( cVarRgb24Image image,
                                   cPixel beg,
                                   cPixel end,
                                   cRgb24 rgb24 );

CLINGO_API bool draw_rgb24_rect_c( cVarRgb24Image image,
                                   cPixel a,
                                   cPixel b,
                                   cRgb24 rgb );

CLINGO_API bool fill_rgb24_rect_c( cVarRgb24Image image,
                                   cPixel a,
                                   cPixel b,
                                   cRgb24 rgb );

#endif
