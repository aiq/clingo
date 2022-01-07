#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/lang/expect.h"

int main( void )
{
   init_tap_c_();

   cChars txt = c_c( "a ☀, no ☂" );
   cRecorder* rec = &recorder_c_( 128 );

   {
      cScanner* sca = &make_scanner_c_( txt.s, txt.v );

      int64_t count = 0;
      cRune rune;
      while ( scan_rune_c( sca, &rune ) )
      {
         ++count;
         record_rune_c( rec, rune );
      }
      expect_c_( count == 9 );
      expect_c_( recorded_is_c( rec, "a ☀, no ☂" ) );
      reset_recorder_c( rec );
   }

   {
      // last rune not complete in slice
      cScanner* sca = &make_scanner_c_( txt.s-1, txt.v );

      int64_t count = 0;
      cRune rune;
      while ( scan_rune_c( sca, &rune ) )
      {
         ++count;
         record_rune_c( rec, rune );
      }
      expect_c_( count == 8 );
      expect_c_( recorded_is_c( rec, "a ☀, no " ) );
      reset_recorder_c( rec );
   }

   return finish_tap_c_();
}
