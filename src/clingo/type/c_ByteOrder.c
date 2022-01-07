#include "clingo/type/c_ByteOrder.h"

/*******************************************************************************

*******************************************************************************/

extern inline c_ByteOrder system_order_c();

extern inline bool system_order_is_c( c_ByteOrder order );

char const* stringify_byte_order_c( c_ByteOrder order )
{
   switch ( order )
   {
      #define XMAP_C_( N, I ) case N: return #N;
         cBYTE_ORDER_
      #undef XMAP_C_
   }
}
