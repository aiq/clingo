#include "clingo/time/cDuration.h"

#include "_/time/write_time_util.h"
#include "clingo/io/read.h"
#include "clingo/io/read_type.h"
#include "clingo/io/write.h"
#include "clingo/time/C_TimeFormats.h"
#include "clingo/type/cCharsSlice.h"
#include "clingo/type/int8.h"
#include "clingo/type/int32.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/


SLICE_IMPL_C_(
   cDuration,           // Type
   cDurationSlice,      // SliceType
   duration_slice_c,    // FuncName
   cVarDurationSlice,   // VarSliceType
   var_duration_slice_c // VarFuncName
)

/*******************************************************************************
 definitions
*******************************************************************************/

static int64_t const NullDurationValue = INT64_MIN;

int64_t const C_Week = 7LL*24LL*60LL*60LL*1000LL*1000LL*1000LL;
int64_t const C_Day  = 24LL*60LL*60LL*1000LL*1000LL*1000LL;
int64_t const C_Hour = 60LL*60LL*1000LL*1000LL*1000LL;
int64_t const C_Min  = 60LL*1000LL*1000LL*1000LL;
int64_t const C_Sec  = 1000LL*1000LL*1000LL;
int64_t const C_Msec = 1000LL*1000LL;
int64_t const C_Usec = 1000LL;
int64_t const C_Nsec = 1LL;

cDuration const C_MaxDuration = (cDuration){ INT64_MAX };

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

cDuration duration_c( int64_t h, int64_t m, int64_t s, int64_t n )
{
   cDuration dur = hours_c( h );
   dur = add_duration_c( dur, mins_c( m ) );
   dur = add_duration_c( dur, secs_c( s ) );
   dur = add_duration_c( dur, nsecs_c( n ) );

	return dur;
}

#define UNIT_DURATION_FUNC_C_( FuncName, Unit )                                \
cDuration FuncName( int64_t inp )                                              \
{                                                                              \
   int64_t val = NullDurationValue;                                            \
   imul64_c( inp, Unit, &val );                                                \
   return nsecs_c( val );                                                      \
}
UNIT_DURATION_FUNC_C_( weeks_c, C_Week )
UNIT_DURATION_FUNC_C_( days_c,  C_Day  )
UNIT_DURATION_FUNC_C_( hours_c, C_Hour )
UNIT_DURATION_FUNC_C_( mins_c,  C_Min  )
UNIT_DURATION_FUNC_C_( secs_c,  C_Sec  )
UNIT_DURATION_FUNC_C_( msecs_c, C_Msec )
UNIT_DURATION_FUNC_C_( usecs_c, C_Usec )

cDuration nsecs_c( int64_t nsecs )
{
   return (cDuration){ ._v = nsecs };
}

extern inline cDuration null_duration_c( void );

/*******************************************************************************
 from
*******************************************************************************/

extern inline cDuration duration_from_hmsn_c( cHmsn hmsn );

cHmsn hmsn_from_duration_c( cDuration dur )
{
   int64_t reduce = 0;

   int64_t const h = as_hours_c( dur );
   reduce = to_time_unit_c( h, C_Hour, C_Min );

   int64_t const m = as_mins_c( dur ) - reduce;
   reduce = to_time_unit_c( reduce, C_Min, C_Sec );
   reduce += to_time_unit_c( m, C_Min, C_Sec );

   int64_t const s = as_secs_c( dur ) - reduce;
   reduce = to_time_unit_c( reduce, C_Sec, C_Nsec );
   reduce += to_time_unit_c( s, C_Sec, C_Nsec );

   int64_t const n = as_nsecs_c( dur ) - reduce;

   return hmsn_c( h, m, s, n );
}

/*******************************************************************************
 conv
*******************************************************************************/

#define DURATION_AS_FUNC_C_( FuncName, Unit )                                  \
int64_t FuncName( cDuration dur )                                              \
{                                                                              \
   if ( !duration_is_valid_c( dur ) ) return 0;                                \
                                                                               \
   return to_time_unit_c( dur._v, C_Nsec, Unit );                              \
}

DURATION_AS_FUNC_C_( as_weeks_c, C_Week )
DURATION_AS_FUNC_C_( as_days_c,  C_Day )
DURATION_AS_FUNC_C_( as_hours_c, C_Hour )
DURATION_AS_FUNC_C_( as_mins_c, C_Min )
DURATION_AS_FUNC_C_( as_secs_c,  C_Sec )
DURATION_AS_FUNC_C_( as_msecs_c, C_Msec )
DURATION_AS_FUNC_C_( as_usecs_c, C_Usec )

