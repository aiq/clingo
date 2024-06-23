#include "clingo/lang/expect.h"
#include "clingo/type/cByte.h"

int main( void )
{
   init_tap_c_();

   cByte byte = 0xaa; // 1010 1010

   expect_at_c_( set_byte_bit_c( byte, 0, 0 ) == 0x2a ); // 0010 1010
   expect_at_c_( set_byte_bit_c( byte, 1, 1 ) == 0xea ); // 1110 1010
   expect_at_c_( set_byte_bit_c( byte, 7, 0 ) == 0xaa ); // 1010 1010
   expect_at_c_( set_byte_bit_c( byte, 7, 1 ) == 0xab ); // 1010 1011

   return finish_tap_c_();
}
