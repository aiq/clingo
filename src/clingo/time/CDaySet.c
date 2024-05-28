#include "clingo/time/CDaySet.h"

#include <errno.h>
#include <stdio.h>

#include "clingo/container/CBitVec.h"
#include "clingo/io/print.h"
#include "clingo/io/write.h"
#include "clingo/io/write_type.h"

#define pln_( ... ) pjotln_c_( xyz, 256, __VA_ARGS__ )

/*******************************************************************************

*******************************************************************************/

struct CDaySet
{
   cDatePeriod active;
   cDatePeriod full;
   CBitVec* bits;
};

static inline void cleanup( void* instance )
{
   CDaySet* set = instance;
   if ( set->bits )
   {
      release_c( set->bits );
   }
}

cMeta const C_DaySetMeta = {
   .desc = stringify_c_( CDaySet ),
   .cleanup = &cleanup
};

/*******************************************************************************

*******************************************************************************/

static int64_t date_to_index( CDaySet const* set, cDate date )
{
   if ( !date_is_valid_c( date ) ) return -1;

   return days_between_dates_c( set->full.first, date );
}

static cDate index_to_date( CDaySet const* set, int64_t index )
{
   if ( index == -1 ) return null_date_c();

   return add_days_to_date_c( set->full.first, index );
}

/*******************************************************************************

*******************************************************************************/

static CDaySet* build_day_set( cDatePeriod period )
{
   int64_t days = date_period_days_c( period );

   CDaySet* result = new_object_c_( CDaySet, &C_DaySetMeta );
   if( result == NULL )
   {
      return NULL;
   }

   result->bits = new_bit_vec_c( days );
   if ( result->bits == NULL )
   {
      release_c( result );
      return NULL;
   }

   result->full = period;
   result->active = null_date_period_c();

   return result;
}

CDaySet* new_day_set_c()
{
   cDate d = add_days_to_date_c( utc_date_c(), -183 );
   return build_day_set( sized_date_period_c( d, 365 ) );
}

CDaySet* target_day_set_c( cDatePeriod period )
{
   if ( not date_period_is_valid_c( period ) ) return NULL;

   return build_day_set( period );
}

/*******************************************************************************

*******************************************************************************/

int64_t count_days_c( const CDaySet* set )
{
   must_exist_c_( set );
   return popcount_bit_vec_c( set->bits, 1 );
}

bool day_set_is_empty_c( const CDaySet* set )
{
   must_exist_c_( set );
   return not date_is_valid_c( set->active.first );
}

cDatePeriod day_set_period_c( const CDaySet* set )
{
   must_exist_c_( set );
   return date_period_c( set->active.first, set->active.last );
}

/*******************************************************************************

*******************************************************************************/

cDate first_in_day_set_c( CDaySet const* set )
{
   must_exist_c_( set );
   return set->active.first;
}

cDate last_in_day_set_c( CDaySet const* set )
{
   must_exist_c_( set );
   return set->active.last;
}

cDate next_in_day_set_c( CDaySet const* set, cDate date )
{
   must_exist_c_( set );
   if ( not date_is_valid_c( date ) or
        gte_c( cmp_date_c( date, set->active.last ) ) ) return null_date_c();

   int64_t oldIdx = date_to_index( set, late_date_c( date, set->full.first ) );
   int64_t newIdx = find_index_of_bit_c( set->bits, 1, oldIdx + 1 ); 
   return index_to_date( set, newIdx );
}

cDate prev_in_day_set_c( CDaySet const* set, cDate date )
{
   must_exist_c_( set );
   if ( not date_is_valid_c( date ) or
        lte_c( cmp_date_c( date, set->active.first ) ) ) return null_date_c();
   
   int64_t oldIdx = date_to_index( set, early_date_c( date, set->full.last ) );
   int64_t newIdx = rfind_index_of_bit_c( set->bits, 1, oldIdx - 1 );
   return index_to_date( set, newIdx );
}

/*******************************************************************************

*******************************************************************************/

