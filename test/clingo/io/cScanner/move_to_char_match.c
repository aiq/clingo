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

   expect_c_( move_to_char_match_c( sca, isdigit ) );
   expect_( sca, "", "458 sad213XyZ" );
   reset_scanner_c( sca );

   expect_c_( move_to_char_match_c( sca, isspace ) );
   expect_( sca, "458", " sad213XyZ" );
   reset_scanner_c( sca );

   expect_c_( move_to_char_match_c( sca, isalpha ) );
   expect_( sca, "458 ", "sad213XyZ" );
   reset_scanner_c( sca );

   expect_c_( move_to_char_match_c( sca, isupper ) );
   expect_( sca, "458 sad213", "XyZ" );
   reset_scanner_c( sca );

   expect_c_( not move_to_char_match_c( sca, ispunct ) );
   expect_( sca, "", "458 sad213XyZ" );

   return finish_tap_c_();
}
