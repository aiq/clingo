#ifndef CLINGO_CONTAINER_SET_H
#define CLINGO_CONTAINER_SET_H

#include "clingo/apidecl.h"
#include "clingo/container/map.h"

/*******************************************************************************

*******************************************************************************/

typedef cMapInfo cSetInfo;

typedef cMapItr cSetItr;

/*******************************************************************************
 iterate
*******************************************************************************/

#define NEXT_IN_SET_C_(                                                        \
   FuncSuffix, SetType, RowType, ValType, DoRefVal                             \
)                                                                              \
cSetItr next_in_##FuncSuffix( SetType const* map,                              \
                              cSetItr itr,                                     \
                              ValType const* val[static 1] )                   \
{                                                                              \
   must_exist_c_( map );                                                       \
   must_exist_c_( val );                                                       \
                                                                               \
   int64_t const start = itr._v < 0 ? 0 : itr._v+1;                            \
   for ( int64_t i = start; i < map->i.size; ++i )                             \
   {                                                                           \
      RowType const* row = map->array + i;                                     \
      if ( row->dist > 0 )                                                     \
      {                                                                        \
         *val = DoRefVal(row->v);                                              \
         return (cSetItr){ ._v = i };                                          \
      }                                                                        \
   }                                                                           \
   *val = NULL;                                                                \
   return start_set_itr_c();                                                   \
}

/*******************************************************************************

*******************************************************************************/

#define SET_STRUCTS_C_(                                                        \
   SetType, RowType, ValType                                                   \
)                                                                              \
struct RowType                                                                 \
{                                                                              \
   int32_t dist;                                                               \
   union                                                                       \
   {                                                                           \
      ValType k;                                                               \
      ValType v;                                                               \
   };                                                                          \
};                                                                             \
typedef struct RowType RowType;                                                \
                                                                               \
struct SetType                                                                 \
{                                                                              \
   RowType* array;                                                             \
   uint8_t shift;                                                              \
   cSetInfo i;                                                                 \
};                                                                             \
typedef struct SetType SetType;

/*******************************************************************************

*******************************************************************************/

#define OBJ_SET_DEF_C_(                                                        \
   LibApi, SetType, ObjType, FuncSuffix, Meta                                  \
)                                                                              \
/**************************************/                                       \
struct SetType;                                                                \
typedef struct SetType SetType;                                                \
LibApi extern cMeta const Meta;                                                \
/**************************************/                                       \
LibApi SetType* make_##FuncSuffix( int64_t size, float maxLoad );              \
LibApi SetType* new_##FuncSuffix();                                            \
/**************************************/                                       \
LibApi cSetInfo const* info_of_##FuncSuffix( SetType const* set );             \
LibApi bool resize_##FuncSuffix( SetType* set, int64_t size );                 \
LibApi bool set_max_load_of_##FuncSuffix( SetType* set, float maxLoad );       \
/**************************************/                                       \
LibApi bool in_##FuncSuffix( SetType const* set, ObjType const* obj );         \
LibApi cSetItr next_in_##FuncSuffix( SetType const* set,                       \
                              cSetItr itr,                                     \
                              ObjType const* obj[static 1] );                  \
LibApi bool remove_from_##FuncSuffix( SetType* set, ObjType const* obj );      \
LibApi bool set_on_##FuncSuffix( SetType* set, ObjType* obj );

/**********************************************************/

