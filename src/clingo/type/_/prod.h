#ifndef CLINGO_TYPE_INTERN_PROD_H
#define CLINGO_TYPE_INTERN_PROD_H

#include "clingo/lang/slice.h"

/*******************************************************************************
 prod
*******************************************************************************/

#define PROD_C_(                                                               \
   FuncName, SliceType, ValueType, ResType, MulFunc                            \
)                                                                              \
bool FuncName( SliceType slice, ResType res[static 1] )                        \
{                                                                              \
   if ( is_empty_c_( slice ) )                                                 \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
                                                                               \
   ValueType const* begin = begin_c_( slice );                                 \
   ValueType const* end = end_c_( slice );                                     \
   ResType prod = *begin;                                                      \
   ++begin;                                                                    \
   for ( ValueType const* iter = begin; iter != end; ++iter )                  \
   {                                                                           \
      if ( not MulFunc( prod, *iter, &prod ) )                                 \
      {                                                                        \
         return false;                                                         \
      }                                                                        \
   }                                                                           \
                                                                               \
   *res = prod;                                                                \
   return true;                                                                \
}

#endif
