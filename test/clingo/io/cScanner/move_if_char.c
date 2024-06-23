#include "clingo/io/cScanner.h"
#include "clingo/lang/expect.h"

#define expect_( Sca, Left, Right )                                            \
{                                                                              \
   expect_at_c_( chars_is_c( scanned_chars_c_( Sca ), (Left) ) );                 \
   expect_at_c_( chars_is_c( unscanned_chars_c_( Sca ), (Right) ) );              \
}

int main( void )
{
   init_tap_c_();

   cScanner* sca = &cstr_scanner_c_( "anne" );

   // ---------------------------------------------- move if it matches the char
   expect_at_c_( move_if_char_c( sca, 'a' ) );
   expect_( sca, "a", "nne" );

   expect_at_c_( not move_if_char_c( sca, 'x' ) );
   expect_( sca, "a", "nne" );

   // -------------------------------------------- the function is case sensitve
   expect_at_c_( not move_if_char_c( sca, 'N' ) );
   expect_( sca, "a", "nne" );

   // ------------------------------------------------------- moves just on char
   expect_at_c_( move_if_char_c( sca, 'n' ) );
   expect_( sca, "an", "ne" );

   return finish_tap_c_();
}
