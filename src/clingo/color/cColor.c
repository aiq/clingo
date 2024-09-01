#include "clingo/color/cColor.h"

#include <iso646.h>
#include <stdlib.h>

#include "_/color_util.h"
#include "clingo/io/write.h"

/*******************************************************************************
 from
*******************************************************************************/

#define u8round_( Val ) uint8_c_( round( Val ) )

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

cColor rgb_color_c( uint32_t raw )
{
   union { uint32_t i; uint8_t s[ 4 ]; } v;
   v.i = swap_uint32_to_c( raw, c_BigEndian );
   return color_c_( v.s[ 1 ], v.s[ 2 ], v.s[ 3 ], 0xff );
}

cColor rgba_color_c( uint32_t raw )
{
   union { uint32_t i; uint8_t s[ 4 ]; } v;
   v.i = swap_uint32_to_c( raw, c_BigEndian );
   return color_c_( v.s[ 0 ], v.s[ 1 ], v.s[ 2 ], v.s[ 3 ] );
}

cColor argb_color_c( uint32_t raw )
{
   union { uint32_t i; uint8_t s[ 4 ]; } v;
   v.i = swap_uint32_to_c( raw, c_BigEndian );
   return color_c_( v.s[ 1 ], v.s[ 2 ], v.s[ 3 ], v.s[ 0 ] );
}

cColor alpha_color_c( uint8_t red, uint8_t green, uint8_t blue, float alpha )
{
   return color_c_( red, green, blue, uint8_from_percent_c( alpha ) );
}

/*******************************************************************************
 from
*******************************************************************************/

cColor from_cmyk32_c( cCmyk32 cmyk )
{
   return from_cmyk_c( cmyk_from_cmyk32_c( cmyk ) );
}

cColor from_cmyk_c( cCmyk cmyk )
{
   cmyk = cmyk_from_cmyk32_c( cmyk32_from_cmyk_c( cmyk ) );  // normalisieren
   cColor color;
   color.r = uint8_from_percent_c( ( 1.0f - cmyk.cyan ) * ( 1.0f - cmyk.key ) );
   color.g = uint8_from_percent_c( ( 1.0f - cmyk.magenta ) * ( 1.0f - cmyk.key ) );
   color.b = uint8_from_percent_c( ( 1.0f - cmyk.yellow ) * ( 1.0f - cmyk.key ) );
   color.a = 0xff;

   return color;
}

cColor from_hsl_c( cHsl hsl )
{
   float c = ( 1.0f - fabsf( 2.0f * hsl.lightness - 1.0f ) ) * hsl.saturation;
   float x = c * (1.0f - fabsf( fmodf( hsl.hue / 60.0f, 2.0f ) - 1.0f ) );
   float min = hsl.lightness - c / 2.0f;

   if ( hsl.hue < 60.0f )
   {
      return from_rgb_c( rgb_c_( c + min, x + min, 0.0f + min ) );
   }
   else if ( hsl.hue < 120.0f )
   {
      return from_rgb_c( rgb_c_( x + min, c + min, 0.0f + min ) );
   }
   else if ( hsl.hue < 180.0f )
   {
      return from_rgb_c( rgb_c_( 0.0f + min, c + min, x + min ) );
   }
   else if ( hsl.hue < 240.0f )
   {
      return from_rgb_c( rgb_c_( 0.0f + min, x + min, c + min ) );
   }
   else if ( hsl.hue < 300.0f )
   {
      return from_rgb_c( rgb_c_( x + min, 0.0f + min, c + min ) );
   }
   else // ( hsl.hue < 360.0 )
   {
      return from_rgb_c( rgb_c_( c + min, 0.0f + min, x + min ) );
   }
}

cColor from_hsv_c( cHsv hsv )
{
   float c = hsv.value * hsv.saturation;
   float x = c * (1.0f - fabsf( fmodf( hsv.hue / 60.0f, 2.0f ) - 1.0f ) );
   float min = hsv.value - c;

   if ( hsv.hue < 60.0 )
   {
      return from_rgb_c( rgb_c_( c + min, x + min, 0.0f + min ) );
   }
   else if ( hsv.hue < 120.0 )
   {
      return from_rgb_c( rgb_c_( x + min, c + min, 0.0f + min ) );
   }
   else if ( hsv.hue < 180.0 )
   {
      return from_rgb_c( rgb_c_( 0.0f + min, c + min, x + min ) );
   }
   else if ( hsv.hue < 240.0 )
   {
      return from_rgb_c( rgb_c_( 0.0f + min, x + min, c + min ) );
   }
   else if ( hsv.hue < 300.0 )
   {
      return from_rgb_c( rgb_c_( x + min, 0.0f + min, c + min ) );
   }
   else // ( hsv.hue < 360.0 )
   {
      return from_rgb_c( rgb_c_( c + min, 0.0f + min, x + min ) );
   }
}

