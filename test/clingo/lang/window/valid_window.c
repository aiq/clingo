#include "clingo/io/cRecorder.h" // for cRecorder
#include "clingo/lang/expect.h"
#include "clingo/lang/window.h"
#include "clingo/type/cChars.h"

WINDOW_C_( char const, cChars, cCharWindow )

int main( void )
{
   init_tap_c_();

   cChars slice = c_c( "abc" );
   cCharWindow window;

   // -------------------------------------------------------------- valid cases
   window = (cCharWindow)front_window_c_( 1, slice );
   expect_c_( valid_window_c_( window ) );

   window = (cCharWindow)front_window_c_( 2, slice );
   expect_c_( valid_window_c_( window ) );

   window = (cCharWindow)front_window_c_( 3, slice );
   expect_c_( valid_window_c_( window ) );

   // ------------------------------------------------------------ invalid cases
   window = (cCharWindow)front_window_c_( 0, slice );
   expect_c_( not valid_window_c_( window ) );

   window = (cCharWindow)front_window_c_( 4, slice );
   expect_c_( not valid_window_c_( window ) );

   // ---------------------------------------------------------- iteration -next
   cRecorder* rec = &recorder_c_( 32 );
   window = (cCharWindow)front_window_c_( 2, c_c( "abcdef" ) );
   while ( valid_window_c_( window ) )
   {
      record_chars_c( rec, as_c_( cChars, window ) );
      next_window_c_( window );
   }
   expect_c_( recorded_is_c( rec, "abbccddeef" ) );

   // ---------------------------------------------------------- iteration -prev
   reset_recorder_c( rec );
   window = (cCharWindow)back_window_c_( 2, c_c( "abcdef" ) );
   while ( valid_window_c_( window ) )
   {
      record_chars_c( rec, as_c_( cChars, window ) );
      prev_window_c_( window );
   }
   expect_c_( recorded_is_c( rec, "efdecdbcab" ) );

   return finish_tap_c_();
}
