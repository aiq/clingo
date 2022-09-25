#ifndef CLINGO_LANG_WINDOW_H
#define CLINGO_LANG_WINDOW_H

#include "clingo/lang/slice.h"

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************
 type
*******************************************************************************/

#define WINDOW_C_( Type, SliceType, WindowType )                               \
struct WindowType                                                              \
{                                                                              \
   int64_t s;                                                                  \
   Type* v;                                                                    \
   SliceType slice;                                                            \
};                                                                             \
typedef struct WindowType WindowType;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define back_window_c_( Size, Slice )                                          \
{                                                                              \
   .s=((Slice).s < (Size)) ? 0 : (Size),                                       \
   .v=end_c_( Slice ) - (Size),                                                \
   .slice=(Slice)                                                              \
}

#define front_window_c_( Size, Slice )                                         \
{                                                                              \
   .s=((Slice).s < (Size)) ? 0 : (Size),                                       \
   .v=(Slice).v,                                                               \
   .slice=(Slice)                                                              \
}

/*******************************************************************************
 use
*******************************************************************************/

#define next_window_c_( Window )                                               \
(                                                                              \
   (Window).v++                                                                \
)

#define prev_window_c_( Window )                                               \
(                                                                              \
   (Window).v--                                                                \
)

#define valid_window_c_( Window )                                              \
(                                                                              \
   points_into_c_( (Window).slice, begin_c_( Window ) ) and                    \
   points_into_c_( (Window).slice, rbegin_c_( Window ) )                       \
)

#endif
