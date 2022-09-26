#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

TEMP_SLICE_C_(
   test,
   {
      char const* inp;
      char const* fmt;
      cDate exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cDate apr01 = date_c( 2013, c_Apr, 1 );
   testSlice tests = slice_c_( test,
      t_( "20130401", "YYYYMMDD", apr01 ),
      t_( "13-4-1", "YY-M-D", apr01 )
   );

   for_each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->inp );

      cDate d = date_c( 1979, 1, 1 );
      bool res = read_date_c( sca, &d, t->fmt );

      cRecorder* rec = &recorder_c_( 32 );
      write_date_c_( rec, d );
      tap_descf_c( res, "%s -> %s", t->fmt, turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}
