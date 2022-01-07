#include "_/io/read_write_util.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      char const* inp;
      char const* exp;
   }
)
#define t_( ... ) ((test){ __VA_ARGS__ })

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( "asdf}", "asdf" ),
      t_( "^^^}}", "^^^}" )
   );

   for_each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->inp );
      cChars tmp;
      bool res = read_in_till_end_c( sca, &tmp );
      res &= chars_is_c( tmp, t->exp );

      tap_descf_c( res, "%s -> %s", t->inp, sca->mem );
   }

   return finish_tap_c_();
}
