#include "clingo/io/read_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      char const* str;
      char const* fmt;
      uint64_t exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // general
      t_( "18", "", 18 ),
      t_( "30df", "x", 12511 ),
      t_( "4E3", "X", 1251 ),
      t_( "7561", "o", 3953 ),
   // boundaries
      t_( "0", "", 0 ),
      t_( "18446744073709551615", "", 18446744073709551615ULL ),
      t_( "18446744073709551616", "", 1844674407370955161ULL ),
   // ignore other data at the end
      t_( "1170343number", "", 1170343 )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cScanner* sca = &cstr_scanner_c_( t.str );

      uint64_t val;
      bool res = read_uint64_c( sca, &val, t.fmt );
      res &= val == t.exp;

      tap_descf_c( res, "test at index %"PRIi64, i );
   }

   return finish_tap_c_();
}
