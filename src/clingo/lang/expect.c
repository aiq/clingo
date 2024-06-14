#include "clingo/lang/expect.h"

#include <inttypes.h>
#include <stdarg.h>
#include <stdlib.h>

#include "clingo/type/cCharsToken.h"
#include "clingo/io/fwrite.h"
#include "clingo/io/print.h"

/*******************************************************************************
********************************************************* Types and Definitions 
*******************************************************************************

*******************************************************************************/

char const* C_TapDesc = " - ";
char const* C_TapSkip = " # SKIP ";
char const* C_TapTodo = " # TODO ";

static FILE* C_LogFile = NULL;
static int C_Success = 0;
static int C_Failure = 0;

/*******************************************************************************
 private util functions
*******************************************************************************/

static int test_number()
{
  return C_Success + C_Failure;
}

/*******************************************************************************
 public functions
*******************************************************************************/

void init_tap_c( const char name[static 1], FILE* output )
{
   C_LogFile = output;
   C_Success = 0;
   C_Failure = 0;

   cErrorStack* es = &error_stack_c_( 128 );
   if ( not fwriteln_c_( C_LogFile, es, "# {s}", name ) )
   {
      println_c_( "abort at tap init: {e}", es->err );
      exit( finish_tap_c_() );
   }
}

void tap_plan_c( int64_t n )
{
   cErrorStack* es = &error_stack_c_( 128 );
   if ( not fwriteln_c_( C_LogFile, es, "1..{i64}", n ) )
   {
      println_c_( "abort at tap plan: {e}", es->err );
      exit( finish_tap_c_() );
   }
}

static void intl_tap( bool result, int n, va_list list )
{
   cErrorStack* es = &error_stack_c_( 128 );
   if ( result )
   {
      C_Success += 1;
      if ( not fwrite_c_( C_LogFile, es, "ok {i64}", test_number() ) )
      {
         println_c_( "abort at test {i64}: {e}", test_number(), es->err );
         exit( finish_tap_c_() );
      }
      fwriteln_list_c( C_LogFile, es, n, list );
   }
   else
   {
      C_Failure += 1;
      fwrite_c_( C_LogFile, es, "not ok {i64}", test_number() );
      if ( not fwriteln_list_c( C_LogFile, es, n, list ) )
      {
         println_c_( "abort at test {i64}: {e}", test_number(), es->err );
         exit( finish_tap_c_() );
      }
   }
}

bool tap_c( bool result, int n, ... )
{
   va_list list;
   va_start( list, n );
   intl_tap( result, n, list );
   va_end( list );
   return result;
}

void tap_note_c( char const note[static 1] )
{
   cErrorStack* es = &error_stack_c_( 128 );
   cCharsToken tok = cstr_token_c_( note );
   while ( next_line_token_c( &tok ) )
   {
      if ( not fwriteln_c_( C_LogFile, es, "# {cs}", tok.x ) )
      {
         println_c_( "abort at note before {i64}: {e}", test_number()+1, es->err );
         exit( finish_tap_c_() );
      }
   }
}

int finish_tap_c( bool withPlan )
{
   if ( withPlan )
   {
      tap_plan_c( test_number() );
   }

   return C_Failure == 0 ? EXIT_SUCCESS
                         : EXIT_FAILURE;
}