#define OBJ_SET_IMPL_C_(                                                       \
   Static, SetType, RowType, ObjType, FuncSuffix, Meta, HashFunc, CmpFunc      \
)                                                                              \
/**************************************/                                       \
SET_STRUCTS_C_( SetType, RowType, ObjType* )                                   \
/**************************************/                                       \
static inline void cleanup_##FuncSuffix( void* instance )                      \
{                                                                              \
   SetType* set = instance;                                                    \
                                                                               \
   if ( set->array )                                                           \
   {                                                                           \
      for ( int64_t i = 0; i < set->i.size; ++i )                              \
      {                                                                        \
         RowType* row = set->array + i;                                        \
         if ( row->dist >= 1 ) /* filled */                                    \
         {                                                                     \
            release_c( row->v );                                               \
         }                                                                     \
      }                                                                        \
      free( set->array );                                                      \
   }                                                                           \
}                                                                              \
Static cMeta const Meta = {                                                    \
   .desc = stringify_c_( SetType ),                                            \
   .cleanup = &cleanup_##FuncSuffix                                            \
};                                                                             \
/**************************************/                                       \
SHARED_MAP_INTL_DECL_C_( SetType, RowType, ObjType const*, FuncSuffix )        \
/**************************************/                                       \
Static MAKE_MAP_C_( FuncSuffix, SetType, RowType, Meta )                       \
Static NEW_MAP_C_( FuncSuffix, SetType )                                       \
/**************************************/                                       \
Static INFO_OF_MAP_C_( FuncSuffix, SetType )                                   \
Static RESIZE_MAP_C_( FuncSuffix, SetType, RowType, HashFunc, do_not_ref_c_ )  \
Static SET_MAX_LOAD_OF_MAP_C_( FuncSuffix, SetType )                           \
/**************************************/                                       \
Static bool in_##FuncSuffix( SetType const* set, ObjType const* obj )          \
{                                                                              \
   must_exist_c_( set );                                                       \
   must_exist_c_( obj );                                                       \
   return intl_index_in_##FuncSuffix( set, HashFunc( obj ), obj ) != -1;       \
}                                                                              \
Static NEXT_IN_SET_C_( FuncSuffix, SetType, RowType, ObjType, do_not_ref_c_ )  \
Static bool remove_from_##FuncSuffix( SetType* set, ObjType const* obj )       \
{                                                                              \
   must_exist_c_( set );                                                       \
   must_exist_c_( obj );                                                       \
                                                                               \
   uint64_t hash = HashFunc( obj );                                            \
   int64_t index = intl_index_in_##FuncSuffix( set, hash, obj );               \
   if ( index == -1 ) return false;                                            \
                                                                               \
   RowType out;                                                                \
   bool res = intl_erase_in_##FuncSuffix( set, index, &out );                  \
   if ( res )                                                                  \
   {                                                                           \
      release_c( out.v );                                                      \
   }                                                                           \
   return res;                                                                 \
}                                                                              \
Static bool set_on_##FuncSuffix( SetType* set, ObjType* obj )                  \
{                                                                              \
   must_exist_c_( set );                                                       \
   must_exist_c_( obj );                                                       \
                                                                               \
   RowType row = { .v=obj };                                                   \
   RowType out = { .dist=0 };                                                  \
   bool res = intl_set_on_##FuncSuffix( set, HashFunc( obj ), &row, &out );    \
   if ( res )                                                                  \
   {                                                                           \
      release_c( obj );                                                        \
   }                                                                           \
   return res;                                                                 \
}                                                                              \
/**************************************/                                       \
static inline INTL_ERASE_IN_MAP_C_( FuncSuffix, SetType, RowType )             \
static inline INTL_INDEX_IN_MAP_C_(                                            \
   FuncSuffix, SetType, RowType, ObjType const*, CmpFunc, do_not_ref_c_        \
)                                                                              \
static inline                                                                  \
INTL_SET_ON_MAP_C_( FuncSuffix, SetType, RowType, CmpFunc, do_not_ref_c_ )

/*******************************************************************************

*******************************************************************************/

#define VAL_SET_DEF_C_(                                                        \
   LibApi, SetType, ValType, FuncSuffix, Meta                                  \
)                                                                              \
/**************************************/                                       \
struct SetType;                                                                \
typedef struct SetType SetType;                                                \
LibApi extern cMeta const Meta;                                                \
/**************************************/                                       \
LibApi SetType* make_##FuncSuffix( int64_t size, float maxLoad );              \
LibApi SetType* new_##FuncSuffix();                                            \
/**************************************/                                       \
LibApi cSetInfo const* info_of_##FuncSuffx( SetType const* set );              \
LibApi bool resize_##FuncSuffix( SetType* set, int64_t size );                 \
LibApi bool set_max_load_of_##FuncSuffix( SetType* set, float maxLoad );       \
/**************************************/                                       \
LibApi bool in_##FuncSuffix( SetType const* set, ValType val );                \
LibApi cSetItr next_in_##FuncSuffix( SetType const* set,                       \
                              cSetItr itr,                                     \
                              ValType const* val[static 1] );                  \
LibApi bool remove_from_##FuncSuffix( SetType* set, ValType val );             \
LibApi bool set_on_##FuncSuffix( SetType* set, ValType val );

/**********************************************************/

