#include "clingo/io/read.h"
#include "clingo/lang/expect.h"
#include "clingo/lang/locale.h"
#include "clingo/time/cWeekDate.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      char const* inp;
      char const* fmt;
      cWeekDate exp;
      int errCode;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   set_locale_c( LC_TIME, "C" ); // For every system the same output

   cWeekDate wd = week_date_c( 2014, 7, c_Fri );
   testSlice tests = slice_c_( test,
      t_( "2014-W07-5", "XXXX-WWW-E", wd, cNoError_ ),
      t_( "14W7 Fri", "XXWW EEE", wd, cNoError_ )
   );

   for_each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->inp );

      cWeekDate wd = week_date_c( 1970, 1, c_Mon );
      bool res = read_week_date_c( sca, &wd, t->fmt );
      res &= eq_c( cmp_week_date_c( wd, t->exp ) );

      cRecorder* rec = &recorder_c_( 32 );
      write_week_date_c_( rec, wd );
      tap_descf_c( res, "%s -> %s", t->fmt, turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}
