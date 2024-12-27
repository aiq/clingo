#include "clingo/lang/expect.h"
#include "clingo/io/FILE.h"
#include "clingo/io/print.h"
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
   FILE* f = open_file_c_( "tmp_tap_block", "w+b", es );
   cVarChars inp;
   {
      init_tap_c( "test session", f );
      tap_block_c_( false )
      {
         tap_line_c_( "k", "the missing {c:q}", 'v' );
      }
      tap_block_c_( expect_at_c_( false ) )
      {
         tap_msg_line_c_( "bla bla bla" );
         tap_exp_line_c_( "a {s:q}", "string" );
         tap_got_line_c_( "foo", "bar", "{i64}", int64_c_( 2000 ) );
         tap_line_c_( "lines", "dfdf\nafddf\n\"OOO\"" );
      }
      expect_block_c_( int64_c_( 0 ), false ){}
      finish_tap_c_();

      inp = (cVarChars)heap_slice_c_( file_size_c( f ), char );
      fseek( f, 0, SEEK_SET );
      fget_chars_c( f, &inp );
   }
   close_file_c( f, es );
   remove_file_c_( "tmp_tap_block", es );

   print_c_( "{cs}", inp );
   init_tap_c_();

   cCharsToken* tok = &chars_token_c_( as_c_( cChars, inp ) );
   expect_line_( tok, "# test session" );
expect_line_( tok, "  ---" );
expect_line_( tok, "  k: \"the missing 'v'\"" );
expect_line_( tok, "  ..." );
expect_line_( tok, "not ok 1 - at line 25" );
expect_line_( tok, "  ---" );
expect_line_( tok, "  message: 'bla bla bla'" );
expect_line_( tok, "  expected: \"a 'string'\"" );
expect_line_( tok, "  got: 'foobar2000'" );
expect_line_( tok, "  lines: |+  " );
expect_line_( tok, "    dfdf" );
expect_line_( tok, "    afddf" );
expect_line_( tok, "    \"OOO\"" );
expect_line_( tok, "  ..." );
expect_line_( tok, "not ok 2 - test 1. at line 32" );
expect_line_( tok, "  ---" );
expect_line_( tok, "  ..." );

   return finish_tap_c_();
}