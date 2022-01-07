#include "clingo/container/CBitVec.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      CBitVec* vec;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   CBitVec* vec1 = bit_vec_from_cstr_c( "0000111111"
                                        "0110001111"
                                        "0001" );

   CBitVec* vec2 = bit_vec_from_cstr_c( "0110101010"
                                        "00101" );

   testSlice tests = slice_c_( test,
   // format
      t_( vec1, "","oooo111111 o11ooo1111 ooo1" ),  // "" / "b/80/10"
      t_( vec1, "/c", "oooo111111 o11ooo1111 ooo1 | 24" ),
      t_( vec1, "01/9c/5", "00001 1111 | 9\n"
                           "10110 0011 | 18\n"
                           "11000 1 | 24" ),
      t_( vec1, "/8/0", "oooo1111\n"
                        "11o11ooo\n"
                        "1111ooo1" ),
      t_( vec1, "_I/12c", "____IIIIII _I | 12\n"
                          "I___IIII__ _I | 24" ),
   // zip
      t_( vec1, "zip", "4z6i_2i3z4i3z+" ),
      t_( vec2, "zip", "_2i_+_+_+3z+_+" ),
   // dbg
      t_( vec1, "dbg", "{ .numOfBits=24"
                       ", .numOfBytes=3"
                       ", .bitMask=11111111 }" ),
      t_( vec2, "dbg", "{ .numOfBits=15"
                       ", .numOfBytes=2"
                       ", .bitMask=1111111o }" )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_bit_vec_c( rec, t.vec, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_descf_c( res, "test '%s' at %"PRIi64, t.fmt, i );
   }

   release_all_c_( vec1, vec2 );

   return finish_tap_c_();
}
