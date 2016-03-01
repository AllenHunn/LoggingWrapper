using System;
using System.Configuration;
using System.Data;
using System.Diagnostics;
using log4net;
using log4net.Appender;
using log4net.Config;
using log4net.Core;
using log4net.Layout;
using log4net.Repository.Hierarchy;

namespace Avtec.Scout.Core.Logging.Config
{
    public static class ScoutLogConfigurator
    {
        public static void Initialize()
        {
            Initialize(null, null, null);
        }

        public static void Initialize(object objSessionId, object objTraceId, object objCurrentUserName, string appName = null)
        {
            try {
                // Make sure there's a scoutLog config section
                ScoutLogConfigSection scoutLogConfig = ConfigurationManager.GetSection("scoutLog") as ScoutLogConfigSection;
                if (scoutLogConfig == null) {
                    Trace.TraceError("Configuration section 'scoutLog' not found.");
                    return;
                }

                // Make sure there's at least 1 appender configured
                if (scoutLogConfig.ActiveAppenders.Count == 0) {
                    Trace.TraceError("No appenders configured in scoutLog configuration section.");
                    return;
                }

                // log4net general settings
                Hierarchy hierarchy = (Hierarchy) LogManager.GetRepository();
                hierarchy.Root.RemoveAllAppenders(); /*Remove any other appenders*/
                hierarchy.Root.Level = LevelFromString(scoutLogConfig.Level);

                // Appenders
                bool anySuccessfulAppenders = false;
                foreach (ActiveAppenderConfig activeAppenders in scoutLogConfig.ActiveAppenders) {
                    if (activeAppenders.Name.ToLower() == "rollingfileappender") {
                        if (ConfigureRollingFileAppender(scoutLogConfig.RollingFileAppender))
                            anySuccessfulAppenders = true;
                    } else if (activeAppenders.Name.ToLower() == "adonetappender") {
                        if (ConfigureAdoNetAppender(scoutLogConfig.AdoNetAppender))
                            anySuccessfulAppenders = true;
                    } else if (activeAppenders.Name.ToLower() == "msmqappender") {
                        if (ConfigureMsmqAppender(scoutLogConfig.MsmqAppender))
                            anySuccessfulAppenders = true;
                    } else {
                        Trace.TraceWarning("Unrecognized appender name: {0}", activeAppenders.Name);
                    }
                }
                if (!anySuccessfulAppenders) {
                    Trace.TraceError("No appenders successfully configured. No logging currently functioning.");
                    return;
                }

                // Global Properties
                GlobalContext.Properties[LogConstants.HostName] = Environment.MachineName;
                GlobalContext.Properties[LogConstants.AppName] = appName ?? scoutLogConfig.AppName;
                GlobalContext.Properties[LogConstants.SessionId] = objSessionId;
                GlobalContext.Properties[LogConstants.TraceId] = objTraceId;
                GlobalContext.Properties[LogConstants.CurrentUser] = objCurrentUserName;
            } catch (Exception ex) {
                Trace.TraceError("{0} reading scoutLog configuration section: {1}", ex.GetType().Name, ex);
                throw;
            }
        }

        private static Level LevelFromString(string levelStr)
        {
            string lowerLevelStr = levelStr.ToLower();
            if (lowerLevelStr == "debug")
                return Level.Debug;
            if (lowerLevelStr == "info")
                return Level.Info;
            if (lowerLevelStr == "warn")
                return Level.Warn;
            if (lowerLevelStr == "error")
                return Level.Error;
            if (lowerLevelStr == "fatal")
                return Level.Fatal;

            Trace.TraceError("Unable to parse scoutLog 'Level' configuration item ({1}). Using the default level 'Info'", levelStr);
            return Level.Info;
        }

        private static bool ConfigureRollingFileAppender(RollingFileAppenderConfig config)
        {
            try {
                if (string.IsNullOrEmpty(config.File)) {
                    Trace.TraceError("RollingFileAppender configuration missing 'File' value. Unable to log to RollingFileAppender.");
                    return false;
                }

                RollingFileAppender rollingFileAppender = new RollingFileAppender();
                rollingFileAppender.File = config.File;
                rollingFileAppender.AppendToFile = true;
                rollingFileAppender.MaxFileSize = config.MaxFileSize;
                rollingFileAppender.MaxSizeRollBackups = config.MaxSizeRollBackups;
                PatternLayout patternLayout = new PatternLayout();
                patternLayout.ConversionPattern = "%level`%utcdate{ISO8601}`%property{HostName}`%property{AppName}`%logger`%message`%property{CurrentUser}`%username`%property{AppSessionId}`%thread`%property{TraceId}`%exception%newline";
                patternLayout.ActivateOptions();
                rollingFileAppender.Layout = patternLayout;
                rollingFileAppender.ActivateOptions();
                BasicConfigurator.Configure(rollingFileAppender);

                return true;
            } catch (Exception ex) {
                Trace.TraceError("{0} attempting to configure RollingFileAppender: {1}", ex);
                return false;
            }
        }

