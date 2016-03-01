using System;
using System.Diagnostics;
using System.Messaging;
using System.Net.Security;
using System.ServiceModel;
using Avtec.Scout.Core.Messaging;
using log4net.Appender;
using log4net.Core;

namespace Avtec.Scout.Core.Logging
{
    public class MsmqAppender : AppenderSkeleton
    {
        private bool _queueWorking = true;

        #region Initialization / Finalization

        public override void ActivateOptions()
        {
            if (this.MessageQueue != null) {
                this.MessageQueue.Dispose();
                this.MessageQueue = null;
            }
            try {
                this.MessageQueue = new MessageQueue(QueueName);
                _queueWorking = true;
            } catch {
                _queueWorking = false;
            }
        }

        protected override void OnClose()
        {
            if (this.MessageQueue != null)
                this.MessageQueue.Dispose();
        }

        #endregion

        #region Properties

        private MessageQueue MessageQueue { get; set; }
        public string QueueName { get; set; }

        #endregion

        protected override bool PreAppendCheck()
        {
            return _queueWorking;
        }

        protected override void Append(LoggingEvent loggingEvent)
        {
            try {
                loggingEvent.Fix = FixFlags.Partial;
                LogMessage logItem = new LogMessage
                {
                    LogLevel = GetLogLevel(loggingEvent.Level),
                    UtcTimestamp = loggingEvent.TimeStamp.ToUniversalTime(),
                    HostName = loggingEvent.Properties[LogConstants.HostName] != null ? loggingEvent.Properties[LogConstants.HostName].ToString() : null,
                    AppName = loggingEvent.Properties[LogConstants.AppName] != null ? loggingEvent.Properties[LogConstants.AppName].ToString() : null,
                    Source = loggingEvent.LoggerName,
                    Message = loggingEvent.RenderedMessage,
                    CurrentUser = loggingEvent.Properties[LogConstants.CurrentUser] != null ? loggingEvent.Properties[LogConstants.CurrentUser].ToString() : null,
                    SessionId = loggingEvent.Properties[LogConstants.SessionId] != null ? loggingEvent.Properties[LogConstants.SessionId].ToString() : null,
                    ThreadId = loggingEvent.ThreadName,
                    TraceId = loggingEvent.Properties[LogConstants.TraceId] != null ? loggingEvent.Properties[LogConstants.TraceId].ToString() : null,
                    ExceptionType = loggingEvent.ExceptionObject != null ? loggingEvent.ExceptionObject.GetType().Name : null,
                    Exception = loggingEvent.ExceptionObject != null ? loggingEvent.ExceptionObject.ToString() : null
                };

                // Send the message
                //Message queueMessage = new Message(logItem);
                //queueMessage.AppSpecific = (int)MessageType.Log;
                //this.MessageQueue.Send(queueMessage);

                ILogService client = GetLogServiceClient();
                client.WriteLog(logItem);
            } catch (Exception ex) {
                Trace.WriteLine(string.Format("[{0}] {1} attempting to send message. Error details: {2}", this.GetType().Name, ex.GetType().Name, ex));
            }
        }

        private ILogService GetLogServiceClient()
        {
            NetMsmqBinding binding = new NetMsmqBinding();
            binding.ExactlyOnce = false;
            binding.Security.Mode = NetMsmqSecurityMode.None;
            binding.Security.Transport.MsmqAuthenticationMode = MsmqAuthenticationMode.None;
            binding.Security.Transport.MsmqProtectionLevel = ProtectionLevel.None;
            EndpointAddress endpointAddress = new EndpointAddress("net.msmq://localhost/private/ScoutLogging");
            return new ChannelFactory<ILogService>(binding, endpointAddress).CreateChannel();
        }

        private LogLevel GetLogLevel(Level level)
        {
            if (level.Value == Level.Debug.Value)
                return LogLevel.Debug;
            if (level.Value == Level.Info.Value)
                return LogLevel.Info;
            if (level.Value == Level.Warn.Value)
                return LogLevel.Warn;
            if (level.Value == Level.Error.Value)
                return LogLevel.Error;
            return LogLevel.Fatal;
        }
    }
}