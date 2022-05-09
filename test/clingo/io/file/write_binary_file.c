#include "clingo/io/file.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cVarBytes bytes = scalars_c_( 256, cByte );
   times_c_( bytes.s, i )
   {
      bytes.v[i] = byte_c_( i );
   }

   cChars path = c_c( "tmp-write_binary_file.bin" );

   expect_c_( write_binary_file_c( path, as_bytes_c( bytes ) ) );

   cVarBytes res = read_binary_file_c( path );
   require_c_( not is_empty_c_( res ) );

   expect_eq_c_( cmp_bytes_c( as_bytes_c( res ), as_bytes_c( bytes ) ) );

   expect_c_( remove_file_c( path ) );
   free( res.v );

   return finish_tap_c_();
}