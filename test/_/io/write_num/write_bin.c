#include "_/io/write_num.h"
#include "clingo/lang/expect.h"
#include "clingo/type/uint16.h"
#include "clingo/type/uint64.h"
#include "clingo/type/uint8.h"

TEMP_SLICE_C_(
   test,
   {
      uint64_t val;
      bool upper;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 0xa1b2c3d4e5f6, true, "10100001""10110010""11000011"
                                "11010100""11100101""11110110" ),
      t_( 0xa1b2c3d4e5f6, false, "1o1oooo1""1o11oo1o""11oooo11"
                                 "11o1o1oo""111oo1o1""1111o11o" ),
      t_( uint8_c_( -1 ), true, "11111111" ),
      t_( uint16_c_( -1 ), true, "11111111""11111111" ),
      t_( uint64_c_( -1 ), true, "11111111""11111111""11111111""11111111"
                                 "11111111""11111111""11111111""11111111" ),
      t_( 12345678901, false, "1o""11o11111""11o111oo""ooo111oo""oo11o1o1" ),
      t_( uint64_c_( -12345678901 ), false,
                     "11111111""11111111""11111111""111111o1"
                     "oo1ooooo""oo1ooo11""111ooo11""11oo1o11" ),
      t_( 0, false, "o" ),
      t_( 0, true, "0" )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cVarChars buf = scalars_c_( 128, char );

      cChars res = as_chars_c( buf );
      res.s = write_bin_c( t.val, t.upper, buf );

      tap_descf_c( chars_is_c( res, t.exp ), "test at index %"PRIi64, i );
   }

   return finish_tap_c_();
}
