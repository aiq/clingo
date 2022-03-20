#include "clingo/io/read.h"
#include "clingo/lang/expect.h"
#include "clingo/time/cOrdinalDate.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      char const* inp;
      char const* fmt;
      cOrdinalDate exp;
      int err;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   //********************************************************************* tests
   testSlice tests = slice_c_( test,
      t_( "2014-023", "YYYY-CCC", ordinal_date_c( 2014,  23 ), cNoError_ ),
      t_( "14/23", "YY/C", ordinal_date_c( 2014, 23 ), cNoError_ ),
      t_( "2014-DDD.1", "YYYY-DDD.C", ordinal_date_c( 2014, 1 ), cNoError_ )
   );

   for_each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->inp );

      cOrdinalDate od = ordinal_date_c( 1970, 1 );
      bool res = read_ordinal_date_c( sca, &od, t->fmt );
      res &= eq_c( cmp_ordinal_date_c( od, t->exp ) );

      cRecorder* rec = &recorder_c_( 32 );
      write_ordinal_date_c_( rec, od );
      tap_descf_c( res, "%s -> %s", t->fmt, turn_into_cstr_c( rec ) );
   }

   //**************************************************************** withErrors
   testSlice withErrors = slice_c_( test,
      t_( "", "YYYY-CC", ordinal_date_c( 1970, 1 ), c_NotAbleToReadValue )
   );

   for_each_c_( test const*, t, withErrors )
   {
      cScanner* sca = &cstr_scanner_c_( t->inp );

      cOrdinalDate od = ordinal_date_c( 1970, 1 );
      bool res = not read_ordinal_date_c( sca, &od, t->fmt );
      res &= ( sca->err == t->err );
      res &= eq_c( cmp_ordinal_date_c( od, t->exp ) );

      cRecorder* rec = &recorder_c_( 32 );
      write_ordinal_date_c_( rec, od );
      tap_descf_c( res, "%s -> %s", t->fmt, turn_into_cstr_c( rec ) );
   }
   return finish_tap_c_();
}
