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

#define IMAGE_TYPE_C_( ImageType, VarImageType )                               \
struct ImageType                                                               \
{                                                                              \
   void const* data;                                                           \
   int32_t w;                                                                  \
   int32_t h;                                                                  \
};                                                                             \
typedef struct ImageType ImageType;                                            \
                                                                               \
struct VarImageType                                                            \
{                                                                              \
   void* data;                                                                 \
   int32_t w;                                                                  \
   int32_t h;                                                                  \
};                                                                             \
typedef struct VarImageType VarImageType;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define pixel_c_( X, Y )                                                       \
   ((cPixel){ .x=(X), .y=(Y) })

CLINGO_API inline bool pixel_is_before_c( cPixel a, cPixel b )
{
   return a.x < b.x and a.y < b.y;
}

CLINGO_API inline bool pixel_is_after_c( cPixel a, cPixel b )
{
   return a.x > b.x and a.y > b.y;
}

/*******************************************************************************
 init
*******************************************************************************/

#define image_copy_c_( Image )                                                 \
   { (Image).data, (Image).w, (Image).h }

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
      (Image).data, (Image).w, (Image).h, sizeof_c_( Type ), (Pixel)           \
   )
CLINGO_API inline void const* to_pixel_value_c( void const* data,
                                                int32_t w,
                                                int32_t h,
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
      (Image).data, (Image).w, (Image).h, sizeof_c_( Type ), (Pixel)           \
   )
CLINGO_API inline void* to_var_pixel_value_c( void* data,
                                              int32_t w,
                                              int32_t h,
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
