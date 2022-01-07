#include "clingo/container/set.h"

/**********++*******************************************************************
********************************************************************* Functions 
********************************************************************************
 info
*******************************************************************************/

extern inline int64_t set_cap_c( cSetInfo const info[static 1] );

extern inline float set_load_c( cSetInfo const info[static 1] );

extern inline bool set_is_empty_c( cSetInfo const info[static 1] );

/*******************************************************************************
 itr
*******************************************************************************/

extern inline cSetItr start_set_itr_c();

extern inline bool set_itr_is_valid_c( cSetItr itr );