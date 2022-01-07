#ifndef CLINGO_LANG_WINDOW_H
#define CLINGO_LANG_WINDOW_H

#include "clingo/lang/slice.h"

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************
 init
*******************************************************************************/

#define INIT_FRONT_WINDOW_C_( FuncName, WindowType, SliceType )                \
void FuncName( WindowType window[static 1],                                    \
               int64_t s,                                                      \
               SliceType slice )                                               \
{                                                                              \
   must_exist_c_( window );                                                    \
   must_be_positive_c_( s );                                                   \
                                                                               \
   if ( slice.s < s )                                                          \
   {                                                                           \
      window->s = 0;                                                           \
      window->v = NULL;                                                        \
      window->slice = slice;                                                   \
      return;                                                                  \
   }                                                                           \
                                                                               \
   window->s = s;                                                              \
   window->v = slice.v;                                                        \
   window->slice = slice;                                                      \
}

/**********************************************************/

#define INIT_BACK_WINDOW_C_( FuncName, WindowType, SliceType )                 \
void FuncName( WindowType window[static 1],                                    \
               int64_t s,                                                      \
               SliceType slice )                                               \
{                                                                              \
   must_exist_c_( window );                                                    \
   must_be_positive_c_( s );                                                   \
                                                                               \
   if ( slice.s < s )                                                          \
   {                                                                           \
      window->s = 0;                                                           \
      window->v = NULL;                                                        \
      window->slice = slice;                                                   \
      return;                                                                  \
   }                                                                           \
                                                                               \
   window->s = s;                                                              \
   window->v = end_c_( slice ) - s;                                            \
   window->slice = slice;                                                      \
}

/*******************************************************************************
 type
*******************************************************************************/

#define WINDOW_DEF_C_( Type,                                                   \
                       WindowType, SliceType, FuncSuffix,                      \
                       VarWindowType, VarSliceType, VarFuncSuffix )            \
struct WindowType                                                              \
{                                                                              \
   int64_t s;                                                                  \
   Type const* v;                                                              \
   SliceType slice;                                                            \
};                                                                             \
typedef struct WindowType WindowType;                                          \
                                                                               \
inline INIT_FRONT_WINDOW_C_( init_front_##FuncSuffix, WindowType, SliceType )  \
inline INIT_BACK_WINDOW_C_( init_back_##FuncSuffix, WindowType, SliceType )    \
                                                                               \
struct VarWindowType                                                           \
{                                                                              \
   int64_t s;                                                                  \
   Type* v;                                                                    \
   VarSliceType slice;                                                         \
};                                                                             \
typedef struct VarWindowType VarWindowType;                                    \
                                                                               \
inline INIT_FRONT_WINDOW_C_( init_front_##VarFuncSuffix,                       \
                             VarWindowType,                                    \
                             VarSliceType )                                    \
inline INIT_BACK_WINDOW_C_( init_back_##VarFuncSuffix,                         \
                            VarWindowType,                                     \
                            VarSliceType )

/**********************************************************/

#define WINDOW_IMPL_C_( WindowType, SliceType, FuncSuffix,                     \
                        VarWindowType, VarSliceType, VarFuncSuffix )           \
extern inline void init_front_##FuncSuffix( WindowType[static 1],              \
                                            int64_t,                           \
                                            SliceType );                       \
extern inline void init_back_##FuncSuffix( WindowType[static 1],               \
                                           int64_t,                            \
                                           SliceType );                        \
extern inline void init_front_##VarFuncSuffix( VarWindowType*,                 \
                                               int64_t,                        \
                                               VarSliceType );                 \
extern inline void init_back_##VarFuncSuffix( VarWindowType*,                  \
                                              int64_t,                         \
                                              VarSliceType );

/**********************************************************/

#define STATIC_FRONT_WINDOW_C_( Type, WindowType, SliceType, FuncSuffix )      \
struct WindowType                                                              \
{                                                                              \
   int64_t s;                                                                  \
   Type* v;                                                                    \
   SliceType slice;                                                            \
};                                                                             \
typedef struct WindowType WindowType;                                          \
static INIT_FRONT_WINDOW_C_( init_front_##FuncSuffix, WindowType, SliceType )

/**********************************************************/

#define STATIC_BACK_WINDOW_C_( Type, WindowType, SliceType, FuncSuffix )       \
struct WindowType                                                              \
{                                                                              \
   int64_t s;                                                                  \
   Type* v;                                                                    \
   SliceType slice;                                                            \
};                                                                             \
typedef struct WindowType WindowType;                                          \
static INIT_BACK_WINDOW_C_( init_back_##FuncSuffix, WindowType, SliceType )

/*******************************************************************************
********************************************************************* Functions
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
