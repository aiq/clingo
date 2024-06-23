#include "clingo/lang/expect.h"
#include "clingo/type/uint64.h"

int main( void )
{
   init_tap_c_();

   c_ByteOrder sysOrder = system_order_c();
   c_ByteOrder othOrder = system_order_is_c( c_BigEndian ) ? c_LittleEndian
                                                           : c_BigEndian;

   expect_at_c_( swap_uint64_to_c( 0x0123456789abcdef, sysOrder ) ==
                                0x0123456789abcdef );

   expect_at_c_( swap_uint64_to_c( 0x0123456789abcdef, othOrder ) ==
                                0xefcdab8967452301 );

   return finish_tap_c_();
}
