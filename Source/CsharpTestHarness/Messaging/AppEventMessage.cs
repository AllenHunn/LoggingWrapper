using System;
using System.Xml.Serialization;

namespace Avtec.Scout.Core.Messaging
{
    [Serializable]
    [XmlRoot]
    public class AppEventMessage
    {
        public int Id { get; set; }
        public string AppSessionId { get; set; }
        public string TraceId { get; set; }
        public DateTime Timestamp { get; set; }
        public string EventType { get; set; }
        public string HostName { get; set; }
        public int Data1 { get; set; }
        public string Data2 { get; set; }
        public string Data3 { get; set; }
    }
}