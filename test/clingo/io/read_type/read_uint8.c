#include "clingo/io/read_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      char const* str;
      char const* fmt;
      uint8_t exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // general
      t_( "18", "", 18 ),
      t_( "1c", "x", 28 ),
      t_( "F0", "X", 240 ),
      t_( "70", "o", 56 ),
   // boundaries
      t_( "0", "", 0 ),
      t_( "255", "", 255 ),
      t_( "2345", "", 234 ),
      t_( "256", "", 25 ),
   // with leading zeros
      t_( "0046", "", 46 ),

   // ignore other data at the end
      t_( "34test", "", 34 )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cScanner* sca = &cstr_scanner_c_( t.str );

      uint8_t val;
      bool res = read_uint8_c( sca, &val, t.fmt );
      res &= val == t.exp;

      tap_descf_c( res, "test at index %"PRIi64, i );
   }

   return finish_tap_c_();
}
