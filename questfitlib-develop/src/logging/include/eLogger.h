
/*
================================================================================#=
FILE:
    eLogger.h

DESCRIPTION:
    Internal (private) include for the event logger module.
================================================================================#=
*/

#ifndef E_LOGGER_H__
#define E_LOGGER_H__

#define MAX_AP_LOG_STRING_LEN   100

#ifdef __cplusplus
extern "C" {
#endif

// -------------------------------------------------------------+-
// Define the logging "level" associated with each log message.
// The numerical values are ordered from lowest to highest severity.
// -------------------------------------------------------------+-
typedef enum 
{
    eLogLvlDebug      = 0,
    eLogLvlInfo       = 1,
    eLogLvlNotice     = 2,
    eLogLvlOffNominal = 3,
    eLogLvlError      = 4,
    eLogLvlFatal      = 5,
    eLogLvlInvalid    = 6,

} tLogLvl;

typedef struct
{
    tLogLvl logLevel;
    char logString[MAX_AP_LOG_STRING_LEN];
}apLogBuf_t;

/*
--------------------------------------------------------------------------------+-
This is the core function that implements the logging feature.
It is called from application code using the macros that are
defined in the eLog.h file.  Note: this uses var args.
--------------------------------------------------------------------------------+-
*/
void logCore(
    const char  *fileName,
    const char  *functionName,
    int          lineNumber,
    tLogLvl      loggingLevel,
	int 	     loggingFacility,
    const char  *formatStr,
    ...
);


/*
--------------------------------------------------------------------------------+-
Sets the logging threshold level.
Only those messages will be logged
whose level is at or above the current threshold level.
--------------------------------------------------------------------------------+-
*/
void setLogLvl(
    tLogLvl      loggingLevel
);


#ifdef __cplusplus
}
#endif

#endif


