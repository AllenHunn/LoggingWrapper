using System;
using System.Xml.Serialization;
using Avtec.Scout.Core.Logging;

namespace Avtec.Scout.Core.Messaging
{
    [Serializable]
    [XmlRoot]
    public class LogMessage
    {
        public LogLevel LogLevel { get; set; }
        public DateTime UtcTimestamp { get; set; }
        public string HostName { get; set; }
        public string AppName { get; set; }
        public string Source { get; set; }
        public string RemoteIpAddr { get; set; }
        public string CurrentUser { get; set; }
        public string Message { get; set; }
        public string SessionId { get; set; }
        public string ThreadId { get; set; }
        public string TraceId { get; set; }
        public string ExceptionType { get; set; }
        public string Exception { get; set; }
    }
}