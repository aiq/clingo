#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   CString* e1 = empty_string_c();
   CString* e2 = lit_c( "" );
   CString* e3 = new_string_c( "" );
   CString* e4 = make_string_c( (cChars)empty_c_() );

   expect_c_( string_is_empty_c( e1 ) );
   expect_c_( string_is_empty_c( e2 ) );
   expect_c_( string_is_empty_c( e3 ) );
   expect_c_( string_is_empty_c( e4 ) );

   expect_c_( e1 == e2 );
   expect_c_( e2 == e3 );
   expect_c_( e3 == e4 );

   return finish_tap_c_();
}
