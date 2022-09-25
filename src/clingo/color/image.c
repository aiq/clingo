#include "clingo/color/image.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
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