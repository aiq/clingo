#include "clingo/lang/expect.h"
#include "clingo/lang/slice.h"
#include "clingo/type/cChars.h"

//************************************** example struct
struct Point
{
   int32_t x;
   int32_t y;
};

typedef struct Point Point;

SLICE_DEF_C_(
   Point,
   PointSlice,
   VarPointSlice
)
//**************************************

static cChars abc = slice_c_( char, 'a', 'b', 'c' );

int main( void )
{
   init_tap_c_();

   // global static slice
   expect_c_( abc.s == 3 );
   expect_c_( abc.v[ 0 ] == 'a' );
   expect_c_( abc.v[ 1 ] == 'b' );
   expect_c_( abc.v[ 2 ] == 'c' );

   // local slice
   cVarChars def = slice_c_( char, 'd', 'e', 'f' );
   expect_c_( def.s == 3 );
   expect_c_( def.v[ 0 ] == 'd' );
   expect_c_( def.v[ 1 ] == 'e' );
   expect_c_( def.v[ 2 ] == 'f' );

   def.v[ 1 ] = 'x';
   expect_c_( def.v[ 1 ] == 'x' );

   // with struct values
   VarPointSlice points = slice_c_( Point, { .x=1, .y=2 }, { 3, 4 } );
   expect_c_( points.v[ 0 ].x == 1 );
   expect_c_( points.v[ 0 ].y == 2 );
   expect_c_( points.v[ 1 ].x == 3 );
   expect_c_( points.v[ 1 ].y == 4 );

   return finish_tap_c_();
}