#define VAL_SET_IMPL_C_(                                                       \
   Static, SetType, RowType, ValType,                                          \
   FuncSuffix, Meta, HashFunc, CmpFunc, DoRef                                  \
)                                                                              \
/**************************************/                                       \
SET_STRUCTS_C_( SetType, RowType, ValType )                                    \
/**************************************/                                       \
static inline void cleanup_##FuncSuffix( void* instance )                      \
{                                                                              \
   SetType* set = instance;                                                    \
                                                                               \
   if ( set->array )                                                           \
   {                                                                           \
      free( set->array );                                                      \
   }                                                                           \
}                                                                              \
Static cMeta const Meta = {                                                    \
   .desc = stringify_c_( SetType ),                                            \
   .cleanup = &cleanup_##FuncSuffix                                            \
};                                                                             \
/**************************************/                                       \
SHARED_MAP_INTL_DECL_C_( SetType, RowType, ValType, FuncSuffix )               \
/**************************************/                                       \
Static MAKE_MAP_C_( FuncSuffix, SetType, RowType, Meta )                       \
Static NEW_MAP_C_( FuncSuffix, SetType )                                       \
/**************************************/                                       \
Static INFO_OF_MAP_C_( FuncSuffix, SetType )                                   \
Static RESIZE_MAP_C_( FuncSuffix, SetType, RowType, HashFunc, DoRef )          \
Static SET_MAX_LOAD_OF_MAP_C_( FuncSuffix, SetType )                           \
/**************************************/                                       \
Static bool in_##FuncSuffix( SetType const* set, ValType val )                 \
{                                                                              \
   must_exist_c_( set );                                                       \
   return intl_index_in_##FuncSuffix( set, HashFunc( DoRef(val) ), val ) != -1;\
}                                                                              \
Static NEXT_IN_SET_C_( FuncSuffix, SetType, RowType, ValType, do_ref_c_ )      \
Static bool remove_from_##FuncSuffix( SetType* set, ValType val )              \
{                                                                              \
   must_exist_c_( set );                                                       \
                                                                               \
   uint64_t hash = HashFunc( DoRef(val) );                                     \
   int64_t index = intl_index_in_##FuncSuffix( set, hash, val );               \
   if ( index == -1 ) return false;                                            \
                                                                               \
   return intl_erase_in_##FuncSuffix( set, index, NULL );                      \
}                                                                              \
Static bool set_on_##FuncSuffix( SetType* set, ValType val )                   \
{                                                                              \
   must_exist_c_( set );                                                       \
                                                                               \
   RowType row = { .v=val };                                                   \
   return intl_set_on_##FuncSuffix( set, HashFunc( DoRef(val) ), &row, NULL ); \
}                                                                              \
/**************************************/                                       \
static inline INTL_ERASE_IN_MAP_C_( FuncSuffix, SetType, RowType )             \
static inline INTL_INDEX_IN_MAP_C_(                                            \
   FuncSuffix, SetType, RowType, ValType, CmpFunc, DoRef                       \
)                                                                              \
static inline INTL_SET_ON_MAP_C_( FuncSuffix, SetType, RowType, CmpFunc, DoRef )

/*******************************************************************************
 info
*******************************************************************************/

CLINGO_API inline int64_t set_cap_c( cSetInfo const info[static 1] )
{
   must_exist_c_( info );
   return int64_c_( (double)info->size * (double)info->maxLoad );
}

CLINGO_API inline float set_load_c( cSetInfo const info[static 1] )
{
   must_exist_c_( info );
   return calculate_load_c( info->size, info->count );

}

CLINGO_API inline bool set_is_empty_c( cSetInfo const info[static 1] )
{
   must_exist_c_( info );
   return info->count == 0;
}

/*******************************************************************************
 itr
*******************************************************************************/

#define iterate_set_c_( Itr, ValPtr, Map, Func )                               \
for (                                                                          \
   cSetItr Itr = Func( Map, start_map_itr_c(), &ValPtr );                      \
   map_itr_is_valid_c( Itr );                                                  \
   Itr = Func( Map, Itr, &ValPtr )                                             \
)

CLINGO_API inline cSetItr start_set_itr_c()
{
   return (cSetItr){ ._v = -1 };
}

CLINGO_API inline bool set_itr_is_valid_c( cSetItr itr )
{
   return itr._v != -1;
}

#endif
