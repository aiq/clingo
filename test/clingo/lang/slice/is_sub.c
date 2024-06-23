#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   // ------------------------------------------------------------------- cChars
   cChars chars = c_c( "Earth, Wind and Fire" );

   cChars earth = left_c_( cChars, chars, 5 );
   cChars wind = sub_c_( cChars, chars, 7, 11 );
   cChars fire = right_c_( cChars, chars, 4 );
   cChars windAndFire = mid_c_( cChars, chars, 7 );

   expect_at_c_( is_sub_c_( chars, earth ) );
   expect_at_c_( is_sub_c_( chars, wind ) );
   expect_at_c_( is_sub_c_( chars, fire ) );
   expect_at_c_( is_sub_c_( chars, windAndFire ) );

   return finish_tap_c_();
}
