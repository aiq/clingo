#ifndef CLINGO_LANG_ALGO_H
#define CLINGO_LANG_ALGO_H

#include "clingo/lang/func.h"
#include "clingo/lang/mem.h"
#include "clingo/lang/slice.h"

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************
 check
*******************************************************************************/

#define CMP_SLICE_C_(                                                          \
   FuncName, SliceType, ValueType, CmpFunc, DoDeref                            \
)                                                                              \
int FuncName( SliceType a, SliceType b )                                       \
{                                                                              \
   ValueType* itrA = begin_c_( a );                                            \
   ValueType* endA = end_c_( a );                                              \
   ValueType* itrB = begin_c_( b );                                            \
   ValueType* endB = end_c_( b );                                              \
   while ( itrA != endA and itrB != endB )                                     \
   {                                                                           \
      int cmpRes = CmpFunc( DoDeref(itrA), DoDeref(itrB) );                    \
      if ( eq_c( cmpRes ) )                                                    \
      {                                                                        \
         ++itrA;                                                               \
         ++itrB;                                                               \
      }                                                                        \
      else if ( lt_c( cmpRes ) )                                               \
      {                                                                        \
         return -1;                                                            \
      }                                                                        \
      else /* gt_c( cmpRes ) */                                                \
      {                                                                        \
         return 1;                                                             \
      }                                                                        \
   }                                                                           \
                                                                               \
   if ( itrA == endA and itrB == endB )                                        \
   {                                                                           \
      return 0;                                                                \
   }                                                                           \
   else if ( a.s < b.s )                                                       \
   {                                                                           \
      return -1;                                                               \
   }                                                                           \
   else                                                                        \
   {                                                                           \
      return 1;                                                                \
   }                                                                           \
}

/******************************************************************************/

#define COUNT_EQ_C_(                                                           \
   FuncName, SliceType, ValueType, SearchType, CmpFunc, DoDeref                \
)                                                                              \
int64_t FuncName( SliceType slice, SearchType val )                            \
{                                                                              \
   if ( is_empty_c_( slice ) )                                                 \
   {                                                                           \
      return 0;                                                                \
   }                                                                           \
                                                                               \
   int64_t count = 0;                                                          \
   ValueType* begin = begin_c_( slice );                                       \
   ValueType* end = end_c_( slice );                                           \
   for ( ValueType* iter = begin; iter != end; ++iter )                        \
   {                                                                           \
      if ( eq_c( CmpFunc( DoDeref( iter ), val ) ) )                           \
      {                                                                        \
         ++count;                                                              \
      }                                                                        \
   }                                                                           \
                                                                               \
   return count;                                                               \
}

/******************************************************************************/

#define ENDS_WITH_C_(                                                          \
   FuncName, SliceType, ValueType, CmpFunc, DoDeref                            \
)                                                                              \
bool FuncName( SliceType slice, SliceType needle )                             \
{                                                                              \
   if ( slice.s < needle.s )                                                   \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
                                                                               \
   ValueType* sliceIter = rbegin_c_( slice );                                  \
   ValueType* needleIter = rbegin_c_( needle );                                \
                                                                               \
   ValueType* end = rend_c_( needle );                                         \
   while ( needleIter != end )                                                 \
   {                                                                           \
      if ( diff_c( CmpFunc( DoDeref( sliceIter ), DoDeref( needleIter ) ) ) )  \
      {                                                                        \
         return false;                                                         \
      }                                                                        \
      --sliceIter;                                                             \
      --needleIter;                                                            \
   }                                                                           \
                                                                               \
   return true;                                                                \
}

/******************************************************************************/

#define STARTS_WITH_C_(                                                        \
   FuncName, SliceType, ValueType, CmpFunc, DoDeref                            \
)                                                                              \
bool FuncName( SliceType slice, SliceType needle )                             \
{                                                                              \
   if ( slice.s < needle.s )                                                   \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
                                                                               \
   ValueType* sliceIter = begin_c_( slice );                                   \
   ValueType* needleIter = begin_c_( needle );                                 \
                                                                               \
   ValueType* end = end_c_( needle );                                          \
   while ( needleIter != end )                                                 \
   {                                                                           \
      if ( diff_c( CmpFunc( DoDeref( sliceIter ), DoDeref( needleIter ) ) ) )  \
      {                                                                        \
         return false;                                                         \
      }                                                                        \
      ++sliceIter;                                                             \
      ++needleIter;                                                            \
   }                                                                           \
                                                                               \
   return true;                                                                \
}

