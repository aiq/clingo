#include "clingo/lang/expect.h"
#include "clingo/lang/window.h"
#include "clingo/type/cChars.h"

WINDOW_C_( char const, cChars, cCharWindow )

int main( void )
{
   init_tap_c_();

   cChars abcdef = c_c( "abcdef" );

   cCharWindow window = front_window_c_( 3, abcdef); // -------------------- abc
   expect_at_c_( valid_window_c_( window ) );
   expect_at_c_( first_c_( window ) == 'a' );
   expect_at_c_( last_c_( window ) == 'c' );

   next_window_c_( window ); // -------------------------------------------- bcd
   expect_at_c_( valid_window_c_( window ) );
   expect_at_c_( first_c_( window ) == 'b' );
   expect_at_c_( last_c_( window ) == 'd' );

   next_window_c_( window ); // -------------------------------------------- cde
   expect_at_c_( valid_window_c_( window ) );
   expect_at_c_( first_c_( window ) == 'c' );
   expect_at_c_( last_c_( window ) == 'e' );

   next_window_c_( window ); // -------------------------------------------- def
   expect_at_c_( valid_window_c_( window ) );
   expect_at_c_( first_c_( window ) == 'd' );
   expect_at_c_( last_c_( window ) == 'f' );

   next_window_c_( window );
   expect_at_c_( not valid_window_c_( window ) );

   return finish_tap_c_();
}
