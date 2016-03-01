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
*   @file LoggingWrapper.h
*
*   @brief Declaration file for LoggingWrapper, a managed C++ class.
*/
/****************************************************************************/

#pragma once

#include <string>

using namespace std;
using namespace System;
using namespace System::Threading::Tasks;
using namespace log4net;
using namespace log4net::Core;
using namespace log4net::Config;

namespace LoggingWrapper {
    /// <summary>
    /// Wraps up all functionality required for logging.
    /// </summary>
    public ref class Logger
	{  
    public:
        Logger();
        Logger(String^ typeName);
        Logger(Type^ type);
        ~Logger();

        void SetLoggingLevel(Level^ level);
        bool WillLog(Level^ level);

        void CreateLogger(String^ typeName);
        void CreateLogger(Type^ type);

        void LogEmergency(Object^ message);
        void LogFatal(Object^ message);
        void LogError(Object^ message);
        void LogWarning(Object^ message);
        void LogInfo(Object^ message);
        void LogNotice(Object^ message);

        void LogDebug(Object^ message);
        void LogDebugMedium(Object^ message);
        void LogDebugHigh(Object^ message);
        void LogDebugAll(Object^ message);     

        void LogEmergency(String^ message, ... array<Object^>^ params);
        void LogFatal(String^ message, ... array<Object^>^ params);
        void LogError(String^ message, ... array<Object^>^ params);
        void LogWarning(String^ message, ... array<Object^>^ params);
        void LogInfo(String^ message, ... array<Object^>^ params);
        void LogNotice(String^ message, ... array<Object^>^ params);

        void LogDebug(String^ message, ... array<Object^>^ params);
        void LogDebugMedium(String^ message, ... array<Object^>^ params);
        void LogDebugHigh(String^ message, ... array<Object^>^ params);
        void LogDebugAll(String^ message, ... array<Object^>^ params);

    internal:
        void Log(Level^ level, Object^ message);
        void Log(Level^ level, String^ message, ... array<Object^>^ params);

    private:
        ILog^ m_Logger;
        void Configure();
        Core::LoggingEvent^ CreateLoggingEvent(String^ message, Core::Level^ level);
        void LogCustom(Object^ message, Core::Level^ level);
    };
}