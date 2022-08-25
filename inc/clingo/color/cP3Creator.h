#ifndef CLINGO_COLOR_CP3CREATOR_H
#define CLINGO_COLOR_CP3CREATOR_H

#include "clingo/apidecl.h"
#include "clingo/color/cRgb24.h"
#include "clingo/io/FILE.h"
#include "clingo/lang/error.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 type
*******************************************************************************/

struct cP3Creator
{
   FILE* file;
   cPixel end;
   cPixel itr;
   int err;
};
typedef struct cP3Creator cP3Creator;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define start_p3_creator_( File, W, H )                                        \
(                                                                              \
   (cP3Creator){                                                               \
      .file=(File),                                                            \
      .end=pixel_c_( (W), (H) ),                                               \
      .itr=pixel_c_( 0, 0 ),                                                   \
      .err=0                                                                   \
   }                                                                           \
)

CLINGO_API bool append_p3_pixel_c( cP3Creator creator[static 1],
                                   cRgb24 rgb );

CLINGO_API bool push_p3_creator_error_c( cErrorStack es[static 1],
                                         cP3Creator creator[static 1] );

#endif
