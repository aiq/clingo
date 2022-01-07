#include "clingo/lang/expect.h"
#include "clingo/type/cBytes.h"

int main( void )
{
   init_tap_c_();

   cVarBytes slice = slice_c_( cByte, 0x00, 0xff );

   toggle_bytes_bit_c( slice, 0 );
   toggle_bytes_bit_c( slice, 2 );
   toggle_bytes_bit_c( slice, 6 );

   toggle_bytes_bit_c( slice, 10 );
   toggle_bytes_bit_c( slice, 13 );

   expect_c_( slice.v[ 0 ] == 0xa2 ); // 0-7   -> 1010 0010
   expect_c_( slice.v[ 1 ] == 0xdb ); // 8-15  -> 1101 1011

   return finish_tap_c_();
}
