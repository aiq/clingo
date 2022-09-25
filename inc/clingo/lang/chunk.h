#ifndef CLINGO_LANG_CHUNK_H
#define CLINGO_LANG_CHUNK_H

#include "clingo/lang/slice.h"

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************
 type
*******************************************************************************/

#define CHUNK_C_( Type, SliceType, ChunkType )                                 \
struct ChunkType                                                               \
{                                                                              \
   int64_t s;                                                                  \
   Type* v;                                                                    \
   int64_t fav;                                                                \
   SliceType slice;                                                            \
};                                                                             \
typedef struct ChunkType ChunkType;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

#define back_chunk_c_( Size, Slice )                                           \
{                                                                              \
   .s=min_c_( (Size), (Slice).s ),                                             \
   .v=end_c_( Slice ) - min_c_( (Size), (Slice).s ),                           \
   .fav=(Size),                                                                \
   .slice=(Slice)                                                              \
}

#define front_chunk_c_( Size, Slice )                                          \
{                                                                              \
   .s=min_c_( (Size), (Slice).s ),                                             \
   .v=(Slice).v,                                                               \
   .fav=(Size),                                                                \
   .slice=(Slice)                                                              \
}

/*******************************************************************************
 use
*******************************************************************************/

#define exact_chunk_c_( Chunk )                                                \
(                                                                              \
   valid_chunk_c_( Chunk ) and                                                 \
   (Chunk).s == (Chunk).fav                                                    \
)

#define next_chunk_c_( Chunk )                                                 \
{                                                                              \
   int64_t const rest = end_c_( (Chunk).slice ) - end_c_( Chunk );             \
   (Chunk).s = min_c_( (Chunk).fav, rest );                                    \
   (Chunk).v = (Chunk).v + (Chunk).fav;                                        \
}

#define prev_chunk_c_( Chunk )                                                 \
{                                                                              \
   int64_t const rest = begin_c_( Chunk ) - begin_c_( (Chunk).slice );         \
   (Chunk).s = min_c_( (Chunk).fav, rest );                                    \
   (Chunk).v = (Chunk).v - (Chunk).s;                                          \
}

#define valid_chunk_c_( Chunk )                                                \
(                                                                              \
   points_into_c_( (Chunk).slice, begin_c_( Chunk ) ) and                      \
   points_into_c_( (Chunk).slice, rbegin_c_( Chunk ) )                         \
)

#endif
