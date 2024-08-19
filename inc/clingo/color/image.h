#ifndef CLINGO_COLOR_IMAGE_H
#define CLINGO_COLOR_IMAGE_H

#include "clingo/apidecl.h"
#include "clingo/lang/func.h"
#include "clingo/lang/math.h"
#include "clingo/lang/mem.h"
#include "clingo/lang/slice.h"

/*******************************************************************************
********************************************************* Types and Definitions 
********************************************************************************
 type
*******************************************************************************/

struct cPixel
{
   int32_t x;
   int32_t y;
};
typedef struct cPixel cPixel;

SLICES_C_(
   cPixel,           // Type
   cPixelSlice,      // SliceType
   cVarPixelSlice    // VarSliceType
)

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************
 init
*******************************************************************************/

#define IMAGES_C_( ImageType, VarImageType )                                   \
struct ImageType                                                               \
{                                                                              \
   int32_t w;                                                                  \
   int32_t h;                                                                  \
   void const* data;                                                           \
};                                                                             \
typedef struct ImageType ImageType;                                            \
                                                                               \
struct VarImageType                                                            \
{                                                                              \
   int32_t w;                                                                  \
   int32_t h;                                                                  \
   void* data;                                                                 \
};                                                                             \
typedef struct VarImageType VarImageType;

/*******************************************************************************
 func
*******************************************************************************/

#define IMAGE_HAS_PIXEL_C_( FuncName, ImageType )                              \
bool FuncName( ImageType image, cPixel pixel )                                 \
{                                                                              \
   return in_range_c_( 0, pixel.x, image.w ) and                               \
          in_range_c_( 0, pixel.y, image.h );                                  \
}

#define GET_IMAGE_PIXEL_C_( FuncName, ImageType, ValueType )                   \
ValueType FuncName( ImageType image, cPixel pixel )                            \
{                                                                              \
   ValueType const* val = to_pixel_value_c_( image, ValueType, pixel );        \
   return ( val != NULL ) ? *val                                               \
                          : (ValueType){0};                                    \
}

#define SET_IMAGE_PIXEL_C_( FuncName, VarImageType, ValueType )                \
bool FuncName( VarImageType image, cPixel pixel, ValueType val )               \
{                                                                              \
   ValueType* ptr = to_var_pixel_value_c_( image, ValueType, pixel );          \
   if ( ptr == NULL )                                                          \
      return false;                                                            \
                                                                               \
   *ptr = val;                                                                 \
   return true;                                                                \
}

/*******************************************************************************
 func
*******************************************************************************/

#define DRAW_IMAGE_LINE_C_( FuncName, VarImageType, ValueType )                \
bool FuncName( VarImageType image, cPixel beg, cPixel end, ValueType val )     \
{                                                                              \
   int32_t dx = 0;                                                             \
   if ( not iabs32_c( end.x - beg.x, &dx ) )                                   \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
   int32_t const sx = beg.x < end.x ? 1 : -1;                                  \
   int32_t dy = 0;                                                             \
   if ( not iabs32_c( end.y - beg.y, &dy ) )                                   \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
   dy *= -1;                                                                   \
   int32_t const sy = beg.y < end.y ? 1 : -1;                                  \
   int32_t err = dx + dy;                                                      \
                                                                               \
   bool res = false;                                                           \
   while ( true )                                                              \
   {                                                                           \
      ValueType* ptr = to_var_pixel_value_c_( image, ValueType, beg );   \
      if ( ptr != NULL )                                                       \
      {                                                                        \
         *ptr = val;                                                           \
         res = true;                                                           \
      }                                                                        \
                                                                               \
      if ( eq_pixel_c( beg, end ) )                                            \
         break;                                                                \
                                                                               \
      int32_t e2;                                                              \
      if ( not imul32_c( 2, err, &e2 ) )                                       \
      {                                                                        \
         return false;                                                         \
      }                                                                        \
      if ( e2 > dy )                                                           \
      {                                                                        \
         err += dy;                                                            \
         beg.x += sx;                                                          \
      }                                                                        \
      if ( e2 < dx )                                                           \
      {                                                                        \
         err += dx;                                                            \
         beg.y += sy;                                                          \
      }                                                                        \
    }                                                                          \
   return res;                                                                 \
}

#define DRAW_IMAGE_RECT_C_( FuncName, VarImageType, ValueType )                \
bool FuncName( VarImageType image, cPixel a, cPixel b, ValueType val )         \
{                                                                              \
   cPixel tl = top_left_pixel_c( a, b );                                       \
   cPixel tr = top_right_pixel_c( a, b );                                      \
   cPixel bl = bottom_left_pixel_c( a, b );                                    \
   cPixel br = bottom_right_pixel_c( a, b );                                   \
                                                                               \
   bool res = false;                                                           \
   for ( int32_t x = tl.x; x <= tr.x; ++x )                                    \
   {                                                                           \
      cPixel pixel = pixel_c_( x, tl.y );                                      \
      ValueType* ptr = to_var_pixel_value_c_( image, ValueType, pixel );       \
      if ( ptr != NULL )                                                       \
      {                                                                        \
         *ptr = val;                                                           \
         res = true;                                                           \
      }                                                                        \
   }                                                                           \
   for ( int32_t x = bl.x; x <= br.x; ++x )                                    \
   {                                                                           \
      cPixel pixel = pixel_c_( x, bl.y );                                      \
      ValueType* ptr = to_var_pixel_value_c_( image, ValueType, pixel );       \
      if ( ptr != NULL )                                                       \
      {                                                                        \
         *ptr = val;                                                           \
         res = true;                                                           \
      }                                                                        \
   }                                                                           \
   for ( int32_t y = tl.y; y <= bl.y; ++y )                                    \
   {                                                                           \
      cPixel pixel = pixel_c_( tl.x, y );                                      \
      ValueType* ptr = to_var_pixel_value_c_( image, ValueType, pixel );       \
      if ( ptr != NULL )                                                       \
      {                                                                        \
         *ptr = val;                                                           \
         res = true;                                                           \
      }                                                                        \
   }                                                                           \
   for ( int32_t y = tr.y; y <= br.y; ++y )                                    \
   {                                                                           \
      cPixel pixel = pixel_c_( tr.x, y );                                      \
      ValueType* ptr = to_var_pixel_value_c_( image, ValueType, pixel );       \
      if ( ptr != NULL )                                                       \
      {                                                                        \
         *ptr = val;                                                           \
         res = true;                                                           \
      }                                                                        \
   }                                                                           \
   return res;                                                                 \
}