cColor from_rgb24_c( cRgb24 rgb )
{
   return color_c_( rgb.red, rgb.green, rgb.blue, 0xff );
}

cColor from_rgb_c( cRgb rgb )
{
   return from_rgb24_c( rgb24_from_rgb_c( rgb ) );
}

/*******************************************************************************
 as
*******************************************************************************/

cCmyk32 as_cmyk32_c( cColor color )
{
   cCmyk cmyk = as_cmyk_c( color );
   return cmyk32_from_cmyk_c( cmyk );
}

cCmyk as_cmyk_c( cColor color )
{
   cRgb rgb = as_rgb_c( color );
   cFloats rgbFloats =  slice_c_( float, rgb.red, rgb.green, rgb.blue );
   cCmyk fcmyk;
   fcmyk.key     = 1.0f - *max_float_c( rgbFloats );
   fcmyk.cyan    = ( 1.0f - rgb.red   - fcmyk.key ) / ( 1.0f - fcmyk.key );
   fcmyk.magenta = ( 1.0f - rgb.green - fcmyk.key ) / ( 1.0f - fcmyk.key );
   fcmyk.yellow  = ( 1.0f - rgb.blue  - fcmyk.key ) / ( 1.0f - fcmyk.key );
   return fcmyk;
}

cHsl as_hsl_c( cColor color )
{
   cRgb rgb = as_rgb_c( color );
   cFloats floats = slice_c_( float, rgb.red, rgb.green, rgb.blue );
   float max = *max_float_c( floats );
   float min = *min_float_c( floats );
   float delta = max - min;

   cHsl hsl = { .saturation = 0.f };

   // hue
   if( rgb.red == max )
   {
      hsl.hue = 60.0f * fmodf( ( rgb.green - rgb.blue ) / delta, 6.0f );
   }
   else if( rgb.green == max )
   {
      hsl.hue = 60.0f * ( ( ( rgb.blue - rgb.red ) / delta ) + 2.0f );
   }
   else // rgbf.blue == max
   {
      hsl.hue = 60.0f * ( ( ( rgb.red - rgb.green ) / delta ) + 4.0f );
   }

   hsl.lightness = ( max + min ) / 2.0f;

   // saturation
   if ( delta != 0.0f )
   {
      hsl.saturation = hsl.lightness > 0.5f ? delta / ( 2.0f - max - min )
                                            : delta / ( max + min );
   }

   return hsl;
}

cHsv as_hsv_c( cColor color )
{
   cRgb rgb = as_rgb_c( color );
   cFloats floats = slice_c_( float, rgb.red, rgb.green, rgb.blue );
   float max = *max_float_c( floats );
   float min = *min_float_c( floats );
   float delta = max - min;

   cHsv hsv = { .saturation = 0.0f };

   // hue
   if( rgb.red == max )
   {
      hsv.hue = 60.0f * fmodf( ( rgb.green - rgb.blue ) / delta, 6.0f );
   }
   else if( rgb.green == max )
   {
      hsv.hue = 60.0f * ( ( ( rgb.blue - rgb.red ) / delta ) + 2.0f );
   }
   else // rgbf.blue == max
   {
      hsv.hue = 60.0f * ( ( ( rgb.red - rgb.green ) / delta ) + 4.0f );
   }

   // saturation
   if ( delta != 0.0f )
   {
      hsv.saturation = delta / max;
   }

   // value
   hsv.value = max;

   return hsv;
}

cRgb24 as_rgb24_c( cColor color )
{
   return rgb24_c_( color.r, color.g, color.b );
}

cRgb as_rgb_c( cColor color )
{
   return rgb_from_rgb24_c( as_rgb24_c( color ) );
}

/*******************************************************************************
 cmp
*******************************************************************************/

extern inline bool eq_color_c( cColor a, cColor b );

extern inline bool eq_rgb_color_c( cColor a, cColor b );

/*******************************************************************************
 alpha
*******************************************************************************/

float color_alpha_c( cColor color )
{
   return uint8_in_percent_c( color.a );
}

