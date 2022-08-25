#ifndef CLINGO_COLOR_CCOLOR_H
#define CLINGO_COLOR_CCOLOR_H

#include "clingo/apidecl.h"
#include "clingo/color/cCmyk.h"
#include "clingo/color/cCmyk32.h"
#include "clingo/color/cHsl.h"
#include "clingo/color/cHsv.h"
#include "clingo/color/cRgb.h"
#include "clingo/color/cRgb24.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

#define cMIX_COLOR_WEIGHT_ 0.5

#define cCONTRAST_COLOR_DARK_ color_c_( 0x00, 0x00, 0x00, 0xff )

#define cCONTRAST_COLOR_LIGHT_ color_c_( 0xff, 0xff, 0xff, 0xff )

#define cCONTRAST_COLOR_THRESHOLD_ 0.43

struct cColor
{
   uint8_t r;
   uint8_t g;
   uint8_t b;
   uint8_t a;
};
typedef struct cColor cColor;

SLICE_DEF_C_(
   cColor,           // Type
   cColorSlice,      // SliceType
   color_slice_c,    // FuncName
   cVarColorSlice,   // VarSliceType
   var_color_slice_c // VarFuncName
)

IMAGE_TYPE_C_(
   cColorImage,   // ImageType
   cVarColorImage // VarImageType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define color_c_( Red, Green, Blue, Alpha )                                    \
   ((cColor){ .r=(Red), .g=(Green), .b=(Blue), .a=(Alpha) })

CLINGO_API cColor rgb_color_c( uint32_t raw );

CLINGO_API cColor rgba_color_c( uint32_t raw );

CLINGO_API cColor argb_color_c( uint32_t raw );

CLINGO_API cColor alpha_color_c( uint8_t red, uint8_t green, uint8_t blue, float alpha );

/*******************************************************************************
 from
*******************************************************************************/

#define from_cmyk32_c_( Cyan, Magenta, Yellow, Key )                           \
   from_cmyk32_c( cmyk32_c_( (Cyan), (Magenta), (Yellow), (Key) ) )
CLINGO_API cColor from_cmyk32_c( cCmyk32 cmyk );

#define from_cmyk_c_( Cyan, Magenta, Yellow, Key )                             \
   from_cmyk_c( cmyk_c_( (Cyan), (Magenta), (Yellow), (Key) ) )
CLINGO_API cColor from_cmyk_c( cCmyk cmyk );

#define from_hsl_c_( Hue, Saturation, Lightness )                              \
   from_hsl_c( hsl_c_( (Hue), (Saturation), (Lightness) ) )
CLINGO_API cColor from_hsl_c( cHsl hsl );

#define from_hsv_c_( Hue, Saturation, Value )                                  \
   from_hsv_c( hsv_c_( (Hue), (Saturation), (Value) ) )
CLINGO_API cColor from_hsv_c( cHsv hsv );

#define from_rgb24_c_( Red, Green, Blue )                                      \
   from_rgb24_c( rgb24_c_( (Red), (Green), (Blue) ) )
CLINGO_API cColor from_rgb24_c( cRgb24 rgb );

#define from_rgb_c_( Red, Green, Blue )                                        \
   from_rgb_c( rgb_c_( (Red), (Green), (Blue) ) )
CLINGO_API cColor from_rgb_c( cRgb rgb );

/*******************************************************************************
 as
*******************************************************************************/

CLINGO_API cCmyk32 as_cmyk32_c( cColor color );

CLINGO_API cCmyk as_cmyk_c( cColor color );

CLINGO_API cHsl as_hsl_c( cColor color );

CLINGO_API cHsv as_hsv_c( cColor color );

CLINGO_API cRgb24 as_rgb24_c( cColor color );

CLINGO_API cRgb as_rgb_c( cColor color );

/*******************************************************************************
 compare
*******************************************************************************/

CLINGO_API inline bool eq_color_c( cColor a, cColor b )
{
   return a.r == b.r and a.g == b.g and a.b == b.b and a.a == b.a;
}

CLINGO_API inline bool eq_rgb_color_c( cColor a, cColor b )
{
   return a.r == b.r and a.g == b.g and a.b == b.b;
}

/*******************************************************************************
 channel information
*******************************************************************************/

CLINGO_API float color_alpha_c( cColor color );

CLINGO_API cColor set_color_alpha_c( cColor color, float alpha );

CLINGO_API float color_luma_c( cColor color );

/*******************************************************************************
 operations
*******************************************************************************/

CLINGO_API cColor saturate_color_c( cColor color, float amount );

CLINGO_API cColor desaturate_color_c( cColor color, float amount );

CLINGO_API cColor lighten_color_c( cColor color, float amount );

CLINGO_API cColor darken_color_c( cColor color, float amount );

CLINGO_API cColor fade_color_c( cColor color, float alpha );

CLINGO_API cColor spin_color_c( cColor color, float angle );

#define mix_color_c_( Color, Extra ) \
   mix_color_c( Color, Extra, cMIX_COLOR_WEIGHT_ )
CLINGO_API cColor mix_color_c( cColor color, cColor extra, float weight );

CLINGO_API cColor greyscale_color_c( cColor color );

#define contrast_color_c_( Color )                 \
   contrast_color_c( (Color),                      \
                     cCONTRAST_COLOR_DARK_,        \
                     cCONTRAST_COLOR_LIGHT_,       \
                     cCONTRAST_COLOR_THRESHOLD_ )
CLINGO_API cColor contrast_color_c( cColor color,
                                    cColor dark,
                                    cColor light,
                                    float threshold );

/*******************************************************************************
 blending
*******************************************************************************/

CLINGO_API cColor multiply_color_c( cColor a, cColor b );

CLINGO_API cColor screen_color_c( cColor a, cColor b );

CLINGO_API cColor overlay_color_c( cColor a, cColor b );

CLINGO_API cColor softlight_color_c( cColor color, cColor extra );

CLINGO_API cColor hardlight_color_c( cColor color, cColor extra );

CLINGO_API cColor difference_color_c( cColor color, cColor other );

CLINGO_API cColor exclusion_color_c( cColor color, cColor other );

CLINGO_API cColor average_color_c( cColor color, cColor other );

CLINGO_API cColor negation_color_c( cColor color, cColor other );

/*******************************************************************************
 io
*******************************************************************************/

#define read_color_c_( Sca, Color )                                            \
   read_color_c( (Sca), (Color), "" )
CLINGO_API bool read_color_c( cScanner sca[static 1],
                              cColor color[static 1],
                              char const fmt[static 1] );

#define write_color_c_( Rec, Color )                                           \
   write_color_c( (Rec), (Color), "" )
CLINGO_API bool write_color_c( cRecorder rec[static 1],
                               cColor color,
                               char const fmt[static 1] );

/*******************************************************************************
 io
*******************************************************************************/

#define heap_var_color_image_c_( W, H )                                        \
(                                                                              \
   (cVarColorImage){                                                           \
      .data=alloc_image_data_c( (W), (H), sizeof_c_( cColor ) ),               \
      .w=(W),                                                                  \
      .h=(H)                                                                   \
   }                                                                           \
)

CLINGO_API cColor get_color_pixel_c( cColorImage image, cPixel pixel );

CLINGO_API void set_color_pixel_c( cVarColorImage image,
                                   cPixel pixel,
                                   cColor color );

#endif
