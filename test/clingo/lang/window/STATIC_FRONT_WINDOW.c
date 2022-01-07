#include "clingo/lang/window.h"
#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

//--------------------- Type,       WindowType, SliceType,  FuncSuffix
STATIC_FRONT_WINDOW_C_( char const, charWindow, cChars,     char_window )

int main( void )
{
   init_tap_c_();

   cChars abcdef = c_c( "abcdef" );

   charWindow window;
   init_front_char_window( &window, 3, abcdef ); // ------------------------ abc
   expect_c_( valid_window_c_( window ) );
   expect_c_( first_c_( window ) == 'a' );
   expect_c_( last_c_( window ) == 'c' );

   next_window_c_( window ); // -------------------------------------------- bcd
   expect_c_( valid_window_c_( window ) );
   expect_c_( first_c_( window ) == 'b' );
   expect_c_( last_c_( window ) == 'd' );

   next_window_c_( window ); // -------------------------------------------- cde
   expect_c_( valid_window_c_( window ) );
   expect_c_( first_c_( window ) == 'c' );
   expect_c_( last_c_( window ) == 'e' );

   next_window_c_( window ); // -------------------------------------------- def
   expect_c_( valid_window_c_( window ) );
   expect_c_( first_c_( window ) == 'd' );
   expect_c_( last_c_( window ) == 'f' );

   next_window_c_( window );
   expect_c_( not valid_window_c_( window ) );

   return finish_tap_c_();
}
