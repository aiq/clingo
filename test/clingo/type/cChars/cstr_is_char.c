#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   expect_at_c_( cstr_is_char_c( "Q", 'Q' ) );

   expect_at_c_( not cstr_is_char_c( "abc", 'a' ) );
   expect_at_c_( not cstr_is_char_c( "x", 'y' ) );
   expect_at_c_( not cstr_is_char_c( "", 'c' ) );

   return finish_tap_c_();
}
