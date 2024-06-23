#include "clingo/lang/expect.h"
#include "clingo/type/cBytes.h"

int main( void )
{
   init_tap_c_();

   cVarBytes slice = slice_c_( cByte, 0x00, 0xff );

   set_bytes_bit_c( slice, 0, 1 );
   set_bytes_bit_c( slice, 2, 1 );
   set_bytes_bit_c( slice, 6, 1 );

   set_bytes_bit_c( slice, 10, 0 );
   set_bytes_bit_c( slice, 13, 0 );

   expect_at_c_( slice.v[0] == 0xa2 ); // 0-7   -> 1010 0010
   expect_at_c_( slice.v[1] == 0xdb ); // 8-15  -> 1101 1011

   return finish_tap_c_();
}
