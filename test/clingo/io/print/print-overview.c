#include "clingo/io/print.h"
#include "clingo/time/cTime.h"

#define pln_( ... ) pjotln_c_( xyz, 256, __VA_ARGS__ )

#define printfln_( ... ) println_c_( asdf, 256, __VA_ARGS__ )

int main( void )
{
   cRecorder* timeRec = &recorder_c_( 32 );
   write_time_c_( timeRec, local_time_c() );

   pln_( c_c( "hello World!" ), " today is ", timeRec, " that is ", true, "!" );

   printfln_( "{cs:q} today is {rec} ", c_c( "hello world!" ), timeRec,
              "that is {bool:Cc}!", true );
}