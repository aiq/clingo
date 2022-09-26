#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      bool val;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // default
      t_( true, "", "true" ),
      t_( false, "", "false" ),
   // lower case
      t_( true, "l", "true" ),
      t_( false, "l", "false" ),
   // upper case
      t_( true, "U", "TRUE" ),
      t_( false, "U", "FALSE" ),
   // camel case
      t_( true, "Cc", "True" ),
      t_( false, "Cc", "False" )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 10 );

      bool res = write_bool_c( rec, t.val, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_descf_c( res, "test at index %"PRIi64, i );
   }

   return finish_tap_c_();
}
