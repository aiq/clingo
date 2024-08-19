#include "clingo/color/image.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 pixel
*******************************************************************************/

extern inline bool eq_pixel_c( cPixel a, cPixel b );

/*******************************************************************************
 pixel rect
*******************************************************************************/

extern inline cPixel top_left_pixel_c( cPixel a, cPixel b );
extern inline cPixel top_right_pixel_c( cPixel a, cPixel b );
extern inline cPixel bottom_left_pixel_c( cPixel a, cPixel b );
extern inline cPixel bottom_right_pixel_c( cPixel a, cPixel b );

/*******************************************************************************
 init
*******************************************************************************/

extern inline void* alloc_image_data_c( int32_t w,
                                        int32_t h,
                                        int64_t typeSize );

extern inline void const* to_pixel_value_c( int32_t w,
                                            int32_t h,
                                            void const* data,
                                            int64_t typeSize,
                                            cPixel pixel );

extern inline void* to_var_pixel_value_c( int32_t w,
                                          int32_t h,
                                          void* data,
                                          int64_t typeSize,
                                          cPixel pixel );