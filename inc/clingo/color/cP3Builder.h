#ifndef CLINGO_COLOR_CP3BUILDER_H
#define CLINGO_COLOR_CP3BUILDER_H

#include "clingo/apidecl.h"
#include "clingo/color/cRgb24.h"
#include "clingo/io/FILE.h"
#include "clingo/lang/error.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cP3Builder
{
   cRecorder ownRec;
   cRecorder* rec;
   cPixel end;
   cPixel itr;
   int err;
};
typedef struct cP3Builder cP3Builder;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

CLINGO_API
bool init_p3_builder_c( cP3Builder b[static 1], int32_t w, int32_t h );

CLINGO_API bool init_p3_builder_shell_c( cP3Builder b[static 1],
                                         cRecorder rec[static 1] ,
                                         int32_t w,
                                         int32_t h );

CLINGO_API void cleanup_p3_builder_c( cP3Builder b[static 1] );

/*******************************************************************************

*******************************************************************************/

CLINGO_API bool add_p3_image_c( cP3Builder b[static 1], cRgb24Image image );

CLINGO_API bool add_p3_pixel_c( cP3Builder b[static 1], cRgb24 rgb );

/*******************************************************************************

*******************************************************************************/

CLINGO_API bool push_p3_builder_error_c( cErrorStack es[static 1],
                                         cP3Builder b[static 1] );

/*******************************************************************************

*******************************************************************************/

CLINGO_API bool write_p3_file_c( cChars path,
                                 cRgb24Image image,
                                 cErrorStack es[static 1] );

#endif
