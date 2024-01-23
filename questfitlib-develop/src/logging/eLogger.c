
/*
================================================================================#=
FILE:
    eLogger.c

DESCRIPTION:
    Internal (private) implementation for the event logger module.

LICENSE:
    The MIT License (MIT)
    Copyright (c) 2017  Robert A. Ensink
================================================================================#=
*/

#include "eLogger.h"

#include <stdint.h>
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
#include <windows.h>
#include <stdlib.h>
#else
#include <time.h>
#include <sys/time.h>
#include <syslog.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    static tLogLvl currentLogLevel = eLogLvlInfo;

    /*
--------------------------------------------------------------------------------+-
--------------------------------------------------------------------------------+-
*/
    const char *logging_level_to_string(tLogLvl given_level)
    {
        static const char *fatal = "fatl";
        static const char *error = "erro";
        static const char *offnominal = "ofno";
        static const char *notice = "notc";
        static const char *info = "info";
        static const char *debug = "debg";
        static const char *notlvl = "nalv";

        if (given_level == eLogLvlDebug)
        {
            return debug;
        }
        else if (given_level == eLogLvlInfo)
        {
            return info;
        }
        else if (given_level == eLogLvlNotice)
        {
            return notice;
        }
        else if (given_level == eLogLvlOffNominal)
        {
            return offnominal;
        }
        else if (given_level == eLogLvlError)
        {
            return error;
        }
        else if (given_level == eLogLvlFatal)
        {
            return fatal;
        }
        else
        {
            return notlvl;
        }
    }

/*
--------------------------------------------------------------------------------+-
--------------------------------------------------------------------------------+-
*/
#ifndef _MSC_VER
    int logging_level_to_syslog_level(tLogLvl given_level)
    {

        if (given_level == eLogLvlDebug)
        {
            return LOG_DEBUG;
        }
        else if (given_level == eLogLvlInfo)
        {
            return LOG_INFO;
        }
        else if (given_level == eLogLvlNotice)
        {
            return LOG_NOTICE;
        }
        else if (given_level == eLogLvlOffNominal)
        {
            return LOG_WARNING;
        }
        else if (given_level == eLogLvlError)
        {
            return LOG_ERR;
        }
        else if (given_level == eLogLvlFatal)
        {
            return LOG_CRIT;
        }
        else
        {
            return LOG_DEBUG;
        }
    }
#endif

    /*
--------------------------------------------------------------------------------+-
--------------------------------------------------------------------------------+-
*/
    void logCore(
        const char *fileName,
        const char *functionName,
        int lineNumber,
        tLogLvl loggingLevel,
        int loggingFacility,
        const char *formatStr,
        ...)
    {
        struct tm ptm;
        char time_string[40] = "";
        long milliseconds = 0;
        char buf[256];

        /* Obtain the time of day, and convert it to a tm struct. */
#ifdef _MSC_VER
        time_t t;
        time(&t);
        localtime_s(&ptm, &t);
        SYSTEMTIME time;
        GetSystemTime(&time);
        milliseconds = time.wMilliseconds;

#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &ptm);
    /* Compute milliseconds from microseconds. */
    milliseconds = tv.tv_usec / 1000;
#endif
        /* Format the date and time, down to a single second. */
        strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", &ptm);

#ifndef _MSC_VER
        openlog(NULL, LOG_CONS, loggingFacility);
#endif

        // Extract just the filename part of the path (if needed)
        const char *file = (strrchr(fileName, '/') ? strrchr(fileName, '/') + 1 : fileName);

        if (loggingLevel >= currentLogLevel)
        {
            va_list argptr;
            va_start(argptr, formatStr);
#ifdef _MSC_VER
            vsprintf_s(buf, sizeof(buf), formatStr, argptr); // @@@ TODO: test for buff overflow
#else
        vsprintf(buf, formatStr, argptr); // @@@ TODO: test for buff overflow
#endif
            va_end(argptr);

#ifdef _MSC_VER
            printf("%s.%03ld - %s: %s:%d:  %s\n",
                   time_string,
                   milliseconds,
                   logging_level_to_string(loggingLevel),
                   file,
                   lineNumber,
                   buf);
            char fpath[1000] = {0};
            sprintf(fpath, "%s/qflog.txt", getenv("APPDATA"));
            FILE *logFile = fopen(fpath, "a");
            fprintf(logFile, "%s.%03ld - %s: %s:%d:  %s\n",
                    time_string,
                    milliseconds,
                    logging_level_to_string(loggingLevel),
                    file,
                    lineNumber,
                    buf);
            fclose(logFile);
#else
        printf("%s.%03ld - %s: %s:%d:  %s\n",
               time_string,
               milliseconds,
               logging_level_to_string(loggingLevel),
               file,
               lineNumber,
               buf);
        syslog(logging_level_to_syslog_level(loggingLevel),
               "%s.%03ld - %s: %s:%d:  %s\n",
               time_string,
               milliseconds,
               logging_level_to_string(loggingLevel),
               file,
               lineNumber,
               buf);
#endif
        }

        return;
    }

    /*
--------------------------------------------------------------------------------+-
--------------------------------------------------------------------------------+-
*/
    void setLogLvl(
        tLogLvl given_level)
    {
        currentLogLevel = given_level;
    }

#ifdef __cplusplus
}
#endif
