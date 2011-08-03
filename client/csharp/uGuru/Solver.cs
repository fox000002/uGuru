using System;
using System.Collections.Generic;
using System.Text;

namespace huys
{
    /// <summary>
    /// 
    /// </summary>
    public class Solver
    {
        private int id;
        private string name;
        private string command;
        private string arg;

        public Solver()
        {}

        public Solver(int id, string name, string command, string arg)
        {
            this.id = id;
            this.name = name;
            this.command = command;
            this.arg = arg;
        }

        public int GetID()
        {
            return this.id;
        }

        public void SetID(int id)
        {
            this.id = id;
        }

        public string GetName()
        {
            return this.name;
        }

        public void SetName(string name)
        {
            this.name = name;
        }

        public string ToXML()
        {
            return string.Format("<solver>" +
             "<id>{0}</id>" +
            "<name>{1}</port>" +
            "<command>{2}</command>" +
            "<arg>{3}</arg>" +
            "</solver>",
            this.id, this.name, this.command, this.arg);
        }

        public override bool Equals(Object o)
        {
            //Check for null and compare run-time types.
            if (o == null || this.GetType() != o.GetType()) return false;

            Solver s = o as Solver;

            return (this.id == s.id);
        }

        public override int GetHashCode()
        {
            return this.id;
        }
    }
}
