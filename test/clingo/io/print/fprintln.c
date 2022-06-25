#include "clingo/io/FILE.h"
#include "clingo/io/print.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      bool res;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   cChars path = c_c( "tmp-fprintln.txt" );
   cErrorStack* es = &error_stack_c_( 128 );

   FILE* file = open_file_c( path, "wb", es );
   require_c_( file != NULL );
   testSlice tests = slice_c_( test,
      t_(
         fprintln_c_( file, es, "{i64:q} in hex is {i64:xq}", int64_c_( 28 ), int64_c_( 28 ) ),
         "'28' in hex is '1c'"
      ),
      t_( true, "" ) // last line
   );
   require_c_( close_file_c( file, es ) );

   file = open_file_c( path, "rb", es );
   require_c_( file != NULL );
   for_each_c_( test const*, t, tests )
   {
      cVarChars buf = char_buffer_c_( 128 );
      bool fin = false;
      fread_line_c( file, 128, &buf, &fin );
      bool res = chars_is_c( as_chars_c( buf ), t->exp );
      tap_desc_c( res, t->exp );
   }
   require_c_( close_file_c( file, es ) );

   require_c_( remove_file_c( path, es ) );

   return finish_tap_c_();
}