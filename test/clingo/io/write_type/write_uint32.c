#include "clingo/lang/expect.h"
#include "clingo/io/write_type.h"

TEMP_SLICE_C_(
   test,
   {
      uint32_t val;
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
      t_( 432109, "", "432109" ),
      t_( 432109, "d", "432109" ),
   // "x"/"X"/"0x"/"0X"
      t_( 432109, "x", "697ed" ),
      t_( 0xa7b7c7d7, "X", "A7B7""C7D7" ),
   // "o"/"0o"
      t_( 432109, "o", "15""13755" ),
   // "b"/"B"/"0b"/"0B"
      t_( 0x15ab88df, "b", "1o1o1""1o1o1o11""1ooo1ooo""11o11111" ),
      t_( 0x15ab88df, "B", "10101""10101011""10001000""11011111" ),
   // sign
      t_( 18, "+", "+18" ),
      t_( 18, "+xq", "'+12'" ),
      t_( 18, "+0xq", "'12'" ), // sign does not work for 0? cases
   // quote
      t_( 18, "dq", "'18'" ),
      t_( 18, "Q", "\"18\"" ),
   // cell
      t_( 18081, "Q(10c.)", "..\"18081\"." )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_uint32_c( rec, t.val, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_c_( res, C_TapDesc, "test at index {i64}", i );
   }

   return finish_tap_c_();
}
