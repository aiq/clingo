#include "clingo/io/cScanner.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   // ------------------------------------------------------------- init scanner
   cScanner* sca = &cstr_scanner_c_( "abcd" );
   expect_at_c_( sca->pos == 0 );
   expect_at_c_( sca->space == 4 );
   expect_at_c_( is_empty_c_( scanned_bytes_c_( sca ) ) );

   // --------------------------------------------------------------- scan chars
   char c = ' ';
   int64_t len = 0;

   len += scan_char_c( sca, &c );
   expect_at_c_( c == 'a' );

   len += scan_char_c( sca, &c );
   expect_at_c_( c == 'b' );

   len += scan_char_c( sca, &c );
   expect_at_c_( c == 'c' );

   len += scan_char_c( sca, &c );
   expect_at_c_( c == 'd' );

   expect_at_c_( len == 4 );
   expect_at_c_( sca->pos == 4 );
   expect_at_c_( sca->space == 0 );

   // ------------------------------------------------- try to scan char outside
   len = scan_char_c( sca, &c );
   expect_at_c_( len == 0 );

   return finish_tap_c_();
}
