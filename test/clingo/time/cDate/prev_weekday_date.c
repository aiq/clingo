#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

TEMP_SLICE_C_(
   test,
   {
      cDate base;
      c_Weekday wd;
      cDate exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cDate date = date_c( 2014, c_Mar, 22 );
   testSlice tests = slice_c_( test,
      t_( date, c_Sat, date_c( 2014, c_Mar, 15 ) ),
      t_( date, c_Mon, date_c( 2014, c_Mar, 17 ) ),
      t_( date, c_Fri, date_c( 2014, c_Mar, 21 ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cDate date = prev_weekday_date_c( t->base, t->wd );
      bool res = eq_date_c( date, t->exp );

      cRecorder* rec = &recorder_c_( 16 );
      write_date_c_( rec, date );
      tap_desc_c( res, turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}
