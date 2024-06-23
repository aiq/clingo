#include "clingo/container/CByteVec.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      CByteVec* vec;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   CByteVec* vec = make_byte_vec_c( 2 );
   for ( cByte byte = 0x00; byte < 32; ++byte )
   {
      require_c_( add_to_byte_vec_c( vec, byte ) );
   }

   testSlice tests = slice_c_( test,
      t_( vec, "", "00 01 02 03 04 05 06 07 08 09 0a 0b "
                          "0c 0d 0e 0f 10 11 12 13 14 15 16 17\n"
                          "18 19 1a 1b 1c 1d 1e 1f" ),
      t_( vec, "/c", "00 01 02 03 04 05 06 07 08 09 0a 0b "
                     "0c 0d 0e 0f 10 11 12 13 14 15 16 17 | 24\n"
                     "18 19 1a 1b 1c 1d 1e 1f | 32" ),
      t_( vec, "X/16c/4", "00010203 04050607 08090A0B 0C0D0E0F | 16\n"
                          "10111213 14151617 18191A1B 1C1D1E1F | 32" ),
      t_( vec, "/20/0", "000102030405060708090a0b0c0d0e0f10111213\n"
                        "1415161718191a1b1c1d1e1f" ),
      t_( vec, "//8", "0001020304050607 08090a0b0c0d0e0f 1011121314151617\n"
                          "18191a1b1c1d1e1f" )
   );

   each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 256 );

      bool res = write_byte_vec_c( rec, t->vec, t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_desc_c_( res, "test format: {s:Q}", t->fmt );
   }

   release_c( vec );

   return finish_tap_c_();
}