int64_t as_nsecs_c( cDuration dur )
{
   if ( !duration_is_valid_c( dur ) ) return 0;

   return dur._v;
}

extern inline int64_t to_time_unit_c( int64_t val, int64_t from, int64_t to );

/*******************************************************************************
 overall
*******************************************************************************/

cDuration add_duration_c( cDuration a, cDuration b )
{
   if ( not duration_is_valid_c( a ) or
        not duration_is_valid_c( b ) ) return null_duration_c();

   int64_t val = NullDurationValue;
   iadd64_c( a._v, b._v, &val );
   return (cDuration){ ._v = val };
}

cDuration between_durations_c( cDuration a, cDuration b )
{
   return add_duration_c( b, invert_duration_c( a ) );
}

int cmp_duration_c( cDuration a, cDuration b )
{
   return cmp_int64_c( a._v, b._v );
}

extern inline bool duration_is_valid_c( cDuration dur );

extern inline bool eq_duration_c( cDuration a, cDuration b );

extern inline cDuration invert_duration_c( cDuration dur );

cDuration truncate_duration_c( cDuration dur,
                               int64_t fac,
                               cDuration tail[static 1] )
{
   if ( fac <= 0 ) return dur;

   *tail = (cDuration){ dur._v % fac };
   return (cDuration){ dur._v - tail->_v };
}

/*******************************************************************************
 io
*******************************************************************************/

struct fmtCheck
{
   char l;
   char const* ls;
   char U;
   char const* Us;
};
typedef struct fmtCheck fmtCheck;
fmtCheck wWCheck = (fmtCheck){ 'w', "w", 'W', "W" };
fmtCheck dDCheck = (fmtCheck){ 'd', "d", 'D', "D" };
fmtCheck hHCheck = (fmtCheck){ 'h', "h", 'H', "H" };
fmtCheck mMCheck = (fmtCheck){ 'm', "m", 'M', "M" };
fmtCheck sSCheck = (fmtCheck){ 's', "s", 'S', "S" };
fmtCheck iICheck = (fmtCheck){ 'i', "ms", 'I', "MS" };
fmtCheck uUCheck = (fmtCheck){ 'u', "µs", 'U', "µS" };
fmtCheck nNCheck = (fmtCheck){ 'n', "ns", 'N', "NS" };

//******************************************************************************

