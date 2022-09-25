#ifndef CLINGO_CONTAINER_VEC_H
#define CLINGO_CONTAINER_VEC_H

#include <stdbool.h>
#include <iso646.h>

#include "clingo/apidecl.h"
#include "clingo/lang/algo.h"
#include "clingo/lang/CObject.h"
#include "clingo/type/float.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************/

struct cVecInfo
{
   int64_t count;
   int64_t cap;
};
typedef struct cVecInfo cVecInfo;

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************
 create
*******************************************************************************/

#define MAKE_VEC_C_(                                                           \
   FuncSuffix, VecType, ValType, Meta                                          \
)                                                                              \
VecType* make_##FuncSuffix( int64_t cap )                                      \
{                                                                              \
   must_be_positive_c_( cap );                                                 \
                                                                               \
   cObjectInfo const info = default_object_info_c_( &Meta );                   \
   VecType* result = alloc_object_c_( VecType, &info );                        \
   if ( result == NULL )                                                       \
   {                                                                           \
      return NULL;                                                             \
   }                                                                           \
                                                                               \
   result->data = alloc_array_c_( cap, ValType );                              \
   if ( result->data == NULL )                                                 \
   {                                                                           \
      release_c( result );                                                     \
      return NULL;                                                             \
   }                                                                           \
                                                                               \
   result->i.cap = cap;                                                        \
   result->i.count = 0;                                                        \
                                                                               \
   return result;                                                              \
}

/******************************************************************************/

#define NEW_VEC_C_(                                                            \
   FuncSuffix, VecType                                                         \
)                                                                              \
VecType* new_##FuncSuffix()                                                    \
{                                                                              \
   return make_##FuncSuffix( 64 );                                             \
}

/*******************************************************************************
 manage
*******************************************************************************/

#define DATA_OF_VEC_C_(                                                        \
   FuncSuffix, VecType, ValType                                                \
)                                                                              \
ValType const* data_of_##FuncSuffix( VecType const* vec )                      \
{                                                                              \
   must_exist_c_( vec );                                                       \
   return vec->data;                                                           \
}

/******************************************************************************/

#define VAR_DATA_OF_VEC_C_(                                                    \
   FuncSuffix, VecType, ValType                                                \
)                                                                              \
ValType* var_data_of_##FuncSuffix( VecType* vec )                              \
{                                                                              \
   must_exist_c_( vec );                                                       \
   return vec->data;                                                           \
}

/******************************************************************************/

#define RESIZE_VEC_C_(                                                         \
   FuncSuffix, VecType, ValType                                                \
)                                                                              \
bool resize_##FuncSuffix( VecType* vec, int64_t cap )                          \
{                                                                              \
   must_exist_c_( vec );                                                       \
                                                                               \
   if ( cap < vec->i.count )                                                   \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
   if ( cap == vec->i.cap )                                                    \
   {                                                                           \
      return true;                                                             \
   }                                                                           \
                                                                               \
   void* newData = realloc_array_c_( vec->data, cap, ValType );                \
   if ( newData == NULL )                                                      \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
                                                                               \
   vec->data = newData;                                                        \
   vec->i.cap = cap;                                                           \
   return true;                                                                \
}

/******************************************************************************/

#define INFO_OF_VEC_C_(                                                        \
   FuncSuffix, VecType                                                         \
)                                                                              \
cVecInfo const* info_of_##FuncSuffix( VecType const* vec )                     \
{                                                                              \
   must_exist_c_( vec );                                                       \
   return &(vec->i);                                                           \
}

/*******************************************************************************
 api
*******************************************************************************/

