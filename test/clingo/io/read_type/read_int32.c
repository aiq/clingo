#include "clingo/io/read_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      char const* str;
      char const* fmt;
      int32_t exp;
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
      t_( "-4E3", "X", -1251 ),
      t_( "7561", "o", 3953 ),
   // boundaries
      t_( "-2147483648", "", -2147483648 ),
      t_( "2147483647", "", 2147483647 ),
      t_( "-2147483649", "", -214748364 ),
   // ignore other data at the end
      t_( "345wxyz", "", 345 )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cScanner* sca = &cstr_scanner_c_( t.str );

      int32_t val;
      bool res = read_int32_c( sca, &val, t.fmt );
      res &= val == t.exp;

      tap_desc_c_( res, "test at index {i64}", i );
   }

   return finish_tap_c_();
}
