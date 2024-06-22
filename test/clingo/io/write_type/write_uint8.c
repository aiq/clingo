#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      uint8_t val;
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
      t_( 18, "", "18" ),
      t_( 18, "d", "18" ),
   // "x"/"X"/"0x"/"0X"
      t_( 28, "x", "1c" ),
      t_( 0, "X", "0" ),
   // "o"/"0o"
      t_( 56, "o", "70" ),
   // "b"/"B"/"0b"/"0B"
      t_( 237, "b", "111o11o1" ),
      t_( 237, "B", "11101101" ),
   // sign
      t_( 18, "+", "+18" ),
      t_( 18, "+xq", "'+12'" ),
      t_( 18, "+0xq", "'12'" ), // sign does not work for 0? cases
   // quote
      t_( 18, "q", "'18'" ),
      t_( 18, "Q", "\"18\"" ),
   // cell
      t_( 78, "+q(10= )", "   '+78'  " )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_uint8_c( rec, t.val, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_c_( res, C_TapDesc, "test at index {i64}", i );
   }

   return finish_tap_c_();
}
