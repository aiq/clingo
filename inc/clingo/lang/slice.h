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
 init
*******************************************************************************/

#define EMPTY_SLICE_C_( FuncName, SliceType )                                  \
SliceType FuncName( void )                                                     \
{                                                                              \
   return (SliceType){ .s=0, .v=NULL };                                        \
}

#define MAKE_SLICE_C_( FuncName, SliceType, Type )                             \
SliceType FuncName( Type* beg, Type* end )                                     \
{                                                                              \
   must_exist_c_( beg );                                                       \
   must_exist_c_( end );                                                       \
                                                                               \
   int64_t s = end - beg;                                                      \
   return ( s < 0 ) ? (SliceType){ .s=0, .v=NULL }                             \
                    : (SliceType){ .s=s, .v=beg };                             \
}

#define SLICE_C_( FuncName, SliceType, Type )                                  \
SliceType FuncName( int64_t s, Type* v )                                       \
{                                                                              \
   must_be_positive_c_( s );                                                   \
   return (SliceType){ .s=s, .v=v };                                           \
}

/*******************************************************************************
 sub
*******************************************************************************/

#define LEFT_SLICE_C_( FuncName, SliceType )                                   \
SliceType FuncName( SliceType slice, int64_t maxLen )                          \
{                                                                              \
   must_be_positive_c_( maxLen );                                              \
                                                                               \
   if ( maxLen == 0 )                                                          \
   {                                                                           \
      return (SliceType){ .s=0, .v=slice.v };                                  \
   }                                                                           \
                                                                               \
   int64_t const minLen = min_c_( slice.s, maxLen );                           \
   return (SliceType){ .s=minLen, .v=slice.v };                                \
}

#define MID_SLICE_C_( FuncName, SliceType )                                    \
SliceType FuncName( SliceType slice, int64_t index )                           \
{                                                                              \
   must_be_positive_c_( index );                                               \
                                                                               \
   if ( index > slice.s )                                                      \
   {                                                                           \
      return (SliceType){ .s=0, .v=NULL };                                     \
   }                                                                           \
                                                                               \
   return (SliceType){ .s=slice.s-index, .v=slice.v+index };                   \
}

#define RIGHT_SLICE_C_( FuncName, SliceType )                                  \
SliceType FuncName( SliceType slice, int64_t maxLen )                          \
{                                                                              \
   must_be_positive_c_( maxLen );                                              \
                                                                               \
   if ( maxLen == 0 )                                                          \
   {                                                                           \
      return (SliceType){ .s=0, .v=slice.v+slice.s };                                \
   }                                                                           \
                                                                               \
   int64_t const minLen = min_c_( slice.s, maxLen );                           \
   return (SliceType){ .s=minLen, .v=slice.v+(slice.s-minLen) };               \
}

#define SUB_SLICE_C_( FuncName, SliceType )                                    \
SliceType FuncName( SliceType slice, int64_t begIdx, int64_t endIdx )          \
{                                                                              \
   must_be_positive_c_( begIdx );                                              \
   must_be_positive_c_( endIdx );                                              \
                                                                               \
   if ( endIdx <= begIdx or endIdx > slice.s )                                 \
   {                                                                           \
      return (SliceType){ .s=0, .v=NULL };                                     \
   }                                                                           \
                                                                               \
   return (SliceType){ .s=(endIdx-begIdx), .v=slice.v+begIdx };                \
}

/*******************************************************************************
 var slice
*******************************************************************************/

#define AS_SLICE_C_( FuncName, SliceType, VarSliceType )                       \
SliceType FuncName( VarSliceType slice )                                       \
{                                                                              \
   return (SliceType){ .s=slice.s, .v=slice.v };                               \
}

#define CAST_SLICE_C_( FuncName, VarSliceType, SliceType )                     \
VarSliceType FuncName( VarSliceType slice, SliceType sub )                     \
{                                                                              \
   int64_t const begIdx = index_of_c_( slice, sub.v );                         \
   int64_t const endIdx = begIdx + sub.s;                                      \
   if ( begIdx == -1 or endIdx <= begIdx or endIdx > slice.s )                 \
   {                                                                           \
      return (VarSliceType){ .s=0, .v=NULL };                                  \
   }                                                                           \
   return (VarSliceType){ .s=(endIdx-begIdx), .v=slice.v+begIdx };             \
}

#define SET_SLICE_C_( FuncName, VarSliceType, SliceType )                      \
int64_t FuncName( VarSliceType dst, SliceType src )                            \
{                                                                              \
   int64_t const n = min_c_( dst.s, src.s );                                   \
   if ( n < 0 ) return 0;                                                      \
                                                                               \
   times_c_( n, i )                                                            \
   {                                                                           \
      dst.v[i] = src.v[i];                                                     \
   }                                                                           \
   return n;                                                                   \
}

/*******************************************************************************
 type
*******************************************************************************/

#define SLICE_DEF_C_( Type, SliceType, FuncSuffix,                             \
                      VarSliceType, VarFuncSuffix )                            \
struct SliceType                                                               \
{                                                                              \
   int64_t s;                                                                  \
   Type const* v;                                                              \
};                                                                             \
typedef struct SliceType SliceType;                                            \
                                                                               \
