#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      uint64_t val;
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
      t_( 7700883377, "", "7700883377" ),
      t_( 7700883377, "d", "7700883377" ),
   // "x"/"X"/"0x"/"0X"
      t_( 98765432123456789, "x", "15e""e2a3""21ce""7d15" ),
      t_( 0x15ee2a321ce7d15, "X", "15E""E2A3""21CE""7D15" ),
   // "o"/"0o"
      t_( 98765432123456789, "o", "5367""05214""41634""76425" ),
   // "b"/"B"/"0b"/"0B"
      t_( 0x8edcba9876543210, "b", "1ooo111o""11o111oo""1o111o1o""1oo11ooo"
                                   "o111o11o""o1o1o1oo""oo11oo1o""ooo1oooo" ),
      t_( 0x8e76543210, "B", "10001110""01110110""01010100""00110010""00010000" ),
   // sign
      t_( 839, "+d", "+839" ),
      t_( 839, "+x", "+347" ),
      t_( 839, "+0x", "347" ), // sign does not work for 0? cases
   // quote
      t_( 0xFFFFFFFFFFFFFFFF, "q", "'18446744073709551615'" ),
      t_( 0xF0E1D2C3B, "xQ", "\"f0e1d2c3b\"" ),
   // cell
      t_( 0xabcdef0123, "xq(6r-)", "'abcde" )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_uint64_c( rec, t.val, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_desc_c_( res, "test at index {i64}", i );
   }

   return finish_tap_c_();
}
