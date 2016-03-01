using System.Configuration;

namespace Avtec.Scout.Core.Logging.Config
{
    public class AdoNetAppenderConfig : ConfigurationElement
    {
        [ConfigurationProperty("bufferSize", IsRequired = false, DefaultValue = 10)]
        [IntegerValidator(MinValue = 1)]
        public int BufferSize
        {
            get { return (int) this["bufferSize"]; }
        }

        [ConfigurationProperty("connectionStringName", IsRequired = true)]
        public string ConnectionStringName
        {
            get { return (string) this["connectionStringName"]; }
        }

        [ConfigurationProperty("connectionType", IsRequired = false, DefaultValue = "System.Data.SqlClient.SqlConnection, System.Data, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089")]
        public string ConnectionType
        {
            get { return (string) this["connectionType"]; }
        }
    }
}