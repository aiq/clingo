#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   // ------------------------------------------------------------------- cChars
   cChars chars = c_c( "Earth, Wind and Fire" );

   cChars earth = left_chars_c( chars, 5 );
   cChars wind = sub_chars_c( chars, 7, 11 );
   cChars fire = right_chars_c( chars, 4 );
   cChars windAndFire = mid_chars_c( chars, 7 );

   expect_c_( is_sub_c_( chars, earth ) );
   expect_c_( is_sub_c_( chars, wind ) );
   expect_c_( is_sub_c_( chars, fire ) );
   expect_c_( is_sub_c_( chars, windAndFire ) );

   return finish_tap_c_();
}
