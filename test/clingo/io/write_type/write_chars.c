#include "clingo/io/write_type.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_C_(
   test,
   {
      char const* txt;
      char const* fmt;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "John", "", "John" ),
      t_( "Paul", "s", "Paul" ),
      t_( "George", "q", "'George'" ),
      t_( "Ringo", "Q", "\"Ringo\"" ),
      t_( "The \"Beatles\":\nJohn\tPaul\tGeorge\tRingo", "e",
          "\"The \\\"Beatles\\\":\\nJohn\\tPaul\\tGeorge\\tRingo\"" )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 128 );

      bool res = write_chars_c( rec, c_c( t->txt ), t->fmt );
      res &= recorded_is_c( rec, t->exp );

      tap_c_( res, C_TapDesc, "test with fmt: {s:q}", t->fmt );
   }

   return finish_tap_c_();
}
