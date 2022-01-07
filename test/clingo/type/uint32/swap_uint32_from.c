#include "clingo/lang/expect.h"
#include "clingo/type/uint32.h"

int main( void )
{
   init_tap_c_();

   c_ByteOrder sysOrder = system_order_c();
   c_ByteOrder othOrder = system_order_is_c( c_BigEndian ) ? c_LittleEndian
                                                           : c_BigEndian;

   expect_c_( swap_uint32_from_c( 0xb7af0000, sysOrder ) ==
                                  0xb7af0000 );

   expect_c_( swap_uint32_from_c( 0xb7af0000, othOrder ) ==
                                  0x0000afb7 );

   return finish_tap_c_();
}
