#include "stdafx.h"
#include "LoggingWrapper.h"

/// <summary>
/// Initializes a new instance of the <see cref="Logger"/> class.
/// This version will not apply a configuration file or create the logger.
/// Configuration must be done through other means and then CreateLogger called.
/// </summary>
LoggingWrapper::Logger::Logger(){ }

/// <summary>
/// Initializes a new instance of the <see cref="Logger"/> class.
/// </summary>
/// <param name="type">The type being logged</param>
LoggingWrapper::Logger::Logger(Type^ type)
{
    Configure();
    CreateLogger(type);
}

/// <summary>
/// Initializes a new instance of the <see cref="Logger"/> class.
/// </summary>
/// <param name="typeName">Name of the type being logged</param>
LoggingWrapper::Logger::Logger(String^ typeName)
{
    Configure();
    CreateLogger(typeName);
}

LoggingWrapper::Logger::~Logger()
{
}

/// <summary>
/// Creates the logger. Generally unnecessary unless the parameterless constructor was used.
/// Configuration must be complete by some means before this method is called.
/// </summary>
/// <param name="typeName">Name of the type being logged.</param>
void LoggingWrapper::Logger::CreateLogger(String^ typeName)
{
    m_Logger = LogManager::GetLogger(typeName);
}

/// <summary>
/// Creates the logger. Generally unnecessary unless the parameterless constructor was used.
/// Configuration must be complete by some means before this method is called.
/// </summary>
/// <param name="type">The type being logged.</param>
void LoggingWrapper::Logger::CreateLogger(Type^ type)
{
    m_Logger = LogManager::GetLogger(type);
}

/// <summary>
/// Sets the logging level.
/// </summary>
/// <param name="level">The level.</param>
void LoggingWrapper::Logger::SetLoggingLevel(Level^ level)
{
    ((log4net::Repository::Hierarchy::Logger^)m_Logger->Logger)->Level = level;
}

/// <summary>
/// Checks if the log will be written for the given level.
/// </summary>
/// <param name="level">The level.</param>
/// <returns>True if it will be logged, otherwise false.</returns>
bool LoggingWrapper::Logger::WillLog(Level^ level)
{
    return m_Logger->Logger->IsEnabledFor(level);
}

/// <summary>
/// Logs the message to the specified level.
/// </summary>
/// <param name="level">Level to log to.</param>
/// <param name="message">The message.</param>
void LoggingWrapper::Logger::Log(Level^ level, Object^ message)
{
    LogCustom(message, level);
}

/// <summary>
/// Logs the message to the specified level.
/// </summary>
/// <param name="level">Level to log to.</param>
/// <param name="message">The message.</param>
/// <param name="params">The parameters.</param>
void LoggingWrapper::Logger::Log(Level^ level, String^ message, ... array<Object^>^ params)
{
    LogCustom(String::Format(message, params), level);
}

/// <summary>
/// Logs the message to the Emergency level.
/// </summary>
/// <param name="message">The message.</param>
void LoggingWrapper::Logger::LogEmergency(Object^ message)
{
    LogCustom(message, Level::Emergency);
}

/// <summary>
/// Logs the message to the Emergency level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">The parameters.</param>
void LoggingWrapper::Logger::LogEmergency(String^ message, array<Object^>^ params)
{
    LogCustom(String::Format(message, params), Level::Emergency);
}

/// <summary>
/// Logs the message to the Fatal level.
/// </summary>
/// <param name="message">The message.</param>
void LoggingWrapper::Logger::LogFatal(Object^ message)
{
    m_Logger->Fatal(message);
}

/// <summary>
/// Logs the message to the Fatal level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">The parameters.</param>
void LoggingWrapper::Logger::LogFatal(String^ message, array<Object^>^ params)
{
    m_Logger->FatalFormat(message, params);
}

/// <summary>
/// Logs the message to the Error level.
/// </summary>
/// <param name="message">The message.</param>
void LoggingWrapper::Logger::LogError(Object^ message)
{
    m_Logger->Error(message);
}

/// <summary>
/// Logs the message to the Error level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">The parameters.</param>
void LoggingWrapper::Logger::LogError(String^ message, array<Object^>^ params)
{
    m_Logger->ErrorFormat(message, params);
}

