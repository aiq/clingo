#include "clingo/lang/expect.h"
#include "clingo/type/cCharsSlice.h"

int main( void )
{
   init_tap_c_();

   cChars nephew = c_c( "Tick" );

   expect_c_( chars_is_any_c_( nephew, "Tick", "Trick", "Track" ) );
   expect_c_( not chars_is_any_c_( nephew, "Trick", "Track" ) );

   return finish_tap_c_();
}