        private static bool ConfigureAdoNetAppender(AdoNetAppenderConfig config)
        {
            try {
                //var connStr = ConfigurationManager.ConnectionStrings[connStringName].ConnectionString;
                string defConnectionType = "System.Data.SqlClient.SqlConnection, System.Data, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089";

                AdoNetAppender adoNetAppender = new AdoNetAppender();
                adoNetAppender.BufferSize = config.BufferSize;
                adoNetAppender.ConnectionStringName = config.ConnectionStringName;
                adoNetAppender.ConnectionType = string.IsNullOrEmpty(config.ConnectionType) ? defConnectionType : config.ConnectionType;
                adoNetAppender.CommandType = CommandType.Text;
                adoNetAppender.CommandText =
                    "INSERT INTO Log ([LogLevel],[LogTimestamp],[HostName],[AppName],[LogSource],[CurrentUser],[LogMessage],[AppSessionId],[Thread],[TraceId],[Exception]) VALUES (@LogLevel, @LogTimestamp, @HostName, @AppName, @LogSource, @CurrentUser, @LogMessage, @AppSessionId, @Thread, @TraceId, @Exception)";

                AdoNetAppenderParameter param = new AdoNetAppenderParameter();
                param.ParameterName = "@LogLevel";
                param.DbType = DbType.String;
                param.Size = 10;
                param.Layout = new Layout2RawLayoutAdapter(GetPatternLayout("%level"));
                adoNetAppender.AddParameter(param);

                param = new AdoNetAppenderParameter();
                param.ParameterName = "@LogTimestamp";
                param.DbType = DbType.DateTime;
                param.Layout = new RawUtcTimeStampLayout();
                adoNetAppender.AddParameter(param);

                param = new AdoNetAppenderParameter();
                param.ParameterName = "@HostName";
                param.DbType = DbType.String;
                param.Size = 100;
                param.Layout = new Layout2RawLayoutAdapter(GetPatternLayout("%property{HostName}"));
                adoNetAppender.AddParameter(param);

                param = new AdoNetAppenderParameter();
                param.ParameterName = "@AppName";
                param.DbType = DbType.String;
                param.Size = 100;
                param.Layout = new Layout2RawLayoutAdapter(GetPatternLayout("%property{AppName}"));
                adoNetAppender.AddParameter(param);

                param = new AdoNetAppenderParameter();
                param.ParameterName = "@LogSource";
                param.DbType = DbType.String;
                param.Size = 200;
                param.Layout = new Layout2RawLayoutAdapter(GetPatternLayout("%logger"));
                adoNetAppender.AddParameter(param);

                param = new AdoNetAppenderParameter();
                param.ParameterName = "@CurrentUser";
                param.DbType = DbType.String;
                param.Size = 200;
                param.Layout = new Layout2RawLayoutAdapter(GetPatternLayout("%property{CurrentUser}"));
                adoNetAppender.AddParameter(param);

                param = new AdoNetAppenderParameter();
                param.ParameterName = "@LogMessage";
                param.DbType = DbType.String;
                param.Size = 2000;
                param.Layout = new Layout2RawLayoutAdapter(GetPatternLayout("%message"));
                adoNetAppender.AddParameter(param);

                param = new AdoNetAppenderParameter();
                param.ParameterName = "@AppSessionId";
                param.DbType = DbType.String;
                param.Size = 88;
                param.Layout = new Layout2RawLayoutAdapter(GetPatternLayout("%property{AppSessionId}"));
                adoNetAppender.AddParameter(param);

                param = new AdoNetAppenderParameter();
                param.ParameterName = "@Thread";
                param.DbType = DbType.String;
                param.Size = 20;
                param.Layout = new Layout2RawLayoutAdapter(GetPatternLayout("%thread"));
                adoNetAppender.AddParameter(param);

                param = new AdoNetAppenderParameter();
                param.ParameterName = "@TraceId";
                param.DbType = DbType.String;
                param.Size = 50;
                param.Layout = new Layout2RawLayoutAdapter(GetPatternLayout("%property{TraceId}"));
                adoNetAppender.AddParameter(param);

                param = new AdoNetAppenderParameter();
                param.ParameterName = "@exception";
                param.DbType = DbType.String;
                param.Size = 2000;
                param.Layout = new Layout2RawLayoutAdapter(new ExceptionLayout());
                adoNetAppender.AddParameter(param);

                adoNetAppender.ActivateOptions();

                BasicConfigurator.Configure(adoNetAppender);

                return true;
            } catch (Exception ex) {
                Trace.TraceError("{0} attempting to configure AdoNetAppender: {1}", ex);
                return false;
            }
        }

        private static bool ConfigureMsmqAppender(MsmqAppenderConfig config)
        {
            try {
                MsmqAppender msmqAppender = new MsmqAppender();
                msmqAppender.QueueName = config.QueueName;
                msmqAppender.ActivateOptions();
                BasicConfigurator.Configure(msmqAppender);

                return true;
            } catch (Exception ex) {
                Trace.TraceError("{0} attempting to configure AdoNetAppender: {1}", ex);
                return false;
            }
        }

        private static PatternLayout GetPatternLayout(string pattern)
        {
            PatternLayout patternLayout = new PatternLayout
            {
                ConversionPattern = pattern
            };
            patternLayout.ActivateOptions();
            return patternLayout;
        }
    }
}