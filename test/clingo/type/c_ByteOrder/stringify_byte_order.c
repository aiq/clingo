#include "clingo/lang/expect.h"
#include "clingo/type/c_ByteOrder.h"

int main( void )
{
   init_tap_c_();

   c_ByteOrder val;

   val = c_BigEndian;
   expect_eq_c_( strcmp( "c_BigEndian", stringify_byte_order_c( val ) ) );

   val = c_LittleEndian;
   expect_eq_c_( strcmp( "c_LittleEndian", stringify_byte_order_c( val ) ) );

   return finish_tap_c_();
}
