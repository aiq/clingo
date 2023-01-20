#include "clingo/io/FILE.h"
#include "clingo/io/print.h"
#include "clingo/lang/expect.h"

#define pln_( ... ) pjotln_c_( xyz, 256, __VA_ARGS__ )

char const* str =
"line 1\n"
"line 2\n"
"\n"
"line 4\n"
"very long line 5\n"
"\n";

TEMP_SLICE_C_(
   line,
   {
      char const* str;
      bool fin;
   }
)
#define l_( ... ) ((line){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cChars path = c_c( "tmp-fget_line.txt" );
   cErrorStack* es = &error_stack_c_( 128 );

   require_c_( write_text_file_c( path, c_c( str ), es ) );
   FILE* file = open_file_c( path, "r", es );
   require_c_( file != NULL );

   lineSlice lines = slice_c_( line,
      { "line 1", true },
      { "line 2", true },
      { "", true },
      { "line 4", true },
      { "very lo", false },
      { "ng line", false },
      { " 5", true },
      { "", true },
      { "", true }
   );

   int64_t i = 0;
   int32_t const n = 8;
   cVarChars buf = var_chars_c_( n );
   bool fin = false;
   while ( fget_line_c( file, n, &buf, &fin ) )
   {
       cChars chars = as_c_( cChars, buf );
       line l = lines.v[i];
       expect_c_( chars_is_c( chars, l.str ) );
       expect_c_( fin == l.fin );
       ++i;
   }

   expect_c_( feof( file ) != 0 );

   require_c_( close_file_c( file, es ) );
   require_c_( remove_file_c( path, es ) );

   return finish_tap_c_();
}