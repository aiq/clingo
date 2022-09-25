#include "clingo/type/cRange.h"

/*******************************************************************************
********************************************************************+ Functions
********************************************************************************
 overall
*******************************************************************************/

extern inline int64_t clamp_into_range_c( cRange range, int64_t value );

extern inline bool eq_range_c( cRange a, cRange b );

extern inline bool in_range_c( cRange range, int64_t value );

extern inline bool range_is_valid_c( cRange range );

extern inline int64_t range_size_c( cRange range );

extern inline cRange shift_range_c( cRange range, int64_t distance );

