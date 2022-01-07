#include "clingo/type/bool.h"

#include <iso646.h>

#include "clingo/lang/algo.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

SLICE_IMPL_C_(
   bool,             // Type
   cBoolSlice,       // SliceType
   bool_slice_c,     // FuncName
   cVarBoolSlice,    // VarSliceType
   var_bool_slice_c  // VarFuncName
)

CHUNK_IMPL_C_(
   cBoolChunk,       // ChunkType
   cBoolSlice,       // SliceType
   bool_chunk_c,     // FuncName
   cVarBoolChunk,    // VarChunkType
   cVarBoolSlice,    // VarSliceType
   var_bool_chunk_c  // VarFuncName
)

WINDOW_IMPL_C_(
   cBoolWindow,      // WindowType
   cBoolSlice,       // SliceType
   bool_window_c,    // FuncName
   cVarBoolWindow,   // VarWindowType
   cVarBoolSlice,    // VarSliceType
   var_bool_window_c // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_bool_c( bool a, bool b );

/*******************************************************************************
 algo
*******************************************************************************/

bool and_bool_slice_values_c( cBoolSlice slice )
{
   for ( int64_t i = 0; i < slice.s; i++ )
   {
      if ( !slice.v[ i ] )
      {
         return false;
      }
   }

   return true;
}

COUNT_EQ_C_(
   count_eq_bool_c,  // FuncName
   cBoolSlice,       // SliceType
   bool const,       // ValueType
   bool,             // SearchType
   cmp_bool_c,       // CmpFunc
   do_deref_c_       // DoDeref
)

bool or_bool_slice_values_c( cBoolSlice slice )
{
   for ( int64_t i = 0; i < slice.s; i++ )
   {
      if ( slice.v[ i ] )
      {
         return true;
      }
   }

   return false;
}

