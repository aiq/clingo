#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   expect_eq_c_( cmp_date_c( local_date_c(), local_date_c() ) );

   {
      cDate d2014_03_03 = date_c( 2014, c_Mar, 3 );
      cDate d2014_03_04 = date_c( 2014, c_Mar, 4 );
      expect_lt_c_( cmp_date_c( d2014_03_03, d2014_03_04 ) );
   }

   {
      cDate d2014_03_10 = date_c( 2014, c_Mar, 10 );
      cDate d2014_03_09 = date_c( 2014, c_Mar, 9 );
      expect_gt_c_( cmp_date_c( d2014_03_10, d2014_03_09 ) );
   }

   {
      cDate d1996_07_11 = date_c( 1996, c_Aug, 11 );
      cDate d2015_05_23 = date_c( 2015, c_May, 23 );
      expect_lt_c_( cmp_date_c( d1996_07_11, d2015_05_23 ) );
      expect_eq_c_( cmp_date_c( d1996_07_11, d1996_07_11 ) );
      expect_gt_c_( cmp_date_c( d2015_05_23, d1996_07_11 ) );
   }

   return finish_tap_c_();
}
