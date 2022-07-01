#ifndef CLINGO_TYPE_CBYTES_H
#define CLINGO_TYPE_CBYTES_H

#include "clingo/apidecl.h"
#include "clingo/lang/chunk.h"
#include "clingo/lang/slice.h"
#include "clingo/lang/window.h"
#include "clingo/type/cByte.h"
#include "clingo/type/cRange.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

SLICE_DEF_C_(
   cByte,         // Type
   cBytes,        // SliceType
   bytes_c,       // FuncName
   cVarBytes,     // VarSliceType
   var_bytes_c    // VarFuncName
)

CHUNK_DEF_C_(
   cByte,            // Type
   cByteChunk,       // ChunkType
   cBytes,           // SliceType
   byte_chunk_c,     // FuncName
   cVarByteChunk,    // VarChunkType
   cVarBytes,        // VarSliceType
   var_byte_chunk_c  // VarFuncName
)

WINDOW_DEF_C_(
   cByte,            // Type
   cByteWindow,      // WindowType
   cBytes,           // SliceType
   byte_window_c,    // FuncName
   cVarByteWindow,   // VarWindowType
   cVarBytes,        // VarSliceType
   var_byte_window_c // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

#define byte_buffer_c_( Size )                                                 \
(                                                                              \
   (cVarBytes)scalars_c_( (Size), cByte )                                      \
)

/*******************************************************************************
 bit
*******************************************************************************/

CLINGO_API inline cByte get_bytes_bit_c( cBytes slice, int64_t pos )
{
   must_be_in_range_c_( 0, pos, slice.s * 8 );

   return get_byte_bit_c( slice.v[ pos / 8 ], pos % 8 );
}

CLINGO_API inline void set_bytes_bit_c( cVarBytes slice, int64_t pos, cByte bit )
{
   must_be_in_range_c_( 0, pos, slice.s * 8 );

   int64_t const bytePos = pos / 8;
   slice.v[ bytePos ] = set_byte_bit_c( slice.v[ bytePos ], pos % 8, bit );
}

CLINGO_API void set_bytes_bits_c( cVarBytes slice, cRange range, cByte bit );

CLINGO_API void set_odd_byte_c( cVarBytes slice,
                                int64_t pos,
                                int64_t bitOffset,
                                cByte byte );

CLINGO_API
void shift_bytes_bits_c( cVarBytes slice, int64_t offset, cByte fillValue );

CLINGO_API inline void toggle_bytes_bit_c( cVarBytes slice, int64_t pos )
{
   must_be_in_range_c_( 0, pos, slice.s * 8 );

   int64_t const bytePos = pos / 8;
   slice.v[ bytePos ] = toggle_byte_bit_c( slice.v[ bytePos ], pos % 8 );
}

/*******************************************************************************
 shift
*******************************************************************************/

CLINGO_API void shift_bytes_c( cVarBytes slice, int64_t offset );

/*******************************************************************************
 logic
*******************************************************************************/

CLINGO_API inline bool bitand_bytes_c( cBytes a, cBytes b, cVarBytes result )
{
   if ( a.s != b.s or a.s != result.s )
   {
      return false;
   }

   for ( int64_t i = 0; i < a.s; ++i )
   {
      result.v[ i ] = a.v[ i ] bitand b.v[ i ];
   }

   return true;
}

CLINGO_API inline bool bitor_bytes_c( cBytes a, cBytes b, cVarBytes result )
{
   if ( a.s != b.s or a.s != result.s )
   {
      return false;
   }

   for ( int64_t i = 0; i < a.s; ++i )
   {
      result.v[ i ] = a.v[ i ] bitor b.v[ i ];
   }

   return true;
}

CLINGO_API inline bool compl_bytes_c( cBytes slice, cVarBytes result )
{
   if ( slice.s != result.s )
   {
      return false;
   }

   for ( int64_t i = 0; i < slice.s; ++i )
   {
      result.v[ i ] = compl slice.v[ i ];
   }

   return true;
}

CLINGO_API inline bool xor_bytes_c( cBytes a, cBytes b, cVarBytes result )
{
   if ( a.s != b.s or a.s != result.s )
   {
      return false;
   }

   for ( int64_t i = 0; i < a.s; ++i )
   {
      result.v[ i ] = a.v[ i ] xor b.v[ i ];
   }

   return true;
}

/*******************************************************************************
 algo
*******************************************************************************/

CLINGO_API bool bytes_ends_with_c( cBytes slice, cBytes needle );

CLINGO_API bool bytes_starts_with_c( cBytes slice, cBytes needle );

#define cmp_bytes_c_( Slice, ... )                                             \
   cmp_bytes_c( (Slice), ((cBytes)slice_c_( cByte, __VA_ARGS__ )) )
CLINGO_API int cmp_bytes_c( cBytes a, cBytes b );

CLINGO_API int64_t count_eq_byte_c( cBytes slice, cByte val );

CLINGO_API cByte const* find_byte_c( cBytes slice, cByte val );

CLINGO_API int64_t index_of_bytes_c( cBytes slice, cBytes sub );

CLINGO_API int64_t insert_byte_c( cVarBytes slice, int64_t index, cByte b );

CLINGO_API int64_t insert_bytes_c( cVarBytes dst, int64_t index, cBytes src );

#endif