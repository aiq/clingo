#ifndef CLINGO_TYPE_UINT64_H
#define CLINGO_TYPE_UINT64_H

#include <stdint.h>

#include "clingo/apidecl.h"
#include "clingo/lang/slice.h"
#include "clingo/type/c_ByteOrder.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICES_C_(
   uint64_t,   // Type
   cUint64s,   // SliceType
   cVarUint64s // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

#define build_uint64_c_( a, b )                                                \
(                                                                              \
   ( ((uint64_t)(a)) << 32 ) + (b)                                             \
)

CLINGO_API inline int cmp_uint64_c( uint64_t a, uint64_t b )
{
   return ( a < b ) ? -1
                    : ( a == b ) ? 0
                                 : 1;
}

#define uint64_c_( Value )                                                     \
(                                                                              \
   (uint64_t)(Value)                                                           \
)

/*******************************************************************************
 conv
*******************************************************************************/

CLINGO_API inline CONV_C_(
   int64_to_uint64_c,   // FuncName
   int64_t,             // FromType
   uint64_t,            // ToType
   0,                   // MinValue
   INT64_MAX            // MaxValue
)

/*******************************************************************************
 swap
*******************************************************************************/

CLINGO_API inline uint64_t swap_uint64_c( uint64_t val )
{
   return swap_eight_bytes_c_( val );
}
CLINGO_API inline uint64_t swap_uint64_from_c( uint64_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_eight_bytes_c_( val );
}
CLINGO_API inline uint64_t swap_uint64_to_c( uint64_t val, c_ByteOrder order )
{
   return system_order_is_c( order ) ? val
                                     : swap_eight_bytes_c_( val );
}

/*******************************************************************************
 math
*******************************************************************************/

CLINGO_API inline bool is_pow2_uint64_c( uint64_t val )
{
   return val and ( ( val & ( val - 1 ) ) == 0 );
}

CLINGO_API inline uint64_t next_pow2_uint64_c( uint64_t val )
{
   --val;
   val |= val >> 1;
   val |= val >> 2;
   val |= val >> 4;
   val |= val >> 8;
   val |= val >> 16;
   val |= val >> 32;
   ++val;

   return val;
}

CLINGO_API inline uint8_t log2_uint64_c( uint64_t val )
{
   static const uint8_t table[ 64 ] =
   {
      63,  0, 58,  1, 59, 47, 53,  2,
      60, 39, 48, 27, 54, 33, 42,  3,
      61, 51, 37, 40, 49, 18, 28, 20,
      55, 30, 34, 11, 43, 14, 22,  4,
      62, 57, 46, 52, 38, 26, 32, 41,
      50, 36, 17, 19, 29, 10, 13, 21,
      56, 45, 25, 31, 35, 16,  9, 12,
      44, 24, 15,  8, 23,  7,  6,  5
   };

   val |= val >> 1;
   val |= val >> 2;
   val |= val >> 4;
   val |= val >> 8;
   val |= val >> 16;
   val |= val >> 32;
   return table[ ( ( val - ( val >> 1 ) ) * 0x07EDD5E59A4E28C2 ) >> 58 ];
}

/*******************************************************************************
 algo
*******************************************************************************/

CLINGO_API int cmp_uint64s_c( cUint64s a, cUint64s b );

CLINGO_API int64_t count_eq_uint64_c( cUint64s slice, uint64_t val );

CLINGO_API uint64_t const* find_uint64_c( cUint64s slice, uint64_t val );

CLINGO_API uint64_t const* max_uint64_c( cUint64s slice );

CLINGO_API uint64_t const* min_uint64_c( cUint64s slice );

CLINGO_API bool prod_uint64_c( cUint64s slice, uint64_t res[static 1] );

CLINGO_API void qsort_uint64s_c( cVarUint64s slice );

CLINGO_API void reverse_uint64s_c( cVarUint64s slice );

CLINGO_API void rotate_uint64s_c( cVarUint64s slice, int64_t distance );

CLINGO_API bool sum_uint64_c( cUint64s slice, uint64_t res[static 1] );

#endif
