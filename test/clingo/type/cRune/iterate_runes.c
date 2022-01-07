#include "clingo/io/cRecorder.h"
#include "clingo/lang/expect.h"
#include "clingo/type/cRune.h"

int main( void )
{
   init_tap_c_();

   cRecorder* ascii = &recorder_c_( 128 );
   cRecorder* unicode = &recorder_c_( 128 );

   cChars chars = c_c( "® yes this is a 𝄞 and €!" );
   cRune r;
   iterate_runes_c_( itr, r, chars )
   {
      cRecorder* rec = rune_size_c( r) == 1 ? ascii : unicode;
      record_rune_c( rec, r );
   }

   expect_c_( recorded_is_c( ascii, " yes this is a  and !" ));
   println_recorded_c( ascii );
   expect_c_( recorded_is_c( unicode, "®𝄞€" ));

   return finish_tap_c_();
}