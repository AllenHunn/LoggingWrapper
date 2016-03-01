#include "CPU.H"

#ifndef DEFINIIONS
#define DEFINIIONS

#define Interface class
#define implements public

#ifdef EXPORTING
#define DLLAPI  __declspec(dllexport)
#else
#define DLLAPI  __declspec(dllimport)
#pragma comment (lib, "LoggingWrapper.lib") // if importing, link also
#endif

// Logging Levels for the common interface
const SIGNED32 LOGGING_LEVEL_NONE = 0;
// FATAL - Indicates that something horribly bad has happened, and most likely,
// the system is of little use to anyone. Someone should probably be paged, and
// sirens should sound.
const SIGNED32 LOGGING_LEVEL_FATAL = 1;
// ERROR - Indicates that something bad has happened, but the error won't cause
// the system to fail in general. A specific task may have failed, and some user
// may have received an error, but the system will keep running. Exceptions are
// generally logged at this level.
const SIGNED32 LOGGING_LEVEL_ERROR = 2;
// WARNING - Signifies that something bad has happened, but the system will
// attempt to recover from it. This message usually indicates that something
// is starting to go wrong.
const SIGNED32 LOGGING_LEVEL_WARNING = 3;
// INFO - Provides informational messages about what's happening, with notable
// events including user login and logout, etc
const SIGNED32 LOGGING_LEVEL_INFO = 4;
// DEBUG - Used by the developer to understand code flow and events for
// debugging process.
const SIGNED32 LOGGING_LEVEL_DEBUGLOW = 5;
const SIGNED32 LOGGING_LEVEL_DEBUGMEDIUM = 6;
const SIGNED32 LOGGING_LEVEL_DEBUGHIGH = 7;
const SIGNED32 LOGGING_LEVEL_DEBUGALL = 8;

static const char* FATAL_STRING = "Fatal";
static const char* ERROR_STRING = "Error";
static const char* WARNING_STRING = "Warning";
static const char* INFO_STRING = "Info";
static const char* DEBUGLOW_STRING = "DebugLow";
static const char* DEBUGMEDIUM_STRING = "DebugMed";
static const char* DEBUGHIGH_STRING = "DebugHigh";
static const char* DEBUGALL_STRING = "DebugAll";

#define UNPACK_MODULE(x) (x >> 16)
#define UNPACK_LEVEL(y) (y & 0xFFFF)
#define PACK_MODULE_LEVEL(x,y)  ((x << 16) | (y & 0xFFFF))

#endif