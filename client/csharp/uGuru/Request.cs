using System;
using System.Collections.Generic;
using System.Text;

namespace huys
{
    /// <summary>
    /// 
    /// </summary>
    public class Request
    {
        private string host;
        private string port;

        public Request(string host)
        {
            this.host = host;
            this.port = "8080";
        }

        public Request(string host, string port)
        {
            this.host = host;
            this.port = port;
        }

        public string ServerInfo()
        {
            return XTTransfer.DownloadData("http://" + host + ":" + port+ "/server_info");
        }

        public string ServerState()
        {
            return XTTransfer.DownloadData("http://" + host + ":" + port + "/server_state");
        }

        public string Submit(string msg)
        {
            return XTTransfer.ExchangeData("http://" + host + ":" + port + "/submit", msg);
        }

        public string Query()
        {
            return XTTransfer.DownloadData("http://" + host + ":" + port + "/query");
        }


        public string Terminate()
        {
            return XTTransfer.DownloadData("http://" + host + ":" + port + "/terminate");
        }
    }
}
