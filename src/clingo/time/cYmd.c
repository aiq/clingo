#include "clingo/time/cYmd.h"

#include "_/time/read_time_util.h"
#include "_/time/write_time_util.h"
#include "clingo/io/read.h"
#include "clingo/lang/algo.h"
#include "clingo/time/C_TimeFormats.h"
#include "clingo/type/int8.h"
#include "clingo/type/int32.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

cYmd ymd_c( int64_t year, int64_t month, int64_t day )
{
   cYmd ymd;
   if ( int64_to_int32_c( year, &(ymd.year) ) and
        int64_to_month_c( month, &(ymd.month) ) and
        int64_to_int8_c( day, &(ymd.day) ) )
   {
      return ymd;
   }

   return (cYmd){ INT32_MIN, c_Dec+1, INT8_MIN };
}

/*******************************************************************************
 cmp
*******************************************************************************/

int cmp_ymd_c( cYmd a, cYmd b )
{
   if ( !ymd_is_valid_c( a ) ) return -1;
   if ( !ymd_is_valid_c( b ) ) return 1;

   if ( a.year > b.year ) return 1;
   else if ( a.year < b.year ) return -1;

   if ( a.month > b.month ) return 1;
   else if ( a.month < b.month ) return -1;

   if ( a.day > b.day ) return 1;
   else if ( a.day < b.day ) return -1;

   return 0;
}

bool ymd_is_valid_c( cYmd ymd )
{
   int8_t monthDays = days_per_month_c_( ymd.month, ymd.year );
   return in_range_c_( 1, ymd.day, monthDays );
}

/*******************************************************************************
 io
*******************************************************************************/

bool read_ymd_c( cScanner sca[static 1],
                 cYmd ymd[static 1],
                 char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = C_IsoDate;
   }
   cScanner* fmtSca = &cstr_scanner_c_( fmt );
   int64_t oldPos = sca->pos;

   cYmd tmp = ymd_c( -1, -1, -1 );
   while ( fmtSca->space > 0 )
   {
      bool res = true;
      int64_t mark = fmtSca->pos;
      int64_t spaces = move_while_char_c( fmtSca, '_' ) ? fmtSca->pos - mark
                                                        : 0;

      mark = fmtSca->pos;
      if ( move_while_char_c( fmtSca, 'Y' ) ) //------------------------------ Y
      {
         res = intl_read_year_c( sca, &tmp.year, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'M' ) ) //------------------------- M
      {
         res = intl_read_month_c( sca, &tmp.month, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'D' ) ) //------------------------- D
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
   if ( not ymd_is_valid_c( tmp ) )
   {
      move_scanner_to_c( sca, oldPos );
      return set_scanner_error_c( sca, c_NotAbleToReadValue );
   }

   *ymd = tmp;
   return true;
}

bool write_ymd_c( cRecorder rec[static 1],
                  cYmd ymd,
                  char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = C_IsoDate;
   }
   cScanner* fmtSca = &cstr_scanner_c_( fmt );
   int64_t const oldPos = rec->pos;

   while ( fmtSca->space > 0 )
   {
      bool res = true;
      int64_t mark = fmtSca->pos;
      int64_t spaces = move_while_char_c( fmtSca, '_' ) ? fmtSca->pos - mark
                                                        : 0;

      mark = fmtSca->pos;
      if ( move_while_char_c( fmtSca, 'D' ) ) //------------------------------ D
      {
         res = intl_write_day_c( rec, ymd.day, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'M' ) ) //------------------------- M
      {
         res = intl_write_month_c( rec, ymd.month, fmtSca->pos - mark, spaces );
      }
      else if ( move_while_char_c( fmtSca, 'Y' ) ) //------------------------- Y
      {
         res = intl_write_year_c( rec, ymd.year, fmtSca->pos - mark );
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

static TAPE_C_( tape_func, cYmd, write_ymd_c, do_deref_c_ )
cTape ymd_tape_c( cYmd const* ymd )
{
   return (cTape){ .i=ymd, .f=tape_func };
}