#define FILL_IMAGE_RECT_C_( FuncName, VarImageType, ValueType )                \
bool FuncName( VarImageType image, cPixel a, cPixel b, ValueType val )         \
{                                                                              \
   bool res = false;                                                           \
   cPixel min = top_left_pixel_c( a, b );                                      \
   cPixel max = bottom_right_pixel_c( a, b );                                  \
   for ( int32_t y = min.y; y <= max.y; ++y )                                  \
   for ( int32_t x = min.x; x <= max.x; ++x )                                  \
   {                                                                           \
      cPixel pixel = pixel_c_( x, y );                                         \
      ValueType* ptr = to_var_pixel_value_c_( image, ValueType, pixel );       \
      if ( ptr != NULL )                                                       \
      {                                                                        \
         *ptr = val;                                                           \
         res = true;                                                           \
      }                                                                        \
   }                                                                           \
   return res;                                                                 \
}

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 pixel
*******************************************************************************/

#define pixel_c_( X, Y )                                                       \
   ((cPixel){ .x=(X), .y=(Y) })

CLINGO_API inline bool eq_pixel_c( cPixel a, cPixel b )
{
   return a.x == b.x and a.y == b.y;
}

/*******************************************************************************
 pixel rect
*******************************************************************************/

CLINGO_API inline cPixel top_left_pixel_c( cPixel a, cPixel b )
{
   return pixel_c_( min_c_( a.x, b.x ), min_c_( a.y, b.y ) );
}

CLINGO_API inline cPixel top_right_pixel_c( cPixel a, cPixel b )
{
   return pixel_c_( max_c_( a.x, b.x ), min_c_( a.y, b.y ) );
}

CLINGO_API inline cPixel bottom_left_pixel_c( cPixel a, cPixel b )
{
   return pixel_c_( min_c_( a.x, b.x ), max_c_( a.y, b.y ) );
}

CLINGO_API inline cPixel bottom_right_pixel_c( cPixel a, cPixel b )
{
   return pixel_c_( max_c_( a.x, b.x ), max_c_( a.y, b.y ) );
}

/*******************************************************************************
 image
*******************************************************************************/

#define image_copy_c_( Image )                                                 \
{                                                                              \
   (Image).w,                                                                  \
   (Image).h,                                                                  \
   (Image).data                                                                \
}

CLINGO_API inline
void* alloc_image_data_c( int32_t w, int32_t h, int64_t typeSize )
{
   must_be_positive_c_( typeSize );

   int64_t size = 0;
   if ( not imul64_c( w, h, &size ) ) return NULL;
   if ( not imul64_c( size, typeSize, &size ) ) return NULL;
   return alloc_c( size );
}

#define for_each_pixel_c_( X, Y, Image )                                       \
for ( int32_t (Y) = 0; (Y) < (Image).h; ++(Y) )                                \
for ( int32_t (X) = 0; (X) < (Image).w; ++(X) )

#define to_pixel_value_c_( Image, Type, Pixel )                                \
   to_pixel_value_c(                                                           \
      (Image).w, (Image).h, (Image).data, sizeof_c_( Type ), (Pixel)           \
   )
CLINGO_API inline void const* to_pixel_value_c( int32_t w,
                                                int32_t h,
                                                void const* data,
                                                int64_t typeSize,
                                                cPixel pixel )
{
   must_exist_c_( data );
   must_be_positive_c_( typeSize );

   if ( not in_range_c_( 0, pixel.x, w-1 ) ) return NULL;
   if ( not in_range_c_( 0, pixel.y, h-1 ) ) return NULL;

   int64_t diff = 0;
   if ( not imul64_c( w, pixel.y, &diff ) ) return NULL;
   if ( not iadd64_c( pixel.x, diff, &diff ) ) return NULL;
   if ( not imul64_c( diff, typeSize, &diff ) ) return NULL;

   return data + diff;
}

#define to_var_pixel_value_c_( Image, Type, Pixel )                            \
   to_var_pixel_value_c(                                                       \
      (Image).w, (Image).h, (Image).data, sizeof_c_( Type ), (Pixel)           \
   )
CLINGO_API inline void* to_var_pixel_value_c( int32_t w,
                                              int32_t h,
                                              void* data,
                                              int64_t typeSize,
                                              cPixel pixel )
{
   must_exist_c_( data );
   must_be_positive_c_( typeSize );

   if ( not in_range_c_( 0, pixel.x, w-1 ) ) return NULL;
   if ( not in_range_c_( 0, pixel.y, h-1 ) ) return NULL;

   int64_t diff = 0;
   if ( not imul64_c( w, pixel.y, &diff ) ) return NULL;
   if ( not iadd64_c( pixel.x, diff, &diff ) ) return NULL;
   if ( not imul64_c( diff, typeSize, &diff ) ) return NULL;

   return data + diff;
}

#endif
