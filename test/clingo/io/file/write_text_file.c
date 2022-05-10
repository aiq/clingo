#include "clingo/io/file.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cChars chars = c_c( "text file text" );

   cChars path = c_c( "tmp-write_text_file.txt" );

   expect_c_( write_text_file_c( path, chars ) == 0 );

   cVarChars res;
   require_c_( read_text_file_c( path, &res ) == 0 );

   expect_c_( eq_chars_c( as_chars_c( res ), chars ) );

   expect_c_( remove_file_c( path ) == 0 );
   free( res.v );

   return finish_tap_c_();
}