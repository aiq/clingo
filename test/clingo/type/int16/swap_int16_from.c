#include "clingo/lang/expect.h"
#include "clingo/type/int16.h"

int main( void )
{
   init_tap_c_();

   c_ByteOrder sysOrder = system_order_c();
   c_ByteOrder othOrder = system_order_is_c( c_BigEndian ) ? c_LittleEndian
                                                           : c_BigEndian;

   // 0x0001 -> 0x0100
   expect_c_( swap_int16_from_c( 1, othOrder ) == 256);
   expect_c_( swap_int16_from_c( 1, sysOrder ) == 1 );
   // 0x2080 -> 0x8020
   expect_c_( swap_int16_from_c( 0x2080, sysOrder ) == 0x2080 );
   expect_c_( swap_int16_from_c( 0x2080, othOrder ) == -32736 );

   return finish_tap_c_();
}
