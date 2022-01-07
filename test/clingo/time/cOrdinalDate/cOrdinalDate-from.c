#include "clingo/lang/expect.h"
#include "clingo/time/cOrdinalDate.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      cYmd ymd;
      cOrdinalDate od;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( ymd_c( 2021,  4, 29 ), ordinal_date_c( 2021, 119 ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 32 );
      write_ordinal_date_c_( rec, t->od );
      record_chars_c_( rec, " / " );
      write_ymd_c_( rec, t->ymd );
      tap_note_c( turn_into_cstr_c( rec ) );

      {  //-------------------------------------------- ordinal_date_from_ymd_c
         cOrdinalDate od = ordinal_date_from_ymd_c( t->ymd );

         write_ordinal_date_c_( rec, od );

         bool res = eq_c( cmp_ordinal_date_c( od, t->od ) );
         tap_desc_c( res, turn_into_cstr_c( rec ) );
      }
      {  //-------------------------------------------- ymd_from_ordinal_date_c
         cYmd ymd = ymd_from_ordinal_date_c( t->od );

         write_ymd_c_( rec, ymd );

         bool res = eq_c( cmp_ymd_c( ymd, t->ymd ) );
         tap_desc_c( res, turn_into_cstr_c( rec ) );
      }
   }

   return finish_tap_c_();
}
