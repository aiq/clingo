#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

TEMP_SLICE_C_(
   test,
   {
      int32_t year;
      c_Month month;
      int8_t day;
      int64_t jd;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   // http://aa.usno.navy.mil/data/docs/JulianDate.php 12:00:00
   testSlice tests = slice_c_( test,
      t_(    1, c_Jan,  1, 1721424 ),
      t_(  333, c_Jan, 27, 1842713 ),
      t_( 1582, c_Oct,  4, 2299160 ),
      t_( 1582, c_Oct, 15, 2299161 ),
      t_( 1900, c_Jan,  1, 2415021 ),
      t_( 1970, c_Jan,  1, 2440588 ),
      t_( 1990, c_Jan,  1, 2447893 ),
      t_( 2000, c_Jan,  1, 2451545 ),
      t_( 2006, c_Jan, 14, 2453750 ),
      t_( 2010, c_Mar, 25, 2455281 ),
      t_( 2014, c_May, 20, 2456798 )
   );

   for_each_c_( test const*, t, tests )
   {
      cDate const date = date_c( t->year, t->month, t->day );
      int64_t const jd = as_julian_day_c( date );

      tap_desc_c_( jd == t->jd, "{i64}.{i64}.{i64}", t->year, t->month, t->day );
   }

   return finish_tap_c_();
}
