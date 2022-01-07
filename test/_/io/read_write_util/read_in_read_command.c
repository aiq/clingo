#include "_/io/read_write_util.h"
#include "clingo/lang/expect.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      char const* inp;
      cReadCommand exp;
   }
)
#define t_( Inp, Type, Op, Uni ) ((test){ Inp, { Type, Op, { Uni } } })
#define tf_( Inp, Type, Op, Func ) ((test){ Inp, { Type, Op, { .func = Func } } })
#define tr_( Inp, Type, Op, Range ) ((test){ Inp, { Type, Op, { .range = Range } } })
#define ts_( Inp, Type, Op, Set ) ((test){ Inp, { Type, Op, { .set = Set } } })

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
   // func
      tf_( "{/+l}bla", '/', '+', 'l' ),
      tf_( "{/>d}bla", '/', '>', 'd' ),
   // set
      ts_( "{*^}}bla", 'a', '*', c_c( "^}" ) ),
   // range
      tr_( "{[?0020-007e}bla", '[', '?', rune_range_c( " ", "~" ) ),
      tr_( "{[*20-7E}bla", '[', '*', rune_range_c( " ", "~" ) ),
      tr_( "{[+ z}", '[', '+', rune_range_c( " ", "z" ) )
   );

   for_each_c_( test const*, t, tests )
   {
      cScanner* sca = &cstr_scanner_c_( t->inp );
      cReadCommand cmd;
      bool res = read_in_read_command_c( sca, &cmd );
      res &= eq_read_command_c( &cmd, &t->exp );
      tap_descf_c( res, "%s with tail %s", t->inp, sca->mem );
   }

   return finish_tap_c_();
}
