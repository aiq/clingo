#ifndef CLINGO_TIME_CDAY_SET_H
#define CLINGO_TIME_CDAY_SET_H

#include "clingo/lang/CObject.h"
#include "clingo/time/cDatePeriod.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************

*******************************************************************************/

extern cMeta const C_DaySetMeta;

struct CDaySet;
typedef struct CDaySet CDaySet;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 create
*******************************************************************************/

CDaySet* new_day_set_c();
CDaySet* target_day_set_c( cDatePeriod period );

/*******************************************************************************
 overall
*******************************************************************************/

int64_t count_days_c( CDaySet const* set );
bool day_set_is_empty_c( CDaySet const* set );
cDatePeriod day_set_period_c( CDaySet const* set );

/*******************************************************************************
 itr
*******************************************************************************/

cDate first_in_day_set_c( CDaySet const* set );

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

cDate last_in_day_set_c( CDaySet const* set );
cDate next_in_day_set_c( CDaySet const* set, cDate date );
cDate prev_in_day_set_c( CDaySet const* set, cDate date );

/*******************************************************************************
 in
*******************************************************************************/

bool date_period_in_day_set_c( CDaySet const* set, cDatePeriod period );
bool days_in_day_set_c( CDaySet const* set, CDaySet const* days );
bool in_day_set_c( CDaySet const* set, cDate date );

/*******************************************************************************
 set
*******************************************************************************/

bool set_date_period_on_day_set_c( CDaySet* set, cDatePeriod period );
bool set_days_on_day_set_c( CDaySet* set, CDaySet const* days );

#define set_many_on_day_set_c_( Set, ... )                                     \
   set_many_on_day_set_c( (Set), (cDateSlice)slice_c_( cDate, __VA_ARGS__ ) )
bool set_many_on_day_set_c( CDaySet* set, cDateSlice slice );

bool set_on_day_set_c( CDaySet* set, cDate date );

/*******************************************************************************
 remove
*******************************************************************************/

void remove_date_period_from_day_set_c( CDaySet* set, cDatePeriod period );
void remove_days_from_day_set_c( CDaySet* set, CDaySet const* days );
void remove_from_day_set_c( CDaySet* set, cDate date );

/*******************************************************************************
 io
*******************************************************************************/

#define write_day_set_c_( Rec, Set )                                           \
   write_day_set_c( (Rec), (Set), "" )
bool write_day_set_c( cRecorder rec[static 1],
                      CDaySet const* set,
                      char const fmt[static 1] );

#endif
