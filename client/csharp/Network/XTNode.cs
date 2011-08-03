using System;
using System.Net.Sockets;
using System.Net;
using System.Net.NetworkInformation;

namespace huys
{
    /// <summary>
    /// uGuru Service Node.
    /// </summary>
    public class XTNode
    {
        public enum Status
        {
            Available   = 0,
            Unavailable = 1,
			ServiceDown = 2,
            ServiceUp   = 4,
            Unknown      = 8
        }


        private string ip;
        private string port;
        private string name;
        private Status status;

        /// <summary>
        /// uGuru Service Node.
        /// </summary>
        public XTNode()
        {

        }

        public XTNode(string ip, string port)
        {
            this.ip = ip;
            this.port = port;
            this.name = "";
            this.status = Status.Unknown;
        }

        public XTNode(string ip, string port, string name)
        {
            this.ip = ip;
            this.port = port;
            this.name = name;
            this.status = Status.Unknown;
        }

        public string GetIP()
        {
            return this.ip;
        }

        public string GetPort()
        {
            return this.port;
        }

        public string GetName()
        {
            return this.name;
        }     

        public Status GetStatus()
        {
            return this.status;
        }

        public bool IsNodeUp()
        {
            Ping pingSender = new Ping();
            PingReply reply = pingSender.Send(ip);

            if (reply.Status == IPStatus.Success)
            {
                this.status = Status.Available;
            }
            else
            {
                this.status = Status.Unavailable;
                return false;
            }


            string sinfo = XTTransfer.DownloadData(String.Format("http://{0}:{1}/server_info", ip, port));

            if (null == sinfo)
            {
                this.status = Status.ServiceDown;
                return false;
            }

            this.status = Status.ServiceUp;
            return true;
        }
    }
}