struct fmtInfo
{
   int64_t n;
   char const* s;
};
typedef struct fmtInfo fmtInfo;
static bool init_info( cScanner sca[static 1], fmtCheck check, fmtInfo i[static 1] )
{
   int64_t p = sca->pos;
   i->s = move_while_char_c( sca, check.l ) ? check.ls :
          move_while_char_c( sca, check.U ) ? check.Us :
                                              "";
   i->n = sca->pos - p;
   return ( i->n <= 2 );
}
//******************************************************************************
static bool inv_err( cScanner sca[static 1], int64_t oldPos )
{
   move_scanner_to_c( sca, oldPos );
   return scan_error_c( sca, c_InvalidReadFormat );
}
static bool not_able_to_read_value( cScanner sca[static 1], int64_t oldPos )
{
   move_scanner_to_c( sca, oldPos );
   return scan_error_c( sca, c_NotAbleToReadValue );
}
struct scanValue
{
   bool hasSep;
   int64_t val;
   bool hasDot;
   int64_t nsecs;
   int64_t nsecsDigits;
   cChars type;
};
typedef struct scanValue scanValue;
static bool scan_value( cScanner sca[static 1], scanValue inp[static 1] )
{
   inp->hasSep = move_if_char_c( sca, ' ' );
   if ( not read_int64_c_( sca, &(inp->val) ) ) return false;
   if ( inp->val < 0 ) return false;

   inp->hasDot = move_if_char_c( sca, '.' );
   if ( inp->hasDot )
   {
      cScanMarker* marker = &scan_marker_c_( sca );
      if ( not read_int64_c_( sca, &(inp->nsecs) ) )return false;
      if ( inp->nsecs < 0 ) return false;

      inp->nsecsDigits = trace_scan_c( marker, true );
      if ( inp->nsecsDigits > 9 ) return false;
   }
   else
   {
      inp->nsecs = 0;
      inp->nsecsDigits = 0;
   }

   char const* typeBeg = sca->mem;
   if ( not ( move_if_chars_c_( sca, "ms" ) or move_if_chars_c_( sca, "MS" ) or
              move_if_chars_c_( sca, "µs" ) or move_if_chars_c_( sca, "µS" ) or
              move_if_chars_c_( sca, "ns" ) or move_if_chars_c_( sca, "NS" ) or
              move_if_any_char_c_( sca, "wWdDhHmMsS" ) ) )
   {
      inp->type = c_c( "" );
      return false;
   }
   char const* typeEnd = sca->mem;
   inp->type = make_chars_c( typeBeg, typeEnd );

   return true;
}
static bool add_var_nsecs( cDuration dur[static 1],
                           int64_t expDigits,
                           int64_t nsecs,
                           int64_t nsecsDigits )
{
   if ( nsecsDigits > expDigits ) return false;

   for ( int64_t i = nsecsDigits; i < expDigits; ++i )
   {
      nsecs *= 10;
   }

   *dur = add_duration_c( *dur, nsecs_c( nsecs ) );
   return true;
}
bool read_duration_c( cScanner sca[static 1],
                      cDuration dur[static 1],
                      char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = C_DurationFormat;
   }
   cScanMarker* smFmt = &scan_marker_c_( &cstr_scanner_c_( fmt ) );
   int64_t oldPos = sca->pos;

   fmtInfo info;
   int64_t sign = move_if_char_c( sca, '-' ) ? -1
                                             : 1;
   cDuration tmp = nsecs_c( 0 );

   while ( smFmt->x->space > 0 )
   {

      scanValue inp;
      if ( not scan_value( sca, &inp ) )
         return not_able_to_read_value( sca, oldPos );

      if ( inp.hasSep and not move_if_char_c( smFmt->x, ' ' ) )
         return not_able_to_read_value( sca, oldPos );

      if ( inp.hasDot )
      {
         cChars tail = view_chars_c( smFmt->x, smFmt->x->space );
         if ( chars_is_c( tail, "*l" ) or chars_is_c( tail, "*U" ) )
         {
            if ( chars_is_any_c_( inp.type, "s", "S" ) )
            {
               tail = c_c( "ss.n" );
            }
            else if ( chars_is_any_c_( inp.type, "ms", "MS" ) )
            {
               tail = c_c( "ii.n" );
            }
            else if ( chars_is_any_c_( inp.type, "µs", "µS" ) )
            {
               tail = c_c( "uu.n" );
            }
         }

         if ( chars_is_any_c_( tail, "ss.n", "SS.N" ) )
         {
            if ( not chars_is_any_c_( inp.type, "s", "S" ) )
               return not_able_to_read_value( sca, oldPos );

            tmp = add_duration_c( tmp, secs_c( inp.val ) );
            if ( not add_var_nsecs( &tmp, 9, inp.nsecs, inp.nsecsDigits ) )
               return not_able_to_read_value( sca, oldPos );
         }
         else if ( chars_is_any_c_( tail, "ii.n", "II.N" ) )
         {
            if ( not chars_is_any_c_( inp.type, "ms", "MS" ) )
               return not_able_to_read_value( sca, oldPos );

            tmp = add_duration_c( tmp, msecs_c( inp.val ) );
            if ( not add_var_nsecs( &tmp, 6, inp.nsecs, inp.nsecsDigits ) )
               return not_able_to_read_value( sca, oldPos );
         }
         else if ( chars_is_any_c_( tail, "uu.n", "UU.N" ) )
         {
            if ( not chars_is_any_c_( inp.type, "µs", "µS" ) )
               return not_able_to_read_value( sca, oldPos );

            tmp = add_duration_c( tmp, usecs_c( inp.val ) );
            if ( not add_var_nsecs( &tmp, 3, inp.nsecs, inp.nsecsDigits ) )
               return not_able_to_read_value( sca, oldPos );
         }
         else
         {
            return inv_err( sca, oldPos );
         }
      }
      else
      {
         //------------------------------------------------------------------ wW
         if ( not init_info( smFmt->x, wWCheck, &info ) )
            return inv_err( sca, oldPos );

         if ( chars_is_c( inp.type, info.s ) )
         {
            tmp = add_duration_c( tmp, weeks_c( inp.val ) );
            continue;
         }
         else if ( info.n == 2 )
            return not_able_to_read_value( sca, oldPos );

         //------------------------------------------------------------------ dD
         if ( not init_info( smFmt->x, dDCheck, &info ) )
            return inv_err( sca, oldPos );

         if ( chars_is_c( inp.type, info.s ) )
         {
            tmp = add_duration_c( tmp, days_c( inp.val ) );
            continue;
         }
         else if ( info.n == 2 )
            return not_able_to_read_value( sca, oldPos );

         //------------------------------------------------------------------ hH
         if ( not init_info( smFmt->x, hHCheck, &info ) )
            return inv_err( sca, oldPos );

         if ( chars_is_c( inp.type, info.s ) )
         {
            tmp = add_duration_c( tmp, hours_c( inp.val ) );
            continue;
         }
         else if ( info.n == 2 )
            return not_able_to_read_value( sca, oldPos );

         //------------------------------------------------------------------ mM
         if ( not init_info( smFmt->x, mMCheck, &info ) )
            return inv_err( sca, oldPos );

         if ( chars_is_c( inp.type, info.s ) )
         {
            tmp = add_duration_c( tmp, mins_c( inp.val ) );
            continue;
         }
         else if ( info.n == 2 )
            return not_able_to_read_value( sca, oldPos );

         //------------------------------------------------------------------ sS
         if ( not init_info( smFmt->x, sSCheck, &info ) )
            return inv_err( sca, oldPos );

         if ( chars_is_c( inp.type, info.s ) )
         {
            tmp = add_duration_c( tmp, secs_c( inp.val ) );
            continue;
         }
         else if ( info.n == 2 )
            return not_able_to_read_value( sca, oldPos );

         //------------------------------------------------------------------ iI
         if ( not init_info( smFmt->x, iICheck, &info ) )
            return inv_err( sca, oldPos );

         if ( chars_is_c( inp.type, info.s ) )
         {
            tmp = add_duration_c( tmp, msecs_c( inp.val ) );
            continue;
         }
         else if ( info.n == 2 )
            return not_able_to_read_value( sca, oldPos );

         //------------------------------------------------------------------ uU
         if ( not init_info( smFmt->x, uUCheck, &info ) )
            return inv_err( sca, oldPos );

         if ( chars_is_c( inp.type, info.s ) )
         {
            tmp = add_duration_c( tmp, usecs_c( inp.val ) );
            continue;
         }
         else if ( info.n == 2 )
            return not_able_to_read_value( sca, oldPos );

         //------------------------------------------------------------------ nN
         if ( not init_info( smFmt->x, nNCheck, &info ) )
            return inv_err( sca, oldPos );

         if ( chars_is_c( inp.type, info.s ) )
         {
            tmp = add_duration_c( tmp, nsecs_c( inp.val ) );
            continue;
         }
         else if ( info.n == 2 )
            return not_able_to_read_value( sca, oldPos );

         //****************************************************************** *l
         if ( move_if_chars_c_( smFmt->x, "*l" ) )
         {
            cDuration val = chars_is_c( inp.type, "s" )  ? secs_c( inp.val )  :
                            chars_is_c( inp.type, "ms" ) ? msecs_c( inp.val ) :
                            chars_is_c( inp.type, "µs" ) ? usecs_c( inp.val ) :
                            chars_is_c( inp.type, "ns" ) ? nsecs_c( inp.val ) :
                                                           null_duration_c();
            if ( not duration_is_valid_c( val ) )
               return not_able_to_read_value( sca, oldPos );

            tmp = add_duration_c( tmp, val );
            continue;
         }

         //****************************************************************** *U
         if ( move_if_chars_c_( smFmt->x, "*U" ) )
         {
            cDuration val = chars_is_c( inp.type, "S" )  ? secs_c( inp.val )  :
                            chars_is_c( inp.type, "MS" ) ? msecs_c( inp.val ) :
                            chars_is_c( inp.type, "µS" ) ? usecs_c( inp.val ) :
                            chars_is_c( inp.type, "NS" ) ? nsecs_c( inp.val ) :
                                                           null_duration_c();
            if ( not duration_is_valid_c( val ) )
               return not_able_to_read_value( sca, oldPos );

            tmp = add_duration_c( tmp, val );
            continue;
         }
      }
   }

   *dur = nsecs_c( tmp._v * sign );

   return true;
}

