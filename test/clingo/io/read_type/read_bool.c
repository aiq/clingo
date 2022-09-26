#include "clingo/io/read_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      char const* str;
      char const* fmt;
      bool expReturn;
      bool expVal;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // default
      t_( "true", "", true, true ),
      t_( "False", "", true, false ),
      t_( "FALSE", "", true, false ),
      t_( "Yes", "", false, false ),
   // *
      t_( "true", "", true, true ),
      t_( "False", "", true, false ),
      t_( "FALSE", "", true, false ),
      t_( "NO", "", false, false ),
   // l
      t_( "true", "l", true, true ),
      t_( "false", "l", true, false ),
      t_( "True", "l", false, false ),
   // U
      t_( "TRUE", "U", true, true ),
      t_( "FALSE", "U", true, false ),
      t_( "false", "U", false, false ),
   // Cc
      t_( "True", "Cc", true, true ),
      t_( "False", "Cc", true, false ),
      t_( "TRUE", "Cc", false, false )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cScanner* sca = &cstr_scanner_c_( t.str );

      bool val = false;
      bool res = read_bool_c( sca, &val, t.fmt ) == t.expReturn;
      res &= val == t.expVal;

      tap_descf_c( res, "test at index %"PRIi64, i );
   }

   return finish_tap_c_();
}
