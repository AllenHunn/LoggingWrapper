// CppTestHarness.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


void TestStandard(INativeLoggingWrapper * pWrapper);

int _tmain(int argc, _TCHAR* argv[])
{
    INativeLoggingWrapper *pWrapper = INativeLoggingWrapper::CreateWrapper("CppTestHarness");
    TestStandard(pWrapper);

    pWrapper->SetLoggerLevel(LOGGING_LEVEL_DEBUGALL);

    delete pWrapper;

	return 0;
}

void TestStandard(INativeLoggingWrapper * pWrapper)
{
    pWrapper->LogDebug("Test LogDebug");
    pWrapper->LogDebugFormat("Test LogDebug %s", "format");

    pWrapper->LogDebugAll("test LogDebugAll");
    pWrapper->LogDebugAllFormat("test LogDebugAll %s, did it work? %s.", "format", "yes");

    pWrapper->LogDebugMedium("test LogDebugMedium");
    pWrapper->LogDebugMediumFormat("test LogDebugMedium %s, did it work? %s.", "format", "yes");

    pWrapper->LogDebugHigh("test LogDebugHigh");
    pWrapper->LogDebugHighFormat("test LogDebugHigh %s, did it work? %s.", "format", "yes");

    pWrapper->LogInfo("test LogInfo");
    pWrapper->LogInfoFormat("test LogInfo %s, did it work? %s.", "format", "yes");

    pWrapper->LogError("test LogError");
    pWrapper->LogErrorFormat("test LogError %s, did it work? %s.", "format", "yes");

    pWrapper->LogEmergency("test LogEmergency");
    pWrapper->LogEmergencyFormat("test LogEmergency %s, did it work? %s.", "format", "yes");

    pWrapper->LogFatal("test LogFatal");
    pWrapper->LogFatalFormat("test LogFatal %s, did it work? %s.", "format", "yes");

    pWrapper->LogNotice("test LogNotice");
    pWrapper->LogNoticeFormat("test LogNotice %s, did it work? %s.", "format", "yes");

    pWrapper->LogWarning("test LogWarning");
    pWrapper->LogWarningFormat("test LogWarning %s, did it work? %s.", "format", "yes");
}