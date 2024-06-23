#include "clingo/lang/expect.h"
#include "clingo/type/bool.h"

int main( void )
{
   init_tap_c_();

   cBoolSlice s01010 = slice_c_( bool, false, true, false, true, false );

   expect_at_c_( count_eq_bool_c( s01010, true  ) == 2 );
   expect_at_c_( count_eq_bool_c( s01010, false ) == 3 );

   return finish_tap_c_();
}