cColor set_color_alpha_c( cColor color, float alpha )
{
   color.a = uint8_from_percent_c( alpha );
   return color;
}

float color_luma_c( cColor color )
{
   return ( 0.2126f * color.r / 255.0f )
        + ( 0.7152f * color.g / 255.0f )
        + ( 0.0722f * color.b / 255.0f );
}

/*******************************************************************************
 operations
*******************************************************************************/

cColor saturate_color_c( cColor color, float amount )
{
   cHsl hsl = as_hsl_c( color );
   hsl.saturation += amount;
   hsl.saturation = clamp_c_( 0.0, hsl.saturation, 1.0 );
   return from_hsl_c( hsl );
}

cColor desaturate_color_c( cColor color, float amount )
{
   cHsl hsl = as_hsl_c( color );
   hsl.saturation -= amount;
   hsl.saturation = clamp_c_( 0.0, hsl.saturation, 1.0 );
   return from_hsl_c( hsl );
}

cColor lighten_color_c( cColor color, float amount )
{
   cHsl hsl = as_hsl_c( color );
   hsl.lightness += amount;
   hsl.lightness = clamp_c_( 0.0, hsl.lightness, 1.0 );
   return from_hsl_c( hsl );
}

cColor darken_color_c( cColor color, float amount )
{
   cHsl hsl = as_hsl_c( color );
   hsl.lightness -= amount;
   hsl.lightness = clamp_c_( 0.0, hsl.lightness, 1.0 );
   return from_hsl_c( hsl );
}

cColor fade_color_c( cColor color, float amount )
{
   float alpha = color_alpha_c( color );
   alpha += amount;
   return set_color_alpha_c( color, alpha );
}

cColor spin_color_c( cColor color, float angle )
{
   cHsl hsl = as_hsl_c( color );
   float hue = fmodf( hsl.hue + angle, 360.0f );
   hsl.hue = hue < 0.0f ? 360.0f + hue
                        : hue;

   return from_hsl_c( hsl );
}

cColor mix_color_c( cColor color, cColor extra, float weight )
{
   float w = weight * 2.0f - 1.0f;
   float a = color_alpha_c( color ) - color_alpha_c( extra );

   float w1 = (
      ( ( w * a == -1.0f ) ? w
                           : ( w + a ) / ( 1 + w * a ) )
      + 1.0f
   ) / 2.0f;
   float w2 = 1.0f - w1;

   cColor result = {};
   result.r = u8round_( color.r * w1 + extra.r * w2 );
   result.g = u8round_( color.g * w1 + extra.g * w2 );
   result.b = u8round_( color.b * w1 + extra.b * w2 );

   result.a = u8round_( color.a * weight + extra.a * ( 1.0 - weight ) );

   return result;
}

cColor greyscale_color_c( cColor color )
{
   return desaturate_color_c( color, 1.0 );
}

cColor contrast_color_c( cColor color, cColor dark, cColor light, float threshold )
{
   //Figure out which is actually light and dark!
   if ( color_luma_c( dark ) > color_luma_c( light ) )
   {
      swap_c_( cColor, dark, light, tmp );
   }

   if ( as_hsl_c( color ).lightness < threshold )
   {
      return light;
   }

   return dark;
}

/*******************************************************************************
 blending
*******************************************************************************/

cColor multiply_color_c( cColor x, cColor y )
{
   uint8_t r = u8round_( x.r * y.r / 255.0 );
   uint8_t g = u8round_( x.g * y.g / 255.0 );
   uint8_t b = u8round_( x.b * y.b / 255.0 );

   return color_c_( r, g, b, x.a );
}

cColor screen_color_c( cColor x, cColor y )
{
   uint8_t r = u8round_( 255.0 - ( 255.0 - x.r ) * ( 255.0 - y.r ) / 255.0 );
   uint8_t g = u8round_( 255.0 - ( 255.0 - x.g ) * ( 255.0 - y.g ) / 255.0 );
   uint8_t b = u8round_( 255.0 - ( 255.0 - x.b ) * ( 255.0 - y.b ) / 255.0 );

   return color_c_( r, g, b, x.a );
}

