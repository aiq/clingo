#include "_/io/write_num.h"
#include "clingo/lang/expect.h"
#include "clingo/type/uint16.h"
#include "clingo/type/uint64.h"
#include "clingo/type/uint8.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      uint64_t val;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 052, "52" ),
      t_( uint8_c_( -64 ), "300" ),
      t_( uint16_c_( -64 ), "17""7700" ),
      t_( uint64_c_( -64 ), "17""7777""7777""7777""7777""7700" ),
      t_( 12345678901, "1337""6701""6065" ),
      t_( uint64_c_( -12345678901 ), "17""7777""7777""6440""1076""1713" ),
      t_( 0, "0" )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cVarChars buf = scalars_c_( 128, char );

      cChars res = as_chars_c( buf );
      res.s = write_oct_c( t.val, buf );

      tap_descf_c( chars_is_c( res, t.exp ), "test at index %"PRIi64, i );
   }

   return finish_tap_c_();
}
