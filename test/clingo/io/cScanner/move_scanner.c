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

   cScanner* sca = &cstr_scanner_c_( "abcdefghijklmnopqrstuvwxyz" );
   expect_( sca, "", "abcdefghijklmnopqrstuvwxyz" );

   move_scanner_c( sca, 6 );
   expect_( sca, "abcdef", "ghijklmnopqrstuvwxyz" );

   move_scanner_c( sca, 5 );
   expect_( sca, "abcdefghijk", "lmnopqrstuvwxyz" );

   move_scanner_c( sca, -3 );
   expect_( sca, "abcdefgh", "ijklmnopqrstuvwxyz" );

   return finish_tap_c_();
}
