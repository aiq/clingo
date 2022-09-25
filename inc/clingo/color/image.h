#ifndef CLINGO_COLOR_IMAGE_H
#define CLINGO_COLOR_IMAGE_H

#include "clingo/apidecl.h"
#include "clingo/lang/func.h"
#include "clingo/lang/math.h"
#include "clingo/lang/mem.h"

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************
 init
*******************************************************************************/

struct cPixel
{
   int32_t x;
   int32_t y;
};
typedef struct cPixel cPixel;

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
********************************************************************* Functions
********************************************************************************
 pixel
*******************************************************************************/

#define pixel_c_( X, Y )                                                       \
   ((cPixel){ .x=(X), .y=(Y) })

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
