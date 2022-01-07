#include "clingo/lang/expect.h"
#include "clingo/time/cDate.h"

int main( void )
{
   init_tap_c_();

   cWeekDate wd = week_date_c( 2008, 39, c_Fri );
   cDate res = from_week_date_c( wd );
   println_scope_c_( rec, 256 )
   {
      write_week_date_c_( rec, wd );
      record_endl_c( rec );
      write_date_c_( rec, res );
   }
   expect_c_( eq_date_c( res, date_c( 2008, c_Sep, 26 ) ) );

   return finish_tap_c_();
}
