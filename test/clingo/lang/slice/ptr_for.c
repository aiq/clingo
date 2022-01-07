#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars abcdef = c_c( "abcdef" );
   char const* ptr = NULL;

   // ---------------------------------------------------- returns valid pointer
   ptr = ptr_for_c_( abcdef, 0 );
   expect_c_( *ptr == 'a' );

   ptr = ptr_for_c_( abcdef, 2 );
   expect_c_( *ptr == 'c' );

   ptr = ptr_for_c_( abcdef, 5 );
   expect_c_( *ptr == 'f' );

   // ---------------------------------------------------- try to access outside
   ptr = ptr_for_c_( abcdef, -1 );
   expect_c_( ptr == NULL );

   ptr = ptr_for_c_( abcdef, 6 );
   expect_c_( ptr == NULL );

   return finish_tap_c_();
}