/// <summary>
/// Logs the message to the Warning level.
/// </summary>
/// <param name="message">The message.</param>
void LoggingWrapper::Logger::LogWarning(Object^ message)
{
    m_Logger->Warn(message);
}

/// <summary>
/// Logs the message to the Warning level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">The parameters.</param>
void LoggingWrapper::Logger::LogWarning(String^ message, array<Object^>^ params)
{
    m_Logger->WarnFormat(message, params);
}

/// <summary>
/// Logs the message to the Information level.
/// </summary>
/// <param name="message">The message.</param>
void LoggingWrapper::Logger::LogInfo(Object^ message)
{
    m_Logger->Info(message);
}

/// <summary>
/// Logs the message to the Information level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">The parameters.</param>
void LoggingWrapper::Logger::LogInfo(String^ message, array<Object^>^ params)
{
    m_Logger->InfoFormat(message, params);
}

/// <summary>
/// Logs the message to the Notice level.
/// </summary>
/// <param name="message">The message.</param>
void LoggingWrapper::Logger::LogNotice(Object^ message)
{
    LogCustom(message, Level::Notice);
}

/// <summary>
/// Logs the message to the Notice level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">The parameters.</param>
void LoggingWrapper::Logger::LogNotice(String^ message, array<Object^>^ params)
{
    LogCustom(String::Format(message, params), Level::Notice);
}

/// <summary>
/// Logs the message to the Debug level.
/// </summary>
/// <param name="message">The message.</param>
void LoggingWrapper::Logger::LogDebug(Object^ message)
{
    m_Logger->Debug(message);
}

/// <summary>
/// Logs the message to the Debug level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">The parameters.</param>
void LoggingWrapper::Logger::LogDebug(String^ message, array<Object^>^ params)
{
    m_Logger->DebugFormat(message, params);
}

/// <summary>
/// Logs the message to the DebugMedium level.
/// </summary>
/// <param name="message">The message.</param>
void LoggingWrapper::Logger::LogDebugMedium(Object^ message)
{
    LogCustom(message, Level::Trace);
}

/// <summary>
/// Logs the message to the DebugMedium level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">The parameters.</param>
void LoggingWrapper::Logger::LogDebugMedium(String^ message, array<Object^>^ params)
{
    LogCustom(String::Format(message, params), Level::Trace);
}

/// <summary>
/// Logs the message to the DebugHigh level.
/// </summary>
/// <param name="message">The message.</param>
void LoggingWrapper::Logger::LogDebugHigh(Object^ message)
{
    LogCustom(message, Level::Verbose);
}

/// <summary>
/// Logs the message to the DebugHigh level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">The parameters.</param>
void LoggingWrapper::Logger::LogDebugHigh(String^ message, array<Object^>^ params)
{
    LogCustom(String::Format(message, params), Level::Verbose);
}

/// <summary>
/// Logs the message to the DebugAll level.
/// </summary>
/// <param name="message">The message.</param>
void LoggingWrapper::Logger::LogDebugAll(Object^ message)
{
    LogCustom(message, Level::Finest);
}

/// <summary>
/// Logs the message to the DebugAll level.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="params">The parameters.</param>
void LoggingWrapper::Logger::LogDebugAll(String^ message, array<Object^>^ params)
{
    LogCustom(String::Format(message, params), Level::Finest);
}

//Private Methods
void LoggingWrapper::Logger::Configure()
{
    log4net::Config::XmlConfigurator::Configure(gcnew System::IO::FileInfo("logger.config"));
}

Core::LoggingEvent^ LoggingWrapper::Logger::CreateLoggingEvent(String^ message, Core::Level^ level)
{
    LoggingEventData led;
    led.Message = message;
    led.Level = level;
    led.LoggerName = m_Logger->Logger->Name;
    led.TimeStamp = DateTime::Now;
    LoggingEvent^ le = gcnew LoggingEvent(led);
    return le;
}

void LoggingWrapper::Logger::LogCustom(Object^ message, Core::Level^ level)
{
    LoggingEvent^ le = CreateLoggingEvent(message->ToString(), level);
    m_Logger->Logger->Log(le);
}