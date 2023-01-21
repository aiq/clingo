#ifndef CLINGO_CONTAINER_MAP_H
#define CLINGO_CONTAINER_MAP_H

#include "clingo/apidecl.h"
#include "clingo/lang/algo.h"
#include "clingo/lang/CObject.h"
#include "clingo/lang/func.h"
#include "clingo/type/cRange.h"
#include "clingo/type/float.h"
#include "clingo/type/int64.h"
#include "clingo/type/uint64.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************/

CLINGO_API extern float const C_MaxMapLoad;

struct cMapInfo
{
   int64_t count;
   int64_t size;
   float maxLoad;
};
typedef struct cMapInfo cMapInfo;

struct cMapItr
{
   int64_t _v;
};
typedef struct cMapItr cMapItr;

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************
 create
*******************************************************************************/

#define MAKE_MAP_C_(                                                           \
   FuncSuffix, MapType, RowType, Meta                                          \
)                                                                              \
MapType* make_##FuncSuffix( int64_t size, float maxLoad )                      \
{                                                                              \
   must_be_positive_c_( size );                                                \
                                                                               \
   MapType* result = new_object_c_( MapType, &Meta );                          \
   if ( result == NULL )                                                       \
   {                                                                           \
      return NULL;                                                             \
   }                                                                           \
                                                                               \
   result->i.size = next_pow2_int64_c( size );                                 \
   result->i.count = 0;                                                        \
   result->shift = 64 - log2_uint64_c( uint64_c_( result->i.size ) );          \
   result->i.maxLoad = maxLoad;                                                \
                                                                               \
   result->array = alloc_array_c_( result->i.size, RowType );                  \
   if ( result->array == NULL )                                                \
   {                                                                           \
      release_c( result );                                                     \
      return NULL;                                                             \
   }                                                                           \
                                                                               \
   return result;                                                              \
}

/**************************************/

#define NEW_MAP_C_(                                                            \
   FuncSuffix, MapType                                                         \
)                                                                              \
MapType* new_##FuncSuffix()                                                    \
{                                                                              \
   return make_##FuncSuffix( 64, C_MaxMapLoad );                               \
}

/*******************************************************************************
 manage
*******************************************************************************/

#define INFO_OF_MAP_C_(                                                        \
   FuncSuffix, MapType                                                         \
)                                                                              \
cMapInfo const* info_of_##FuncSuffix( MapType const* map )                     \
{                                                                              \
   must_exist_c_( map );                                                       \
   return &(map->i);                                                           \
}

/**************************************/

#define RESIZE_MAP_C_(                                                         \
   FuncSuffix, MapType, RowType, HashFunc, DoRef                               \
)                                                                              \
bool resize_##FuncSuffix( MapType* map, int64_t size )                         \
{                                                                              \
   must_exist_c_( map );                                                       \
                                                                               \
   int64_t const newSize = next_pow2_int64_c( size );                          \
   {                                                                           \
      float const next = calculate_load_c( newSize, map->i.count );            \
      if ( next > map->i.maxLoad )                                             \
      {                                                                        \
         return false;                                                         \
      }                                                                        \
   }                                                                           \
                                                                               \
   RowType* newArray = alloc_array_c_( newSize, RowType );                     \
   if ( newArray == NULL )                                                     \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
                                                                               \
   int64_t const oldSize = map->i.size;                                        \
   int64_t oldCount = map->i.count;                                            \
   RowType* oldArray = map->array;                                             \
   map->i.size = newSize;                                                      \
   map->i.count = 0;                                                           \
   map->array = newArray;                                                      \
   map->shift = 64 - log2_uint64_c( uint64_c_( map->i.size ) );                \
   for ( int64_t i = 0; i < oldSize; ++i )                                     \
   {                                                                           \
      RowType* row = oldArray + i;                                             \
      if ( row->dist > 0 )                                                     \
      {                                                                        \
         intl_set_on_##FuncSuffix( map, HashFunc( DoRef(row->k) ), row, NULL );\
         --oldCount;                                                           \
         if ( oldCount < 1 )                                                   \
         {                                                                     \
            break;                                                             \
         }                                                                     \
      }                                                                        \
   }                                                                           \
   free( oldArray );                                                           \
   return true;                                                                \
}

