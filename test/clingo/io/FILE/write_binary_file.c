#include "clingo/io/FILE.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cChars path = c_c( "tmp-write_binary_file.bin" );
   cErrorStack* es = &error_stack_c_( 128 );

   cVarBytes bytes = scalars_c_( 256, cByte );
   times_c_( bytes.s, i )
   {
      bytes.v[i] = byte_c_( i );
   }
   expect_c_( write_binary_file_c( path, as_c_( cBytes, bytes ), es ) );

   cVarBytes res = read_binary_file_c( path, es );
   require_c_( not is_invalid_c_( res ) );

   expect_eq_c_( cmp_bytes_c( as_c_( cBytes, res ), as_c_( cBytes, bytes ) ) );

   expect_c_( remove_file_c( path, es ) );
   free( res.v );

   return finish_tap_c_();
}