/*******************************************************************************
 find
*******************************************************************************/

#define BSEARCH_C_(                                                            \
   FuncName, SliceType, ValueType, SearchType, CmpFunc, DoDeref                \
)                                                                              \
ValueType* FuncName( SliceType slice, SearchType val )                         \
{                                                                              \
   if ( is_empty_c_( slice ) )                                                 \
   {                                                                           \
      return NULL;                                                             \
   }                                                                           \
                                                                               \
   int64_t l = 0;                                                              \
   int64_t r = slice.s - 1;                                                    \
   while ( l <= r )                                                            \
   {                                                                           \
      int64_t const m = l + ( ( r - l ) / 2 );                                 \
      ValueType* ptr = ptr_for_c_( slice, m );                                 \
      int const cmp = CmpFunc( DoDeref( ptr ), val );                          \
      if ( eq_c( cmp ) )                                                       \
      {                                                                        \
         return ptr;                                                           \
      }                                                                        \
      else if ( gt_c( cmp ) )                                                  \
      {                                                                        \
         r = m - 1;                                                            \
      }                                                                        \
      else /* lt_c( cmp ) */                                                   \
      {                                                                        \
         l = m + 1;                                                            \
      }                                                                        \
   }                                                                           \
                                                                               \
   return NULL;                                                                \
}

/******************************************************************************/

#define FIND_MAX_C_(                                                           \
   FuncName, SliceType, ValueType, CmpFunc, DoDeref                            \
)                                                                              \
ValueType* FuncName( SliceType slice )                                         \
{                                                                              \
   if ( is_empty_c_( slice ) )                                                 \
   {                                                                           \
      return NULL;                                                             \
   }                                                                           \
                                                                               \
   ValueType* max = begin_c_( slice );                                         \
   ValueType* begin = begin_c_( slice ) + 1;                                   \
   ValueType* end = end_c_( slice );                                           \
   for ( ValueType* iter = begin; iter != end; ++iter )                        \
   {                                                                           \
      if ( gt_c( CmpFunc( DoDeref( iter ), DoDeref( max ) ) ) )                \
      {                                                                        \
         max = iter;                                                           \
      }                                                                        \
   }                                                                           \
                                                                               \
   return max;                                                                 \
}

/******************************************************************************/

#define FIND_MIN_C_(                                                           \
   FuncName, SliceType, ValueType, CmpFunc, DoDeref                            \
)                                                                              \
ValueType* FuncName( SliceType slice )                                         \
{                                                                              \
   if ( is_empty_c_( slice ) )                                                 \
   {                                                                           \
      return NULL;                                                             \
   }                                                                           \
                                                                               \
   ValueType* min = begin_c_( slice );                                         \
   ValueType* begin = begin_c_( slice ) + 1;                                   \
   ValueType* end = end_c_( slice );                                           \
   for ( ValueType* iter = begin; iter != end; ++iter )                        \
   {                                                                           \
      if ( lt_c( CmpFunc( DoDeref( iter ), DoDeref( min ) ) ) )                \
      {                                                                        \
         min = iter;                                                           \
      }                                                                        \
   }                                                                           \
                                                                               \
   return min;                                                                 \
}

/******************************************************************************/

#define FIND_VAL_C_(                                                           \
   FuncName, SliceType, ValueType, SearchType, CmpFunc, DoDeref                \
)                                                                              \
ValueType* FuncName( SliceType slice, SearchType val )                         \
{                                                                              \
   if ( is_empty_c_( slice ) )                                                 \
   {                                                                           \
      return NULL;                                                             \
   }                                                                           \
                                                                               \
   ValueType* beg = begin_c_( slice );                                         \
   ValueType* end = end_c_( slice );                                           \
   for ( ValueType* itr = beg; itr != end; ++itr )                             \
   {                                                                           \
      if ( eq_c( CmpFunc( DoDeref( itr ), val ) ) )                            \
      {                                                                        \
         return itr;                                                           \
      }                                                                        \
   }                                                                           \
                                                                               \
   return NULL;                                                                \
}

/******************************************************************************/