/**************************************/

#define SET_MAX_LOAD_OF_MAP_C_(                                                \
   FuncSuffix, MapType                                                         \
)                                                                              \
bool set_max_load_of_##FuncSuffix( MapType* map, float load )                  \
{                                                                              \
   must_exist_c_( map );                                                       \
                                                                               \
   if ( not in_range_c_( 0.1, load, 1.0 ) )                                    \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
                                                                               \
   map->i.maxLoad = load;                                                      \
   return true;                                                                \
}

/*******************************************************************************
 iterate
*******************************************************************************/

#define NEXT_IN_MAP_C_(                                                        \
   FuncSuffix, MapType, RowType, KeyType, DoRefKey, ValType, DoRefVal          \
)                                                                              \
cMapItr next_in_##FuncSuffix( MapType const* map,                              \
                              cMapItr itr,                                     \
                              KeyType const* key[static 1],                    \
                              ValType const* val[static 1] )                   \
{                                                                              \
   must_exist_c_( map );                                                       \
   must_exist_c_( key );                                                       \
   must_exist_c_( val );                                                       \
                                                                               \
   int64_t const start = itr._v < 0 ? 0 : itr._v+1;                            \
   for ( int64_t i = start; i < map->i.size; ++i )                             \
   {                                                                           \
      RowType const* row = map->array + i;                                     \
      if ( row->dist > 0 )                                                     \
      {                                                                        \
         *key = DoRefKey(row->k);                                              \
         *val = DoRefVal(row->v);                                              \
         return (cMapItr){ ._v = i };                                          \
      }                                                                        \
   }                                                                           \
   *key = NULL;                                                                \
   *val = NULL;                                                                \
   return start_map_itr_c();                                                   \
}

#define NEXT_VAR_IN_MAP_C_(                                                    \
   FuncSuffix, MapType, RowType, KeyType, DoRefKey, ValType, DoRefVal          \
)                                                                              \
cMapItr next_var_in_##FuncSuffix( MapType* map,                                \
                                  cMapItr itr,                                 \
                                  KeyType const* key[static 1],                \
                                  ValType* val[static 1] )                     \
{                                                                              \
   must_exist_c_( map );                                                       \
   must_exist_c_( key );                                                       \
   must_exist_c_( val );                                                       \
                                                                               \
   int64_t const start = itr._v < 0 ? 0 : itr._v+1;                            \
   for ( int64_t i = start; i < map->i.size; ++i )                             \
   {                                                                           \
      RowType* row = map->array + i;                                           \
      if ( row->dist > 0 )                                                     \
      {                                                                        \
         *key = DoRefKey(row->k);                                              \
         *val = DoRefVal(row->v);                                              \
         return (cMapItr){ ._v = i };                                          \
      }                                                                        \
   }                                                                           \
   *key = NULL;                                                                \
   *val = NULL;                                                                \
   return start_map_itr_c();                                                   \
}

/*******************************************************************************
 intl
*******************************************************************************/

#define INTL_ERASE_IN_MAP_C_(                                                  \
   FuncSuffix, MapType, RowType                                                \
)                                                                              \
bool intl_erase_in_##FuncSuffix( MapType* map, int64_t index, RowType* oldRow )\
{                                                                              \
   must_exist_c_( map );                                                       \
   if ( not in_range_c_( 0, index, map->i.size - 1 ) )                         \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
                                                                               \
   /* is where something to delete */                                          \
   if ( map->array[index].dist < 1 )                                           \
   {                                                                           \
      return false;                                                            \
   }                                                                           \
                                                                               \
   map->i.count -= 1;                                                          \
   if ( oldRow )                                                               \
   {                                                                           \
      *oldRow = map->array[index];                                             \
   }                                                                           \
   map->array[index] = (RowType){ .dist=0 };                                   \
   for ( int64_t c = 0; c < map->i.size; ++c, ++index )                        \
   {                                                                           \
      int64_t oth = index + 1;                                                 \
      if ( index == map->i.size )                                              \
      {                                                                        \
         index = 0;                                                            \
      }                                                                        \
      if ( oth == map->i.size )                                                \
      {                                                                        \
         oth = 0;                                                              \
      }                                                                        \
      if ( map->array[oth].dist < 1 )                                          \
      {                                                                        \
         return true;                                                          \
      }                                                                        \
      swap_c_( RowType, map->array[index], map->array[oth], xyz );             \
      map->array[index].dist -= 1;                                             \
   }                                                                           \
                                                                               \
   return false; /* something went wrong */                                    \
}

