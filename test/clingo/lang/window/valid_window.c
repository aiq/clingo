#include "clingo/io/cRecorder.h" // for cRecorder
#include "clingo/lang/expect.h"
#include "clingo/lang/window.h"
#include "clingo/type/cChars.h"

int main( void )
{
   init_tap_c_();

   cChars slice = c_c( "abc" );
   cCharWindow window;

   // -------------------------------------------------------------- valid cases
   init_front_char_window_c( &window, 1, slice );
   expect_c_( valid_window_c_( window ) );

   init_front_char_window_c( &window, 2, slice );
   expect_c_( valid_window_c_( window ) );

   init_front_char_window_c( &window, 3, slice );
   expect_c_( valid_window_c_( window ) );

   // ------------------------------------------------------------ invalid cases
   init_front_char_window_c( &window, 0, slice );
   expect_c_( not valid_window_c_( window ) );

   init_front_char_window_c( &window, 4, slice );
   expect_c_( not valid_window_c_( window ) );

   // ---------------------------------------------------------- iteration -next
   cRecorder* rec = &recorder_c_( 32 );
   init_front_char_window_c( &window, 2, c_c( "abcdef" ) );
   while ( valid_window_c_( window ) )
   {
      record_chars_c( rec, chars_c( window.s, window.v ) );
      next_window_c_( window );
   }
   expect_c_( recorded_is_c( rec, "abbccddeef" ) );

   // ---------------------------------------------------------- iteration -prev
   reset_recorder_c( rec );
   init_back_char_window_c( &window, 2, c_c( "abcdef" ) );
   while ( valid_window_c_( window ) )
   {
      record_chars_c( rec, chars_c( window.s, window.v ) );
      prev_window_c_( window );
   }
   expect_c_( recorded_is_c( rec, "efdecdbcab" ) );

   return finish_tap_c_();
}
