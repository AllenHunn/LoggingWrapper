#include "stdafx.h"
#include "NativeLoggerWrapper.h"

NativeLoggingWrapper::~NativeLoggingWrapper()
{
    m_Logger->LogDebugHigh("Logger destroyed.");
    delete m_Logger;
}

NativeLoggingWrapper::NativeLoggingWrapper(const char *typeName)
{
    m_Logger = gcnew Logger(gcnew String(typeName));
}

/// <summary>
/// Determines if the current logger will log for the specified level.
/// </summary>
/// <param name="nLevel">Numeric representation of a logging level.</param>
bool NativeLoggingWrapper::WillLog(UNSIGNED32 nLevel)
{
    auto level = GetLevel(nLevel);
    bool bRtn = m_Logger->WillLog(*level);
    delete level;
    return bRtn;
}

/// <summary>
/// Changes the logging level of the current logger dynamically.
/// If you don't know you need to use it, it's preferable not to.
/// </summary>
/// <param name="nLevel">Numeric representation of a logging level.</param>
void NativeLoggingWrapper::SetLoggerLevel(UNSIGNED32 nLevel)
{
    auto level = GetLevel(nLevel);
    m_Logger->SetLoggingLevel(*level);
    delete level;
}

/// <summary>
/// Logs the message to the specified level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::Log(UNSIGNED32 nLevel, const char* message)
{
    auto level = GetLevel(nLevel);
    m_Logger->Log(*level, gcnew String(message));
}

/// <summary>
/// Logs the message to the specified level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogFormat(UNSIGNED32 nLevel, char* message, ...)
{
    va_list params;
    va_start(params, message);
    LogFormatEx(nLevel, message, params);
    va_end(params);
}

/// <summary>
/// Logs the message to the specified level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">format parameters</param>
void NativeLoggingWrapper::LogFormatEx(UNSIGNED32 nLevel, char* message, va_list params)
{
    char *temp = GetFormattedStr(message, params);
    Log(nLevel, temp);
    delete temp;
}

/// <summary>
/// Logs the message to the Emergency level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogEmergency(char* message)
{
    m_Logger->LogEmergency(gcnew String(message));
}

/// <summary>
/// Logs the message to the Emergency level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogEmergencyFormat(char* message, ...)
{
    va_list params;
    va_start(params, message);
    LogEmergencyFormatEx(message, params);
    va_end(params);
}

/// <summary>
/// Logs the message to the Emergency level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">format parameters</param>
void NativeLoggingWrapper::LogEmergencyFormatEx(char* message, va_list params)
{
    char *temp = GetFormattedStr(message, params);
    LogEmergency(temp);
    delete temp;
}

/// <summary>
/// Logs the message to the Fatal level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogFatal(char* message)
{
    m_Logger->LogFatal(gcnew String(message));
}

/// <summary>
/// Logs the message to the Fatal level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogFatalFormat(char* message, ...)
{
    va_list params;
    va_start(params, message);
    LogFatalFormatEx(message, params);
    va_end(params);
}

/// <summary>
/// Logs the message to the Fatal level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">format parameters</param>
void NativeLoggingWrapper::LogFatalFormatEx(char* message, va_list params)
{
    char *temp = GetFormattedStr(message, params);
    LogFatal(temp);
    delete temp;
}

/// <summary>
/// Logs the message to the Error level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogError(char* message)
{
    m_Logger->LogError(gcnew String(message));
}

/// <summary>
/// Logs the message to the Error level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogErrorFormat(char* message, ...)
{
    va_list params;
    va_start(params, message);
    LogErrorFormatEx(message, params);
    va_end(params);
}

/// <summary>
/// Logs the message to the Error level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">format parameters</param>
void NativeLoggingWrapper::LogErrorFormatEx(char* message, va_list params)
{
    char *temp = GetFormattedStr(message, params);
    LogError(temp);
    delete temp;
}

/// <summary>
/// Logs the message to the warning level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogWarning(char* message)
{
    m_Logger->LogWarning(gcnew String(message));
}

/// <summary>
/// Logs the message to the warning level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogWarningFormat(char* message, ...)
{
    va_list params;
    va_start(params, message);
    LogWarningFormatEx(message, params);
    va_end(params);
}

/// <summary>
/// Logs the message to the warning level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">format parameters</param>
void NativeLoggingWrapper::LogWarningFormatEx(char* message, va_list params)
{
    char *temp = GetFormattedStr(message, params);
    LogWarning(temp);
    delete temp;
}

/// <summary>
/// Logs the message to the Information level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogInfo(char* message)
{
    m_Logger->LogInfo(gcnew String(message));
}

/// <summary>
/// Logs the message to the Information level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogInfoFormat(char* message, ...)
{
    va_list params;
    va_start(params, message);
    LogInfoFormatEx(message, params);
    va_end(params);
}

/// <summary>
/// Logs the message to the Information level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">format parameters</param>
void NativeLoggingWrapper::LogInfoFormatEx(char* message, va_list params)
{
    char *temp = GetFormattedStr(message, params);
    LogInfo(temp);
    delete temp;
}

