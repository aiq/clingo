#include "clingo/lang/chunk.h"
#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

CHUNK_C_( char const, cChars, cCharChunk )

int main( void )
{
   init_tap_c_();

   cChars abcdefg = c_c( "abcdefg" );

   cCharChunk chunk = front_chunk_c_( 2, abcdefg ); // ---------------------- ab
   expect_at_c_( valid_chunk_c_( chunk ) );
   expect_at_c_( first_c_( chunk ) == 'a' );
   expect_at_c_( last_c_( chunk ) == 'b' );

   next_chunk_c_( chunk ); // ----------------------------------------------- cd
   expect_at_c_( valid_chunk_c_( chunk ) );
   expect_at_c_( first_c_( chunk ) == 'c' );
   expect_at_c_( last_c_( chunk ) == 'd' );

   next_chunk_c_( chunk ); // ----------------------------------------------- ef
   expect_at_c_( valid_chunk_c_( chunk ) );
   expect_at_c_( first_c_( chunk ) == 'e' );
   expect_at_c_( last_c_( chunk ) == 'f' );

   next_chunk_c_( chunk ); // ------------------------------------------------ g
   expect_at_c_( valid_chunk_c_( chunk ) );
   expect_at_c_( first_c_( chunk ) == 'g' );
   expect_at_c_( last_c_( chunk ) == 'g' );

   next_chunk_c_( chunk );
   expect_at_c_( not valid_chunk_c_( chunk ) );

  return finish_tap_c_();
}
