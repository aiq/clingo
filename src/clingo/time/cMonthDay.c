#include "clingo/time/cMonthDay.h"

#include "_/read_time_util.h"
#include "_/write_time_util.h"
#include "clingo/lang/algo.h"
#include "clingo/type/int8.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 overall
*******************************************************************************/

int cmp_month_day_c( cMonthDay a, cMonthDay b )
{
   if ( a.month > b.month ) return 1;
   else if ( a.month < b.month ) return -1;

   if ( a.day > b.day ) return 1;
   else if ( a.day < b.day ) return -1;

   return 0;
}

cMonthDay month_day_c( int64_t month, int64_t day )
{
   cMonthDay md;
   if ( int64_to_month_c( month, &(md.month) ) and
        int64_to_int8_c( day, &(md.day) ) )
   {
      return md;
   }

   return (cMonthDay){ c_Jan, INT8_MIN };
}

/*******************************************************************************
 io
*******************************************************************************/

bool read_month_day_c( cScanner sca[static 1],
                       cMonthDay md[static 1],
                       char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = "MMM._D";
   }
   cScanner* fmtSca = &cstr_scanner_c_( fmt );
   int64_t oldPos = sca->pos;

   cMonthDay tmp = month_day_c( -1, -1 );
   while ( fmtSca->space > 0 )
   {
      bool res = true;
      int64_t mark = fmtSca->pos;
      int64_t spaces = move_while_char_c( fmtSca, '_' ) ? fmtSca->pos - mark
                                                        : 0;

      mark = fmtSca->pos;
      if ( move_while_char_c( fmtSca, 'M' ) ) //------------------------------- M
      {
         res = intl_read_month_c( sca, &tmp.month, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'D' ) ) //-------------------------- D
      {
         res = intl_read_day_c( sca, &tmp.day, fmtSca->pos - mark, spaces );
      }
      else
      {
         res = intl_read_time_seperator_c( sca, fmtSca );
      }

      if ( not res )
      {
         move_scanner_to_c( sca, oldPos );
         return false;
      }
   }

   *md = tmp;
   return true;
}

bool write_month_day_c( cRecorder rec[static 1],
                        cMonthDay md,
                        char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = "MMM._D";
   }
   cScanner* fmtSca = &cstr_scanner_c_( fmt );
   int64_t oldPos = rec->pos;

   while( fmtSca->space > 0 )
   {
      bool res = true;
      int64_t mark = fmtSca->pos;
      int64_t spaces = move_while_char_c( fmtSca, '_' ) ? fmtSca->pos - mark
                                                        : 0;

      mark = fmtSca->pos;
      if ( move_while_char_c( fmtSca, 'D' ) ) //------------------------------- D
      {
         res = intl_write_hour_c( rec, md.day, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'M' ) ) //-------------------------- M
      {
         res = intl_write_month_c( rec, md.month, fmtSca->pos - mark, spaces );
      }
      else
      {
         res = intl_write_time_seperator_c( rec, fmtSca );
      }

      if ( not res )
      {
         move_recorder_to_c( rec, oldPos );
         return false;
      } 
   }

   return true;
}

static TAPE_C_( tape_func, cMonthDay, write_month_day_c, do_deref_c_ )
cTape month_day_tape_c( cMonthDay const* md )
{
   return (cTape){ .i=md, .f=tape_func };
}
