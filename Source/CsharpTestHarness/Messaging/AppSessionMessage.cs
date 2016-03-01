using System;
using System.Xml.Serialization;

namespace Avtec.Scout.Core.Messaging
{
    [Serializable]
    [XmlRoot]
    public class AppSessionMessage
    {
        public int Id { get; set; }
        public int TenantId { get; set; }
        public string AppSessionId { get; set; }
        public DateTime Timestamp { get; set; }
        public string HostName { get; set; }
        public string UserName { get; set; }
        public int UserId { get; set; }
        public string ClientIpAddress { get; set; }
        public string ClientBrowserName { get; set; }
        public string ClientBrowserVersion { get; set; }
        public string ClientPlatform { get; set; }
    }
}