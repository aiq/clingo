#include "clingo/time/C_TimeFormats.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 date definitions
*******************************************************************************/

char const*const C_DateFormat       = "YYYY.MM.DD";
char const*const C_TextDate         = "EEE MMM _D YYYY";
char const*const C_IsoDate          = "YYYY-MM-DD";
char const*const C_IsoOrdinalDate   = "YYYY-CCC";
char const*const C_IsoWeekDate      = "XXXX-WWW-E";
char const*const C_Rfc2822Date      = "EEE, DD MMM YYYY";

/*******************************************************************************
 daytime definitions
*******************************************************************************/

char const*const C_DaytimeFormat    = "hh:mm:ss.n";
char const*const C_IsoDaytime       = "hh:mm:ss";
char const*const C_KitchenTime      = "_k:mmAP";

/*******************************************************************************
 duration definitions
*******************************************************************************/

char const*const C_DurationFormat   = "wdhm*l";

/*******************************************************************************
 time definitions
*******************************************************************************/

char const*const C_TimeFormat       = "YYYY.MM.DD hh:mm:ss oooo";
char const*const C_IsoTime          = "YYYY-MM-DDThh:mm:ssoooo";
char const*const C_Rfc2822Time      = "EEE, DD MMM YYYY hh:mm:sszzzz";

char const*const C_AnsiCTime        = "EEE MMM _D hh:mm:ss YYYY";
char const*const C_Rfc882Time       = "DD MMM YY hh:mm oooo";
char const*const C_Rfc1123Time      = "EEE, DD MMM YYYY hh:mm:ss oooo";
char const*const C_Rfc3339Time      = "YYYY-MM-DDThh:mm:sszz";
char const*const C_Rfc3339TimeNano  = "YYYY-MM-DDThh:mm:ss.nzz";

