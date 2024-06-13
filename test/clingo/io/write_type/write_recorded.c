#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      cRecorder* src;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cRecorder* hi = &recorder_c_( 128 );
   record_chars_c_( hi, "Hi!" );

   testSlice tests = slice_c_( test,
      t_( hi, "", "Hi!" ),
      t_( hi, "cs/q", "'Hi!'" ),
      t_( hi, "bs", "48 69 21" ),
      t_( hi, "bs///2", "4869 21" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_recorded_c( rec, t->src, t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_c_( res, C_TapDesc, "test with fmt: {s:Q}", t->fmt );
   }

   return finish_tap_c_();
}