#include "_/time/write_time_util.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 util
*******************************************************************************/

extern inline bool intl_write_xsec_c( cRecorder rec[static 1],
                                      int64_t val,
                                      bool trim,
                                      char const fmt[static 1] );

extern inline bool intl_write_time_seperator_c( cRecorder rec[static 1],
                                                cScanner fmtSca[static 1] );

/*******************************************************************************
 date
*******************************************************************************/

extern inline bool intl_write_day_c( cRecorder rec[static 1],
                                     int8_t day,
                                     int64_t fmt,
                                     int64_t spaces );

extern inline bool intl_write_day_of_year_c( cRecorder rec[static 1],
                                             int16_t dayOfYear,
                                             int64_t fmt,
                                             int64_t spaces );

extern inline bool intl_write_month_c( cRecorder rec[static 1],
                                       c_Month month,
                                       int64_t fmt,
                                       int64_t spaces );

extern inline bool intl_write_week_c( cRecorder rec[static 1],
                                      int64_t week,
                                      int64_t fmt );

extern inline bool intl_write_weekday_c( cRecorder rec[static 1],
                                         c_Weekday wd,
                                         int64_t fmt );

extern inline bool intl_write_year_c( cRecorder rec[static 1],
                                      int32_t year,
                                      int64_t fmt );

/*******************************************************************************
 time
*******************************************************************************/

extern inline bool intl_write_hour_c( cRecorder rec[static 1],
                                      int32_t hour,
                                      int64_t fmt,
                                      int64_t spaces );

extern inline bool intl_write_kitchen_hour_c( cRecorder rec[static 1],
                                              int32_t hour,
                                              int64_t fmt,
                                              int64_t spaces );

extern inline bool intl_write_min_c( cRecorder rec[static 1],
                                     int32_t min,
                                     int64_t fmt,
                                     int64_t spaces );

extern inline bool intl_write_sec_c( cRecorder rec[static 1],
                                     int32_t sec,
                                     int64_t fmt,
                                     int64_t spaces );

extern inline bool intl_write_msec_c( cRecorder rec[static 1],
                                      int64_t msec,
                                      int64_t fmt );

extern inline bool intl_write_usec_c( cRecorder rec[static 1],
                                      int64_t usec,
                                      int64_t fmt );

extern inline bool intl_write_nsec_c( cRecorder rec[static 1],
                                      int64_t nsec,
                                      int64_t fmt );

extern inline bool intl_write_offset_c( cRecorder rec[static 1],
                                        cTzOffset tz,
                                        int64_t fmt,
                                        bool z );
