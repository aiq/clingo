#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      int64_t val;
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
   // "x", "X"
      t_( 28, "x", "1c" ),
      t_( 0, "0X", "0" ),
      t_( 98765432123456789, "x", "15e""e2a3""21ce""7d15" ),
      t_( -98765432123456789, "X", "-15E""E2A3""21CE""7D15" ),
      t_( -98765432123456789, "0X", "FEA1""1D5C""DE31""82EB" ),
   // "o"
      t_( 56, "o", "70" ),
      t_( 56, "0o", "70" ),
      t_( -98765432123456789, "o", "-5367""05214""41634""76425" ),
      t_( -98765432123456789, "0o", "17""72410""72563""36143""01353" ),
   // "b"/"B"
      t_( 98765432123456789, "b", "1""o1o1111o""111ooo1o""1o1ooo11""oo1oooo1"
                                               "11oo111o""o11111o1""ooo1o1o1" ),
      t_( 98765432123456789, "0b", "1""o1o1111o""111ooo1o""1o1ooo11""oo1oooo1"
                                                "11oo111o""o11111o1""ooo1o1o1" ),
      t_( -98765432123456789, "B", "-1""01011110""11100010""10100011""00100001"
                                                 "11001110""01111101""00010101" ),
      t_( -98765432123456789, "0B", "11111110""10100001""00011101""01011100"
                                    "11011110""00110001""10000010""11101011" ),
   // sign
      t_( 18, "+d", "+18" ),
      t_( 18, "+bq", "'+1oo1o'" ),
      t_( 18, "+0bq", "'1oo1o'" ), // sign does not work for 0? cases
   // quote
      t_( 18, "q", "'18'" ),
      t_( 18, "Q", "\"18\"" ),
   // cell
      t_( 18, "dQ(10c-)","---\"18\"---" )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_int64_c( rec, t.val, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_descf_c( res, "test at index %"PRIi64, i );
   }

   return finish_tap_c_();
}
