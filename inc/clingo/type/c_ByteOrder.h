#ifndef CLINGO_LANG_C_BYTE_ORDER_H
#define CLINGO_LANG_C_BYTE_ORDER_H

#include <stdbool.h>
#include <stdint.h>

#include "clingo/apidecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

#define cBYTE_ORDER_                                                           \
   XMAP_C_( c_BigEndian, 0 )                                                   \
   XMAP_C_( c_LittleEndian, 1 )

#define XMAP_C_( N, I ) N = I,
enum c_ByteOrder { cBYTE_ORDER_ };
#undef XMAP_C_

typedef enum c_ByteOrder c_ByteOrder;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 swap
*******************************************************************************/

#define swap_two_bytes_c_( Data )                                              \
(                                                                              \
   ( ((Data) >> 8) & 0x00FF ) |                                                \
   ( ((Data) << 8) & 0xFF00 )                                                  \
)

#define swap_four_bytes_c_( Data )	                                           \
(                                                                              \
   ( ((Data) >> 24) & 0x000000FF ) |                                           \
   ( ((Data) >>  8) & 0x0000FF00 ) |                                           \
   ( ((Data) <<  8) & 0x00FF0000 ) |                                           \
   ( ((Data) << 24) & 0xFF000000 )                                             \
)

#define swap_eight_bytes_c_( Data )	                                           \
(                                                                              \
   ( ((Data) >> 56) & 0x00000000000000FF ) |                                   \
   ( ((Data) >> 40) & 0x000000000000FF00 ) |                                   \
   ( ((Data) >> 24) & 0x0000000000FF0000 ) |                                   \
   ( ((Data) >>  8) & 0x00000000FF000000 ) |                                   \
   ( ((Data) <<  8) & 0x000000FF00000000 ) |                                   \
   ( ((Data) << 24) & 0x0000FF0000000000 ) |                                   \
   ( ((Data) << 40) & 0x00FF000000000000 ) |                                   \
   ( ((Data) << 56) & 0xFF00000000000000 )                                     \
)

/*******************************************************************************
 util
*******************************************************************************/

CLINGO_API inline c_ByteOrder system_order_c()
{
   int16_t word = 0x4321;
   return ( (*(char *)& word) == 0x21 ) ? c_LittleEndian
                                        : c_BigEndian;
}

CLINGO_API inline bool system_order_is_c( c_ByteOrder order )
{
  return system_order_c() == order;
}

CLINGO_API char const* stringify_byte_order_c( c_ByteOrder order );

#endif
