#include "clingo/lang/expect.h"

#include <inttypes.h>
#include <stdarg.h>
#include <stdlib.h>

#include "clingo/type/cCharsToken.h"
#include "clingo/io/fwrite.h"

/*******************************************************************************
 global test context
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

   fprintf( C_LogFile, "# %s\n", name );
}

void tap_plan_c( int64_t n )
{
   fprintf( C_LogFile, "1..%"PRIi64"\n", n );
}

static void intl_tap( bool result, int n, va_list list )
{
   cErrorStack* es = &error_stack_c_( 128 );
   if ( result )
   {
      C_Success += 1;
      fwrite_c_( C_LogFile, es, "ok {i64}", test_number() );
      fwriteln_list_c( C_LogFile, es, n, list );
   }
   else
   {
      C_Failure += 1;
      fwrite_c_( C_LogFile, es, "not ok {i64}", test_number() );
      fwriteln_list_c( C_LogFile, es, n, list );
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
   cCharsToken tok;
   init_cstr_token_c( &tok, note );
   while ( next_token_till_char_c( &tok, '\n' ) )
   {
      fputc( '#', C_LogFile );
      fputc( ' ', C_LogFile );
      for_each_c_( char const*, c, tok.x )
      {
         fputc( *c, C_LogFile );
      }
      fputc( '\n', C_LogFile );
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
