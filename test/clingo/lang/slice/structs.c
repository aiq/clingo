#include "clingo/lang/slice.h"
#include "clingo/lang/expect.h"

//************************************** example struct
struct Point
{
   int64_t x;
   int64_t y;
};

typedef struct Point Point;

SLICE_DEF_C_(
   Point,         
   PointSlice,
   VarPointSlice
)
//**************************************

int main( void )
{
   init_tap_c_();

   VarPointSlice slice = structs_c_( 3, Point );
   slice.v[ 0 ] = (Point){ .x=1, .y=200 };
   slice.v[ 1 ] = (Point){ 3000, 44 };
   slice.v[ 2 ].x = -55;
   slice.v[ 2 ].y = 666;

   expect_c_( slice.s == 3 );
   expect_c_( slice.v[ 0 ].x ==    1 );
   expect_c_( slice.v[ 0 ].y ==  200 );
   expect_c_( slice.v[ 1 ].x == 3000 );
   expect_c_( slice.v[ 1 ].y ==   44 );
   expect_c_( slice.v[ 2 ].x ==  -55 );
   expect_c_( slice.v[ 2 ].y ==  666 );

   // wrong code we acces the memory outside the array
   // slice.v[ 3 ] = (Point){ .x=999 };

   return finish_tap_c_();
}