//******************************************************************************
static bool do_write( int64_t n, int64_t val )
{
   return ( n == 1 and val != 0 ) or ( n == 2 );
}
static bool rec_err( cRecorder rec[static 1], int64_t oldPos )
{
   move_recorder_to_c( rec, oldPos );
   return set_recorder_error_c( rec, c_InvalidWriteFormat );
}
static bool record_sep( cScanner fmt[static 1], cRecorder rec[static 1] )
{
   if ( move_if_char_c( fmt, ' ' ) )
   {
      return record_char_c( rec, ' ' );
   }
   return true;
}
bool write_duration_c( cRecorder rec[static 1],
                       cDuration dur,
                       char const fmt[static 1] )
{
   if ( *fmt == '\0' )
   {
      fmt = C_DurationFormat;
   }

   cScanner* sca = &cstr_scanner_c_( fmt );

   fmtInfo info;
   int64_t oldPos = rec->pos;
   char const* fstr = "%"PRIi64"%s";
   once_c_( xyz )
   {
      //------------------------------------------------------------------- sign
      if ( dur._v < 0 )
      {
         if ( not record_char_c( rec, '-' ) ) break;
         dur = invert_duration_c( dur );
      }

      //--------------------------------------------------------------------- wW
      if ( not init_info( sca, wWCheck, &info ) ) return rec_err( rec, oldPos );
      if ( do_write( info.n, as_weeks_c( dur ) ) )
      {
         cDuration v = truncate_duration_c( dur, C_Week, &dur );
         if ( not recordf_c( rec, fstr, as_weeks_c( v ), info.s ) ) break;
      }
      if ( not record_sep( sca, rec ) ) break;

      //--------------------------------------------------------------------- dD
      if ( not init_info( sca, dDCheck, &info ) ) return rec_err( rec, oldPos );
      if ( do_write( info.n, as_days_c( dur ) ) )
      {
         cDuration v = truncate_duration_c( dur, C_Day, &dur );
         if ( not recordf_c( rec, fstr, as_days_c( v ), info.s ) ) break;
      }
      if ( not record_sep( sca, rec ) ) break;

      //--------------------------------------------------------------------- hH
      if ( not init_info( sca, hHCheck, &info ) ) return rec_err( rec, oldPos );
      if ( do_write( info.n, as_hours_c( dur ) ) )
      {
         cDuration v = truncate_duration_c( dur, C_Hour, &dur );
         if ( not recordf_c( rec, fstr, as_hours_c( v ), info.s ) ) break;
      }
      if ( not record_sep( sca, rec ) ) break;

      //--------------------------------------------------------------------- mM
      if ( not init_info( sca, mMCheck, &info ) ) return rec_err( rec, oldPos );
      if ( do_write( info.n, as_mins_c( dur ) ) )
      {
         cDuration v = truncate_duration_c( dur, C_Min, &dur );
         if ( not recordf_c( rec, fstr, as_mins_c( v ), info.s ) ) break;
      }
      if ( not record_sep( sca, rec ) ) break;

      //---------------------------------------------------------------------- *
      if ( unscanned_is_c( sca, "*U" ) )
      {
         sca = ( as_secs_c( dur )  > 0 ) ? &cstr_scanner_c_( "SS.N" ) :
               ( as_msecs_c( dur ) > 0 ) ? &cstr_scanner_c_( "II.N" ) :
               ( as_usecs_c( dur ) > 0 ) ? &cstr_scanner_c_( "UU.N" ) :
                                           &cstr_scanner_c_( "NN" );
      }
      else if ( unscanned_is_c( sca, "*l" ) )
      {
         sca = ( as_secs_c( dur )  > 0 ) ? &cstr_scanner_c_( "ss.n" ) :
               ( as_msecs_c( dur ) > 0 ) ? &cstr_scanner_c_( "ii.n" ) :
               ( as_usecs_c( dur ) > 0 ) ? &cstr_scanner_c_( "uu.n" ) :
                                           &cstr_scanner_c_( "nn" );
      }

      //--------------------------------------------------------------------- sS
      if ( not init_info( sca, sSCheck, &info ) ) return rec_err( rec, oldPos );
      if ( do_write( info.n, as_secs_c( dur ) ) )
      {
         cDuration v = truncate_duration_c( dur, C_Sec, &dur );
         if ( not recordf_c( rec, "%"PRIi64, as_secs_c( v ) ) ) break;
         if ( info.n == 2 and move_if_char_c( sca, '.' ) )
         {
            if ( move_if_any_char_c_( sca, "iI" ) )
            {
               int64_t i = as_msecs_c( dur );
               if ( not intl_write_xsec_c( rec, i, true, ".%03d" ) ) break;
            }
            else if ( move_if_any_char_c_( sca, "uU" ) )
            {
               int64_t u = as_usecs_c( dur );
               if ( not intl_write_xsec_c( rec, u, true, ".%06d" ) ) break;
            }
            else if ( move_if_any_char_c_( sca, "nN" ) )
            {
               int64_t n = as_nsecs_c( dur );
               if ( not intl_write_xsec_c( rec, n, true, ".%09d" ) ) break;
            }
            else
            {
               return rec_err( rec, oldPos );
            }
            if ( sca->space > 0 ) return rec_err( rec, oldPos );
            if ( not record_chars_c_( rec, info.s ) ) break;
            return true;
         }
         if ( sca->space > 0 ) return rec_err( rec, oldPos );
         if ( not record_chars_c_( rec, info.s ) ) break;
      }
      if ( not record_sep( sca, rec ) ) break;

      //--------------------------------------------------------------------- iI
      if ( not init_info( sca, iICheck, &info ) ) return rec_err( rec, oldPos );
      if ( do_write( info.n, as_msecs_c( dur ) ) )
      {
         cDuration v = truncate_duration_c( dur, C_Msec, &dur );
         if ( not recordf_c( rec, "%"PRIi64, as_msecs_c( v ) ) ) break;
         if ( info.n == 2 and move_if_char_c( sca, '.' ) )
         {
            if ( move_if_any_char_c_( sca, "uU" ) )
            {
               int64_t u = as_usecs_c( dur );
               if ( not intl_write_xsec_c( rec, u, true, ".%03d" ) ) break;
            }
            else if ( move_if_any_char_c_( sca, "nN" ) )
            {
               int64_t n = as_nsecs_c( dur );
               if ( not intl_write_xsec_c( rec, n, true, ".%06d" ) ) break;
            }
            else
            {
               return rec_err( rec, oldPos );
            }
            if ( sca->space > 0 ) return rec_err( rec, oldPos );
            if ( not record_chars_c_( rec, info.s ) ) break;
            return true;
         }
         if ( sca->space > 0 ) return rec_err( rec, oldPos );
         if ( not record_chars_c_( rec, info.s ) ) break;
      }
      if ( not record_sep( sca, rec ) ) break;

      //--------------------------------------------------------------------- uU
      if ( not init_info( sca, uUCheck, &info ) ) return rec_err( rec, oldPos );
      if ( do_write( info.n, as_usecs_c( dur ) ) )
      {
         cDuration v = truncate_duration_c( dur, C_Usec, &dur );
         if ( not recordf_c( rec, "%"PRIi64, as_usecs_c( v ) ) ) break;
         if ( info.n == 2 and move_if_char_c( sca, '.' ) )
         {
            if ( move_if_any_char_c_( sca, "nN" ) )
            {
               int64_t n = as_nsecs_c( dur );
               if ( not intl_write_xsec_c( rec, n, true, ".%03d" ) ) break;
            }
            else
            {
               return rec_err( rec, oldPos );
            }
            if ( sca->space > 0 ) return rec_err( rec, oldPos );
            if ( not record_chars_c_( rec, info.s ) ) break;
            return true;
         }
         if ( sca->space > 0 ) return rec_err( rec, oldPos );
         if ( not record_chars_c_( rec, info.s ) ) break;
      }
      if ( not record_sep( sca, rec ) ) break;

      //--------------------------------------------------------------------- nN
      if ( not init_info( sca, nNCheck, &info ) ) return rec_err( rec, oldPos );
      if ( do_write( info.n, as_nsecs_c( dur ) ) )
      {
         if ( not recordf_c( rec, fstr, as_nsecs_c( dur ), info.s ) ) break; 
      }

      if ( sca->space > 0 ) return rec_err( rec, oldPos );
      return true;
   }

   move_recorder_to_c( rec, oldPos );
   return set_recorder_error_c( rec, c_NotEnoughRecorderSpace );
}

