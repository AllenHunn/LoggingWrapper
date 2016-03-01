using Avtec.Scout.Core.Logging.Config;
using log4net.Core;
using LoggingWrapper;

namespace CsharpTestHarness
{
    internal class Program
    {
        private static void Main( string[ ] args )
        {
            TestStandardConfiguration();
            TestProgrammaticallyDrivenConfiguration();
            TestStandardConfigurationSetLoggingLevel();
        }

        private static void TestStandardConfiguration()
        {
            var logger = new Logger( typeof( Program ) );
            int age = 20;
            logger.LogDebug( "Test LogDebug" );
            logger.LogDebug( new TestData( "LogDebug", age++ ) );
            logger.LogDebug( "Test LogDebug {0}", "format" );

            logger.LogDebugAll( "test LogDebugAll" );
            logger.LogDebugAll( new TestData( "LogDebugAll", age++ ) );
            logger.LogDebugAll( "test LogDebugAll {0}, did it work? {1}.", "format", "yes" );

            logger.LogDebugMedium( "test LogDebugMedium" );
            logger.LogDebugMedium( new TestData( "LogDebugMedium", age++ ) );
            logger.LogDebugMedium( "test LogDebugMedium {0}, did it work? {1}.", "format", "yes" );

            logger.LogDebugHigh( "test LogDebugHigh" );
            logger.LogDebugHigh( new TestData( "LogDebugHigh", age++ ) );
            logger.LogDebugHigh( "test LogDebugHigh {0}, did it work? {1}.", "format", "yes" );

            logger.LogInfo( "test LogInfo" );
            logger.LogInfo( new TestData( "LogInfo", age++ ) );
            logger.LogInfo( "test LogInfo {0}, did it work? {1}.", "format", "yes" );

            logger.LogError( "test LogError" );
            logger.LogError( new TestData( "LogError", age++ ) );
            logger.LogError( "test LogError {0}, did it work? {1}.", "format", "yes" );

            logger.LogEmergency( "test LogEmergency" );
            logger.LogEmergency( new TestData( "LogEmergency", age++ ) );
            logger.LogEmergency( "test LogEmergency {0}, did it work? {1}.", "format", "yes" );

            logger.LogFatal( "test LogFatal" );
            logger.LogFatal( new TestData( "LogFatal", age++ ) );
            logger.LogFatal( "test LogFatal {0}, did it work? {1}.", "format", "yes" );

            logger.LogNotice( "test LogNotice" );
            logger.LogNotice( new TestData( "LogNotice", age++ ) );
            logger.LogNotice( "test LogNotice {0}, did it work? {1}.", "format", "yes" );

            logger.LogWarning( "test LogWarning" );
            logger.LogWarning( new TestData( "LogWarning", age ) );
        }

        private static void TestStandardConfigurationSetLoggingLevel( )
        {
            var logger = new Logger( typeof( Program ) );
            logger.LogEmergency("Will log warning? {0}", logger.WillLog(Level.Warn));
            logger.SetLoggingLevel(Level.Error);
            logger.LogEmergency( "Will log warning? {0}", logger.WillLog( Level.Warn ) );

            logger.LogDebug( "Shouldn't appear." );

            logger.LogDebugAll( "Shouldn't appear." );

            logger.LogDebugMedium( "Shouldn't appear." );

            logger.LogDebugHigh( "Shouldn't appear." );

            logger.LogInfo( "Shouldn't appear." );

            logger.LogError( "Should appear." );

            logger.LogEmergency( "Should appear." );

            logger.LogFatal( "Should appear." );

            logger.LogNotice( "Shouldn't appear." );

            logger.LogWarning( "Shouldn't appear." );

            logger.SetLoggingLevel( Level.Info );

            logger.LogDebug( "Shouldn't appear." );

            logger.LogDebugAll( "Shouldn't appear." );

            logger.LogDebugMedium( "Shouldn't appear." );

            logger.LogDebugHigh( "Shouldn't appear." );

            logger.LogInfo( "Should appear." );

            logger.LogError( "Should appear." );

            logger.LogEmergency( "Should appear." );

            logger.LogFatal( "Should appear." );

            logger.LogNotice( "Should appear." );

            logger.LogWarning( "Should appear." );
        }

        private static void TestProgrammaticallyDrivenConfiguration()
        {
            var logger = new Logger();
            ScoutLogConfigurator.Initialize();
            logger.CreateLogger(typeof (Program));
            int age = 20;
            logger.LogDebug("Test LogDebug");
            logger.LogDebug(new TestData("LogDebug", age++));
            logger.LogDebug("Test LogDebug {0}", "format");

            logger.LogDebugAll("test LogDebugAll");
            logger.LogDebugAll(new TestData("LogDebugAll", age++));
            logger.LogDebugAll("test LogDebugAll {0}, did it work? {1}.", "format", "yes");

            logger.LogDebugMedium("test LogDebugMedium");
            logger.LogDebugMedium(new TestData("LogDebugMedium", age++));
            logger.LogDebugMedium("test LogDebugMedium {0}, did it work? {1}.", "format", "yes");

            logger.LogDebugHigh("test LogDebugHigh");
            logger.LogDebugHigh(new TestData("LogDebugHigh", age++));
            logger.LogDebugHigh("test LogDebugHigh {0}, did it work? {1}.", "format", "yes");

            logger.LogInfo("test LogInfo");
            logger.LogInfo(new TestData("LogInfo", age++));
            logger.LogInfo("test LogInfo {0}, did it work? {1}.", "format", "yes");

            logger.LogError("test LogError");
            logger.LogError(new TestData("LogError", age++));
            logger.LogError("test LogError {0}, did it work? {1}.", "format", "yes");

            logger.LogEmergency("test LogEmergency");
            logger.LogEmergency(new TestData("LogEmergency", age++));
            logger.LogEmergency("test LogEmergency {0}, did it work? {1}.", "format", "yes");

            logger.LogFatal("test LogFatal");
            logger.LogFatal(new TestData("LogFatal", age++));
            logger.LogFatal("test LogFatal {0}, did it work? {1}.", "format", "yes");

            logger.LogNotice("test LogNotice");
            logger.LogNotice(new TestData("LogNotice", age++));
            logger.LogNotice("test LogNotice {0}, did it work? {1}.", "format", "yes");

            logger.LogWarning("test LogWarning");
            logger.LogWarning(new TestData("LogWarning", age));
        }
    }

    internal class TestData
    {
        public TestData( string name, int age )
        {
            Name = name;
            Age = age;
        }

        public override string ToString( )
        {
            return string.Format( "Name: {0}. Age: {1}.", Name, Age );
        }

        public string Name { get; set; }

        public int Age { get; set; }
    }
}