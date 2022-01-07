#include "clingo/io/write.h"
#include "clingo/lang/expect.h"
#include "clingo/lang/locale.h"
#include "clingo/time/cWeekDate.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      cWeekDate wd;
      char const* fmt;
      char const* exp;
      int err;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   set_locale_c( LC_TIME, "C" ); // For every system the same output

   //********************************************************************* tests
   cWeekDate wd = week_date_c( 2014, 7, c_Fri );
   testSlice tests = slice_c_( test,
      t_( wd, "XXWW EEE", "14W7 Fri" ),
      t_( wd, "XXXX-WWW-E", "2014-W07-5" ),
      t_( wd, "XX/WW/PPP", "14/W7/PPP" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 32 );

      bool res = write_week_date_c( rec, t->wd, t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_descf_c( res, "test: %s -> %s", t->fmt, t->exp );
   }

   //**************************************************************** withErrors
   testSlice withErrors = slice_c_( test,
      t_( wd, "XX/W", "", c_InvalidWriteFormat )
   );

   for_each_c_( test const*, t, withErrors )
   {
      cRecorder* rec = &recorder_c_( 32 );

      bool res = not write_week_date_c( rec, t->wd, t->fmt );
      res &= ( rec->err == t->err );
      res &= recorded_is_c( rec, t->exp );

      tap_descf_c( res, "test: %s -> %s", t->fmt, t->exp );
   }

   return finish_tap_c_();
}