bool date_period_in_day_set_c( CDaySet const* set, cDatePeriod period )
{
   must_exist_c_( set );

   if ( not date_period_is_valid_c( period ) ) return false;

   if ( not is_sub_date_period_c( set->active, period ) ) return false;

   int64_t firstIndex = date_to_index( set, period.first );
   int64_t lastIndex = date_to_index( set, period.last );
   for ( int64_t i = firstIndex; i <= lastIndex; i++ )
   {
      if ( get_from_bit_vec_c( set->bits, i ) != 1 ) return false;
   }

   return true;
}

bool days_in_day_set_c( CDaySet const* set, CDaySet const* days )
{
   must_exist_c_( set );
   must_exist_c_( days );

   iterate_day_set_c_( d, days )
   {
      if ( not in_day_set_c( set, d ) ) return false;
   }

   return true;
}

bool in_day_set_c( CDaySet const* set, cDate date )
{
   must_exist_c_( set );

   if ( not date_is_valid_c( date ) ) return false;

   if ( not in_date_period_c( set->active, date ) ) return false;

   cByte bit = get_from_bit_vec_c( set->bits, date_to_index( set, date ) );
   return ( bit == 1 );
}

/*******************************************************************************

*******************************************************************************/

static inline bool rearrange_day_set( CDaySet* set, cDatePeriod period )
{
   cDatePeriod newPeriod;
   {
      int64_t reqDays = date_period_days_c( period );
      cDate first = add_days_to_date_c( period.first, -1*( reqDays / 2 ) );
      newPeriod = sized_date_period_c( first, 2*reqDays );
   }

   int64_t bitsN = date_period_days_c( newPeriod );
   CBitVec* newBits = new_bit_vec_c( bitsN );
   if ( newBits == NULL ) return false;

   int64_t delta = days_between_dates_c( newPeriod.first, set->full.first );
   for ( int64_t i = find_index_of_bit_c( set->bits, 1, 0 );
         i != -1;
         i = find_index_of_bit_c( set->bits, 1, i ) )
   {
      set_on_bit_vec_c( newBits, delta + i, 1 );
   }

   release_c( set->bits );
   set->bits = newBits;
   set->full = newPeriod;
   cDate first = index_to_date( set, find_index_of_bit_c( set->bits, 1, 0 ) );
   cDate last = index_to_date( set, rfind_index_of_bit_c( set->bits, 1, bitsN-1 ) );
   set->active = date_period_c( first, last );

   return true;
}

bool set_date_period_on_day_set_c( CDaySet* set, cDatePeriod period )
{
   must_exist_c_( set );

   if ( not date_period_is_valid_c( period ) ) return true;

   if ( not is_sub_date_period_c( set->full, period ) )
   {
      cDatePeriod reqPeriod = unite_date_periods_c( set->full, period );
      if ( not rearrange_day_set( set, reqPeriod ) ) return false;
   }

   cRange range = closed_range_c_( date_to_index( set, period.first ),
                                   date_to_index( set, period.last ) );
   set_range_on_bit_vec_c( set->bits, range, 1 );
   set->active = unite_date_periods_c( set->active, period );

   return set;
}

bool set_days_on_day_set_c( CDaySet* set, CDaySet const* days )
{
   must_exist_c_( set );
   must_exist_c_( days );

   if ( day_set_is_empty_c( days ) ) return true;

   if ( not is_sub_date_period_c( set->full, days->active ) )
   {
      cDatePeriod reqPeriod = unite_date_periods_c( set->full, days->active );
      if ( not rearrange_day_set( set, reqPeriod ) ) return false;
   }

   set->active = unite_date_periods_c( set->active, days->active );
   iterate_day_set_c_( day, days )
   {
      int64_t idx = date_to_index( set, day );
      set_on_bit_vec_c( set->bits, idx, 1 );
   }
   return set;
}

