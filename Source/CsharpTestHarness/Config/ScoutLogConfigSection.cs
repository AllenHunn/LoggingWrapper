using System;
using System.Configuration;

namespace Avtec.Scout.Core.Logging.Config
{
    [Serializable]
    public class ScoutLogConfigSection : ConfigurationSection
    {
        [ConfigurationProperty("appName", IsRequired = true)]
        public string AppName
        {
            get { return (string) this["appName"]; }
        }

        [ConfigurationProperty("level", IsRequired = true)]
        public string Level
        {
            get { return (string) this["level"]; }
        }

        [ConfigurationProperty("appenders")]
        [ConfigurationCollection(typeof (ActiveAppenderConfigCollection), AddItemName = "appender")]
        public ActiveAppenderConfigCollection ActiveAppenders
        {
            get { return (ActiveAppenderConfigCollection) this["appenders"]; }
        }

        [ConfigurationProperty("rollingFileAppender", IsRequired = false)]
        public RollingFileAppenderConfig RollingFileAppender
        {
            get { return this["rollingFileAppender"] as RollingFileAppenderConfig; }
        }

        [ConfigurationProperty("adoNetAppender", IsRequired = false)]
        public AdoNetAppenderConfig AdoNetAppender
        {
            get { return this["adoNetAppender"] as AdoNetAppenderConfig; }
        }

        [ConfigurationProperty("msmqAppender", IsRequired = false)]
        public MsmqAppenderConfig MsmqAppender
        {
            get { return this["msmqAppender"] as MsmqAppenderConfig; }
        }
    }
}