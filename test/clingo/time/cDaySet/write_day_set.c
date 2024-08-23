#include "clingo/lang/expect.h"
#include "clingo/time/CDaySet.h"

TEMP_SLICE_C_(
   test,
   {
      CDaySet* set;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cDate emFirst = date_c( 2021, 6, 11 );
   cDate emLast = date_c( 2021, 7, 11 );
   CDaySet* ds = target_day_set_c( date_period_c( emFirst, emLast ) );
   // group
   cDate groupFirst = emFirst;
   cDate groupLast = date_c( 2021, 6, 23 );
   set_date_period_on_day_set_c( ds, date_period_c( groupFirst, groupLast ) );
   // last sixteen
   set_many_on_day_set_c_( ds, date_c( 2021, 6, 26 ),
                               date_c( 2021, 6, 27 ),
                               date_c( 2021, 6, 28 ),
                               date_c( 2021, 6, 29 ) );
   // quarter-final
   set_many_on_day_set_c_( ds, date_c( 2021, 7, 2 ), date_c( 2021, 7, 3 ) );
   // semi-final
   set_many_on_day_set_c_( ds, date_c( 2021, 7, 6 ), date_c( 2021, 7, 7 ) );
   // final
   set_on_day_set_c( ds, date_c( 2021, 7, 11 ) );

   testSlice tests = slice_c_( test,
      t_( ds, "zip", "2021-06-11(13i2z4i2z2i2z2i3z+)" ),
      t_( ds, "", "2021-06:  .... .. ....1 11 11111 11 111.. 11 11.\n"
                  "2021-07:    .1 1. .11.. .1 ..... .. ..... .. ..... .\n" )
   );

   each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 1024 );

      bool res = write_day_set_c( rec, t->set, t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_desc_c_( res, "test {s:q} -> \n{rec}", t->fmt, rec );
   }

   release_c( ds );

   return finish_tap_c_();
}
