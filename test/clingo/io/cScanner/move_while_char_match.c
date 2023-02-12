#include <ctype.h>
#include "clingo/io/cScanner.h"
#include "clingo/lang/expect.h"

#define expect_( Sca, Left, Right )                                            \
{                                                                              \
   expect_c_( chars_is_c( scanned_chars_c_( Sca ), (Left) ) );                 \
   expect_c_( chars_is_c( unscanned_chars_c_( Sca ), (Right) ) );              \
}

int main()
{
   init_tap_c_();

   cScanner* sca = &cstr_scanner_c_( "458 sad213XyZ" );

   // ------------------------------------------------
   expect_c_( move_while_char_match_c( sca, char_is_digit_c ) );
   expect_( sca, "458", " sad213XyZ" );

   expect_c_( not move_while_char_match_c( sca, char_is_punct_c ) );
   expect_( sca, "458", " sad213XyZ" );

   expect_c_( move_while_char_match_c( sca, char_is_space_c ) );
   expect_( sca, "458 ", "sad213XyZ" );

   expect_c_( move_while_char_match_c( sca, char_is_alpha_c ) );
   expect_( sca, "458 sad", "213XyZ" );

   expect_c_( move_while_char_match_c( sca, char_is_alnum_c ) );
   expect_( sca, "458 sad213XyZ", "" );

   return finish_tap_c_();
}
