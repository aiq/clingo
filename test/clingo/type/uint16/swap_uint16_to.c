#include "clingo/lang/expect.h"
#include "clingo/type/uint16.h"

int main( void )
{
   init_tap_c_();

   c_ByteOrder sysOrder = system_order_c();
   c_ByteOrder othOrder = system_order_is_c( c_BigEndian ) ? c_LittleEndian
                                                           : c_BigEndian;

   expect_c_( swap_uint16_to_c( 0x2080, sysOrder ) ==
                                0x2080 );

   expect_c_( swap_uint16_to_c( 0x2080, othOrder ) ==
                                0x8020 );

   return finish_tap_c_();
}