#define ADD_TO_VEC_C_(                                                         \
   FuncSuffix, VecType, ValType, Retain, DoDeref                               \
)                                                                              \
bool add_to_##FuncSuffix( VecType* vec, ValType val )                          \
{                                                                              \
   must_exist_c_( vec );                                                       \
   /*must_exist_c_( val );*/                                                   \
                                                                               \
   if ( vec->i.count == vec->i.cap )                                           \
   {                                                                           \
      if ( not resize_##FuncSuffix( vec, vec->i.cap * 2 ) )                    \
      {                                                                        \
         return false;                                                         \
      }                                                                        \
   }                                                                           \
                                                                               \
   Retain( val );                                                              \
   vec->data[ vec->i.count ] = DoDeref(val);                                   \
   vec->i.count += 1;                                                          \
   return true;                                                                \
}

/**************************************/

#define ADD_ARRAY_TO_VEC_C_(                                                   \
   FuncSuffix, VecType, ValType, Retain                                        \
)                                                                              \
bool add_array_to_##FuncSuffix( VecType* vec, int64_t n, ValType const* arr )  \
{                                                                              \
   must_exist_c_( vec );                                                       \
   must_exist_c_( arr );                                                       \
                                                                               \
   int64_t const reqSize = vec->i.count + n;                                   \
                                                                               \
   if ( reqSize > vec->i.cap )                                                 \
   {                                                                           \
      if ( not resize_##FuncSuffix( vec, ( reqSize*2 ) ) )                     \
      {                                                                        \
         return false;                                                         \
      }                                                                        \
   }                                                                           \
                                                                               \
   int64_t count = vec->i.count;                                               \
   for ( int64_t i = 0; count < reqSize; ++i, ++count )                        \
   {                                                                           \
      Retain( arr[i] );                                                        \
      vec->data[ count ] = arr[i];                                             \
   }                                                                           \
   vec->i.count = count;                                                       \
                                                                               \
   return true;                                                                \
}

/**************************************/

#define GET_FROM_VEC_C_(                                                       \
   FuncSuffix, VecType, ReturnType, DoDeref                                    \
)                                                                              \
ReturnType get_from_##FuncSuffix( VecType const* vec, int64_t pos )            \
{                                                                              \
   must_exist_c_( vec );                                                       \
   must_be_in_range_c_( 0, pos, vec->i.count-1 );                              \
   return DoDeref((vec->data + pos));                                          \
}

/**************************************/

#define GET_VAR_FROM_VEC_C_(                                                   \
   FuncSuffix, VecType, ValType                                                \
)                                                                              \
ValType* get_var_from_##FuncSuffix( VecType* vec, int64_t pos )                \
{                                                                              \
   must_exist_c_( vec );                                                       \
   must_be_in_range_c_( 0, pos, vec->i.count-1 );                              \
   return vec->data + pos;                                                     \
}

/**************************************/

#define INSERT_INTO_VEC_C_(                                                    \
   FuncSuffix, VecType, ValType, Retain                               \
)                                                                              \
bool insert_into_##FuncSuffix( VecType* vec, int64_t pos, ValType val )        \
{                                                                              \
   must_exist_c_( vec );                                                       \
   /*must_exist_c_( val );*/                                                   \
   must_be_in_range_c_( 0, pos, vec->i.count-1 );                              \
                                                                               \
   if ( vec->i.count == vec->i.cap )                                           \
   {                                                                           \
      if ( not resize_##FuncSuffix( vec, vec->i.cap * 2 ) )                    \
      {                                                                        \
         return false;                                                         \
      }                                                                        \
   }                                                                           \
                                                                               \
   void* dst = vec->data + pos + 1;                                            \
   void* src = vec->data + pos;                                                \
   int64_t n = ( vec->i.count - pos ) * sizeof_c_( ValType );                  \
   size_t size;                                                                \
   if ( not int64_to_size_c( n, &size ) ) return false;                        \
                                                                               \
   Retain( val );                                                              \
                                                                               \
   memmove( dst, src, size );                                                  \
   vec->data[ pos ] = val;                                                     \
   vec->i.count += 1;                                                          \
                                                                               \
   return true;                                                                \
}

/**************************************/

#define REMOVE_FROM_VEC_C_(                                                    \
   FuncSuffix, VecType, ValType, Release                                       \
)                                                                              \
bool remove_from_##FuncSuffix( VecType* vec, int64_t pos )                     \
{                                                                              \
   must_exist_c_( vec );                                                       \
   must_be_in_range_c_( 0, pos, vec->i.count-1 );                              \
                                                                               \
   void* dst = vec->data + pos;                                                \
   void* src = vec->data + pos + 1;                                            \
   int64_t n = ( ( vec->i.count - 1 ) - pos ) * sizeof_c_( ValType );          \
   size_t size;                                                                \
   if ( not int64_to_size_c( n, &size ) ) return false;                        \
                                                                               \
   Release( vec->data[ pos ] );                                                \
                                                                               \
   memmove( dst, src, size );                                                  \
   vec->i.count - 1;                                                           \
                                                                               \
   return true;                                                                \
}

