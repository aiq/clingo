#include "clingo/io/cScanner.h"
#include "clingo/lang/expect.h"

int main()
{
   init_tap_c_();

   // ------------------------------------------------------------- init scanner
   cBytes data = slice_c_( cByte, 0xab, 0xcd, 0xef );
   cScanner* sca = &make_scanner_c_( data.s, data.v );
   expect_c_( sca->pos == 0 );
   expect_c_( sca->space == 3 );
   expect_c_( is_empty_c_( scanned_bytes_c_( sca ) ) );

   // --------------------------------------------------------------- scan bytes
   cByte byte = 0x00;
   int64_t len = 0;

   len += scan_byte_c( sca, &byte );
   expect_c_( byte == 0xab );

   len += scan_byte_c( sca, &byte );
   expect_c_( byte == 0xcd );

   len += scan_byte_c( sca, &byte );
   expect_c_( byte == 0xef );

   expect_c_( len == 3 );
   expect_c_( sca->pos == 3 );
   expect_c_( sca->space == 0 );

   // ------------------------------------------------- try to scan byte outside
   len = scan_byte_c( sca, &byte );
   expect_c_( len == 0 );

   return finish_tap_c_();
}
