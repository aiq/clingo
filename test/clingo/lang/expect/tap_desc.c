#include "clingo/lang/expect.h"
#include "clingo/io/FILE.h"
#include "clingo/type/cCharsToken.h"

#define expect_line_( Tok, Exp )                                               \
   require_c_( next_line_token_c( Tok ) );                                     \
   expect_block_at_c_( chars_is_c( (Tok)->x, (Exp) ) )                         \
   {                                                                           \
      tap_exp_line_c_( "{s}", (Exp) );                                         \
      tap_got_line_c_( "{cs}", (Tok)->x );                                      \
   }

int main( void )
{
   cErrorStack* es = &error_stack_c_( 1024 );
   FILE* f = open_file_c_( "tmp_tap_desc", "w+b", es );
   cVarChars inp;
   {
      init_tap_c( "test session", f );
      tap_note_c( "tap_desc_c_" );
      tap_desc_c_( true, "some description" );
      tap_desc_c_( true, "some description", C_TapSkip, "surprise" );
      tap_desc_c_( false, "some description", C_TapTodo, "no time" );
      tap_desc_c_( false, "{i64} description about {s}", int64_c_( 1 ), "tests" );
      finish_tap_c_();

      inp = (cVarChars)heap_slice_c_( file_size_c( f ), char );
      fseek( f, 0, SEEK_SET );
      fget_chars_c( f, &inp );
   }
   close_file_c( f, es );
   remove_file_c_( "tmp_tap_desc", es );

   init_tap_c_();

   cCharsToken* tok = &chars_token_c_( as_c_( cChars, inp ) );
   expect_line_( tok, "# test session" );
   expect_line_( tok, "# tap_desc_c_" );
   expect_line_( tok, "ok 1 - some description" );
   expect_line_( tok, "ok 2 - some description # SKIP surprise" );
   expect_line_( tok, "not ok 3 - some description # TODO no time" );
   expect_line_( tok, "not ok 4 - 1 description about tests" );
   expect_line_( tok, "1..4" );
   expect_line_( tok, "" );
   expect_at_c_( not next_line_token_c( tok ) );

   return finish_tap_c_();
}
