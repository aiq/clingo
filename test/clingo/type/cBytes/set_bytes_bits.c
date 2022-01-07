#include "clingo/lang/expect.h"
#include "clingo/type/cBytes.h"

int main( void )
{
   init_tap_c_();

   cVarBytes slice = slice_c_( cByte, 0x0f, 0xf0 );

   set_bytes_bits_c( slice, closed_range_c_( 5, 9 ), 0 );
   expect_c_( slice.v[0] == 0x08 ); // 0-7    -> 0000 1000
   expect_c_( slice.v[1] == 0x30 ); // 8-15   -> 0011 0000

   set_bytes_bits_c( slice, closed_range_c_( 2, 5 ), 1 );
   expect_c_( slice.v[0] == 0x3c ); // 0-7    -> 0011 1100
   expect_c_( slice.v[1] == 0x30 ); // 8-15   -> 0011 0000

   return finish_tap_c_();
}