bool set_many_on_day_set_c( CDaySet* set, cDateSlice slice )
{
   cDatePeriod bound = determine_date_period_c( slice );

   if ( not is_sub_date_period_c( set->full, bound ) )
   {
      cDatePeriod reqPeriod = unite_date_periods_c( set->full, bound );
      if ( not rearrange_day_set( set, reqPeriod ) ) return false;
   }

   for_each_c_( cDate const*, date, slice )
   {
      set_on_day_set_c( set, *date );
   }

   return true;
}

bool set_on_day_set_c( CDaySet* set, cDate date )
{
   must_exist_c_( set );

   if ( not date_is_valid_c( date ) ) return true;

   return set_date_period_on_day_set_c( set, single_date_period_c( date ) );
}

/*******************************************************************************

*******************************************************************************/

void remove_date_period_from_day_set_c( CDaySet* set, cDatePeriod period )
{
   must_exist_c_( set );

   if ( not date_period_is_valid_c( period ) ) return;

   cDatePeriod intersection = intersect_date_periods_c( set->active, period );
   if ( not date_period_is_valid_c( intersection ) ) return;

   cRange range = closed_range_c_( date_to_index( set, intersection.first ),
                                   date_to_index( set, intersection.last ) );
   set_range_on_bit_vec_c( set->bits, range, 0 );

   if ( in_date_period_c( intersection, set->active.first ) )
   {
      set->active.first = next_in_day_set_c( set, set->active.first );
   }
   else if ( in_date_period_c( intersection, set->active.last ) )
   {
      set->active.last = prev_in_day_set_c( set, set->active.last );
   }
}

void remove_days_from_day_set_c( CDaySet* set, CDaySet const* days )
{
   must_exist_c_( set );
   must_exist_c_( days );

   if ( day_set_is_empty_c( days ) ) return;

   if ( not date_periods_overlap_c( set->active, days->active ) ) return;

   iterate_day_set_c_( day, days )
   {
      remove_from_day_set_c( set, day );
   }
}

void remove_from_day_set_c( CDaySet* set, cDate date )
{
   must_exist_c_( set );

   if ( not in_day_set_c( set, date ) ) return;

   int64_t idx = date_to_index( set, date );
   set_on_bit_vec_c( set->bits, idx, 0 );
   if ( eq_date_c( set->active.first, date ) )
   {
      set->active.first = next_in_day_set_c( set, set->active.first );
   }
   else if ( eq_date_c( set->active.last, date ) )
   {
      set->active.last = prev_in_day_set_c( set, set->active.last );
   }
}

/*******************************************************************************
 io
*******************************************************************************/

static inline bool jot_date_period( cRecorder rec[static 1],
                                    cDatePeriod period )
{
   return record_chars_c_( rec, "[" ) and
          write_date_c_( rec, period.first ) and
          record_chars_c_( rec, ".." ) and
          write_date_c_( rec, period.last ) and
          record_chars_c_( rec, "]" );
}

static inline bool write_zip_value( cRecorder rec[static 1],
                                    cByte val,
                                    int64_t n )
{
   if ( n == 1 )
   {
      char c = val ? '+'
                   : '_';
      return record_char_c( rec, c );
   }
   else
   {
      char c = val ? 'i'
                   : 'z';
      return write_int64_c_( rec, n ) and record_char_c( rec, c );
   }
}

