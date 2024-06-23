#include "clingo/lang/expect.h"
#include "clingo/type/cCharsSlice.h"

int main( void )
{
   init_tap_c_();

   cCharsSlice slc = cs_c_( "abc", "def", "gol" );

   expect_at_c_( slc.s == 3 );
   expect_at_c_( chars_is_c( slc.v[0], "abc" ) );
   expect_at_c_( chars_is_c( slc.v[1], "def" ) );
   expect_at_c_( chars_is_c( slc.v[2], "gol" ) );

   return finish_tap_c_();
}
