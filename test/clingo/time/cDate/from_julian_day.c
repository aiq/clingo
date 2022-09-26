#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

TEMP_SLICE_C_(
   test,
   {
      int64_t jd;
      cYmd exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   // http://aa.usno.navy.mil/data/docs/JulianDate.php 12:00:00
   testSlice tests = slice_c_( test,
      t_( 1721424, ymd_c(    1, c_Jan,  1 ) ),
      t_( 1842713, ymd_c(  333, c_Jan, 27 ) ),
      t_( 2299160, ymd_c( 1582, c_Oct,  4 ) ),
      t_( 2299161, ymd_c( 1582, c_Oct, 15 ) ),
      t_( 2415021, ymd_c( 1900, c_Jan,  1 ) ),
      t_( 2440588, ymd_c( 1970, c_Jan,  1 ) ),
      t_( 2447893, ymd_c( 1990, c_Jan,  1 ) ),
      t_( 2451545, ymd_c( 2000, c_Jan,  1 ) ),
      t_( 2453750, ymd_c( 2006, c_Jan, 14 ) ),
      t_( 2455281, ymd_c( 2010, c_Mar, 25 ) ),
      t_( 2456798, ymd_c( 2014, c_May, 20 ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cDate date = from_julian_day_c( t->jd );
      bool res = eq_c( cmp_ymd_c( as_ymd_c( date ), t->exp ) );
      //bool res = eq_date_c( date, t->exp );

      tap_descf_c( res, "%"PRIi64, t->jd );
   }

   return finish_tap_c_();
}
