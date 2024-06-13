#include "clingo/lang/expect.h"
#include "clingo/io/FILE.h"
#include "clingo/io/print.h"

int main( void )
{
   cErrorStack* es = &error_stack_c_( 1024 );
   FILE* f = wopen_file_c( c_c("tmp_expect"), es );
   init_tap_c( "test session", f );

   tap_note_c( "test expect_c_" );
   expect_c_( true );
   expect_c_( false );

   tap_note_c( "tap_desc_c_" );
   tap_desc_c_( true, "some description" );
   tap_desc_c_( true, "some description", C_TapSkip, "surprise" );
   tap_desc_c_( false, "some description", C_TapTodo, "no time" );
   tap_desc_c_( false, "{i64} description about {s}", 1, "tests" );

   tap_note_c( "tap_skip_c_" );
   tap_skip_c_( true, "with reason" );
   tap_skip_c_( false, "" );

   tap_note_c( "tap_todo_c_" );
   tap_todo_c_( true, "with reason" );
   tap_todo_c_( false, "" );

   tap_note_c( "tap_c_" );
   tap_c_( true, C_TapDesc, "a description", C_TapSkip, "with reason" );
   tap_c_( false, C_TapDesc, "more description", C_TapTodo, "more reason" );

   finish_tap_c_();
   close_file_c( f, es );

   cVarChars log = read_text_file_c( c_c("tmp_expect"), es );
   println_c_( "---------------------------------" );
   print_c_( "{cs}", log );
   println_c_( "---------------------------------" );
   free( log.v );

   init_tap_c_();

   expect_c_( true );

   return finish_tap_c_();
}
