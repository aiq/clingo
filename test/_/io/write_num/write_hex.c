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
      t_( 0xa1b2c3d4e5f6, false, "a1b2""c3d4""e5f6" ),
      t_( 0xa1b2c3d4e5f6, true, "A1B2""C3D4""E5F6" ),
      t_( uint8_c_( -1 ), true, "FF" ),
      t_( uint16_c_( -1 ), true, "FFFF" ),
      t_( uint64_c_( -1 ), true, "FFFF""FFFF""FFFF""FFFF" ),
      t_( 12345678901, false, "2""dfdc""1c35" ),
      t_( uint64_c_( -12345678901 ), false, "ffff""fffd""2023""e3cb" ),
      t_( 0, true, "0" ),
      t_( 0, false, "0" )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cVarChars buf = scalars_c_( 128, char );

      cChars res = as_chars_c( buf );
      res.s = write_hex_c( t.val, t.upper, buf );

      tap_descf_c( chars_is_c( res, t.exp ), "test at index %"PRIi64, i );
   }

   return finish_tap_c_();
}
