#include "clingo/lang/expect.h"
#include "clingo/type/int32.h"

int main( void )
{
   init_tap_c_();

   c_ByteOrder sysOrder = system_order_c();
   c_ByteOrder othOrder = system_order_is_c( c_BigEndian ) ? c_LittleEndian
                                                           : c_BigEndian;

   expect_at_c_( swap_int32_to_c( 0x7caf0000, sysOrder ) == 0x7caf0000 );

   expect_at_c_( swap_int32_to_c( 0x7caf0000, othOrder ) == 0x0000af7c );

   return finish_tap_c_();
}
