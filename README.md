# LoggingWrapper
C++/CLI Wrapper for Log4Net to allow Log4Net to be used consistently across .Net applications and native C++.

#Problem
There are currently multiple logging solutions being used by various applications. This not only makes writing a universal parser impossible, but the lack of a common code base makes for poor extensibility and troublesome maintenance. 
#Solution
The solution to the problem was to create a managed C++ library that exposed an interface that could be consumed by native applications. 

##Managed
* LoggingWrapper.Logger(string typename)
* LoggingWrapper.Logger(Type type)

##Unmanaged
*	INativeLoggingWrapper in Interface/INativeLoggingWrapper.h

Notes on usage
##Managed : LoggingWrapper.Logger
The LoggingWrapper namespace contains a class called Logger. All methods are annotated and should be self-explanatory.  There are three constructors; however, the parameterless constructor requires the configuration settings be set manually before initializing a logger. Similarly, calling CreateLogger is generally unnecessary, unless the configuration settings were done manually. Unless there is a specific need to do so, it is generally recommended to use one of the two default constructors, passing in the name or type of the object that is being logged. 

##Unmanaged : INativeLoggingWrapper
The INativeLoggingWrapper.h located in the interface folder contains definitions for the methods being exposed to native applications. It is extremely important that only this header be included, and that the static INativeLoggingWrapper *CreateWrapper(const char *typeName); method be used for instantiation. There are complications when including managed members in an unmanaged class and attempting to utilize the concrete implementation directly will cause compilation errors. Please note, despite the logger being managed, it is important to call the destructor so that the pinned pointer can be released and the object made eligible for garbage collection. 

#Examples
##Managed
```cpp
var logger = new Logger( typeof( Program ) );
logger.LogDebug( "Test LogDebug" );
logger.LogDebug( "Test LogDebug {0}", "string" );
```

##Unmanaged
```cpp
INativeLoggingWrapper *pWrapper = INativeLoggingWrapper::CreateWrapper("CppTestHarness");
pWrapper->LogDebug("Test LogDebug");
pWrapper->LogDebugFormat("Test LogDebug %s", "string");
```

#Technical Notes
| Problem        | Solution           |
| ------------- |:-------------|
|Unmanaged classes can’t contain managed members|	gcroot in #include <vcclr.h> provides a wrapper that “pins” the managed object into the unmanaged heap. The result is a native pointer to a managed application. It must be destroyed, as it is completely unmanaged and will not be collected by the gc.|
|Native projects compiled without the /CLR can’t reference any CLR classes. In other words, if UnManagedClass lives in UnmanagedDll and references MixedMode.h, compilation will fail.|	A native wrapper that pure native projects reference through an interface header that contains no CLR elements. Hence the INativeWrapper.h and its factory method. The native consumer has no idea that it’s referencing managed objects under the hood.|

