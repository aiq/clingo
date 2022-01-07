#include "clingo/lang/chunk.h"
#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

//-------------------- Type,       ChunkType, SliceType,    FuncSuffix
STATIC_FRONT_CHUNK_C_( char const, charChunk, cChars,       char_chunk )

int main( void )
{
   init_tap_c_();

   cChars abcdefg = c_c( "abcdefg" );

   charChunk chunk;
   init_front_char_chunk( &chunk, 2, abcdefg ); // -------------------------- ab
   expect_c_( valid_chunk_c_( chunk ) );
   expect_c_( first_c_( chunk ) == 'a' );
   expect_c_( last_c_( chunk ) == 'b' );

   next_chunk_c_( chunk ); // ----------------------------------------------- cd
   expect_c_( valid_chunk_c_( chunk ) );
   expect_c_( first_c_( chunk ) == 'c' );
   expect_c_( last_c_( chunk ) == 'd' );

   next_chunk_c_( chunk ); // ----------------------------------------------- ef
   expect_c_( valid_chunk_c_( chunk ) );
   expect_c_( first_c_( chunk ) == 'e' );
   expect_c_( last_c_( chunk ) == 'f' );

   next_chunk_c_( chunk ); // ------------------------------------------------ g
   expect_c_( valid_chunk_c_( chunk ) );
   expect_c_( first_c_( chunk ) == 'g' );
   expect_c_( last_c_( chunk ) == 'g' );

   next_chunk_c_( chunk );
   expect_c_( not valid_chunk_c_( chunk ) );
   return finish_tap_c_();
}
