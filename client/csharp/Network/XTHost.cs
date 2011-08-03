using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace huys
{
    public class XTHost
    {
        public static IPAddress GetHostIP()
        {
            string hname = Dns.GetHostName();
            IPHostEntry he = Dns.GetHostEntry(hname);

            foreach (IPAddress ip in he.AddressList)
            {
                if (!IPAddress.IsLoopback(ip) && 
                    ip.AddressFamily == AddressFamily.InterNetwork)
                {
                    return ip;
                }
            }

            return null;
        }
    }
}