bool write_day_set_c( cRecorder rec[static 1],
                      CDaySet const* set,
                      char const fmt[static 1] )
{
   must_exist_c_( rec );
   must_exist_c_( set );
   must_exist_c_( fmt );

   if ( day_set_is_empty_c( set ) )
   {
      return record_chars_c_( rec, "'empty'" )
               ? true
               : set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
   }

   cChars const fmtCs = c_c( fmt );
   int64_t const oldPos = rec->pos;
   // ---------------------------------------------------------------------- zip
   if ( chars_is_c( fmtCs, "zip" ) )
   {
      once_c_( xyz )
      {
         if ( not write_date_c_( rec, set->active.first ) ) break;

         if ( not record_char_c( rec, '(' ) ) break;

         int64_t first = date_to_index( set, set->active.first );
         int64_t last = date_to_index( set, set->active.last );

         cByte prevVal = get_from_bit_vec_c( set->bits, first );
         int64_t counter = 1;
         for ( int64_t i = first+1; i <= last; ++i )
         {
            cByte currVal = get_from_bit_vec_c( set->bits, i );

            if ( currVal == prevVal )
            {
               ++counter;
            }
            else
            {
               if ( not write_zip_value( rec, prevVal, counter ) ) break;

               prevVal = currVal;
               counter = 1;
            }
         }
         if ( not write_zip_value( rec, prevVal, counter ) ) break;

         if ( not record_char_c( rec, ')' ) ) break;

         return true;
      }

      move_recorder_to_c( rec, oldPos );
      return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
   }

   // ---------------------------------------------------------------------- dbg
   if ( chars_is_c( fmtCs, "dbg" ) )
   {
      if ( record_chars_c_( rec, "{ .active=" ) and
           jot_date_period( rec, set->active ) and
           record_chars_c_( rec, ", .full=" ) and
           jot_date_period( rec, set->full ) and
           record_chars_c_( rec, ", .bits=" ) and
           write_bit_vec_c( rec, set->bits, "dbg" ) and
           record_chars_c_( rec, " }" ) )
      {
         return true;
      }
      else
      {
         move_recorder_to_c( rec, oldPos );
         return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
      }
   }

   // ------------------------------------------------------------------- format

   cChars charSet = c_c( ".1" ); // ----------------------------------- charSet
   {
      if ( fmtCs.s == 0 )
      {
         // same as default
      }
      else if ( fmtCs.s == 2 )
      {
         charSet = fmtCs;
      }
      else
      {
         return set_recorder_error_c( rec, c_InvalidWriteFormat );
      }
   }

   pln_( "charSet: '", charSet, "'" );

   cDate date = set->active.first;
   int64_t lastActiveIdx = date_to_index( set, set->active.last );
   while ( date_is_valid_c( date ) )
   {
      cYmd const ymd = as_ymd_c( date );
      int8_t const dpm = days_per_month_c_( ymd.month, ymd.year );
      cDate const firstDate = date_c( ymd.year, ymd.month, 1 );
      cDate const lastDate = date_c( ymd.year, ymd.month, dpm );
      c_Weekday firstWd = date_weekday_c( firstDate );

      int64_t firstIdx = date_to_index( set, firstDate );
      if ( firstIdx == -1 )
      {
         int64_t delta = days_between_dates_c( firstDate, date );
         firstIdx = date_to_index( set, date ) - delta;
      }
      int64_t lastIdx = date_to_index( set, lastDate );
      if ( lastIdx == -1 )
      {
         int64_t delta = days_between_dates_c( date, lastDate );
         lastIdx = date_to_index( set, date ) + delta;
      }
      
      bool res = true;
      {
         res &= write_ymd_c( rec, ymd, "YYYY.MM:" );

         c_Weekday wd = c_Mon;
         while ( res and wd != firstWd )
         {
            if ( wd == c_Mon )
            {
               res &= record_char_c( rec, ' ' );
            }
            res &= record_char_c( rec, ' ' );
            wd = next_weekday_c( wd );
         }
         println_recorded_c( rec );
         for ( int64_t i = firstIdx; res and i <= lastIdx; ++i )
         {
            char c = charSet.v[0];
            if ( in_range_c_( 0, i, lastActiveIdx ) )
            {
               c = get_from_bit_vec_c( set->bits, i ) ? charSet.v[1]
                                                      : charSet.v[0];
            }

            if ( wd == c_Mon or wd == c_Sat )
            {
               res &= record_char_c( rec, ' ' );
            }
            res &= record_char_c( rec, c );
            wd = next_weekday_c( wd );
         }
         res &= record_char_c( rec, '\n' );
      }
      if ( not res )
      {
         move_recorder_to_c( rec, oldPos );
         return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
      }

      date = next_in_day_set_c( set, lastDate );
   }

   return true;
}