/// <summary>
/// Logs the message to the Notice level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogNotice(char* message)
{
    m_Logger->LogNotice(gcnew String(message));
}

/// <summary>
/// Logs the message to the Notice level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogNoticeFormat(char* message, ...)
{
    va_list params;
    va_start(params, message);
    LogNoticeFormatEx(message, params);
    va_end(params);
}

/// <summary>
/// Logs the message to the Notice level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">format parameters</param>
void NativeLoggingWrapper::LogNoticeFormatEx(char* message, va_list params)
{
    char *temp = GetFormattedStr(message, params);
    LogNotice(temp);
    delete temp;
}

/// <summary>
/// Logs the message to the Debug level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogDebug(char* message)
{
    m_Logger->LogDebug(gcnew String(message));
}

/// <summary>
/// Logs the message to the Debug level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogDebugFormat(char* message, ...)
{
    va_list params;
    va_start(params, message);
    LogDebugFormatEx(message, params);
    va_end(params);
}

/// <summary>
/// Logs the message to the Debug level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">format params</param>
void NativeLoggingWrapper::LogDebugFormatEx(char* message, va_list params)
{
    char *temp = GetFormattedStr(message, params);
    LogDebug(temp);
    delete temp;
}

/// <summary>
/// Logs the message to the DebugMedium level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogDebugMedium(char* message)
{
    m_Logger->LogDebugMedium(gcnew String(message));
}

/// <summary>
/// Logs the message to the DebugMedium level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogDebugMediumFormat(char* message, ...)
{
    va_list params;
    va_start(params, message);
    LogDebugMediumFormatEx(message, params);
    va_end(params);
}

/// <summary>
/// Logs the message to the DebugMedium level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">format parameters</param>
void NativeLoggingWrapper::LogDebugMediumFormatEx(char* message, va_list params)
{
    char *temp = GetFormattedStr(message, params);
    LogDebugMedium(temp);
    delete temp;
}

/// <summary>
/// Logs the message to the DebugHigh level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogDebugHigh(char* message)
{
    m_Logger->LogDebugHigh(gcnew String(message));
}

/// <summary>
/// Logs the message to the DebugHigh level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogDebugHighFormat(char* message, ...)
{
    va_list params;
    va_start(params, message);
    LogDebugHighFormatEx(message, params);
    va_end(params);
}

/// <summary>
/// Logs the message to the DebugHigh level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">format parameters</param>
void NativeLoggingWrapper::LogDebugHighFormatEx(char* message, va_list params)
{
    char *temp = GetFormattedStr(message, params);
    LogDebugHigh(temp);
    delete temp;
}

/// <summary>
/// Logs the message to the DebugAll level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogDebugAll(char* message)
{
    m_Logger->LogDebugAll(gcnew String(message));
}

/// <summary>
/// Logs the message to the DebugAll level.
/// </summary>
/// <param name="message">The message.</param>
void NativeLoggingWrapper::LogDebugAllFormat(char* message, ...)
{
    va_list params;
    va_start(params, message);
    LogDebugAllFormatEx(message, params);
    va_end(params);
}

/// <summary>
/// Logs the message to the DebugAll level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">format params</param>
void NativeLoggingWrapper::LogDebugAllFormatEx(char* message, va_list params)
{
    char *temp = GetFormattedStr(message, params);
    LogDebugAll(temp);
    delete temp;
}

char* NativeLoggingWrapper::GetFormattedStr(char* message, va_list params)
{
    int size = _vscprintf(message, params);
    char *temp = (char*)malloc(size+1);
    vsnprintf_s(temp, size + 1, size + 1, message, params);
    return temp;
}

gcroot<Level^>* NativeLoggingWrapper::GetLevel(UNSIGNED32 nLevel)
{
    Level^ level;
    switch (nLevel)
    {
    case LOGGING_LEVEL_NONE:
        level = Level::Off;
        break;
    case LOGGING_LEVEL_FATAL:
        level = Level::Fatal;
        break;
    case LOGGING_LEVEL_ERROR:
        level = Level::Error;
        break;
    case LOGGING_LEVEL_WARNING:
        level = Level::Warn;
        break;
    case LOGGING_LEVEL_INFO:
        level = Level::Info;
        break;
    case LOGGING_LEVEL_DEBUGLOW:
        level = Level::Debug;
        break;
    case LOGGING_LEVEL_DEBUGMEDIUM:
        level = Level::Trace;
        break;
    case LOGGING_LEVEL_DEBUGHIGH:
        level = Level::Verbose;
        break;
    case LOGGING_LEVEL_DEBUGALL:
        level = Level::Finest;
        break;
    default:
        level = Level::Error;
        break;
    }
    return new gcroot<Level^>(level);
}

/// <summary>
/// Creates an instance of the wrapper implementation.
/// </summary>
/// <param name="typeName">Name of the type that will be logged for.</param>
/// <returns>A new instance of INativeLoggingWrapper.</returns>
INativeLoggingWrapper *INativeLoggingWrapper::CreateWrapper(const char *typeName)
{
    return ((INativeLoggingWrapper *)new NativeLoggingWrapper(typeName));
}