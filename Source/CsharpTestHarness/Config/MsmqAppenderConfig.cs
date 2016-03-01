using System.Configuration;

namespace Avtec.Scout.Core.Logging.Config
{
    public class MsmqAppenderConfig : ConfigurationElement
    {
        [ConfigurationProperty("queueName", IsRequired = true)]
        public string QueueName
        {
            get { return (string) this["queueName"]; }
        }
    }
}