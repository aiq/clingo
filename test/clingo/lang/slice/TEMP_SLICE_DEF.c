#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      char const* input;
      int exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "1234", 1234 ),
      t_( "-78", -78 )
   );

   for ( int64_t i = 0; i < tests.s; ++i )
   {
      test t = tests.v[i];
      int res = atoi( t.input );
      tap_descf_c( res == t.exp, "test at index %"PRIi64, i );
   }

   return finish_tap_c_();
}
