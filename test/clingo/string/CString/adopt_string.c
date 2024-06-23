#include "clingo/lang/expect.h"
#include "clingo/string/CString.h"

int main( void )
{
   init_tap_c_();

   char* cstr = alloc_c( 4 );
   cstr[ 0 ] = 'a';
   cstr[ 1 ] = 'b';
   cstr[ 2 ] = 'c';
   cstr[ 3 ] = '\0';

   CString* str = adopt_cstr_c( cstr );

   expect_at_c_( string_is_c( str, "abc" ) );
   expect_at_c_( scstr_c( str ) == cstr );

   release_c( str );

   return finish_tap_c_();
}
