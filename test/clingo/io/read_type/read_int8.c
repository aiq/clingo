#include "clingo/io/read_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      char const* str;
      char const* fmt;
      int8_t exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // general
      t_( "22", "", 22 ),
      t_( "1c", "x", 28 ),
      t_( "0", "X", 0 ),
      t_( "-70", "o", -56 ),
   // boundaries
      t_( "-128", "", -128 ),
      t_( "127", "", 127 ),
      t_( "-2345", "", -23 ),
      t_( "128", "", 12 ),
   // with leading zeros
      t_( "-0046", "", -46 ),
   // ignore other data at the end
      t_( "32-blocks", "", 32 )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cScanner* sca = &cstr_scanner_c_( t.str );

      int8_t val;
      bool res = read_int8_c( sca, &val, t.fmt );
      res &= val == t.exp;

      tap_descf_c( res, "test at index %"PRIi64, i );
   }

   return finish_tap_c_();
}