/**************************************/

#define INTL_INDEX_IN_MAP_C_(                                                  \
   FuncSuffix, MapType, RowType, KeyType, CmpFunc, DoRef                       \
)                                                                              \
int64_t intl_index_in_##FuncSuffix( MapType const* map,                        \
                                    uint64_t hash,                             \
                                    KeyType key )                              \
{                                                                              \
   must_exist_c_( map );                                                       \
   /*must_exist_c_( key );*/                                                   \
                                                                               \
   int64_t index = fibonacci_hash_index_c( hash, map->shift );                 \
   int32_t dist = 1;                                                           \
   for ( int64_t i = 0; i < map->i.size; ++i, ++index, ++dist )                \
   {                                                                           \
      if ( index == map->i.size )                                              \
      {                                                                        \
         index = 0;                                                            \
      }                                                                        \
                                                                               \
      RowType* oldRow = map->array + index;                                    \
      if ( oldRow->dist < dist )                                               \
      {                                                                        \
         return -1;                                                            \
      }                                                                        \
      else if ( oldRow->dist == dist ) /* same index */                        \
      {                                                                        \
         if ( eq_c( CmpFunc( DoRef(oldRow->k), DoRef(key) ) ) )                \
         {                                                                     \
            return index;                                                      \
         }                                                                     \
      }                                                                        \
   }                                                                           \
                                                                               \
   return -1;                                                                  \
}

/**************************************/

#define INTL_SET_ON_MAP_C_(                                                    \
   FuncSuffix, MapType, RowType, CmpFunc, DoRef                                \
)                                                                              \
bool intl_set_on_##FuncSuffix( MapType* map,                                   \
                               uint64_t hash,                                  \
                               RowType* row,                                   \
                               RowType* out )                                  \
{                                                                              \
   must_exist_c_( map );                                                       \
   must_exist_c_( row );                                                       \
                                                                               \
   { /* grow if needed */                                                      \
      float const next = calculate_load_c( map->i.size, map->i.count + 1 );    \
      if ( next > map->i.maxLoad )                                             \
      {                                                                        \
         if ( not resize_##FuncSuffix( map, map->i.size + 1 ) )                \
         {                                                                     \
            return false;                                                      \
         }                                                                     \
      }                                                                        \
   }                                                                           \
                                                                               \
   row->dist = 1;                                                              \
   int64_t index = fibonacci_hash_index_c( hash, map->shift );                 \
   for ( int64_t c = 0; c < map->i.size; ++c, ++index )                        \
   {                                                                           \
      if ( index == map->i.size )                                              \
      {                                                                        \
         index = 0;                                                            \
      }                                                                        \
                                                                               \
      RowType* oldRow = map->array + index;                                    \
      if ( oldRow->dist < 1 ) /* empty */                                      \
      {                                                                        \
         *oldRow = *row;                                                       \
         map->i.count += 1;                                                    \
         return true;                                                          \
      }                                                                        \
      else if ( oldRow->dist == row->dist ) /* same index */                   \
      {                                                                        \
         if ( eq_c( CmpFunc( DoRef(oldRow->k), DoRef(row->k) ) ) )             \
         {                                                                     \
            if ( out )                                                         \
            {                                                                  \
               *out = *oldRow;                                                 \
            }                                                                  \
            *oldRow = *row;                                                    \
            return true;                                                       \
         }                                                                     \
      }                                                                        \
      else if ( oldRow->dist < row->dist ) /* has lower dept */                \
      {                                                                        \
         swap_c_( RowType, *oldRow, *row, xyz );                               \
      }                                                                        \
                                                                               \
      row->dist += 1;                                                          \
   }                                                                           \
                                                                               \
   return false;                                                               \
}

/*******************************************************************************

*******************************************************************************/

#define MAP_STRUCTS_C_(                                                        \
   MapType, RowType, KeyType, ValType                                          \
)                                                                              \
struct RowType                                                                 \
{                                                                              \
   int32_t dist;                                                               \
   KeyType k;                                                                  \
   ValType v;                                                                  \
};                                                                             \
typedef struct RowType RowType;                                                \
                                                                               \
