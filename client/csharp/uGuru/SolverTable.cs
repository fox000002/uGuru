using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Text;
using System.Xml;

namespace huys
{
    /// <summary>
    /// 
    /// </summary>
    public sealed class SolverTable
    {
        private SolverTable()
        { }

        public static SolverTable Instance
        {
            get
            {
                return Nested.instance;
            }
        }

        private Hashtable solvers = new Hashtable();

        public void FromXML(string fn)
        {
            try
            {
                XmlDocument xdoc = new XmlDocument();
                xdoc.Load(fn);

                XmlNodeList nodeList;
                XmlNode root = xdoc.DocumentElement;

                nodeList = root.SelectNodes("descendant::solver");

                //Change the price on the books.
                foreach (XmlNode nd in nodeList)
                {
                    int id = Convert.ToInt32(nd["id"].InnerText);

                    Solver s = new Solver(id,
                        nd["name"].InnerText,
                        nd["command"].InnerText,
                        nd["arg"].InnerText);

                    this.solvers[id] = s;
                }
            }
            catch (System.Exception ex)
            {
                Console.Write(ex.ToString());
            }
        }


        public void ClearAll()
        {
            this.solvers.Clear();
        }

        Solver FromID(int id)
        {
            return solvers[id] as Solver;
        }

        class Nested
        {
            // Explicit static constructor to tell C# compiler
            // not to mark type as Before Field Initialization
            static Nested()
            {}

            internal static readonly SolverTable instance = new SolverTable();
        }
    }
}