/**************************************/

#define SET_ON_VEC_C_(                                                         \
   FuncSuffix, VecType, ValType, Retain, Release, DoDeref                      \
)                                                                              \
void set_on_##FuncSuffix( VecType* vec, int64_t pos, ValType val )             \
{                                                                              \
   must_exist_c_( vec );                                                       \
   must_be_in_range_c_( 0, pos, vec->i.count-1 );                              \
                                                                               \
   Release( vec->data[ pos ] );                                                \
   Retain( val );                                                              \
   vec->data[ pos ] = DoDeref( val );                                          \
}

/*******************************************************************************
 type
*******************************************************************************/

#define VEC_STRUCT_C_(                                                         \
   VecType, ValType                                                            \
)                                                                              \
struct VecType                                                                 \
{                                                                              \
   ValType* data;                                                              \
   cVecInfo i;                                                                 \
};                                                                             \
typedef struct VecType VecType;



#define OBJ_VEC_DEF_C_(                                                        \
   LibApi, VecType, ObjType, FuncSuffix, Meta                                  \
)                                                                              \
/**************************************/                                       \
struct VecType;                                                                \
typedef struct VecType VecType;                                                \
LibApi extern cMeta const Meta;                                                \
/**************************************/                                       \
LibApi VecType* make_##FuncSuffix( int64_t cap );                              \
LibApi VecType* new_##FuncSuffix( void );                                      \
/**************************************/                                       \
LibApi ObjType* const* data_of_##FuncSuffix( VecType const* vec );             \
LibApi ObjType** var_data_of_##FuncSuffix( VecType* vec );                     \
/**************************************/                                       \
LibApi bool resize_##FuncSuffix( VecType* vec, int64_t size );                 \
/**************************************/                                       \
LibApi cVecInfo const* info_of_##FuncSuffix( VecType const* vec );             \
/**************************************/                                       \
LibApi bool add_to_##FuncSuffix( VecType* vec, ObjType* obj );                 \
LibApi bool add_array_to_##FuncSuffix( VecType* vec, int64_t n, ObjType* const* arr );\
LibApi ObjType* get_from_##FuncSuffix( VecType const* vec, int64_t pos );      \
LibApi bool insert_into_##FuncSuffix( VecType* vec, int64_t pos, ObjType* obj );      \
LibApi bool remove_from_##FuncSuffix( VecType* vec, int64_t pos );             \
LibApi void set_on_##FuncSuffix( VecType* vec, int64_t pos, ObjType* obj );

/**********************************************************/

