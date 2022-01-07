#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"
#include "clingo/type/cCharsToken.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      char const* text;
      char const* set;
      bool ignoreEmpty;
      char const* exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "- This, is-a sample string.", " ,.-", false, "- , -  ." )
   );

   for_each_c_( test const*, t, tests )
   {
      cRecorder* rec = &recorder_c_( 128 );

      cCharsToken tok;
      init_cstr_token_c( &tok, t->text );
      while ( next_token_till_any_char_c_( &tok, t->set ) )
      {
         if ( t->ignoreEmpty and is_empty_c_( tok.x ) ) continue;

         record_chars_c( rec, token_delimiter_c( &tok ) );
      }
      bool res = recorded_is_c( rec, t->exp );
      tap_descf_c( res, "test expected: %s", t->exp );
   }

   return finish_tap_c_();
}
