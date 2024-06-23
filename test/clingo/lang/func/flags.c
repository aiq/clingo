#include "clingo/lang/expect.h"
#include "clingo/lang/func.h"

#define cFLAGS_                                                                \
   XMAP_C_( c_1, 1 << 0 )                                                      \
   XMAP_C_( c_2, 1 << 1 )                                                      \
   XMAP_C_( c_3, 1 << 2 )                                                      \
   XMAP_C_( c_4, 1 << 3 )                                                      \
   XMAP_C_( c_5, 1 << 4 )                                                      \
   XMAP_C_( c_6, 1 << 5 )                                                      \
   XMAP_C_( c_7, 1 << 6 )                                                      \
   XMAP_C_( c_8, 1 << 7 )

#define XMAP_C_( N, I ) N = I,
enum c_Flags { cFLAGS_ };
#undef XMAP_C_

int main( void )
{
   init_tap_c_();

   uint8_t config = 0;

   expect_at_c_( not has_c_( config, c_1|c_2|c_3|c_4|c_5|c_6|c_7|c_8 ) );

   config = set_c_( config, c_1|c_2|c_3|c_6|c_7 );
   expect_at_c_( has_c_( config, c_1|c_2|c_3|c_6|c_7 ) );
   expect_at_c_( not has_c_( config, c_4|c_5|c_8 ) );

   config = unset_c_( config, c_2|c_3|c_7 );
   expect_at_c_( has_c_( config, c_1|c_6 ) );
   expect_at_c_( not has_c_( config, c_2|c_3|c_4|c_5|c_7|c_8 ) );

   return finish_tap_c_();
}
