using System.Configuration;

namespace Avtec.Scout.Core.Logging.Config
{
    public class RollingFileAppenderConfig : ConfigurationElement
    {
        [ConfigurationProperty("file", IsRequired = true)]
        public string File
        {
            get { return (string) this["file"]; }
        }

        [ConfigurationProperty("maxFileSize", IsRequired = true, DefaultValue = 10000000)]
        [IntegerValidator(MinValue = 10000)]
        public int MaxFileSize
        {
            get { return (int) this["maxFileSize"]; }
        }

        [ConfigurationProperty("maxSizeRollBackups", IsRequired = true, DefaultValue = 1)]
        [IntegerValidator(MinValue = 1)]
        public int MaxSizeRollBackups
        {
            get { return (int) this["maxSizeRollBackups"]; }
        }
    }
}