#define OBJ_VEC_IMPL_C_(                                                       \
   Static, VecType, ObjType, FuncSuffix, Meta                                  \
)                                                                              \
/**************************************/                                       \
VEC_STRUCT_C_( VecType, ObjType* )                                             \
/**************************************/                                       \
static inline void cleanup_##FuncSuffix( void* instance )                      \
{                                                                              \
   VecType* vec = instance;                                                    \
                                                                               \
   if ( vec->data )                                                            \
   {                                                                           \
      for ( int64_t i = 0; i < vec->i.count; ++i )                             \
      {                                                                        \
         release_c( vec->data[ i ] );                                          \
      }                                                                        \
      free( vec->data );                                                       \
   }                                                                           \
}                                                                              \
Static cMeta const Meta = {                                                    \
   .desc = stringify_c_( VecType ),                                            \
   .cleanup = &cleanup_##FuncSuffix                                            \
};                                                                             \
/**************************************/                                       \
Static MAKE_VEC_C_( FuncSuffix, VecType, ObjType*, Meta )                      \
Static NEW_VEC_C_( FuncSuffix, VecType )                                       \
/**************************************/                                       \
Static DATA_OF_VEC_C_( FuncSuffix, VecType, ObjType* )                         \
Static VAR_DATA_OF_VEC_C_( FuncSuffix, VecType, ObjType* )                     \
Static RESIZE_VEC_C_( FuncSuffix, VecType, ObjType* )                          \
Static INFO_OF_VEC_C_( FuncSuffix, VecType )                                   \
/**************************************/                                       \
Static ADD_TO_VEC_C_(                                                          \
   FuncSuffix, VecType, ObjType*, retain_c, do_not_deref_c_                    \
)                                                                              \
Static ADD_ARRAY_TO_VEC_C_(                                                    \
   FuncSuffix, VecType, ObjType*, retain_c                                     \
)                                                                              \
Static GET_FROM_VEC_C_( FuncSuffix, VecType, ObjType*, do_deref_c_ )           \
Static INSERT_INTO_VEC_C_(                                                     \
   FuncSuffix, VecType, ObjType*, retain_c                                     \
)                                                                              \
Static REMOVE_FROM_VEC_C_( FuncSuffix, VecType, ObjType*, release_c )          \
Static SET_ON_VEC_C_(                                                          \
   FuncSuffix, VecType, ObjType*, retain_c, release_c, do_not_deref_c_         \
)

/*******************************************************************************

*******************************************************************************/

#define VAL_VEC_DEF_C_(                                                        \
   LibApi, VecType, ValType, FuncSuffix, Meta                                  \
)                                                                              \
/**************************************/                                       \
struct VecType;                                                                \
typedef struct VecType VecType;                                                \
LibApi extern cMeta const Meta;                                                \
/**************************************/                                       \
LibApi VecType* make_##FuncSuffix( int64_t cap );                              \
LibApi VecType* new_##FuncSuffix();                                            \
/**************************************/                                       \
LibApi ValType const* data_of_##FuncSuffix( VecType const* vec );              \
LibApi ValType* var_data_of_##FuncSuffix( VecType* vec );                      \
/**************************************/                                       \
LibApi bool resize_##FuncSuffix( VecType* vec, int64_t cap );                  \
/**************************************/                                       \
LibApi cVecInfo const* info_of_##FuncSuffix( VecType const* vec );             \
/**************************************/                                       \
LibApi bool add_to_##FuncSuffix( VecType* vec, ValType val );                  \
LibApi bool add_array_to_##FuncSuffix( VecType* vec, int64_t n, ValType const* arr ); \
LibApi ValType const* get_from_##FuncSuffix( VecType const* vec, int64_t pos );\
LibApi ValType* get_var_from_##FuncSuffix( VecType* vec, int64_t pos );        \
LibApi bool insert_into_##FuncSuffix( VecType* vec, int64_t pos, ValType val );\
LibApi bool remove_from_##FuncSuffix( VecType* vec, int64_t pos );             \
LibApi void set_on_##FuncSuffix( VecType* vec, int64_t pos, ValType val );

/**********************************************************/