inline SLICE_C_( FuncSuffix, SliceType, Type const )                           \
inline MAKE_SLICE_C_( make_##FuncSuffix, SliceType, Type const )               \
inline EMPTY_SLICE_C_( empty_##FuncSuffix, SliceType )                         \
                                                                               \
inline SUB_SLICE_C_( sub_##FuncSuffix, SliceType )                             \
inline LEFT_SLICE_C_( left_##FuncSuffix, SliceType )                           \
inline MID_SLICE_C_( mid_##FuncSuffix, SliceType )                             \
inline RIGHT_SLICE_C_( right_##FuncSuffix, SliceType )                         \
                                                                               \
struct VarSliceType                                                            \
{                                                                              \
   int64_t s;                                                                  \
   Type* v;                                                                    \
};                                                                             \
typedef struct VarSliceType VarSliceType;                                      \
                                                                               \
inline SLICE_C_( VarFuncSuffix, VarSliceType, Type )                           \
inline MAKE_SLICE_C_( make_##VarFuncSuffix, VarSliceType, Type )               \
inline EMPTY_SLICE_C_( empty_##VarFuncSuffix, VarSliceType )                   \
                                                                               \
inline SUB_SLICE_C_( sub_##VarFuncSuffix, VarSliceType )                       \
inline LEFT_SLICE_C_( left_##VarFuncSuffix, VarSliceType )                     \
inline MID_SLICE_C_( mid_##VarFuncSuffix, VarSliceType )                       \
inline RIGHT_SLICE_C_( right_##VarFuncSuffix, VarSliceType )                   \
                                                                               \
inline AS_SLICE_C_( as_##FuncSuffix, SliceType, VarSliceType )                 \
inline CAST_SLICE_C_( cast_##FuncSuffix, VarSliceType, SliceType )             \
inline SET_SLICE_C_( set_##FuncSuffix, VarSliceType, SliceType )

/**********************************************************/

#define SLICE_IMPL_C_( Type, SliceType, FuncSuffix,                            \
                       VarSliceType, VarFuncSuffix )                           \
extern inline SliceType FuncSuffix( int64_t, Type const* );                    \
extern inline SliceType make_##FuncSuffix( Type const*, Type const* );         \
extern inline SliceType empty_##FuncSuffix( void );                            \
extern inline SliceType sub_##FuncSuffix( SliceType, int64_t, int64_t );       \
extern inline SliceType left_##FuncSuffix( SliceType, int64_t );               \
extern inline SliceType mid_##FuncSuffix( SliceType, int64_t );                \
extern inline SliceType right_##FuncSuffix( SliceType, int64_t );              \
                                                                               \
extern inline VarSliceType VarFuncSuffix( int64_t, Type* );                    \
extern inline VarSliceType make_##VarFuncSuffix( Type*, Type* );               \
extern inline VarSliceType empty_##VarFuncSuffix( void );                      \
extern inline VarSliceType sub_##VarFuncSuffix( VarSliceType, int64_t, int64_t );\
extern inline VarSliceType left_##VarFuncSuffix( VarSliceType, int64_t );      \
extern inline VarSliceType mid_##VarFuncSuffix( VarSliceType, int64_t );       \
extern inline VarSliceType right_##VarFuncSuffix( VarSliceType, int64_t );     \
extern inline SliceType as_##FuncSuffix( VarSliceType );                       \
extern inline VarSliceType cast_##FuncSuffix( VarSliceType, SliceType );       \
extern inline int64_t set_##FuncSuffix( VarSliceType, SliceType );

/*******************************************************************************
 temp
*******************************************************************************/

#define TEMP_SLICE_DEF_C_( Entry, EntryStruct )                                \
struct Entry                                                                   \
EntryStruct;                                                                   \
typedef struct Entry Entry;                                                    \
struct Entry##Slice                                                            \
{                                                                              \
   int64_t s;                                                                  \
   Entry const* v;                                                             \
};                                                                             \
typedef struct Entry##Slice Entry##Slice;

#define TEMP_VAR_SLICE_DEF_C_( Entry, EntryStruct )                            \
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

#define heap_slice_c_( Size, Type )                                            \
{                                                                              \
   .s=(Size),                                                                  \
   .v=(Type*)alloc_array_c( (Size), sizeof_c_(Type) )                          \
}

#define invalid_slice_c_()                                                     \
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

#define get_c_( Slice, Index, Def )                                            \
(                                                                              \
   valid_index_c_( (Slice), (Index) )                                          \
      ? (Slice).v[ (Index) ]                                                   \
      : (Def)                                                                  \
)

#define last_c_( Slice )                                                       \
(                                                                              \
   (Slice).v[ (Slice).s - 1 ]                                                  \
)

#define put_c_( Slice, Index, Value )                                          \
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

#define for_each_c_( Type, Itr, Slice )                                        \
for ( Type (Itr) = begin_c_( Slice ); (Itr) < end_c_( Slice ); ++(Itr) )

#define index_of_c_( Slice, Ptr )                                              \
(                                                                              \
   points_into_c_( (Slice), (Ptr) )                                            \
      ? (Ptr) - (Slice).v                                                      \
      : -1                                                                     \
)

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
