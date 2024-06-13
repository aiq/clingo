#include "clingo/io/read_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      char const* str;
      char const* fmt;
      int64_t exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // general
      t_( "42", "", 42 ),
      t_( "aBcD", "x", 43981 ),
      t_( "-4a3F", "X", -19007 ),
      t_( "7561", "o", 3953 ),
   // boundaries
      t_( "-9223372036854775808", "", int64_c_( -9223372036854775807 - 1 ) ),
      t_( "9223372036854775807", "", int64_c_( 9223372036854775807 ) ),
      t_( "9223372036854775808", "", int64_c_( 922337203685477580 ) ),
   // ignore other data at the end
      t_( "777 oth", "", 777 )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cScanner* sca = &cstr_scanner_c_( t.str );

      int64_t val;
      bool res = read_int64_c( sca, &val, t.fmt );
      res &= val == t.exp;

      
      tap_desc_c_( res, "test at index {i64}", i );
   }

   return finish_tap_c_();
}
