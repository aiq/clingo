#include "clingo/io/cScanner.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   // ------------------------------------------------------------- init scanner
   cScanner* sca = &cstr_scanner_c_( "---abba---" );
   expect_c_( sca->pos == 0 );
   expect_c_( sca->space == 10 );
   expect_c_( is_empty_c_( scanned_bytes_c_( sca ) ) );

   // ----------------------------------------------------------------- view pad
   cChars pad = view_pad_c( sca, '-' );
   expect_c_( chars_is_c( pad, "---" ) );
   expect_c_( sca->pos == 3 );
   expect_c_( sca->space == 7 );

   pad = view_pad_c( sca, 'a' );
   expect_c_( chars_is_c( pad, "a" ) );

   pad = view_pad_c( sca, 'b' );
   expect_c_( chars_is_c( pad, "bb" ) );
   expect_c_( sca->pos == 6 );
   expect_c_( sca->space == 4 );

   // --------------------------------------------- try to view not existing pad
   pad = view_pad_c( sca, 'X' );
   expect_c_( is_empty_c_( pad ) );
   expect_c_( sca->pos == 6 );
   expect_c_( sca->space == 4 );

   // ----------------------------------------------------------- view rest data
   pad = view_pad_c( sca, 'a' );
   expect_c_( chars_is_c( pad, "a" ) );

   pad = view_pad_c( sca, '-' );
   expect_c_( chars_is_c( pad, "---" ) );
   expect_c_( sca->pos == 10 );
   expect_c_( sca->space == 0 );

   // -------------------------------------------------- try to view pad outside
   pad = view_pad_c( sca, '-' );
   expect_c_( is_empty_c_( pad ) );

   return finish_tap_c_();
}
