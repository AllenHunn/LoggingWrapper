using System.ServiceModel;
using Avtec.Scout.Core.Messaging;

namespace Avtec.Scout.Core.Logging
{
    [ServiceContract]
    public interface ILogService
    {
        [OperationContract(IsOneWay = true)]
        void WriteLog(LogMessage logMessage);
    }
}