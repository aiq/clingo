#ifndef CLINGO_CONTAINER_PILE_H
#define CLINGO_CONTAINER_PILE_H

#include "clingo/lang/algo.h"
#include "clingo/lang/math.h"
#include "clingo/lang/mem.h"
#include "clingo/lang/slice.h"

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************
 mem
*******************************************************************************/

#define ALLOC_PILE_C_( FuncName, PileType, Type )                              \
bool FuncName( PileType pile[static 1], int64_t size )                         \
{                                                                              \
   pile->v = alloc_array_c_( size, Type );                                     \
   if ( pile->v == NULL ) return false;                                        \
                                                                               \
   pile->s = 0;                                                                \
   pile->cap = size;                                                           \
                                                                               \
   return true;                                                                \
}

/******************************************************************************/

#define REALLOC_PILE_C_( FuncName, PileType, Type )                            \
bool FuncName( PileType pile[static 1], int64_t size )                         \
{                                                                              \
   void* mem = realloc_array_c_( pile->v, size, Type );                        \
   if ( mem == NULL ) return false;                                            \
                                                                               \
   pile->v = mem;                                                              \
   pile->cap = size;                                                           \
                                                                               \
   return true;                                                                \
}

/*******************************************************************************
 manipulate
*******************************************************************************/

#define INSERT_C_(                                                             \
   FuncName, PileType, Type, InsertType, DoDeref, ReallocFunc                  \
)                                                                              \
bool FuncName( PileType pile[static 1], int64_t pos, InsertType val )          \
                                                                               \
{                                                                              \
   must_be_in_range_c_( 0, pos, pile->s );                                     \
                                                                               \
   if ( pile->s == pile->cap )                                                 \
   {                                                                           \
      int64_t newCap;                                                          \
      if ( not imul64_c( pile->cap, 2, &newCap ) or                            \
           not ReallocFunc( pile, newCap ) )                                   \
      {                                                                        \
         return false;                                                         \
      }                                                                        \
      pile->cap = newCap;                                                      \
   }                                                                           \
                                                                               \
   void* dst = pile->v + pos + 1;                                              \
   void* src = pile->v + pos;                                                  \
   int64_t n = ( pile->s - pos ) * sizeof_c_( Type );                          \
   size_t size;                                                                \
   if ( not int64_to_size_c( n, &size ) ) return false;                        \
                                                                               \
   memmove( dst, src, size );                                                  \
   pile->v[pos] = DoDeref( val );                                              \
   pile->s += 1;                                                               \
                                                                               \
   return true;                                                                \
}

/******************************************************************************/

#define PUT_C_( FuncName, PileType, ParaType, DoDeref, ReallocFunc )           \
bool FuncName( PileType pile[static 1], ParaType val )                         \
{                                                                              \
   if ( pile->s == pile->cap )                                                 \
   {                                                                           \
      if ( pile->cap == 0 )                                                    \
      {                                                                        \
         pile->cap = 4;                                                        \
      }                                                                        \
      int64_t newCap;                                                          \
      if ( not imul64_c( pile->cap, 2, &newCap ) or                            \
           not ReallocFunc( pile, newCap ) )                                   \
      {                                                                        \
         return false;                                                         \
      }                                                                        \
      pile->cap = newCap;                                                      \
   }                                                                           \
   pile->v[ pile->s ] = DoDeref( val );                                        \
   pile->s += 1;                                                               \
   return true;                                                                \
}

/*******************************************************************************
 type
*******************************************************************************/

#define PILE_C_( Type, PileType )                                              \
struct PileType                                                                \
{                                                                              \
   int64_t s;                                                                  \
   Type* v;                                                                    \
   int64_t cap;                                                                \
};                                                                             \
typedef struct PileType PileType;

#define PILE_DEF_C_( Type, PileType, FuncSuffix, ParaType )                    \
PILE_C_( Type, PileType )                                                      \
                                                                               \
bool alloc_pile_of_##FuncSuffix( PileType pile[static 1], int64_t size );      \
bool realloc_pile_of_##FuncSuffix( PileType pile[static 1], int64_t size );    \
bool insert_##FuncSuffix( PileType pile[static 1], int64_t pos, ParaType val ) \
bool put_##FuncSuffix( PileType pile[static 1], ParaType val );

/**********************************************************/

#define PILE_IMPL_C_( Type, PileType, FuncSuffix, ParaType, DoDeref )          \
ALLOC_PILE_C_( alloc_pile_of_##FuncSuffix, PileType, Type )                    \
REALLOC_PILE_C_( realloc_pile_of_##FuncSuffix, PileType, Type )                \
INSERT_C_(                                                                     \
   insert_##FuncSuffix, PileType, Type, ParaType, DoDeref,                     \
   realloc_pile_of_##FuncSuffix                                                \
)                                                                              \
PUT_C_(                                                                        \
   put_##FuncSuffix, PileType, ParaType, DoDeref, realloc_pile_of_##FuncSuffix \
)

/**********************************************************/

#define STATIC_PILE_IMPL_C_(                                                   \
   Attr, Type, PileType, FuncSuffix, ParaType, DoDeref                         \
)                                                                              \
PILE_C_( Type, PileType )                                                      \
                                                                               \
static Attr ALLOC_PILE_C_( alloc_pile_of_##FuncSuffix, PileType, Type )        \
static Attr REALLOC_PILE_C_( realloc_pile_of_##FuncSuffix, PileType, Type )    \
static Attr INSERT_C_(                                                         \
   insert_##FuncSuffix, PileType, Type, ParaType, DoDeref,                     \
   realloc_pile_of_##FuncSuffix                                                \
)                                                                              \
static Attr PUT_C_(                                                            \
   put_##FuncSuffix, PileType, ParaType, DoDeref,                              \
   realloc_pile_of_##FuncSuffix                                                \
)

/*******************************************************************************
********************************************************************* Functions 
********************************************************************************
 init
*******************************************************************************/

#define false_realloc_c_( Pile, Size ) false

#endif