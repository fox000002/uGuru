using System;
using System.Collections.Generic;
using System.Text;

namespace huys
{
    /// <summary>
    /// 
    /// </summary>
    public class Task
    {
        private int id;
        private string name;
        private Solver solver;
        private string subdir;
        private string[] files;

        public Task()
        {

        }

        public Task(int id, string name, string subdir)
        {
            this.id = id;
            this.name = name;
            this.solver = null;
            this.subdir = subdir;
            this.files = null;
        }


        public Task(int id, string name, Solver solver, string subdir)
        {
            this.id = id;
            this.name = name;
            this.solver = solver;
            this.subdir = subdir;
            this.files = null;
        }

        public Task(int id, string name, Solver solver, string subdir, string[] files)
        {
            this.id = id;
            this.name = name;
            this.solver = solver;
            this.subdir = subdir;
            this.files = files;
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

        public Solver GetSolver()
        {
            return this.solver;
        }

        public int GetSolverID()
        {
            return this.solver.GetID();
        }

        public void SetSolver(Solver s)
        {
            this.solver = s;
        }

        public string GetSubdir()
        {
            return this.subdir;
        }

        public void SetSubdir(string dir)
        {
            this.subdir = dir;
        }

        public string ToXML()
        {
            return string.Format("<solver>" + 
             "<id>{0}</id>" +
            "<name>{1}</name>" +
            "<sid>{2}<sid>" +
            "<subdir>{3}</subdir>" +
            "</solver>",
            this.id, this.name, this.solver.GetID(), this.subdir);
        }

        public override bool Equals(Object o)
        {
            //Check for null and compare run-time types.
            if (o == null || this.GetType() != o.GetType()) return false;

            Task t = o as Task;

            return (this.id == t.id);
        }

        public override int GetHashCode()
        {
            return this.id;
        }

    }
}