struct MapType                                                                 \
{                                                                              \
   RowType* array;                                                             \
   uint8_t shift;                                                              \
   cMapInfo i;                                                                 \
};                                                                             \
typedef struct MapType MapType;


/*******************************************************************************

*******************************************************************************/

#define SHARED_MAP_INTL_DECL_C_(                                               \
   MapType, RowType, KeyType, FuncSuffix                                       \
)                                                                              \
static inline bool                                                             \
intl_erase_in_##FuncSuffix( MapType*, int64_t, RowType* );                     \
static inline int64_t                                                          \
intl_index_in_##FuncSuffix( MapType const*, uint64_t, KeyType );               \
static inline bool                                                             \
intl_set_on_##FuncSuffix( MapType*, uint64_t, RowType*, RowType* );


/*******************************************************************************

*******************************************************************************/

#define OBJ_OBJ_MAP_DEF_C_(                                                    \
   LibApi, MapType, KeyType, ValType, FuncSuffix, Meta                         \
)                                                                              \
/**************************************/                                       \
struct MapType;                                                                \
typedef struct MapType MapType;                                                \
LibApi extern cMeta const Meta;                                                \
/**************************************/                                       \
LibApi MapType* make_##FuncSuffix( int64_t size, float maxLoad );                     \
LibApi MapType* new_##FuncSuffix( void );                                      \
/**************************************/                                       \
LibApi cMapInfo const* info_of_##FuncSuffix( MapType const* map );                    \
LibApi bool resize_##FuncSuffix( MapType* map, int64_t size );                        \
LibApi bool set_max_load_of_##FuncSuffix( MapType* map, float maxLoad );              \
/**************************************/                                       \
LibApi cMapItr next_in_##FuncSuffix( MapType const* map,                              \
                              cMapItr itr,                                     \
                              KeyType const* key[static 1],                    \
                              ValType const* val[static 1] );                  \
LibApi cMapItr next_var_in_##FuncSuffix( MapType* map,                                \
                                  cMapItr itr,                                 \
                                  KeyType const* key[static 1],                \
                                  ValType* val[static 1] );                    \
/**************************************/                                       \
LibApi ValType* get_from_##FuncSuffix( MapType const* map, KeyType const* key );      \
LibApi bool in_##FuncSuffix( MapType const* map, KeyType const* key );                \
LibApi bool remove_from_##FuncSuffix( MapType* map, KeyType const* key );             \
LibApi bool set_on_##FuncSuffix( MapType* map, KeyType* key, ValType* val );

/******************************************************************************/

