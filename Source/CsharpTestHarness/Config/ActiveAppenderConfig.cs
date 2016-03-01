using System.Collections.Generic;
using System.Configuration;

namespace Avtec.Scout.Core.Logging.Config
{
    public class ActiveAppenderConfig : ConfigurationElement
    {
        [ConfigurationProperty("name", IsRequired = true)]
        public string Name
        {
            get { return (string) this["name"]; }
        }
    }

    #region Collection class

    public class ActiveAppenderConfigCollection : ConfigurationElementCollection, IEnumerable<ActiveAppenderConfig>
    {
        private readonly List<ActiveAppenderConfig> _elements;

        public ActiveAppenderConfigCollection()
        {
            _elements = new List<ActiveAppenderConfig>();
        }

        protected override ConfigurationElement CreateNewElement()
        {
            ActiveAppenderConfig element = new ActiveAppenderConfig();
            _elements.Add(element);

            return element;
        }

        protected override object GetElementKey(ConfigurationElement element)
        {
            return ((ActiveAppenderConfig) element).Name;
        }

        public new IEnumerator<ActiveAppenderConfig> GetEnumerator()
        {
            return _elements.GetEnumerator();
        }
    }

    #endregion
}