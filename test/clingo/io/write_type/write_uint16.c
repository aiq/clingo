#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      uint16_t val;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // ""/"d"
      t_( 168, "", "168" ),
      t_( 168, "d", "168" ),
   // "x"/"X"/"0x"/"0X"
      t_( 1968, "x", "7b0" ),
      t_( 12968, "X", "32A8" ),
   // "o"/"0o"
      t_( 12968, "o", "31250" ),
   // "b"/"B"/"0b"/"0B"
      t_( 12968, "b", "11oo1o""1o1o1ooo" ),
      t_( 15968, "B", "111110""01100000" ),
   // sign
      t_( 534, "+d", "+534" ),
      t_( 15900, "+xq", "'+3e1c'" ),
      t_( 15900, "+0xq", "'3e1c'" ), // sign does not work for 0? cases
   // quote
      t_( 4596, "q", "'4596'" ),
      t_( 4596, "Q", "\"4596\"" ),
   // cell
      t_( 136, "dQ(10c-)", "---\"136\"--" )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_uint16_c( rec, t.val, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_descf_c( res, "test at index %"PRIi64, i );
   }

   return finish_tap_c_();
}