#define VAL_VEC_IMPL_C_(                                                       \
   Static, VecType, ValType, FuncSuffix, Meta, InDepthCleanup                  \
)                                                                              \
/**************************************/                                       \
VEC_STRUCT_C_( VecType, ValType )                                              \
/**************************************/                                       \
static inline void cleanup_##FuncSuffix( void* instance )                      \
{                                                                              \
   VecType* vec = instance;                                                    \
   InDepthCleanup( vec );                                                      \
                                                                               \
   if ( vec->data )                                                            \
   {                                                                           \
      free( vec->data );                                                       \
   }                                                                           \
}                                                                              \
Static cMeta const Meta = {                                                    \
   .desc = stringify_c_( VecType ),                                            \
   .cleanup = &cleanup_##FuncSuffix                                            \
};                                                                             \
/**************************************/                                       \
Static MAKE_VEC_C_( FuncSuffix, VecType, ValType, Meta )                       \
Static NEW_VEC_C_( FuncSuffix, VecType )                                       \
/**************************************/                                       \
Static DATA_OF_VEC_C_( FuncSuffix, VecType, ValType )                          \
Static VAR_DATA_OF_VEC_C_( FuncSuffix, VecType, ValType )                      \
Static RESIZE_VEC_C_( FuncSuffix, VecType, ValType )                           \
Static INFO_OF_VEC_C_( FuncSuffix, VecType )                                   \
/**************************************/                                       \
Static ADD_TO_VEC_C_(                                                          \
   FuncSuffix, VecType, ValType, do_nothing_c_, do_not_deref_c_                \
)                                                                              \
Static ADD_ARRAY_TO_VEC_C_(                                                    \
   FuncSuffix, VecType, ValType, do_nothing_c_                                 \
)                                                                              \
Static GET_FROM_VEC_C_( FuncSuffix, VecType, ValType const*, do_not_deref_c_ ) \
Static GET_VAR_FROM_VEC_C_( FuncSuffix, VecType, ValType )                     \
Static INSERT_INTO_VEC_C_(                                                     \
   FuncSuffix, VecType, ValType, do_nothing_c_                                 \
)                                                                              \
Static REMOVE_FROM_VEC_C_( FuncSuffix, VecType, ValType, do_nothing_c_ )       \
Static SET_ON_VEC_C_(                                                          \
   FuncSuffix, VecType, ValType, do_nothing_c_, do_nothing_c_, do_not_deref_c_ \
)

/*******************************************************************************
 extra
*******************************************************************************/

#define BUILD_VEC_C_(                                                          \
   FuncSuffix, VecType, ValType, Meta                                          \
)                                                                              \
VecType* build_##FuncSuffix( int64_t cap, int64_t count, ValType* data )       \
{                                                                              \
   must_be_positive_c_( count );                                               \
   must_exist_c_( data );                                                      \
                                                                               \
   cObjectInfo const info = default_object_info_c_( &Meta );                   \
   VecType* result = alloc_object_c_( VecType, &info );                        \
   if ( result == NULL )                                                       \
   {                                                                           \
      return NULL;                                                             \
   }                                                                           \
                                                                               \
   result->data = data;                                                        \
   result->i.cap = cap;                                                        \
   result->i.count = count;                                                    \
                                                                               \
   return result;                                                              \
}

#define SLICE_OF_VEC_C_(                                                       \
   FuncSuffix, VecType, SliceType                                              \
)                                                                              \
SliceType slice_of_##FuncSuffix( VecType const* vec )                          \
{                                                                              \
   must_exist_c_( vec );                                                       \
   return (SliceType){                                                         \
      .s = info_of_##FuncSuffix( vec )->count,                                 \
      .v = data_of_##FuncSuffix( vec )                                         \
   };                                                                          \
}

#define VAR_SLICE_OF_VEC_C_(                                                   \
   FuncSuffix, VecType, SliceType                                              \
)                                                                              \
SliceType var_slice_of_##FuncSuffix( VecType* vec )                            \
{                                                                              \
   must_exist_c_( vec );                                                       \
   return (SliceType){                                                         \
      .s = info_of_##FuncSuffix( vec )->count,                                 \
      .v = var_data_of_##FuncSuffix( vec )                                     \
   };                                                                          \
}

/**********++*******************************************************************
********************************************************************* Functions 
********************************************************************************
 info
*******************************************************************************/

CLINGO_API inline float vec_load_c( cVecInfo const info[static 1] )
{
   must_exist_c_( info );
   double cap = (double)info->cap;
   double count = (double)info->count;
   return float_c_( ( 1.0 / cap ) * count );
}

CLINGO_API inline bool vec_is_empty_c( cVecInfo const info[static 1] )
{
   must_exist_c_( info );
   return info->count == 0;
}

#endif
