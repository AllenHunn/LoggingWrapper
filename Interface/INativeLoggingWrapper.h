/*******************************************************************************
*
*	Copyright (c) 1990-2014
*
*	Avtec Inc.
*	100 Innovation Place
*	Lexington, SC 29072 USA
*	(803) 358-3600
*
*	All rights reserved. Copying, compilation, modification, distribution
*	or any other use whatsoever of this material is strictly prohibited
*	without the written consent of Avtec Inc.
*
*******************************************************************************/

/****************************************************************************/
/*!
*
*   @file INativeLoggerWrapper.h
*
*   @brief Declaration file for INativeLoggerWrapper.
*/
/****************************************************************************/

#pragma once

#include <string>
#include "Definitions.h"

/****************************************************************************/
/*!
*   @brief Interface providing access to the native C++ wrapper.
*
*   This interface allows loosely coupled access to the concrete wrapper,
*   which in turn calls the underlying logging functionality.
*
*   WARNING: Please reference only this header file.
*   Instances must be created via the CreateWrapper method within, or your
*   code will not function.
*/
/****************************************************************************/
Interface DLLAPI INativeLoggingWrapper
{
public:
    /// <summary>
    /// Creates an instance of the wrapper implementation.
    /// </summary>
    /// <param name="typeName">Name of the type that will be logged for.</param>
    /// <returns>A new instance of INativeLoggingWrapper.</returns>
    static INativeLoggingWrapper *CreateWrapper(const char *typeName);

    /// <summary>
    /// Logs the message to the specified level.
    /// </summary>
    /// <param name="message">The message.</param>
    virtual void Log(UNSIGNED32 nLevel, const char* message) = 0;

    /// <summary>
    /// Logs the message to the specified level.
    /// </summary>
    /// <param name="message">The message.</param>
    /// <param name="params">format parameters</param>
    virtual void LogFormat(UNSIGNED32 nLevel, char* message, ...) = 0;

    /// <summary>
    /// Logs the message to the Emergency level.
    /// </summary>
    /// <param name="message">The message.</param>
    virtual void LogEmergency(char* message) = 0;

    /// <summary>
    /// Logs the message to the Fatal level.
    /// </summary>
    /// <param name="message">The message.</param>
    virtual void LogFatal(char* message) = 0;

    /// <summary>
    /// Logs the message to the Error level.
    /// </summary>
    /// <param name="message">The message.</param>
    virtual void LogError(char* message) = 0;

    /// <summary>
    /// Logs the message to the Warning level.
    /// </summary>
    /// <param name="message">The message.</param>
    virtual void LogWarning(char* message) = 0;

    /// <summary>
    /// Logs the message to the Information level.
    /// </summary>
    /// <param name="message">The message.</param>
    virtual void LogInfo(char* message) = 0;
    
    /// <summary>
    /// Logs the message to the Notice level.
    /// </summary>
    /// <param name="message">The message.</param>
    virtual void LogNotice(char* message) = 0;

    /// <summary>
    /// Logs the message to the Debug level.
    /// </summary>
    /// <param name="message">The message.</param>
    virtual void LogDebug(char* message) = 0;

    /// <summary>
    /// Logs the message to the DebugMedium level.
    /// </summary>
    /// <param name="message">The message.</param>
    virtual void LogDebugMedium(char* message) = 0;

    /// <summary>
    /// Logs the message to the DebugHigh level.
    /// </summary>
    /// <param name="message">The message.</param>
    virtual void LogDebugHigh(char* message) = 0;

    /// <summary>
    /// Logs the message to the DebugAll level.
    /// </summary>
    /// <param name="message">The message.</param>
    virtual void LogDebugAll(char* message) = 0;

    /// <summary>
    /// Logs the message to the Emergency level.
    /// </summary>
    /// <param name="message">The message.</param>
    /// <param name="params">format parameters</param>
    virtual void LogEmergencyFormat(char* message, ...) = 0;

    /// <summary>
    /// Logs the message to the Fatal level.
    /// </summary>
    /// <param name="message">The message.</param>
    /// <param name="params">format parameters</param>
    virtual void LogFatalFormat(char* message, ...) = 0;

    /// <summary>
    /// Logs the message to the Error level.
    /// </summary>
    /// <param name="message">The message.</param>
    /// <param name="params">format parameters</param>
    virtual void LogErrorFormat(char* message, ...) = 0;

    /// <summary>
    /// Logs the message to the Warning level.
    /// </summary>
    /// <param name="message">The message.</param>
    /// <param name="params">format parameters</param>
    virtual void LogWarningFormat(char* message, ...) = 0;
    
    /// <summary>
    /// Logs the message to the Information level.
    /// </summary>
    /// <param name="message">The message.</param>
    /// <param name="params">format parameters</param>
    virtual void LogInfoFormat(char* message, ...) = 0;

    /// <summary>
    /// Logs the message to the Notice level.
    /// </summary>
    /// <param name="message">The message.</param>
    /// <param name="params">format parameters</param>
    virtual void LogNoticeFormat(char* message, ...) = 0;

    /// <summary>
    /// Logs the message to the Debug level.
    /// </summary>
    /// <param name="message">The message.</param>
    /// <param name="params">format parameters</param>
    virtual void LogDebugFormat(char* message, ...) = 0;

    /// <summary>
    /// Logs the message to the DebugMedium level.
    /// </summary>
    /// <param name="message">The message.</param>
    /// <param name="params">format parameters</param>
    virtual void LogDebugMediumFormat(char* message, ...) = 0;

    /// <summary>
    /// Logs the message to the DebugHigh level.
    /// </summary>
    /// <param name="message">The message.</param>
    /// <param name="params">format parameters</param>
    virtual void LogDebugHighFormat(char* message, ...) = 0;

    /// <summary>
    /// Logs the message to the DebugAll level.
    /// </summary>
    /// <param name="message">The message.</param>
    /// <param name="params">format parameters</param>
    virtual void LogDebugAllFormat(char* message, ...) = 0;

    /// <summary>
    /// Changes the logging level of the current logger dynamically.
    /// If you don't know you need to use it, it's preferable not to.
    /// </summary>
    /// <param name="nLevel">Numeric representation of a logging level.</param>
    virtual void SetLoggerLevel(UNSIGNED32 nLevel) = 0;

    /// <summary>
    /// Determines if the current logger will log for the specified level.
    /// </summary>
    /// <param name="nLevel">Numeric representation of a logging level.</param>
    virtual bool WillLog(UNSIGNED32 nLevel) = 0;

    /// <summary>
    /// Finalizes an instance of the INativeLoggingWrapper class.
    /// It is important that this be called to free unmanaged resources.
    /// </summary>
    /// <returns></returns>
    virtual ~INativeLoggingWrapper(){};
};


