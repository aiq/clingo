#include "clingo/io/FILE.h"
#include "clingo/io/fwrite.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
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

   cChars path = c_c( "tmp-fwriteln.txt" );
   cErrorStack* es = &error_stack_c_( 128 );

   FILE* file = open_file_c( path, "wb", es );
   require_c_( file != NULL );
   testSlice tests = slice_c_( test,
      t_(
         fwriteln_c_( file, es, "{i64:q} in hex is {i64:xq}", int64_c_( 28 ), int64_c_( 28 ) ),
         "'28' in hex is '1c'"
      ),
      t_( true, "" ) // last line
   );
   require_c_( close_file_c( file, es ) );

   file = open_file_c( path, "rb", es );
   require_c_( file != NULL );
   for_each_c_( test const*, t, tests )
   {
      cVarChars buf = var_chars_c_( 128 );
      bool fin = false;
      fget_line_c( file, 128, &buf, &fin );
      bool res = chars_is_c( as_c_( cChars, buf ), t->exp );
      tap_c_( res, C_TapDesc, "{s}", t->exp );
   }
   require_c_( close_file_c( file, es ) );

   require_c_( remove_file_c( path, es ) );

   return finish_tap_c_();
}