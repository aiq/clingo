#include "clingo/color/image.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

extern inline bool pixel_is_before_c( cPixel a, cPixel b );

extern inline bool pixel_is_after_c( cPixel a, cPixel b );

/*******************************************************************************
 init
*******************************************************************************/

extern inline void* alloc_image_data_c( int32_t w,
                                        int32_t h,
                                        int64_t typeSize );

extern inline void const* to_pixel_value_c( void const* data,
                                            int32_t w,
                                            int32_t h,
                                            int64_t typeSize,
                                            cPixel pixel );

extern inline void* to_var_pixel_value_c( void* data,
                                          int32_t w,
                                          int32_t h,
                                          int64_t typeSize,
                                          cPixel pixel );