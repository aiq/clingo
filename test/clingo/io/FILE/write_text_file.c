#include "clingo/io/FILE.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cChars path = c_c( "tmp-write_text_file.txt" );
   cErrorStack* es = &error_stack_c_( 128 );

   cChars chars = c_c( "text file text" );
   expect_c_( write_text_file_c( path, chars, es ) );

   cVarChars res = read_text_file_c( path, es );
   require_c_( not is_invalid_c_( res )  );

   expect_c_( eq_chars_c( as_c_( cChars, res ), chars ) );

   expect_c_( remove_file_c( path, es ) );
   free( res.v );

   return finish_tap_c_();
}