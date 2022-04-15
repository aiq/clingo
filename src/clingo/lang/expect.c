#include "clingo/lang/expect.h"

#include <inttypes.h>
#include <stdarg.h>
#include <stdlib.h>

#include "clingo/type/cCharsToken.h"

/*******************************************************************************
 global test context
*******************************************************************************/

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

void tap_c( bool result )
{
   if ( result )
   {
      C_Success += 1;
      fprintf( C_LogFile, "ok %i\n", test_number() );
   }
   else
   {
      C_Failure += 1;
      fprintf( C_LogFile, "not ok %i\n", test_number() );
   }
}

void tap_desc_c( bool result, char const desc[static 1] )
{
   return tap_descf_c( result, "%s", desc );
}

void tap_descf_c( bool result, char const format[static 1], ... )
{
   if ( result )
   {
      C_Success += 1;
      fprintf( C_LogFile, "ok %i - ", test_number() );
   }
   else
   {
      C_Failure += 1;
      fprintf( C_LogFile, "not ok %i - ", test_number() );
   }
   va_list args;
   va_start( args, format );
   vfprintf( C_LogFile, format, args );
   va_end( args );
   putc( '\n', C_LogFile );
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

void tap_skip_c( bool result, char const reason[static 1] )
{
   if ( result )
   {
      C_Success += 1;
      fprintf( C_LogFile, "ok %i # skip %s\n", test_number(), reason );
   }
   else
   {
      C_Failure += 1;
      fprintf( C_LogFile, "not ok %i # skip %s\n", test_number(), reason );
   }
}

void tap_todo_c( bool result, char const explanation[static 1] )
{
   if ( result )
   {
      C_Success += 1;
      fprintf( C_LogFile, "ok %i # TODO %s\n", test_number(), explanation );
   }
   else
   {
      C_Failure += 1;
      fprintf( C_LogFile, "not ok %i # TODO %s\n", test_number(), explanation );
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
