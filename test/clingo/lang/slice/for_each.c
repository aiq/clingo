#include "clingo/io/cRecorder.h"
#include "clingo/io/write.h"
#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cCharsSlice.h"

int main( void )
{
   init_tap_c_();

   cVarChars buf = scalars_c_( 8, char );

   cCharsSlice words = cs_c_( "link", "zelda", "mario", "samus" );

   cRecorder* rec = &recorder_c_( 1024 );
   for_each_c_( i, cChars const*, word, words )
   {
      write_c_( rec, "[{i64}:{cs:q}]", i, *word );
   }

   expect_at_c_( recorded_is_c( rec, "[0:'link'][1:'zelda'][2:'mario'][3:'samus']" ) );

   return finish_tap_c_();
}