#define OBJ_OBJ_MAP_IMPL_C_(                                                   \
   Static, MapType, RowType, KeyType, ValType,                                 \
   FuncSuffix, Meta, HashFunc, CmpFunc                                         \
)                                                                              \
/**************************************/                                       \
MAP_STRUCTS_C_( MapType, RowType, KeyType*, ValType* )                         \
/**************************************/                                       \
static inline void cleanup_##FuncSuffix( void* instance )                      \
{                                                                              \
   MapType* map = instance;                                                    \
                                                                               \
   if ( map->array )                                                           \
   {                                                                           \
      for ( int64_t i = 0; i < map->i.size; ++i )                              \
      {                                                                        \
         RowType* row = map->array + i;                                        \
         if ( row->dist >= 1 ) /* filled */                                    \
         {                                                                     \
            release_c( row->k );                                               \
            release_c( row->v );                                               \
         }                                                                     \
      }                                                                        \
      free( map->array );                                                      \
   }                                                                           \
}                                                                              \
Static cMeta const Meta = {                                                    \
   .desc = stringify_c_( MapType ),                                            \
   .cleanup = &cleanup_##FuncSuffix                                            \
};                                                                             \
/**************************************/                                       \
SHARED_MAP_INTL_DECL_C_( MapType, RowType, KeyType const*, FuncSuffix )        \
/**************************************/                                       \
Static MAKE_MAP_C_( FuncSuffix, MapType, RowType, Meta )                       \
Static NEW_MAP_C_( FuncSuffix, MapType )                                       \
/**************************************/                                       \
Static INFO_OF_MAP_C_( FuncSuffix, MapType )                                   \
Static RESIZE_MAP_C_( FuncSuffix, MapType, RowType, HashFunc, do_not_ref_c_ )  \
Static SET_MAX_LOAD_OF_MAP_C_( FuncSuffix, MapType )                           \
/**************************************/                                       \
Static NEXT_IN_MAP_C_(                                                         \
   FuncSuffix, MapType, RowType, KeyType, do_not_ref_c_, ValType, do_not_ref_c_\
)                                                                              \
Static NEXT_VAR_IN_MAP_C_(                                                     \
   FuncSuffix, MapType, RowType, KeyType, do_not_ref_c_, ValType, do_not_ref_c_\
)                                                                              \
/**************************************/                                       \
Static ValType*                                                                \
get_from_##FuncSuffix( MapType const* map, KeyType const* key )                \
{                                                                              \
   must_exist_c_( map );                                                       \
   must_exist_c_( key );                                                       \
                                                                               \
   uint64_t hash = HashFunc( key );                                            \
   int64_t index = intl_index_in_##FuncSuffix( map, hash, key );               \
   return index != -1 ? map->array[index].v : NULL;                            \
}                                                                              \
Static bool in_##FuncSuffix( MapType const* map, KeyType const* key )          \
{                                                                              \
   return get_from_##FuncSuffix( map, key ) != NULL;                           \
}                                                                              \
Static bool remove_from_##FuncSuffix( MapType* map, KeyType const* key )       \
{                                                                              \
   must_exist_c_( map );                                                       \
   must_exist_c_( key );                                                       \
                                                                               \
   uint64_t hash = HashFunc( key );                                            \
   int64_t index = intl_index_in_##FuncSuffix( map, hash, key );               \
   if ( index == -1 ) return false;                                            \
                                                                               \
   RowType out;                                                                \
   bool res = intl_erase_in_##FuncSuffix( map, index, &out );                  \
   if ( res )                                                                  \
   {                                                                           \
      release_c( out.k );                                                      \
      release_c( out.v );                                                      \
   }                                                                           \
   return res;                                                                 \
}                                                                              \
Static bool set_on_##FuncSuffix( MapType* map, KeyType* key, ValType* val )    \
{                                                                              \
   must_exist_c_( map );                                                       \
   must_exist_c_( key );                                                       \
   must_exist_c_( val );                                                       \
                                                                               \
   RowType row = { .k=key, .v=val };                                           \
   RowType out = { .dist=0 };                                                  \
   bool res = intl_set_on_##FuncSuffix( map, HashFunc( key ), &row, &out );    \
   if ( res )                                                                  \
   {                                                                           \
      retain_c( key );                                                         \
      retain_c( val );                                                         \
      if ( out.dist > 0 )                                                      \
      {                                                                        \
         release_c( out.k );                                                   \
         release_c( out.v );                                                   \
      }                                                                        \
   }                                                                           \
   return res;                                                                 \
}                                                                              \
/**************************************/                                       \
static inline INTL_ERASE_IN_MAP_C_( FuncSuffix, MapType, RowType )             \
static inline INTL_INDEX_IN_MAP_C_(                                            \
   FuncSuffix, MapType, RowType, KeyType const*, CmpFunc, do_not_ref_c_        \
)                                                                              \
static inline                                                                  \
INTL_SET_ON_MAP_C_( FuncSuffix, MapType, RowType, CmpFunc, do_not_ref_c_ )

/*******************************************************************************

*******************************************************************************/

