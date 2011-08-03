using System;
using System.Collections.Generic;
using System.Text;

namespace huys
{
    /// <summary>
    /// 
    /// </summary>
    public class Node
    {
        public enum NodeStatus
        {
            OK      = 0,
            DOWN    = 1,
            Unknown = 2
        }

        private string ip;
        private string port;
        private string name;

        private NodeStatus status = NodeStatus.Unknown;

        public Node()
        {}

        public Node(string ip, string port, string name)
        {
            this.ip = ip;
            this.port = port;
            this.name = name;
        }

        public NodeStatus Status()
        {
            return this.status;
        }

        public bool IsOK()
        {
            return this.status == NodeStatus.OK;
        }

        public void SetStatus(NodeStatus status)
        {
            this.status = status;
        }

        public string GetIP()
        {
            return this.ip;
        }

        public string ToXML()
        {
            return string.Format("<node>" +
             "<ip>{0}</ip>" +
            "<port>{1}</port>" +
            "<name>{2}</name>" +
            "</node>",
            this.ip, this.port, this.name);
        }

        public override bool Equals(Object o)
        {
            //Check for null and compare run-time types.
            if (o == null || this.GetType() != o.GetType()) return false;

            Node n = o as Node;

            return (this.ip == n.ip);
        }

        public override int GetHashCode()
        {
            return this.ip.GetHashCode();
        }
    }
}
