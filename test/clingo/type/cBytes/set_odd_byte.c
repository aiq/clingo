#include "clingo/lang/expect.h"
#include "clingo/type/cBytes.h"

#define expect_bytes_( Slice, ... )                                            \
   expect_eq_c_(                                                               \
      cmp_bytes_c(                                                             \
         as_bytes_c( Slice ),                                                  \
         bytes_c( (Slice).s, (cByte[]){ __VA_ARGS__ } )                        \
      )                                                                        \
   )

int main( void )
{
   init_tap_c_();

   // 11110001 11110011 11110101 11110111 11110000
   cVarBytes bytes = slice_c_( cByte, 0xf1, 0xf3, 0xf5, 0xf7, 0xf0 );

   set_odd_byte_c( bytes, 2, 4, 0x44 ); // 01000100
   // 11110001 11110011 11110100 01000111 11110000
   expect_bytes_( bytes, 0xf1, 0xf3, 0xf4, 0x47, 0xf0 );

   set_odd_byte_c( bytes, 0, 0, 0x12 ); // 00010010
   // 00010010 11110011 11110100 01000111 11110000
   expect_bytes_( bytes, 0x12, 0xf3, 0xf4, 0x47, 0xf0 );

   set_odd_byte_c( bytes, 4, 7, 0xff ); // 11111111
   // 00010010 11110011 11110100 01000111 11110001
   expect_bytes_( bytes, 0x12, 0xf3, 0xf4, 0x47, 0xf1 );

   return finish_tap_c_();
}
