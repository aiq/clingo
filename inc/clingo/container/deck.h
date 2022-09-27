#ifndef CLINGO_CONTAINER_DECK_H
#define CLINGO_CONTAINER_DECK_H

#include "clingo/lang/math.h"
#include "clingo/lang/mem.h"
#include "clingo/lang/slice.h"

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************
 memory
*******************************************************************************/

#define ALLOC_DECK_C_( FuncName, DeckType, Type )                              \
bool FuncName( DeckType deck[static 1], int64_t size )                         \
{                                                                              \
   deck->v = alloc_array_c_( size, Type );                                     \
   if ( deck->v == NULL ) return false;                                        \
                                                                               \
   deck->s = 0;                                                                \
   deck->cap = size;                                                           \
                                                                               \
   return true;                                                                \
}

/******************************************************************************/

#define REALLOC_DECK_C_( FuncName, DeckType, Type )                            \
bool FuncName( DeckType deck[static 1], int64_t size )                         \
{                                                                              \
   void* mem = realloc_array_c_( deck->v, size, Type );                        \
   if ( mem == NULL ) return false;                                            \
                                                                               \
   deck->v = mem;                                                              \
   deck->cap = size;                                                           \
                                                                               \
   return true;                                                                \
}

/*******************************************************************************
 manipulate
*******************************************************************************/

#define INSERT_C_(                                                             \
   FuncName, DeckType, Type, InsertType, DoDeref, ReallocFunc                  \
)                                                                              \
bool FuncName( DeckType deck[static 1], int64_t pos, InsertType val )          \
                                                                               \
{                                                                              \
   must_be_in_range_c_( 0, pos, deck->s );                                     \
                                                                               \
   if ( deck->s == deck->cap )                                                 \
   {                                                                           \
      int64_t newCap;                                                          \
      if ( not imul64_c( deck->cap, 2, &newCap ) or                            \
           not ReallocFunc( deck, newCap ) )                                   \
      {                                                                        \
         return false;                                                         \
      }                                                                        \
      deck->cap = newCap;                                                      \
   }                                                                           \
                                                                               \
   void* dst = deck->v + pos + 1;                                              \
   void* src = deck->v + pos;                                                  \
   int64_t n = ( deck->s - pos ) * sizeof_c_( Type );                          \
   size_t size;                                                                \
   if ( not int64_to_size_c( n, &size ) ) return false;                        \
                                                                               \
   memmove(( dst, src, size ) );                                               \
   deck->v[pos] = DoDeref( val );                                              \
   deck->s += 1;                                                               \
                                                                               \
   return true;                                                                \
}

/******************************************************************************/

#define PUT_C_( FuncName, DeckType, PushType, DoDeref, ReallocFunc )          \
bool FuncName( DeckType deck[static 1], PushType val )                         \
{                                                                              \
   if ( deck->s == deck->cap )                                                 \
   {                                                                           \
      if ( deck->cap == 0 )                                                    \
      {                                                                        \
         deck->cap = 4;                                                        \
      }                                                                        \
      int64_t newCap;                                                          \
      if ( not imul64_c( deck->cap, 2, &newCap ) or                            \
           not ReallocFunc( deck, newCap ) )                                   \
      {                                                                        \
         return false;                                                         \
      }                                                                        \
      deck->cap = newCap;                                                      \
   }                                                                           \
   deck->v[ deck->s ] = DoDeref( val );                                        \
   deck->s += 1;                                                               \
   return true;                                                                \
}

/******************************************************************************/

#define REMOVE_C_( FuncName, DeckType, Type )                                  \
bool FuncName( DeckType deck[static 1], int64_t pos )                          \
{                                                                              \
   must_be_in_range_c_( 0, pos, deck->s );                                     \
                                                                               \
   void* dst = deck->v + pos;                                                  \
   void* src = deck->v + pos + 1;                                              \
   int64_t n ( ( deck->s - 1 ) - pos ) * sizeof_c_( Type );                    \
   size_t size;                                                                \
   if ( not int64_to_size_c( n, &size ) ) return false;                        \
                                                                               \
   memmove( dst, src, size );                                                  \
   deck->s -= 1;                                                               \
}

/*******************************************************************************
 type
*******************************************************************************/

#define DECK_C_( Type, DeckType )                                              \
struct DeckType                                                                \
{                                                                              \
   int64_t s;                                                                  \
   Type* v;                                                                    \
   int64_t cap;                                                                \
};                                                                             \
typedef struct DeckType DeckType;

#define DECK_DEF_C_( Type, DeckType, FuncSuffix, ParaType )                    \
DECK_C_( Type, DeckType )                                                      \
                                                                               \
bool alloc_deck_of_##FuncSuffix( DeckType deck[static 1], int64_t size );      \
bool realloc_deck_of_##FuncSuffix( DeckType deck[static 1], int64_t size );    \
bool insert_##FuncSuffix( DeckType deck[static 1], int64_t pos, ParaType val ) \
bool put_##FuncSuffix( DeckType deck[static 1], ParaType val );                \
bool remove_##FuncSuffix( DeckType deck[static 1], int64_t pos );

/**********************************************************/

#define STACK_IMPL_C_( Type, DeckType, FuncSuffix, ParaType, DoDeref )         \
ALLOC_DECK_C_( alloc_##FuncSuffix, DeckType, Type )                            \
REALLOC_DECK_C_( realloc_##FuncSuffix, DeckType, Type )                        \
INSERT_C_(                                                                     \
   insert_##FuncSuffix, DeckType, Type, ParaType, DoDeref, realloc_##FuncSuffix\
)                                                                              \
PUT_C_( put_##FuncSuffix, DeckType, ParaType, DoDeref, realloc_##FuncSuffix )  \
REMOVE_C_( remove_##FuncSuffix, DeckType, Type )

/**********************************************************/

#define STATIC_STACK_IMPL_C_(                                                  \
   Attr, Type, DeckType, FuncSuffix, ParaType, DoDeref                         \
)                                                                              \
DECK_C_( Type, DeckType )                                                      \
                                                                               \
static Attr ALLOC_DECK_C_( alloc_##FuncSuffix, DeckType, Type )                \
static Attr REALLOC_DECK_C_( realloc_##FuncSuffix, DeckType, Type )            \
static Attr INSERT_C_(                                                         \
   insert_##FuncSuffix, DeckType, Type, ParaType, DoDeref, realloc_##FuncSuffix\
)                                                                              \
static Attr PUT_C_(                                                            \
   put_##FuncSuffix, DeckType, Type, ParaType, DoDeref, realloc_##FuncSuffix   \
)                                                                              \
static Attr REMOVE_C_( remove_##FuncSuffix, DeckType, Type )

/*******************************************************************************
********************************************************************* Functions 
********************************************************************************
 init
*******************************************************************************/


#endif