#define VAL_VAL_MAP_DEF_C_(                                                    \
   LibApi, MapType, KeyType, ValType, FuncSuffix, Meta                                 \
)                                                                              \
/**************************************/                                       \
struct MapType;                                                                \
typedef struct MapType MapType;                                                \
LibApi extern cMeta const Meta;                                                       \
/**************************************/                                       \
LibApi MapType* make_##FuncSuffix( int64_t size, float maxLoad );                     \
LibApi MapType* new_##FuncSuffix( void );                                      \
/**************************************/                                       \
LibApi cMapInfo const* info_of_##FuncSuffix( MapType const* map );                    \
LibApi bool resize_##FuncSuffix( MapType* map, int64_t size );                        \
LibApi bool set_max_load_of_##FuncSuffix( MapType* map, float maxLoad );              \
/**************************************/                                       \
LibApi cMapItr next_in_##FuncSuffix( MapType const* map,                              \
                              cMapItr itr,                                     \
                              KeyType const* key[static 1],                    \
                              ValType const* val[static 1] );                  \
LibApi cMapItr next_var_in_##FuncSuffix( MapType* map,                                \
                                  cMapItr itr,                                 \
                                  KeyType const* key[static 1],                \
                                  ValType* val[static 1] );                    \
/**************************************/                                       \
LibApi ValType const* get_from_##FuncSuffix( MapType const* map, KeyType key );       \
LibApi ValType* get_var_from_##FuncSuffix( MapType* map, KeyType key );               \
LibApi bool in_##FuncSuffix( MapType const* map, KeyType key );                       \
LibApi bool remove_from_##FuncSuffix( MapType* map, KeyType key );                    \
LibApi bool set_on_##FuncSuffix( MapType* map, KeyType key, ValType val );

/******************************************************************************/

#define VAL_VAL_MAP_IMPL_C_(                                                   \
   Static, MapType, RowType, KeyType, ValType,                                 \
   FuncSuffix, Meta, HashFunc, CmpFunc, DoRef                                  \
)                                                                              \
/**************************************/                                       \
MAP_STRUCTS_C_( MapType, RowType, KeyType, ValType )                           \
/**************************************/                                       \
SHARED_MAP_INTL_DECL_C_( MapType, RowType, KeyType, FuncSuffix )               \
/**************************************/                                       \
static inline void cleanup_##FuncSuffix( void* instance )                      \
{                                                                              \
   MapType* map = instance;                                                    \
                                                                               \
   if ( map->array )                                                           \
   {                                                                           \
      free( map->array );                                                      \
   }                                                                           \
}                                                                              \
Static cMeta const Meta = {                                                    \
   .desc = stringify_c_( MapType ),                                            \
   .cleanup = &cleanup_##FuncSuffix                                            \
};                                                                             \
/**************************************/                                       \
Static MAKE_MAP_C_( FuncSuffix, MapType, RowType, Meta )                       \
Static NEW_MAP_C_( FuncSuffix, MapType )                                       \
/**************************************/                                       \
Static INFO_OF_MAP_C_( FuncSuffix, MapType )                                   \
Static RESIZE_MAP_C_( FuncSuffix, MapType, RowType, HashFunc, DoRef )          \
Static SET_MAX_LOAD_OF_MAP_C_( FuncSuffix, MapType )                           \
/**************************************/                                       \
Static NEXT_IN_MAP_C_(                                                         \
   FuncSuffix, MapType, RowType, KeyType, do_ref_c_, ValType, do_ref_c_        \
)                                                                              \
Static NEXT_VAR_IN_MAP_C_(                                                     \
   FuncSuffix, MapType, RowType, KeyType, do_ref_c_, ValType, do_ref_c_        \
)                                                                              \
/**************************************/                                       \
Static ValType const*                                                          \
get_from_##FuncSuffix( MapType const* map, KeyType key )                       \
{                                                                              \
   must_exist_c_( map );                                                       \
   uint64_t hash = HashFunc( DoRef(key) );                                     \
   int64_t index = intl_index_in_##FuncSuffix( map, hash, key );               \
   return index != -1 ? &(map->array[ index ].v) : NULL;                       \
}                                                                              \
Static ValType* get_var_from_##FuncSuffix( MapType* map, KeyType key )         \
{                                                                              \
   must_exist_c_( map );                                                       \
   uint64_t hash = HashFunc( DoRef(key) );                                     \
   int64_t index = intl_index_in_##FuncSuffix( map, hash, key );               \
   return index != -1 ? &(map->array[ index ].v) : NULL;                       \
}                                                                              \
Static bool in_##FuncSuffix( MapType const* map, KeyType key )                 \
{                                                                              \
   return get_from_##FuncSuffix( map, key ) != NULL;                           \
}                                                                              \
Static bool remove_from_##FuncSuffix( MapType* map, KeyType key )              \
{                                                                              \
   must_exist_c_( map );                                                       \
                                                                               \
   uint64_t hash = HashFunc( DoRef(key) );                                     \
   int64_t index = intl_index_in_##FuncSuffix( map, hash, key );               \
   if ( index == -1 ) return false;                                            \
                                                                               \
   return intl_erase_in_##FuncSuffix( map, index, NULL );                      \
}                                                                              \
Static bool                                                                    \
set_on_##FuncSuffix( MapType* map, KeyType key, ValType val )                  \
{                                                                              \
   must_exist_c_( map );                                                       \
                                                                               \
   RowType row = { .k=key, .v=val };                                           \
   return intl_set_on_##FuncSuffix( map, HashFunc( DoRef(key) ), &row, NULL ); \
}                                                                              \
/**************************************/                                       \
static inline INTL_ERASE_IN_MAP_C_( FuncSuffix, MapType, RowType )             \
static inline                                                                  \
INTL_INDEX_IN_MAP_C_( FuncSuffix, MapType, RowType, KeyType, CmpFunc, DoRef )  \
static inline INTL_SET_ON_MAP_C_( FuncSuffix, MapType, RowType, CmpFunc, DoRef )