#define INDEX_OF_SLICE_C_(                                                     \
   FuncName, SliceType, ValueType, CmpFunc, DoDeref                            \
)                                                                              \
int64_t FuncName( SliceType slice, SliceType sub )                             \
{                                                                              \
   if ( is_empty_c_( slice ) or is_empty_c_( sub ) )                           \
   {                                                                           \
      return -1;                                                               \
   }                                                                           \
                                                                               \
   if ( slice.s < sub.s )                                                      \
   {                                                                           \
      return -1;                                                               \
   }                                                                           \
                                                                               \
   ValueType* mainBeg = begin_c_( slice );                                     \
   ValueType* mainEnd = end_c_( slice );                                       \
   ValueType* subBeg = begin_c_( sub );                                        \
   ValueType* subEnd = end_c_( sub );                                          \
                                                                               \
   for ( ValueType* mainItr = mainBeg; mainItr != mainEnd; ++mainItr )         \
   {                                                                           \
      ValueType* tmpItr = mainItr;                                             \
      ValueType* subItr = subBeg;                                              \
      while ( subItr != subEnd and                                             \
              tmpItr != mainEnd and                                            \
              eq_c( CmpFunc( DoDeref( tmpItr ), DoDeref( subItr ) ) ) )        \
      {                                                                        \
         ++subItr;                                                             \
         ++tmpItr;                                                             \
      }                                                                        \
      if ( subItr == subEnd )                                                  \
      {                                                                        \
         return index_of_c_( slice, mainItr );                                 \
      }                                                                        \
   }                                                                           \
                                                                               \
   return -1;                                                                  \
}

/*******************************************************************************
 manipulate
*******************************************************************************/

#define QSORT_C_(                                                              \
   FuncName, SliceType, ValueType, CmpFunc, DoDeref                            \
)                                                                              \
void FuncName( SliceType slice )                                               \
{                                                                              \
   static int64_t const InsertSortThreshold = 64;                              \
                                                                               \
   must_be_positive_c_( slice.s );                                             \
                                                                               \
   if ( slice.s < 2 )                                                          \
   {                                                                           \
      return;                                                                  \
   }                                                                           \
                                                                               \
   int64_t const footprint = sizeof_c_( ValueType ) * slice.s;                 \
   if ( footprint < InsertSortThreshold )                                      \
   {                                                                           \
      /****************************************************** insertion sort */\
                                                                               \
      ValueType* beg = begin_c_( slice ) + 1; /* ptr on the second entry */    \
      ValueType* end = end_c_( slice );                                        \
      for ( ValueType* itr = beg; itr < end; ++itr )                           \
      {                                                                        \
         ValueType* currPtr = itr;                                             \
         ValueType* leftPtr = itr - 1;                                         \
         int cmp = CmpFunc( DoDeref( currPtr ), DoDeref( leftPtr ) );          \
         while ( lt_c( cmp ) )                                                 \
         {                                                                     \
            swap_c_( ValueType, *leftPtr, *currPtr, x );                       \
                                                                               \
            --currPtr;                                                         \
            --leftPtr;                                                         \
            if ( currPtr < beg )                                               \
            {                                                                  \
               break;                                                          \
            }                                                                  \
            cmp = CmpFunc( DoDeref( currPtr ), DoDeref( leftPtr ) );           \
         }                                                                     \
      }                                                                        \
      return;                                                                  \
   }                                                                           \
                                                                               \
   /************************************************************** quicksort */\
                                                                               \
   /********************************************************* pivot */         \
   ValueType* pivot = NULL;                                                    \
   {                                                                           \
      ValueType* firstPtr = begin_c_( slice );                                 \
      int64_t const midPos = slice.s / 2;                                      \
      ValueType* midPtr = ptr_for_c_( slice, midPos );                         \
      ValueType* lastPtr = rbegin_c_( slice );                                 \
                                                                               \
      if ( lt_c( CmpFunc( DoDeref( midPtr ), DoDeref( firstPtr ) ) ) )         \
      {                                                                        \
         swap_c_( ValueType*, firstPtr, midPtr, x );                           \
      }                                                                        \
                                                                               \
      if ( lt_c( CmpFunc( DoDeref( lastPtr ), DoDeref( midPtr ) ) ) )          \
      {                                                                        \
         swap_c_( ValueType*, midPtr, lastPtr, x );                            \
      }                                                                        \
                                                                               \
      if ( lt_c( CmpFunc( DoDeref( midPtr ), DoDeref( firstPtr ) ) ) )         \
      {                                                                        \
         swap_c_( ValueType*, firstPtr, midPtr, x );                           \
      }                                                                        \
      pivot = midPtr;                                                          \
    }                                                                          \
   ValueType pivotVal = *pivot;  /* copy outside the slice array */            \
   pivot = &pivotVal;                                                          \
                                                                               \
   /***************************************************** partition */         \
   SliceType leftPart;                                                         \
   SliceType rightPart;                                                        \
   {                                                                           \
      ValueType* left = begin_c_( slice );                                     \
      while ( lte_c( CmpFunc( DoDeref( left ), DoDeref( pivot ) ) ) )          \
      {                                                                        \
         ++left;                                                               \
      }                                                                        \
                                                                               \
      ValueType* right = rbegin_c_( slice );                                   \
      while ( gt_c( CmpFunc( DoDeref( right ), DoDeref( pivot ) ) ) )          \
      {                                                                        \
         --right;                                                              \
      }                                                                        \
                                                                               \
      while ( left < right )                                                   \
      {                                                                        \
         swap_c_( ValueType, *left, *right, x );                               \
                                                                               \
         while ( lte_c( CmpFunc( DoDeref( left ), DoDeref( pivot ) ) ) )       \
         {                                                                     \
            ++left;                                                            \
         }                                                                     \
         while ( gt_c( CmpFunc( DoDeref( right ), DoDeref( pivot ) ) ) )       \
         {                                                                     \
            --right;                                                           \
         }                                                                     \
      }                                                                        \
                                                                               \
      int64_t const splitIndex = index_of_c_( slice, left );                   \
      leftPart.v = slice.v;                                                    \
      leftPart.s = splitIndex;                                                 \
                                                                               \
      rightPart.v = left;                                                      \
      rightPart.s = slice.s - splitIndex;                                      \
   }                                                                           \
                                                                               \
   FuncName( leftPart );                                                       \
   FuncName( rightPart );                                                      \
}

