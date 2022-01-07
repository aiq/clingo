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

   // ----------------------------------------------------- left shift
   {
      // 00001111 00001111 00001111 00001111 00001111
      cVarBytes bytes = slice_c_( cByte, 0x0f, 0x0f, 0x0f, 0x0f, 0xf );
      shift_bytes_c( bytes, -5, 0 );
      // 11100001 11100001 11100001 11100001 11100000
      expect_bytes_( bytes, 0xe1, 0xe1, 0xe1, 0xe1, 0xe0 );
   }
   {
      // 00000011 10000111 10000111 10000111 10000111
      cVarBytes bytes = slice_c_( cByte, 0x03, 0x87, 0x87, 0x87, 0x87 );
      shift_bytes_c( bytes, -13, 0 );
      // 11110000 11110000 11110000 11100000 00000000
      expect_bytes_( bytes, 0xf0, 0xf0, 0xf0, 0xe0, 0x00 );
   }

   {
      // 00000000 00000000 00000000 00000000 00000001
      cVarBytes bytes = slice_c_( cByte, 0x00, 0x00, 0x00, 0x00, 0x01 );
      shift_bytes_c( bytes, -39, 1 );
      // 11111111 11111111 11111111 11111111 11111111
      expect_bytes_( bytes, 0xff, 0xff, 0xff, 0xff, 0xff );
   }

   // ----------------------------------------------------- right shift
   {
      // 11100001 11100001 11100001 11100001 11100000
      cVarBytes bytes = slice_c_( cByte, 0xe1, 0xe1, 0xe1, 0xe1, 0xe0 );
      shift_bytes_c( bytes, 6, 0 );
      // 00000011 10000111 10000111 10000111 10000111
      expect_bytes_( bytes, 0x03, 0x87, 0x87, 0x87, 0x87 );
   }
   {
      // 11110000 11110000 11110000 11100000 00000000
      cVarBytes bytes = slice_c_( cByte, 0xf0, 0xf0, 0xf0, 0xe0, 0x00 );
      shift_bytes_c( bytes, 16, 0 );
      // 00000000 00000000 11110000 11110000 11110000
      expect_bytes_( bytes, 0x00, 0x00, 0xf0, 0xf0, 0xf0 );
   }
   {
      // 10000000 00000000 00000000 00000000 00000000
      cVarBytes bytes = slice_c_( cByte, 0x80, 0x00, 0x00, 0x00, 0x00 );
      shift_bytes_c( bytes, 39, 1 );
      // 11111111 11111111 11111111 11111111 11111111
      expect_bytes_( bytes, 0xff, 0xff, 0xff, 0xff, 0xff );
   }

   // ----------------------------------------------------- left & right shift
   {
      // 00001111 00001111 00001111 00001111 00001111
      cVarBytes bytes = slice_c_( cByte, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f );

      shift_bytes_c( bytes, -5, 0 );
      // 11100001 11100001 11100001 11100001 11100000
      expect_bytes_( bytes, 0xe1, 0xe1, 0xe1, 0xe1, 0xe0 );

      shift_bytes_c( bytes, 6, 0 );
      // 00000011 10000111 10000111 10000111 10000111
      expect_bytes_( bytes, 0x03, 0x87, 0x87, 0x87, 0x87 );

      shift_bytes_c( bytes, -13, 0 );
      // 11110000 11110000 11110000 11100000 00000000
      expect_bytes_( bytes, 0xf0, 0xf0, 0xf0, 0xe0, 0x00 );

      shift_bytes_c( bytes, 16, 0 );
      // 00000000 00000000 11110000 11110000 11110000
      expect_bytes_( bytes, 0x00, 0x00, 0xf0, 0xf0, 0xf0 );
   }

   return finish_tap_c_();
}
