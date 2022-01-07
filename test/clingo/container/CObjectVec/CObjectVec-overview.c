#include "clingo/lang/expect.h"
#include "clingo/container/CBitVec.h"
#include "clingo/container/CByteVec.h"
#include "clingo/container/CInt64Map.h"
#include "clingo/container/CInt64Set.h"
#include "clingo/container/CInt64Vec.h"
#include "clingo/container/CObjectVec.h"

int main( void )
{
   init_tap_c_();

   CObjectVec* gc = retain_c( new_object_vec_c() );
   cVecInfo const* info = info_of_object_vec_c( gc );

   add_to_object_vec_c( gc, new_bit_vec_c( 64 ) );
   add_to_object_vec_c( gc, new_byte_vec_c() );
   add_to_object_vec_c( gc, new_int64_map_c() );
   add_to_object_vec_c( gc, new_int64_set_c() );
   add_to_object_vec_c( gc, new_int64_vec_c() );

   expect_c_( info->count == 5 );

   release_c( gc );

   return finish_tap_c_();
}