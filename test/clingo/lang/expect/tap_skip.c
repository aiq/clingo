#include "clingo/lang/expect.h"
#include "clingo/io/FILE.h"
#include "clingo/type/cCharsToken.h"

#define expect_line_( Tok, Exp )                                               \
   require_c_( next_line_token_c( Tok ) );                                     \
   tap_desc_c_( chars_is_c( (Tok)->x, (Exp) ), "got: {cs}", (Tok)->x );

int main( void )
{
   cErrorStack* es = &error_stack_c_( 1024 );
   FILE* f = open_file_c_( "tmp_tap_skip", "w+b", es );

   init_tap_c( "test session", f );
   tap_note_c( "tap_skip_c_" );
   tap_skip_c_( true, "with reason" );
   tap_skip_c_( false, "" );
   finish_tap_c_();

   cVarChars inp = heap_slice_c_( file_size_c( f ), char );
   fseek( f, 0, SEEK_SET );
   fget_chars_c( f, &inp );
   close_file_c( f, es );
   remove_file_c_( "tmp_tap_skip", es );

   init_tap_c_();

   cCharsToken* tok = &chars_token_c_( as_c_( cChars, inp ) );
   expect_line_( tok, "# test session" );
   expect_line_( tok, "# tap_skip_c_" );
   expect_line_( tok, "ok 1 # SKIP with reason" );
   expect_line_( tok, "not ok 2 # SKIP " );
   expect_line_( tok, "1..2" );
   expect_line_( tok, "" );
   expect_c_( not next_line_token_c( tok ) );

   return finish_tap_c_();
}
