#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      cByte val;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // ""/"x"/"X"
      t_( 0xaF, "", "af" ),
      t_( 0xF, "x", "0f" ),
      t_( 0xaF, "X", "AF" ),
   // "b"/"B"
      t_( 0x7a, "b", "o1111o1o" ),
      t_( 0xa, "B", "00001010" )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 16 );

      bool res = write_byte_c( rec, t.val, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_desc_c_( res, "test at index {i64}", i );
   }

   return finish_tap_c_();
}
