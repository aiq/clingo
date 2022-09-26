#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

TEMP_SLICE_C_(
   test,
   {
      cYmd ymd;
      cWeekDate wd;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // 1976 - 1977
      t_( ymd_c( 1977, c_Jan,  1 ), week_date_c( 1976, 53, c_Sat ) ),
      t_( ymd_c( 1977, c_Jan,  2 ), week_date_c( 1976, 53, c_Sun ) ),
   // 1977 - 1978
      t_( ymd_c( 1977, c_Dec, 31 ), week_date_c( 1977, 52, c_Sat ) ),
      t_( ymd_c( 1978, c_Jan,  1 ), week_date_c( 1977, 52, c_Sun ) ),
      t_( ymd_c( 1978, c_Jan,  2 ), week_date_c( 1978,  1, c_Mon ) ),
   // 1978 - 1979
      t_( ymd_c( 1978, c_Dec, 31 ), week_date_c( 1978, 52, c_Sun ) ),
      t_( ymd_c( 1979, c_Jan,  1 ), week_date_c( 1979,  1, c_Mon ) ),
   // 1979 - 1980
      t_( ymd_c( 1979, c_Dec, 30 ), week_date_c( 1979, 52, c_Sun ) ),
      t_( ymd_c( 1979, c_Dec, 31 ), week_date_c( 1980,  1, c_Mon ) ),
      t_( ymd_c( 1980, c_Jan,  1 ), week_date_c( 1980,  1, c_Tue ) ),
   // 1980 - 1981
      t_( ymd_c( 1980, c_Dec, 28 ), week_date_c( 1980, 52, c_Sun ) ),
      t_( ymd_c( 1980, c_Dec, 29 ), week_date_c( 1981,  1, c_Mon ) ),
      t_( ymd_c( 1980, c_Dec, 30 ), week_date_c( 1981,  1, c_Tue ) ),
      t_( ymd_c( 1980, c_Dec, 31 ), week_date_c( 1981,  1, c_Wed ) ),
      t_( ymd_c( 1981, c_Jan,  1 ), week_date_c( 1981,  1, c_Thu ) ),
   // 2008
      t_( ymd_c( 2008, c_Sep, 26 ), week_date_c( 2008, 39, c_Fri ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 32 );
      write_week_date_c_( rec, t->wd );
      record_chars_c_( rec, " / " );
      write_ymd_c_( rec, t->ymd );
      tap_note_c( turn_into_cstr_c( rec ) );

      {  //----------------------------------------------- week_date_from_ymd_c
         cWeekDate wd = week_date_from_ymd_c( t->ymd );

         write_week_date_c_( rec, wd );

         bool res = eq_c( cmp_week_date_c( wd, t->wd ) );
         tap_desc_c( res, turn_into_cstr_c( rec ) );
      }
      {  //----------------------------------------------- ymd_from_week_date_c
         cYmd ymd = ymd_from_week_date_c( t->wd );

         write_ymd_c_( rec, ymd );

         bool res = eq_c( cmp_ymd_c( ymd, t->ymd ) );
         tap_desc_c( res, turn_into_cstr_c( rec ) );
      }
   }

   return finish_tap_c_();
}
