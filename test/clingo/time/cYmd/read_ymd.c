#include "clingo/io/read.h"
#include "clingo/lang/expect.h"
#include "clingo/time/cYmd.h"

TEMP_SLICE_C_(
   test,
   {
      char const* inp;
      char const* fmt;
      cYmd exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "20130401", "YYYYMMDD", ymd_c( 2013, 4, 1 ) ),
      t_( "5-7-2001", "D-M-YYYY", ymd_c( 2001, 7, 5 ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->inp );

      cYmd ymd = ymd_c( 1970, 1, 1 );
      bool res = read_ymd_c( sca, &ymd, t->fmt );
      res &= eq_c( cmp_ymd_c( ymd, t->exp ) );

      cRecorder* rec = &recorder_c_( 32 );
      write_ymd_c_( rec, ymd );
      tap_desc_c_( res, "{s} -> {rec}", t->fmt, rec );
   }

   return finish_tap_c_();
}
