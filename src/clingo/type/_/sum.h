#ifndef CLINGO_ALGO_SUM_H
#define CLINGO_ALGO_SUM_H

#include "clingo/lang/slice.h"

/*******************************************************************************
 sum
*******************************************************************************/

#define SUM_C_(                                                                \
   FuncName, SliceType, ValueType, ResType, AddFunc                            \
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
   ResType sum = *begin;                                                       \
   ++begin;                                                                    \
   for ( ValueType const* iter = begin; iter != end; ++iter )                  \
   {                                                                           \
      if ( not AddFunc( sum, *iter, &sum ) )                                   \
      {                                                                        \
         return false;                                                         \
      }                                                                        \
   }                                                                           \
                                                                               \
   *res = sum;                                                                 \
   return true;                                                                \
}

#endif
