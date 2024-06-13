#include "clingo/io/read.h"
#include "clingo/lang/expect.h"
#include "clingo/time/cHmsn.h"

TEMP_SLICE_C_(
   test,
   {
      char const* str;
      char const* fmt;
      cHmsn exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "180312", "hhmmss", hmsn_c( 18, 3, 12, 0 ) ),
      t_( "18:03:12.1", "hh:mm:ss.i", hmsn_c( 18, 3, 12, 100000000 ) ),
      t_( "18:03:12.001", "hh:mm:ss.iii", hmsn_c( 18, 3, 12, 1000000 ) ),
      t_( "03:04:15.0 pm", "kk:mm:ss.u ap", hmsn_c( 15, 4, 15, 0 ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->str );

      cHmsn hmsn;
      bool res = read_hmsn_c( sca, &hmsn, t->fmt );
      res &= eq_c( cmp_hmsn_c( hmsn, t->exp ) );

      cRecorder* rec = &recorder_c_( 32 );
      write_hmsn_c_( rec, hmsn );
      tap_desc_c_( res, "{s} -> {rec}", t->fmt, rec );
   }

   return finish_tap_c_();
}
