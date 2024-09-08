#include "clingo/lang/expect.h"
#include "clingo/time/cDatePeriod.h"

TEMP_SLICE_C_(
   test,
   {
      cDates inp;
      cDatePeriod exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( (cDates)empty_c_(), null_date_period_c() ),
      t_(
         slice_c_( cDate, date_c( 2020, 11, 30 ) ),
         single_date_period_c( date_c( 2020, 11, 30 ) )
      ),
      t_(
         slice_c_( cDate, date_c( 2020, 11, 30 ),
                          date_c( 2020, 10, 26 ),
                          date_c( 2019, 12, 13 ) ),
         make_date_period_c( 2019, 12, 13, 2020, 11, 30 )
      )
   );
   
   each_c_( test const*, t, tests )
   {
      cDatePeriod period = determine_date_period_c( t->inp );

      bool res = eq_date_period_c( period, t->exp );

      cRecorder* rec = &recorder_c_( 32 );
      {
         write_date_c_( rec, period.first );
         record_chars_c_( rec, " -> " );
         write_date_c_( rec, period.last );
      }
      tap_desc_c_( res, "{rec}", rec );
   }

   return finish_tap_c_();
}
