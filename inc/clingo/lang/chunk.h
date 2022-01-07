#ifndef CLINGO_LANG_CHUNK_H
#define CLINGO_LANG_CHUNK_H

#include "clingo/lang/slice.h"

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************
 init
*******************************************************************************/

#define INIT_FRONT_CHUNK_C_( FuncSuffix, ChunkType, SliceType )                \
void FuncSuffix( ChunkType chunk[static 1], int64_t s, SliceType slice )       \
{                                                                              \
   must_exist_c_( chunk );                                                     \
   must_be_positive_c_( s );                                                   \
                                                                               \
   chunk->s = min_c_( s, slice.s );                                            \
   chunk->v = slice.v;                                                         \
   chunk->favSize = s;                                                         \
   chunk->slice = slice;                                                       \
}

/**********************************************************/

#define INIT_BACK_CHUNK_C_( FuncName, ChunkType, SliceType )                   \
void FuncName( ChunkType chunk[static 1], int64_t s, SliceType slice )         \
{                                                                              \
   must_exist_c_( chunk );                                                     \
   must_be_positive_c_( s );                                                   \
                                                                               \
   chunk->s = min_c_( s, slice.s );                                            \
   chunk->v = end_c_( slice ) - min_c_( s, slice.s );                          \
   chunk->favSize = s;                                                         \
   chunk->slice = slice;                                                       \
}

/*******************************************************************************
 type
*******************************************************************************/

#define CHUNK_DEF_C_( Type,                                                    \
                      ChunkType, SliceType, FuncSuffix,                        \
                      VarChunkType, VarSliceType, VarFuncSuffix )              \
struct ChunkType                                                               \
{                                                                              \
   int64_t s;                                                                  \
   Type const* v;                                                              \
   int64_t favSize;                                                            \
   SliceType slice;                                                            \
};                                                                             \
typedef struct ChunkType ChunkType;                                            \
                                                                               \
inline INIT_FRONT_CHUNK_C_( init_front_##FuncSuffix, ChunkType, SliceType )    \
inline INIT_BACK_CHUNK_C_( init_back_##FuncSuffix, ChunkType, SliceType )      \
                                                                               \
struct VarChunkType                                                            \
{                                                                              \
   int64_t s;                                                                  \
   Type* v;                                                                    \
   int64_t favSize;                                                            \
   VarSliceType slice;                                                         \
};                                                                             \
                                                                               \
typedef struct VarChunkType VarChunkType;                                      \
                                                                               \
inline INIT_FRONT_CHUNK_C_( init_front_##VarFuncSuffix,                        \
                            VarChunkType,                                      \
                            VarSliceType )                                     \
inline INIT_BACK_CHUNK_C_( init_back_##VarFuncSuffix,                          \
                           VarChunkType,                                       \
                           VarSliceType )

/**********************************************************/

#define CHUNK_IMPL_C_( ChunkType, SliceType, FuncSuffix,                       \
                       VarChunkType, VarSliceType, VarFuncSuffix )             \
extern inline void init_front_##FuncSuffix( ChunkType[static 1],               \
                                            int64_t,                           \
                                            SliceType );                       \
extern inline void init_back_##FuncSuffix( ChunkType[static 1],                \
                                           int64_t,                            \
                                           SliceType );                        \
                                                                               \
extern inline void init_front_##VarFuncSuffix( VarChunkType[static 1],         \
                                               int64_t,                        \
                                               VarSliceType );                 \
extern inline void init_back_##VarFuncSuffix( VarChunkType[static 1],          \
                                              int64_t,                         \
                                              VarSliceType );

/**********************************************************/

#define STATIC_FRONT_CHUNK_C_( Type, ChunkType, SliceType, FuncSuffix )        \
struct ChunkType                                                               \
{                                                                              \
   int64_t s;                                                                  \
   Type* v;                                                                    \
   int64_t favSize;                                                            \
   SliceType slice;                                                            \
};                                                                             \
typedef struct ChunkType ChunkType;                                            \
static INIT_FRONT_CHUNK_C_( init_front_##FuncSuffix, ChunkType, SliceType )

/**********************************************************/

#define STATIC_BACK_CHUNK_C_( Type, ChunkType, SliceType, FuncSuffix )         \
struct ChunkType                                                               \
{                                                                              \
   int64_t s;                                                                  \
   Type* v;                                                                    \
   int64_t favSize;                                                            \
   SliceType slice;                                                            \
};                                                                             \
typedef struct ChunkType ChunkType;                                            \
static INIT_BACK_CHUNK_C_( init_back_##FuncSuffix, ChunkType, SliceType )

/*******************************************************************************
********************************************************************* Functions
*******************************************************************************/

#define exact_chunk_c_( Chunk )                                                \
(                                                                              \
   valid_chunk_c_( Chunk ) and                                                 \
   (Chunk).s == (Chunk).favSize                                                \
)

#define next_chunk_c_( Chunk )                                                 \
{                                                                              \
   int64_t const rest = end_c_( (Chunk).slice ) - end_c_( Chunk );             \
   (Chunk).s = min_c_( (Chunk).favSize, rest );                                \
   (Chunk).v = (Chunk).v + (Chunk).favSize;                                    \
}

#define prev_chunk_c_( Chunk )                                                 \
{                                                                              \
   int64_t const rest = begin_c_( Chunk ) - begin_c_( (Chunk).slice );         \
   (Chunk).s = min_c_( (Chunk).favSize, rest );                                \
   (Chunk).v = (Chunk).v - (Chunk).s;                                          \
}

#define valid_chunk_c_( Chunk )                                                \
(                                                                              \
   points_into_c_( (Chunk).slice, begin_c_( Chunk ) ) and                      \
   points_into_c_( (Chunk).slice, rbegin_c_( Chunk ) )                         \
)

#endif
