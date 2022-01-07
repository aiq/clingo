#include "clingo/lang/chunk.h"
#include "clingo/lang/expect.h"
#include "clingo/type/cChars.h"

//------------------- Type,       ChunkType, SliceType,  FuncSuffix
STATIC_BACK_CHUNK_C_( char const, charChunk, cChars,     char_chunk )

int main( void )
{
   init_tap_c_();

   cChars abcdefg = c_c( "abcdefg" );

   charChunk chunk;
   init_back_char_chunk( &chunk, 2, abcdefg ); // --------------------------- fg
   expect_c_( valid_chunk_c_( chunk ) );
   expect_c_( first_c_( chunk ) == 'f' );
   expect_c_( last_c_( chunk ) == 'g' );

   prev_chunk_c_( chunk ); // ----------------------------------------------- de
   expect_c_( valid_chunk_c_( chunk ) );
   expect_c_( first_c_( chunk ) == 'd' );
   expect_c_( last_c_( chunk ) == 'e' );

   prev_chunk_c_( chunk ); // ----------------------------------------------- bc
   expect_c_( valid_chunk_c_( chunk ) );
   expect_c_( first_c_( chunk ) == 'b' );
   expect_c_( last_c_( chunk ) == 'c' );

   prev_chunk_c_( chunk ); // ------------------------------------------------ a
   expect_c_( valid_chunk_c_( chunk ) );
   expect_c_( first_c_( chunk ) == 'a' );
   expect_c_( last_c_( chunk ) == 'a' );

   prev_chunk_c_( chunk );
   expect_c_( not valid_chunk_c_( chunk ) );

   return finish_tap_c_();
}
