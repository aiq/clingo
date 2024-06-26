#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h" // find_char_c

int main( void )
{
   init_tap_c_();

   cChars chars = c_c( "abcdefgh" );
   char const* ptr = NULL;

   ptr = find_char_c( chars, 'a' ); // --------------------------------------- a
   expect_at_c_( *ptr == 'a' );
   expect_at_c_( index_of_c_( chars, ptr ) == 0 );

   ptr = find_char_c( chars, 'b' ); // --------------------------------------- b
   expect_at_c_( *ptr == 'b' );
   expect_at_c_( index_of_c_( chars, ptr ) == 1 );

   ptr = find_char_c( chars, 'e' ); // --------------------------------------- e
   expect_at_c_( *ptr == 'e' );
   expect_at_c_( index_of_c_( chars, ptr ) == 4 );

   ptr = find_char_c( chars, 'h' ); // --------------------------------------- h
   expect_at_c_( *ptr == 'h' );
   expect_at_c_( index_of_c_( chars, ptr ) == 7 );

   ptr = find_char_c( chars, 'x' ); // --------------------------------------- x
   expect_at_c_( ptr == NULL );
   expect_at_c_( not points_into_c_( chars, ptr ) );

   return finish_tap_c_();
}
