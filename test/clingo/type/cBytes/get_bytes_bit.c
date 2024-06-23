#include "clingo/lang/expect.h"
#include "clingo/type/cBytes.h"

int main( void )
{
   init_tap_c_();

   cBytes slice = slice_c_( cByte, 0xa2, 0xdb );

   // a - 1010
   expect_at_c_( get_bytes_bit_c( slice,  0 ) == 1 );
   expect_at_c_( get_bytes_bit_c( slice,  1 ) == 0 );
   expect_at_c_( get_bytes_bit_c( slice,  2 ) == 1 );
   expect_at_c_( get_bytes_bit_c( slice,  3 ) == 0 );
   // 2 - 0010
   expect_at_c_( get_bytes_bit_c( slice,  4 ) == 0 );
   expect_at_c_( get_bytes_bit_c( slice,  5 ) == 0 );
   expect_at_c_( get_bytes_bit_c( slice,  6 ) == 1 );
   expect_at_c_( get_bytes_bit_c( slice,  7 ) == 0 );
   // d - 1101
   expect_at_c_( get_bytes_bit_c( slice,  8 ) == 1 );
   expect_at_c_( get_bytes_bit_c( slice,  9 ) == 1 );
   expect_at_c_( get_bytes_bit_c( slice, 10 ) == 0 );
   expect_at_c_( get_bytes_bit_c( slice, 11 ) == 1 );
   // b - 1011
   expect_at_c_( get_bytes_bit_c( slice, 12 ) == 1 );
   expect_at_c_( get_bytes_bit_c( slice, 13 ) == 0 );
   expect_at_c_( get_bytes_bit_c( slice, 14 ) == 1 );
   expect_at_c_( get_bytes_bit_c( slice, 15 ) == 1 );

   return finish_tap_c_();
}