/******************************************************************************/

#define REVERSE_C_(                                                            \
   FuncName, SliceType, ValueType                                              \
)                                                                              \
void FuncName( SliceType slice )                                               \
{                                                                              \
   ValueType* left = begin_c_( slice );                                        \
   ValueType* right = rbegin_c_( slice );                                      \
   for ( ; left < right; ++left, --right )                                     \
   {                                                                           \
      ValueType tmp = *left;                                                   \
      *left = *right;                                                          \
      *right = tmp;                                                            \
   }                                                                           \
}

/******************************************************************************/

#define ROTATE_C_(                                                             \
   FuncName, SliceType, ValueType                                              \
)                                                                              \
void FuncName( SliceType slice, int64_t distance )                             \
{                                                                              \
   if ( is_empty_c_( slice ) )                                                 \
   {                                                                           \
      return;                                                                  \
   }                                                                           \
                                                                               \
   int64_t const size = slice.s;                                               \
   distance = distance % size;                                                 \
   if ( distance < 0 )                                                         \
   {                                                                           \
      distance += size;                                                        \
   }                                                                           \
                                                                               \
   int64_t counter = 0;                                                        \
   for ( int64_t start = 0; counter < size; ++start )                          \
   {                                                                           \
      int64_t currPos = start;                                                 \
      ValueType val = slice.v[ start ];                                        \
      do                                                                       \
      {                                                                        \
         int64_t nextPos = ( currPos + distance ) % size;                      \
         ValueType tmp = slice.v[ nextPos ];                                   \
         slice.v[ nextPos ] = val;                                             \
         val = tmp;                                                            \
         currPos = nextPos;                                                    \
         ++counter;                                                            \
      }                                                                        \
      while ( start != currPos );                                              \
   }                                                                           \
}

/******************************************************************************/

#define SET_SLICE_C_( FuncName, VarSliceType, SliceType )                      \
int64_t FuncName( VarSliceType dst, SliceType src )                            \
{                                                                              \
   int64_t const n = min_c_( dst.s, src.s );                                   \
   if ( n < 0 ) return 0;                                                      \
                                                                               \
   dst.s = n;                                                                  \
   times_c_( n, i )                                                            \
   {                                                                           \
      dst.v[i] = src.v[i];                                                     \
   }                                                                           \
   return n;                                                                   \
}

/**********++*******************************************************************
********************************************************************* Functions 
********************************************************************************
 parameter
*******************************************************************************/

#define do_deref_c_( Ptr )                                                     \
   *(Ptr)

#define do_ref_c_( Val )                                                       \
   &(Val)

#define do_nothing_c_( Val )

#define do_not_deref_c_( Ptr )                                                 \
   (Ptr)

#define do_not_ref_c_( Val )                                                   \
   (Val)

#endif
