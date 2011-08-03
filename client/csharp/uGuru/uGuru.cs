using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace huys
{
    /// <summary>
    /// 
    /// </summary>
    public sealed class uGuru
    {
        private uGuru()
        { }

        public static uGuru Instance
        {
            get
            {
                return Nested.instance;
            }
        }

        private ArrayList tasks = new ArrayList();

        private ArrayList nodes = new ArrayList();

        public Hashtable NodeTaskTable = new Hashtable();


        public ArrayList GetTasks()
        {
            return tasks;
        }

        public void Add(Task t)
        {
            if (!this.tasks.Contains(t))
            {
                this.tasks.Add(t);
            }
        }

        public ArrayList GetNodes()
        {
            return nodes;
        }

        public void Add(Node nd)
        {
            if (!this.nodes.Contains(nd))
            {
                this.nodes.Add(nd);
            }
        }

        public ArrayList GetAvailableNodes()
        {
            ArrayList al = new ArrayList();

            foreach (Node nd in nodes)
            {
                if (nd.IsOK())
                {
                    al.Add(nd);
                }
            }

            return al;
        }

        public void AddTaskToNode(Task t, Node n)
        {
            ArrayList lv;
            
            if (t == null || n == null) return;

            if (NodeTaskTable.Contains(n))
            {
                lv = NodeTaskTable[n] as ArrayList;

                if (lv.Contains(t))
                {
                    Console.WriteLine("Task {0} is already in NodeTaskList", t.GetID());
                    return;
                }

                lv.Add(t);
                return;
            }

            // Create Key-Value Pair Entry
            NodeTaskTable[n] = new ArrayList();
            lv = NodeTaskTable[n] as ArrayList;
            lv.Add(t);
        }

        public void RemoveTaskFromNode(Task t, Node n)
        {
            if (t == null || n == null) return;

            if (!NodeTaskTable.Contains(n))
            {
                Console.WriteLine("No such Entry {0} in NodeTaskList", n.GetIP());
                return;
            }

            ArrayList lv = NodeTaskTable[n] as ArrayList;

            if (!lv.Contains(t))
            {
                Console.WriteLine("Task {0} is not in NodeTaskList", t.GetID());
                return;
            }

            lv.Remove(t);
        }

        public Boolean IsNodeInTable(Node n)
        {
            if (n == null) return false;

            return NodeTaskTable.Contains(n);
        }

        public Boolean IsTaskInTable(Task t)
        {
            if (t == null) return false;

            foreach (Node n in this.NodeTaskTable.Keys)
            {
                ArrayList lv = NodeTaskTable[n] as ArrayList;
                if (lv.Contains(t))
                {
                    return true;
                }
            }

            return false;
        }

        public string DumpTaskXML()
        {
            StringBuilder xb = new StringBuilder();

            xb.AppendLine("<Tasks>");
            foreach (Task t in tasks)
            {
                xb.AppendLine(t.ToXML());
            }
            xb.AppendLine("</Tasks>");

            return xb.ToString();
        }

        public string DumpNodeXML()
        {
            StringBuilder xb = new StringBuilder();

            xb.AppendLine("<Nodes>");
            foreach (Node n in nodes)
            {
                xb.AppendLine(n.ToXML());
            }
            xb.AppendLine("</Nodes>");

            return xb.ToString();
        }

        public string DumpNodeTaskXML(Node n)
        {
            ArrayList alTasks = NodeTaskTable[n] as ArrayList;

            if (null == alTasks)
            {
                return null;
            }

            StringBuilder xb = new StringBuilder();

            xb.AppendLine("<Tasks>");
            foreach (Task t in alTasks)
            {
                xb.AppendLine(t.ToXML());
            }
            xb.AppendLine("</Tasks>");

            return xb.ToString();
        }

        class Nested
        {
            // Explicit static constructor to tell C# compiler
            // not to mark type as Before Field Initialization
            static Nested()
            { }

            internal static readonly uGuru instance = new uGuru();
        }
    }
}
