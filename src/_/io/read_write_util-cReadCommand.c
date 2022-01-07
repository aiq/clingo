#include "_/io/read_write_util.h"

#include <ctype.h>
#include "clingo/io/read_type.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

static inline c_check_char getCommandFunc( int c )
{
   switch ( c )
   {
      case 'a': return isalpha;
      case 'c': return iscntrl;
      case 'd': return isdigit;
      case 'g': return isgraph;
      case 'l': return islower;
      case 'o': return isprint;
      case 'p': return ispunct;
      case 's': return isspace;
      case 'u': return isupper;
      case 'w': return isalnum;
      case 'x': return isxdigit;
         break;
      default:
         return NULL;
         break;
   }
}

static inline int validCommandType( int c )
{
   return c == '/' or
          c == '[';
}

static inline int validCommandOp( int c )
{
   return c == '=' or
          c == '*' or
          c == '+' or
          c == '>' or
          c == '?';
}

static inline int validCommandFunc( int c )
{
   return getCommandFunc( c ) != NULL;
}

static bool read_in_special_sign( cScanner sca[static 1], cRune r[static 1] )
{
   if ( move_if_chars_c_( sca, "^^" ) )
   {
      *r = rune_c( "^" );
   }
   else if ( move_if_chars_c_( sca, "^}" ) )
   {
      *r = rune_c( "}" );
   }
   else if ( scan_rune_c( sca, r ) )
   {
      return true;
   }

   return false;
}

/*******************************************************************************

*******************************************************************************/

bool eq_read_command_c( cReadCommand const a[static 1],
                        cReadCommand const b[static 1] )
{
   if ( a->type != b->type ) return false;
   if ( a->op != b->op ) return false;
   if ( a->type == 'a' and not eq_chars_c( a->set, b->set ) )
      return false;
   
   if ( a->type == '/' and a->func != b->func )
      return false;

   if ( a->type == '[' and not eq_rune_range_c( a->range, b->range ) )
      return false;

   return true;
}

/******************************************************************************/

bool read_in_rune_range_c( cScanner sca[static 1], cRuneRange range[static 1] )
{
   int64_t const initPos = sca->pos;
   cChars rngStr;
   if ( not read_in_till_end_c( sca, &rngStr ) )
   {
      move_scanner_to_c( sca, initPos );
      return false;
   }
   cScanner* rngSca = &make_scanner_c_( rngStr.s, rngStr.v );

   uint32_t min;
   uint32_t max;
   if ( read_uint32_c( rngSca, &min, "x" ) and 
        move_if_char_c( rngSca, '-' ) and
        read_uint32_c( rngSca, &max, "x" ) )
   {
      *range = utf32_rune_range_c( min, max );
   }
   else
   {
      reset_scanner_c( rngSca );
      cRune min;
      cRune max;
      if ( read_in_special_sign( rngSca, &min ) and
           read_in_special_sign( rngSca, &max ) )
      {
         *range = build_rune_range_c( min, max );
      }
      else
      {
         move_scanner_to_c( sca, initPos );
         return false;
      }
   }

   if ( rngSca->space > 0 )
   {
      return false;
   }

   return true;
}

/******************************************************************************/

bool handle_read_command_c( cScanner sca[static 1],
                            cReadCommand const cmd[static 1] )
{
   if ( cmd->op == '>' )
   {
      if ( cmd->type == 'a')
      {
         return move_to_any_rune_c( sca, cmd->set );
      }
      else if ( cmd->type == '/' )
      {
         c_check_char func = getCommandFunc( cmd->func );
         if ( not func ) return false;

         return move_to_char_match_c( sca, func );
      }
      else if ( cmd->type == '[' )
      {
         return move_to_in_range_c( sca, cmd->range );
      }
   }
   else if ( cmd->op == '=' or cmd->op == '?' )
   {
      bool res = false;

      if ( cmd->type == 'a')
      {
         res = move_if_any_rune_c( sca, cmd->set );
      }
      else if ( cmd->type == '/' )
      {
         c_check_char func = getCommandFunc( cmd->func );
         if ( not func ) return false;

         res = move_if_char_match_c( sca, func );
      }
      else if ( cmd->type == '[' )
      {
         res = move_if_in_range_c( sca, cmd->range );
      }

      return cmd->op == '=' ? res
                            : true;
      return true;
   }
   else if ( cmd->op == '+' or cmd->op == '*' )
   {
      bool res = false;

      if ( cmd->type == 'a')
      {
         res = move_while_any_rune_c( sca, cmd->set );
      }
      else if ( cmd->type == '/' )
      {
         c_check_char func = getCommandFunc( cmd->func );
         if ( not func ) return false;

         res = move_while_char_match_c( sca, func );
      }
      else if ( cmd->type == '[' )
      {
         res = move_while_in_range_c( sca, cmd->range );
      }

      return cmd->op == '+' ? res
                            : true;
   }

   return false;
}

/*******************************************************************************

*******************************************************************************/

bool read_in_read_command_c( cScanner sca[static 1],
                             cReadCommand cmd[static 1] )
{
   must_exist_c_( sca );
   must_exist_c_( cmd );

   reset_read_command_c( cmd );

   if ( sca->space < 4 )
   {
      return false;
   }

   int64_t const initPos = sca->pos;

   if ( not move_if_char_c( sca, '{' ) ) // --------------------------------- {
   {
      return false;
   }

   char const* typeStr = sca->mem;
   if ( not move_if_char_match_c( sca, validCommandType ) ) // ------------ type
   {
      typeStr = "a";
   }
   cmd->type = *typeStr;

   char const* opStr = sca->mem; // ----------------------------------------- op
   if ( not move_if_char_match_c( sca, validCommandOp ) )
   {
      move_scanner_to_c( sca, initPos );
      return false;
   }
   cmd->op = *opStr;

   if ( cmd->type == '/' ) // --------------------------------------------- func
   {
      char const* funcStr = sca->mem;
      if ( not move_if_char_match_c( sca, validCommandFunc ) )
      {
         move_scanner_to_c( sca, initPos );
         return false;
      }
      cmd->func = *funcStr;
   }
   else if ( cmd->type == '[' ) // --------------------------------------- range
   {
      if ( not read_in_rune_range_c( sca, &cmd->range ) )
      {
         move_scanner_to_c( sca, initPos );
         return false;
      }
   }
   else if ( cmd->type == 'a' ) // ---------------------------------------- set
   {
      cChars setStr;
      if ( not read_in_till_end_c( sca, &setStr ) )
      {
         move_scanner_to_c( sca, initPos );
         return false;
      }
      cmd->set = setStr;
   }
   else
   {
      move_scanner_to_c( sca, initPos );
      return false;
   }

   if ( not move_if_char_c( sca, '}' ) ) // --------------------------------- }
   {
      move_scanner_to_c( sca, initPos );
      return false;
   }

   return true;
}

/******************************************************************************/

void reset_read_command_c( cReadCommand cmd[static 1] )
{
   must_exist_c_( cmd );

   cmd->type = ' ';
   cmd->op = ' ';
}