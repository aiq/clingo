#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      int8_t val;
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
      t_( 42, "x", "2a" ),
      t_( 42, "0x", "2a" ),
      t_( -42, "X", "-2A" ),
      t_( -42, "0X", "D6" ),
   // "o"/"0o"
      t_( 56, "o", "70" ),
      t_( 56, "0o", "70" ),
      t_( -56, "o", "-70" ),
      t_( -56, "0o", "310" ),
   // "b"/"B"/"0b"/"0B"
      t_( 12, "b", "11oo" ),
      t_( 12, "0b", "11oo" ),
      t_( -12, "B", "-1100" ),
      t_( -12, "0B", "11110100" ),
   // sign
      t_( 18, "+d", "+18" ),
      t_( 18, "+xq", "'+12'" ),
      t_( 18, "+0xq", "'12'" ), // sign does not work for 0? cases
   // quote
      t_( 18, "q", "'18'" ),
      t_( 18, "Q", "\"18\"" ),
   // cell
      t_( 18, "Q(10c-)", "---\"18\"---" )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_int8_c( rec, t.val, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_desc_c_( res, "test at index {i64}", i );
   }

   return finish_tap_c_();
}
