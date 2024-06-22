#include "clingo/time/cDaytime.h"

#include "clingo/lang/algo.h"
#include "clingo/time/C_TimeFormats.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

cDaytime daytime_c( int64_t h, int64_t m, int64_t s, int64_t n )
{
   cDuration dur = duration_c( h, m, s, n );
   return from_duration_c( dur );
}

cDaytime local_daytime_c( void )
{
   return null_daytime_c();
}

cDaytime null_daytime_c( void )
{
   return (cDaytime){ -1 };
}

cDaytime utc_daytime_c( void )
{
   return null_daytime_c();
}

/*******************************************************************************
 from
*******************************************************************************/

cDaytime from_duration_c( cDuration dur )
{
   return (cDaytime){ dur._v % C_Day };
}

cDaytime from_hmsn_c( cHmsn hmsn )
{
   cDuration dur = duration_from_hmsn_c( hmsn );
   return from_duration_c( dur );
}

/*******************************************************************************
 as
*******************************************************************************/

cDuration as_duration_c( cDaytime dt )
{
   return (cDuration){ dt._v };
}

cHmsn as_hmsn_c( cDaytime dt )
{
   cDuration dur = as_duration_c( dt );
   return hmsn_from_duration_c( dur );
}

/*******************************************************************************
 add
*******************************************************************************/

cDaytime add_to_daytime_c( cDaytime dt, cDuration dur )
{
   cDuration res = add_duration_c( as_duration_c( dt ), dur );
   return from_duration_c( res );
}

/*******************************************************************************
 diff
*******************************************************************************/

cDuration between_daytimes_c( cDaytime a, cDaytime b )
{
   return between_durations_c( as_duration_c( a ), as_duration_c( b ) );
}

/*******************************************************************************
 cmp
*******************************************************************************/

int cmp_daytime_c( cDaytime a, cDaytime b )
{
   return cmp_int64_c( a._v, b._v );
}

bool daytime_is_valid_c( cDaytime dt )
{
   return in_range_c_( 0, dt._v, 24*C_Hour );
}

cDaytime early_daytime_c( cDaytime a, cDaytime b )
{
   return lt_c( cmp_daytime_c( a, b ) ) ? a
                                        : b;
}

extern inline bool eq_daytime_c( cDaytime a, cDaytime b );

cDaytime late_daytime_c( cDaytime a, cDaytime b )
{
   return gt_c( cmp_daytime_c( a, b ) ) ? a
                                        : b;
}

/*******************************************************************************
 io
*******************************************************************************/

bool read_daytime_c( cScanner sca[static 1],
                     cDaytime dt[static 1],
                     char const fmt[static 1] )
{
   cHmsn hmsn;
   bool res = read_hmsn_c( sca, &hmsn, fmt );
   if ( res )
   {
      *dt = from_hmsn_c( hmsn );
   }
   return res;
}

bool write_daytime_c( cRecorder rec[static 1],
                      cDaytime dt,
                      char const fmt[static 1] )
{
   return write_hmsn_c( rec, as_hmsn_c( dt ), fmt );
}

static TAPE_C_( tape_func, cDaytime, write_daytime_c, do_deref_c_ )
cTape daytime_tape_c( cDaytime const* dt )
{
   return (cTape){ .i=dt, .f=tape_func };
}
