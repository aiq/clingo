#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"
#include "clingo/lang/locale.h"

TEMP_SLICE_C_(
   test,
   {
      float val;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   set_locale_c( LC_ALL, "C" );

   testSlice tests = slice_c_( test,
   // PI
      t_( 3.14f, "", "3.1400001" ),
      t_( 3.14f, "e", "3.140000e+00" ),
      t_( 3.14f, "X.4", "0X1.91EBP+1" ),
      t_( 3.14f, "+,3q(10r.)", "..'+3,140'" ),
      t_( 3.14f, "dbg", "{ .sign=0, .exponent=80, .mantissa=48f5c3 }" )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_float_c( rec, t.val, t.fmt );
      res &= recorded_is_c( rec, t.exp );

      tap_desc_c_( res, "test: {rec}", rec );
   }

   return finish_tap_c_();
}
