#ifndef CLINGO_TIME_CDAYSET_H
#define CLINGO_TIME_CDAYSET_H

#include "clingo/apidecl.h"
#include "clingo/lang/CObject.h"
#include "clingo/time/cDatePeriod.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************

*******************************************************************************/

CLINGO_API extern cMeta const C_DaySetMeta;

struct CDaySet;
typedef struct CDaySet CDaySet;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 create
*******************************************************************************/

CLINGO_API CDaySet* new_day_set_c();
CLINGO_API CDaySet* target_day_set_c( cDatePeriod period );

/*******************************************************************************
 overall
*******************************************************************************/

CLINGO_API int64_t count_days_c( CDaySet const* set );
CLINGO_API bool day_set_is_empty_c( CDaySet const* set );
CLINGO_API cDatePeriod day_set_period_c( CDaySet const* set );

/*******************************************************************************
 itr
*******************************************************************************/

CLINGO_API cDate first_in_day_set_c( CDaySet const* set );

#define iterate_day_set_c_( Day, DaySet )                                      \
for (                                                                          \
   cDate Day = first_in_day_set_c( DaySet );                                   \
   date_is_valid_c( Day );                                                     \
   Day = next_in_day_set_c( DaySet, Day )                                      \
)

#define riterate_day_set_c_( Day, DaySet )                                     \
for (                                                                          \
   cDate Day = last_in_day_set_c( DaySet );                                    \
   date_is_valid_c( Day );                                                     \
   Day = prev_in_day_set_c( DaySet, Day )                                      \
)

CLINGO_API cDate last_in_day_set_c( CDaySet const* set );
CLINGO_API cDate next_in_day_set_c( CDaySet const* set, cDate date );
CLINGO_API cDate prev_in_day_set_c( CDaySet const* set, cDate date );

/*******************************************************************************
 in
*******************************************************************************/

CLINGO_API bool date_period_in_day_set_c( CDaySet const* set, cDatePeriod period );
CLINGO_API bool days_in_day_set_c( CDaySet const* set, CDaySet const* days );
CLINGO_API bool in_day_set_c( CDaySet const* set, cDate date );

/*******************************************************************************
 set
*******************************************************************************/

CLINGO_API bool set_date_period_on_day_set_c( CDaySet* set, cDatePeriod period );
CLINGO_API bool set_days_on_day_set_c( CDaySet* set, CDaySet const* days );

#define set_many_on_day_set_c_( Set, ... )                                     \
   set_many_on_day_set_c( (Set), (cDateSlice)slice_c_( cDate, __VA_ARGS__ ) )
CLINGO_API bool set_many_on_day_set_c( CDaySet* set, cDateSlice slice );

CLINGO_API bool set_on_day_set_c( CDaySet* set, cDate date );

/*******************************************************************************
 remove
*******************************************************************************/

CLINGO_API void remove_date_period_from_day_set_c( CDaySet* set, cDatePeriod period );
CLINGO_API void remove_days_from_day_set_c( CDaySet* set, CDaySet const* days );
CLINGO_API void remove_from_day_set_c( CDaySet* set, cDate date );

/*******************************************************************************
 io
*******************************************************************************/

#define write_day_set_c_( Rec, Set )                                           \
   write_day_set_c( (Rec), (Set), "" )
CLINGO_API bool write_day_set_c( cRecorder rec[static 1],
                      CDaySet const* set,
                      char const fmt[static 1] );

CLINGO_API cTape day_set_tape_c( CDaySet const* set );

#endif
