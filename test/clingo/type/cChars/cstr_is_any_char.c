#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   expect_c_( cstr_is_any_char_c_( "Q", "CQ" ) );

   expect_c_( not cstr_is_any_char_c_( "CQ", "CQ" ) );
   expect_c_( not cstr_is_any_char_c_( "a", "xyz" ) );
   expect_c_( not cstr_is_any_char_c_( "", "abc" ) );

   return finish_tap_c_();
}
