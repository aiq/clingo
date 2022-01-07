#include "clingo/lang/expect.h"
#include "clingo/type/cByte.h"

int main( void )
{
   init_tap_c_();

   cByte byte = 0xaa; // 1010 1010
   expect_c_( get_byte_bit_c( byte, 0 ) == 1 );
   expect_c_( get_byte_bit_c( byte, 1 ) == 0 );
   expect_c_( get_byte_bit_c( byte, 4 ) == 1 );
   expect_c_( get_byte_bit_c( byte, 7 ) == 0 );

   return finish_tap_c_();
}
