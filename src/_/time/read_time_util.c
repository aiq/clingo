#include "_/time/read_time_util.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 util
*******************************************************************************/

extern inline bool intl_read_hms_val_c( cScanner sca[static 1],
                                        int8_t val[static 1],
                                        int64_t fmt,
                                        int64_t spaces );

extern inline bool intl_read_xsec_c( cScanner sca[static 1],
                                     int32_t val[static 1],
                                     int64_t fmt );

extern inline bool intl_read_time_seperator_c( cScanner sca[static 1],
                                               cScanner fmtSca[static 1] );

/*******************************************************************************
 date
*******************************************************************************/

extern inline bool intl_read_day_of_year_c( cScanner sca[static 1],
                                            int16_t day[static 1],
                                            int64_t fmt,
                                            int64_t spaces );

extern inline bool intl_read_day_c( cScanner sca[static 1],
                                    int8_t day[static 1],
                                    int64_t fmt,
                                    int64_t spaces );

extern inline bool intl_read_month_c( cScanner sca[static 1],
                                      c_Month month[static 1],
                                      int64_t fmt,
                                      int64_t spaces );

extern inline bool intl_read_week_c( cScanner sca[static 1],
                                     int8_t week[static 1],
                                     int64_t fmt );

extern inline bool intl_read_weekday_c( cScanner sca[static 1],
                                        c_Weekday wd[static 1],
                                        int64_t fmt );

extern inline bool intl_read_year_c( cScanner sca[static 1],
                                     int32_t year[static 1],
                                     int64_t fmt,
                                     int64_t spaces );

/*******************************************************************************
 time
*******************************************************************************/

extern inline bool intl_read_hour_c( cScanner sca[static 1],
                                     int32_t val[static 1],
                                     int64_t fmt,
                                     int64_t spaces );

extern inline bool intl_read_kitchen_hour_c( cScanner sca[static 1],
                                             int32_t val[static 1],
                                             int64_t fmt,
                                             int64_t spaces );

extern inline bool intl_read_min_c( cScanner sca[static 1],
                                    int8_t val[static 1],
                                    int64_t fmt,
                                    int64_t spaces );

extern inline bool intl_read_sec_c( cScanner sca[static 1],
                                    int8_t val[static 1],
                                    int64_t fmt,
                                    int64_t spaces );

extern inline bool intl_read_isec_c( cScanner sca[static 1],
                                     int32_t isec[static 1],
                                     int64_t fmt );

extern inline bool intl_read_usec_c( cScanner sca[static 1],
                                     int32_t usec[static 1],
                                     int64_t fmt );

extern inline bool intl_read_nsec_c( cScanner sca[static 1],
                                     int32_t nsec[static 1],
                                     int64_t fmt );

extern inline bool intl_read_ap_c( cScanner sca[static 1],
                                   bool pm[static 1] );

extern inline bool intl_read_offset_c( cScanner sca[static 1],
                                       cTzOffset tz[static 1],
                                       int64_t fmt,
                                       bool z );
