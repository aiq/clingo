#ifndef CLINGO_LANG_SLICE_H
#define CLINGO_LANG_SLICE_H

#include <inttypes.h>
#include <iso646.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "clingo/lang/func.h"
#include "clingo/lang/math.h"
#include "clingo/lang/mem.h"

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************
 type
*******************************************************************************/

#define SLICES_C_( Type, SliceType, VarSliceType )                             \
struct SliceType                                                               \
{                                                                              \
   int64_t s;                                                                  \
   Type const* v;                                                              \
};                                                                             \
typedef struct SliceType SliceType;                                            \
                                                                               \
struct VarSliceType                                                            \
{                                                                              \
   int64_t s;                                                                  \
   Type* v;                                                                    \
};                                                                             \
typedef struct VarSliceType VarSliceType;

/*******************************************************************************
 temp
*******************************************************************************/

#define TEMP_SLICE_C_( Entry, EntryStruct )                                \
struct Entry                                                                   \
EntryStruct;                                                                   \
typedef struct Entry Entry;                                                    \
struct Entry##Slice                                                            \
{                                                                              \
   int64_t s;                                                                  \
   Entry const* v;                                                             \
};                                                                             \
typedef struct Entry##Slice Entry##Slice;

#define TEMP_VAR_SLICE_C_( Entry, EntryStruct )                            \
struct Entry                                                                   \
EntryStruct;                                                                   \
typedef struct Entry Entry;                                                    \
struct Entry##Slice                                                            \
{                                                                              \
   int64_t s;                                                                  \
   Entry* v;                                                                   \
};                                                                             \
typedef struct Entry##Slice Entry##Slice;

/*******************************************************************************
********************************************************************* Functions 
********************************************************************************
 init
*******************************************************************************/

#define as_c_( SliceType, Slice )                                              \
(SliceType){                                                                   \
   .s=(Slice).s,                                                               \
   .v=(Slice).v                                                                \
}

#define atween_c_( Beg, End )                                                  \
{                                                                              \
   .s=(End) - (Beg),                                                           \
   .v=(Beg)                                                                    \
}

#define empty_c_()                                                             \
{                                                                              \
   .s=0,                                                                       \
   .v=NULL                                                                     \
}

#define heap_slice_c_( Size, Type )                                            \
{                                                                              \
   .s=(Size),                                                                  \
   .v=(Type*)alloc_array_c( (Size), sizeof_c_(Type) )                          \
}

#define invalid_c_()                                                           \
{                                                                              \
   .s=-1,                                                                      \
   .v=NULL                                                                     \
}

#define scalars_c_( Size, Type )                                               \
{                                                                              \
   .s=(Size),                                                                  \
   .v=(Type[]){ [(Size)-1]=0 }                                                 \
}

#define slice_c_( Type, ... )                                                  \
{                                                                              \
   .s=nargs_c_( __VA_ARGS__ ),                                                 \
   .v=(Type[]){ __VA_ARGS__ }                                                  \
}

#define structs_c_( Size, Type )                                               \
{                                                                              \
   .s=(Size),                                                                  \
   .v=(Type[]){ [(Size)-1]={} }                                                \
}

/*******************************************************************************
 sub
*******************************************************************************/

#define left_c_( SliceType, Slice, MaxLen )                                    \
(                                                                              \
   (SliceType){                                                                \
      .s=(min_c_( (Slice).s, (MaxLen) ) ),                                     \
      .v=(Slice).v                                                             \
   }                                                                           \
)

#define mid_c_( SliceType, Slice, Idx )                                        \
(                                                                              \
   ( not in_range_c_( 0, (Idx), (Slice).s ) )                                  \
      ? (SliceType)empty_c_()                                                  \
      : (SliceType){ .s=(Slice).s-(Idx), .v=(Slice).v+(Idx) }                  \
)

#define right_c_( SliceType, Slice, MaxLen )                                   \
(                                                                              \
   ( (MaxLen) <= 0 )                                                           \
      ? (SliceType)empty_c_()                                                  \
      : (SliceType){                                                           \
           .s=min_c_( (Slice).s, (MaxLen) ),                                   \
           .v=(Slice).v + ( (Slice).s - min_c_( (Slice).s, (MaxLen) ) )        \
        }                                                                      \
)

