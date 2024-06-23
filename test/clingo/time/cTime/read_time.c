#include "clingo/lang/expect.h"
#include "clingo/time/C_TimeFormats.h"
#include "clingo/time/cTime.h"

TEMP_SLICE_C_(
   test,
   {
      char const* inp;
      char const* fmt;
      cTime exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "2006-01-02T15:04:05Z", C_Rfc3339Time,
          make_time_c( 2006, c_Jan, 2, 15, 4, 5, 0, utc_c() ) ),
      t_( "21.06.12", "YY.MM.DD",
          make_time_c( 2021, c_Jun, 12, 0, 0, 0, 0, utc_c() ) )
   );

   each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->inp );

      cTime time;
      bool res = read_time_c( sca, &time, t->fmt );
      res = eq_time_c( time, t->exp );

      tap_desc_c_( res, "{s}", t->inp );
   }

   return finish_tap_c_();
}