cColor overlay_color_c( cColor x, cColor y )
{
   uint8_t r = x.r < 128 ? u8round_( 2.0 * x.r * y.r / 255.0 )
                         : u8round_( 255.0 - 2.0 * ( 255.0 - x.r ) * ( 255.0 - y.r ) / 255.0 );
   uint8_t g = x.g < 128 ? u8round_( 2.0 * x.g * y.g / 255.0 )
                         : u8round_( 255.0 - 2.0 * ( 255.0 - x.g ) * ( 255.0 - y.g ) / 255.0 );
   uint8_t b = x.b < 128 ? u8round_( 2.0 * x.b * y.b / 255.0 )
                         : u8round_( 255.0 - 2.0 * ( 255.0 - x.b ) * ( 255.0 - y.b ) / 255.0 );

   return color_c_( r, g, b, x.a );
}

cColor softlight_color_c( cColor x, cColor y )
{
   double t = 0.0;
   
   t = y.r * x.r / 255.0;
   uint8_t r = u8round_( t + x.r * ( 255.0 - ( 255.0 - x.r ) * ( 255.0 - y.r ) / 255.0 - t ) / 255.0 );
   t = y.g * x.g / 255.0;
   uint8_t g = u8round_( t + x.g * ( 255.0 - ( 255.0 - x.g ) * ( 255.0 - y.g ) / 255.0 - t ) / 255.0 );
   t = y.b * x.b / 255.0;
   uint8_t b = u8round_( t + x.b * ( 255.0 - ( 255.0 - x.b ) * ( 255.0 - y.b ) / 255.0 - t ) / 255.0 );

   return color_c_( r, g, b, x.a );
}

cColor hardlight_color_c( cColor x, cColor y )
{
   uint8_t r = y.r < 128 ? u8round_( 2.0 * y.r * x.r / 255.0 )
                         : u8round_( 255.0 - 2.0 * ( 255.0 - y.r ) * ( 255.0 - x.r ) / 255.0 );
   uint8_t g = y.g < 128 ? u8round_( 2.0 * y.g * x.g / 255.0 )
                         : u8round_( 255.0 - 2.0 * ( 255.0 - y.g ) * ( 255.0 - x.g ) / 255.0 );
   uint8_t b = y.b < 128 ? u8round_( 2.0 * y.b * x.b / 255.0 )
                         : u8round_( 255.0 - 2.0 * ( 255.0 - y.b ) * ( 255.0 - x.b ) / 255.0 );

   return color_c_( r, g, b, x.a );
}

cColor difference_color_c( cColor x, cColor y )
{
   uint8_t r = u8round_( abs( x.r - y.r ) );
   uint8_t g = u8round_( abs( x.g - y.g ) );
   uint8_t b = u8round_( abs( x.b - y.b ) );

   return color_c_( r, g, b, x.a );
}

cColor exclusion_color_c( cColor x, cColor y )
{
   uint8_t r = u8round_( x.r + y.r * ( 255.0 - x.r - x.r ) / 255.0 );
   uint8_t g = u8round_( x.g + y.g * ( 255.0 - x.g - x.g ) / 255.0 );
   uint8_t b = u8round_( x.b + y.b * ( 255.0 - x.b - x.b ) / 255.0 );

   return color_c_( r, g, b, x.a );
}

cColor average_color_c( cColor x, cColor y )
{
   uint8_t r = u8round_( ( x.r + y.r ) / 2.0 );
   uint8_t g = u8round_( ( x.g + y.g ) / 2.0 );
   uint8_t b = u8round_( ( x.b + y.b ) / 2.0 );

   return color_c_( r, g, b, x.a );
}

cColor negation_color_c( cColor x, cColor y )
{
   uint8_t r = u8round_( 255.0 - fabs( 255.0 - y.r - x.r ) );
   uint8_t g = u8round_( 255.0 - fabs( 255.0 - y.g - x.g ) );
   uint8_t b = u8round_( 255.0 - fabs( 255.0 - y.b - x.b ) );

   return color_c_( r, g, b, x.a );
}

/*******************************************************************************
 io
*******************************************************************************/

GET_IMAGE_PIXEL_C_( get_color_pixel_c, cColorImage, cColor )

IMAGE_HAS_PIXEL_C_( has_color_pixel_c, cColorImage )

SET_IMAGE_PIXEL_C_( set_color_pixel_c, cVarColorImage, cColor )

/*******************************************************************************
 io
*******************************************************************************/

DRAW_IMAGE_LINE_C_( draw_color_line_c, cVarColorImage, cColor )

DRAW_IMAGE_RECT_C_( draw_color_rect_c, cVarColorImage, cColor )

FILL_IMAGE_RECT_C_( fill_color_rect_c, cVarColorImage, cColor )