#define sub_c_( SliceType, Slice, BegIdx, EndIdx )                             \
(                                                                              \
   (                                                                           \
      (BegIdx) < 0 or (EndIdx) < 0 or                                          \
      (EndIdx) <= (BegIdx) or (EndIdx) > (Slice).s                             \
   )                                                                           \
      ? (SliceType)empty_c_()                                                  \
      : (SliceType){ .s=(EndIdx) - (BegIdx), .v=(Slice).v + (BegIdx) }         \
)

/*******************************************************************************
 check
*******************************************************************************/

#define is_empty_c_( Slice )                                                   \
(                                                                              \
   (Slice).s <= 0                                                              \
)

#define is_invalid_c_( Slice )                                                 \
(                                                                              \
   (Slice).s < 0                                                               \
)

#define is_sub_c_( Main, Sub )                                                 \
(                                                                              \
   begin_c_( Main ) <= begin_c_( Sub ) and                                     \
   rbegin_c_( Main ) >= rbegin_c_( Sub )                                       \
)

#define valid_index_c_( Slice, Index )                                         \
(                                                                              \
   (Index) >= 0 and (Index) < (Slice).s                                        \
)

/*******************************************************************************
 access
*******************************************************************************/

#define first_c_( Slice )                                                      \
(                                                                              \
   (Slice).v[ 0 ]                                                              \
)

#define get_if_c_( Slice, Index, Def )                                         \
(                                                                              \
   valid_index_c_( (Slice), (Index) )                                          \
      ? (Slice).v[ (Index) ]                                                   \
      : (Def)                                                                  \
)

#define last_c_( Slice )                                                       \
(                                                                              \
   (Slice).v[ (Slice).s - 1 ]                                                  \
)

#define set_if_c_( Slice, Index, Value )                                       \
{                                                                              \
   if ( valid_index_c_( (Slice), (Index) ) )                                   \
      (Slice).v[ (Index) ] = (Value);                                          \
}

/*******************************************************************************
 pointer access
*******************************************************************************/

#define begin_c_( Slice )                                                      \
(                                                                              \
   is_empty_c_( Slice )                                                        \
      ? NULL                                                                   \
      : (Slice).v                                                              \
)

#define end_c_( Slice )                                                        \
(                                                                              \
   is_empty_c_( Slice )                                                        \
      ? NULL                                                                   \
      : (Slice).v + (Slice).s                                                  \
)

#define each_c_( Type, Itr, Slice )                                        \
for ( Type (Itr) = begin_c_( Slice ); (Itr) < end_c_( Slice ); ++(Itr) )

#define index_of_c_( Slice, Ptr )                                              \
(                                                                              \
   points_into_c_( (Slice), (Ptr) )                                            \
      ? (Ptr) - (Slice).v                                                      \
      : -1                                                                     \
)

#define for_each_c_( N, Type, Itr, Slice )                                     \
for ( int64_t (N) =  0; (N) < (Slice).s; )                                     \
for ( Type (Itr) = (Slice).v+(N); (Itr) == (Slice).v+(N); ++(N) )

#define nth_c_( Slice, N )                                                     \
(                                                                              \
   ( (N) >= 0 ) ? ptr_for_c_( (Slice), (N) )                                   \
                : ptr_for_c_( (Slice), ( (Slice).s + (N) ) )                   \
)

#define points_into_c_( Slice, Ptr )                                           \
(                                                                              \
   (Ptr) > rend_c_( Slice ) && (Ptr) < end_c_( Slice )                         \
      ? true                                                                   \
      : false                                                                  \
)

#define ptr_for_c_( Slice, Index )                                             \
(                                                                              \
   valid_index_c_( (Slice), (Index) )                                          \
      ? (Slice).v + (Index)                                                    \
      : NULL                                                                   \
)

#define rbegin_c_( Slice )                                                     \
(                                                                              \
   is_empty_c_( Slice )                                                        \
      ? NULL                                                                   \
      : (Slice).v + (Slice).s - 1                                              \
)

#define rend_c_( Slice )                                                       \
(                                                                              \
   is_empty_c_( Slice )                                                        \
      ? NULL                                                                   \
      : (Slice).v - 1                                                          \
)

#endif
