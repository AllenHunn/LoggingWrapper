/****************************************************************************/
/*!
*
*   @file NativeLoggerWrapper.h
*
*   @brief Declaration file for NativeLoggerWrapper.
*/
/****************************************************************************/

#pragma once

#include <INativeLoggingWrapper.h>
#include <vcclr.h>
#include "LoggingWrapper.h"
#include <cstdio>
#include <stdarg.h>

using namespace LoggingWrapper;

/****************************************************************************/
/*!
*   @brief Native C++ wrapper to underlying logging functionality.
*
*   This is the concrete implementation of the INativeLoggerWrapper interface.
*   
*   WARNING: Please do not reference this header file. Your code won't compile.
*   This class must be instantiated via INativeLoggingWrapper.CreateWrapper.
*   Your code should only reference INativeLoggingWrapper.h.
*/
/****************************************************************************/
class DLLAPI NativeLoggingWrapper : 
    implements INativeLoggingWrapper
{
public:
    NativeLoggingWrapper(const char *typeName);
    ~NativeLoggingWrapper();

    virtual void SetLoggerLevel(UNSIGNED32 nLevel);

    virtual bool WillLog(UNSIGNED32 nLevel);

    virtual void Log(UNSIGNED32 nLevel, const char* message);

    virtual void LogFormat(UNSIGNED32 nLevel, char* message, ...);

    virtual void LogFormatEx(UNSIGNED32 nLevel, char* message, va_list params);

    virtual void LogEmergency(char* message);

    virtual void LogEmergencyFormat(char* message, ...);

    virtual void LogEmergencyFormatEx(char* message, va_list params);

    virtual void LogFatal(char* message);

    virtual void LogFatalFormat(char* message, ...);

    virtual void LogFatalFormatEx(char* message, va_list params);

    virtual void LogError(char* message);

    virtual void LogErrorFormat(char* message, ...);

    virtual void LogErrorFormatEx(char* message, va_list params);

    virtual void LogWarning(char* message);

    virtual void LogWarningFormat(char* message, ...);

    virtual void LogWarningFormatEx(char* message, va_list params);

    virtual void LogInfo(char* message);

    virtual void LogInfoFormat(char* message, ...);

    virtual void LogInfoFormatEx(char* message, va_list params);

    virtual void LogNotice(char* message);

    virtual void LogNoticeFormat(char* message, ...);

    virtual void LogNoticeFormatEx(char* message, va_list params);

    virtual void LogDebug(char* message);

    virtual void LogDebugFormat(char* message, ...);

    virtual void LogDebugFormatEx(char* message, va_list params);

    virtual void LogDebugMedium(char* message);

    virtual void LogDebugMediumFormat(char* message, ...);

    virtual void LogDebugMediumFormatEx(char* message, va_list params);

    virtual void LogDebugHigh(char* message);

    virtual void LogDebugHighFormat(char* message, ...);

    virtual void LogDebugHighFormatEx(char* message, va_list params);

    virtual void LogDebugAll(char* message);

    virtual void LogDebugAllFormat(char* message, ...);

    virtual void LogDebugAllFormatEx(char* message, va_list params);

private:
    gcroot<Logger^> m_Logger;
    char* GetFormattedStr(char* message, va_list args);
    gcroot<Level^>* GetLevel(UNSIGNED32 nLevel);
};

