#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "", "00 01 02 03 04 05 06 07 08 09 0a 0b "
              "0c 0d 0e 0f 10 11 12 13 14 15 16 17" ),
      t_( "/c", "00 01 02 03 04 05 06 07 08 09 0a 0b "
                "0c 0d 0e 0f 10 11 12 13 14 15 16 17 | 24" ),
      t_( "X/16c/4", "00010203 04050607 08090A0B 0C0D0E0F | 16\n"
                     "10111213 14151617 | 24" ),
      t_( "/20/0", "000102030405060708090a0b0c0d0e0f10111213\n"
                   "14151617" ),
      t_( "//8", "0001020304050607 08090a0b0c0d0e0f 1011121314151617" )
   );

   cBytes slice = slice_c_( cByte,
      0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
      0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_bytes_c( rec, slice, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_c_( res, C_TapDesc, "test at index {i64}", i );
   }

   return finish_tap_c_();
}
