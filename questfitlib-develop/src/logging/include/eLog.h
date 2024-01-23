
/*
================================================================================#=
FILE:
    eLog.h

DESCRIPTION:
    Public API for the event logger utility module.

LICENSE:
    The MIT License (MIT)

    Copyright (c) 2017  Robert A. Ensink

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
    OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
================================================================================#=
*/

#ifndef E_LOG_H
#define E_LOG_H

#ifndef _MSC_VER
#include <syslog.h>
#else
#define LOG_LOCAL0 0
#endif
#include "eLogger.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
================================================================================#=
The Event Log module defines a number of 'logging levels' which are
used to classify each event.  These levels are defined below
where they are listed from highest to lowest priority.

FATAL
    The 'Fatal' level is identical to an 'Error' (as described below) except
    a 'Fatal will result in the calling process to exit with an error code.
    Use 'Fatal' when a reset/restart is the only viable method by which
    the system can recover from the error.
    Also use 'Fatal' for assertions or other design-time errors.
    Use 'Error' when the system can recover or otherwise handle the problem.

ERROR
    The 'Error' level is used to indicate that the system
    has detected something wrong that needs to be fixed.
    Typically, these are software design or coding errors, i.e., bugs.
    Developers, maintainers, and administrators need to know about errors
    because the goal is to drive the number of 'Error' occurrences to zero;
    even for systems that have been deployed to the field.

    The 'ERROR' level is used regardless of whether the origin of the error
    is internal, external, or indeterminate.  So, for example, when a function
    receives a bad parameter value from an external interface, the function
    should log an ERROR even though the ultimate source of the bad value
    is coming from some external source.

OFF-NOMINAL
    The 'Off-Nominal' level is identical to an 'Info' (as described below)
    except that 'Off-Nominal' is used to log events that are
    (1) unusual, exceptional, or otherwise anomolous but which also
    (2) must be properly handled and recovered from
    as part of the required normal operation of the system.
    'Off Nominals' are typically mapped to a 'Warning' priority.
    An 'Off-Nominal' is not an error.  We would expect them to be infrequent,
    but there is no need to address them as issues unless they occur more often
    than we might expect.  Examples include loosing a network connection,
    receiving an invalid input from an interface, or unexpected power loss.

NOTICE
    The 'Notice' level is identical to an 'Info' (as described below)
    but with a slightly higher priority.  Notices are not errors;
    they indicate normal operation of the system, but they contain information
    that is significant enough to warrant special treatment such as
    routing to a persistent log file as opposed to an ephemeral /tmp log file.

INFO
    The 'Info' level is used to log significant state changes and other important
    events that are part of the normal operation of the system.
    It may also be used to log the system's identity and other fixed
    but important characteristics such as the software version.
    The purpose of an INFO message is to provide visibility
    into the operation of the system in order to support troubleshooting.
    The INFO logging statements typically remain in the production code.

DEBUG
    The 'Debug' level is identical to an 'Info' (as described above)
    but with a slightly lower priority.
    Debug statements are typically filtered out of the production code.
    Use 'Debug' to focus in greater detail on the operation of particular
    areas of the code during development and integration.
================================================================================#=
*/

#undef  CONFIG_LOGGER
#define CONFIG_LOGGER

#ifdef  CONFIG_LOGGER

#define elogFatal(formatStr, ...) logCore( \
    __FILE__, __FUNCTION__, __LINE__, \
    eLogLvlFatal, LOG_LOCAL0, formatStr, ##__VA_ARGS__ )

#define elogAssert(_condition_, formatStr, ...) if(!(_condition_)) { \
    logCore( \
        __FILE__, __FUNCTION__, __LINE__, \
        eLogLvlFatal, LOG_LOCAL0, formatStr, ##__VA_ARGS__ ); \
}

#define elogError(formatStr, ...) logCore( \
    __FILE__, __FUNCTION__, __LINE__, \
    eLogLvlError, LOG_LOCAL0, formatStr, ##__VA_ARGS__ )

#define elogOffNominal(formatStr, ...) logCore( \
    __FILE__, __FUNCTION__, __LINE__, \
    eLogLvlOffNominal, LOG_LOCAL0, formatStr, ##__VA_ARGS__ )

#define elogNotice(formatStr, ...) logCore( \
    __FILE__, __FUNCTION__, __LINE__, \
    eLogLvlNotice, LOG_LOCAL0, formatStr, ##__VA_ARGS__ )

#define elogInfo(formatStr, ...) logCore( \
    __FILE__, __FUNCTION__, __LINE__, \
    eLogLvlInfo, LOG_LOCAL0, formatStr, ##__VA_ARGS__ )

#define elogDebug(formatStr, ...) logCore( \
    __FILE__, __FUNCTION__, __LINE__, \
    eLogLvlDebug, LOG_LOCAL0, formatStr, ##__VA_ARGS__ )

#define elogSMI(formatStr, ...) logCore( \
    __FILE__, __FUNCTION__, __LINE__, \
    eLogLvlNotice, LOG_LOCAL1, formatStr, ##__VA_ARGS__ )

#else

#define elogAssert(_condition_, formatStr, ...)  do{} while(0)
#define elogFatal(formatStr, ...)       do{} while(0)
#define elogError(formatStr, ...)       do{} while(0)
#define elogOffNominal(formatStr, ...)  do{} while(0)
#define elogNotice(formatStr, ...)      do{} while(0)
#define elogInfo(formatStr, ...)        do{} while(0)
#define elogDebug(formatStr, ...)       do{} while(0)
#define elogSMI(formatStr, ...) 		do{} while(0)

#endif

#ifdef __cplusplus
}
#endif

#endif  /// E_LOG_H ///