/**********++*******************************************************************
********************************************************************* Functions 
********************************************************************************
 util
*******************************************************************************/

CLINGO_API inline float calculate_load_c( int64_t cap, int64_t count )
{
   double fcap = (double)cap;
   double fcount = (double)count;
   return float_c_( ( 1.0 / fcap ) * fcount );
}

CLINGO_API inline int64_t fibonacci_hash_index_c( uint64_t hash, uint8_t shift )
{
   uint64_t u64 = ( 11400714819323198485ull * hash ) >> shift;
   int64_t i64 = 0;
   uint64_to_int64_c( u64, &i64 );
   return i64;
}

CLINGO_API inline uint64_t combine_hashes_c( cUint64Slice hashes )
{
   uint64_t hash = 17;
   for_each_c_( uint64_t const*, oth, hashes )
   {
      hash = hash * 37 + *oth;
   }
   return hash;
}

/*******************************************************************************
 info
*******************************************************************************/

CLINGO_API inline int64_t map_cap_c( cMapInfo const info[static 1] )
{
   must_exist_c_( info );
   return int64_c_( (double)info->size * (double)info->maxLoad );
}

CLINGO_API inline float map_load_c( cMapInfo const info[static 1] )
{
   must_exist_c_( info );
   return calculate_load_c( info->size, info->count );

}

CLINGO_API inline bool map_is_empty_c( cMapInfo const info[static 1] )
{
   must_exist_c_( info );
   return info->count == 0;
}

/*******************************************************************************
 itr
*******************************************************************************/

#define iterate_map_c_( Itr, KeyPop, ValPop, Map, Func )                       \
for (                                                                          \
   cMapItr Itr = Func( Map, start_map_itr_c(), KeyPop, ValPop );               \
   map_itr_is_valid_c( Itr );                                                  \
   Itr = Func( Map, Itr, KeyPop, ValPop )                                      \
)

CLINGO_API inline cMapItr start_map_itr_c()
{
   return (cMapItr){ ._v = -1 };
}

CLINGO_API inline bool map_itr_is_valid_c( cMapItr itr )
{
   return itr._v != -1;
}

#endif
