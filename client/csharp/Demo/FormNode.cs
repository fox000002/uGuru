using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.IO;


using CustomListView = huys.UI.CustomListView;
using XTTransfer = huys.XTTransfer;
using XTNode = huys.XTNode;


namespace test_UI
{
    public partial class FormNode : Form
    {
        private CustomListView lv = new CustomListView();

        public FormNode()
        {
            InitializeComponent();

            this.lv.Dock = DockStyle.None;
            this.lv.Height = this.Height / 2;
            this.lv.Width = this.Width - 60;
            this.lv.Location = new Point(30, 200);

            this.lv.Columns.Add("Index", 90, HorizontalAlignment.Left);
            this.lv.Columns.Add("IP", 90, HorizontalAlignment.Center);
            this.lv.Columns.Add("Port", 90, HorizontalAlignment.Center);
            this.lv.Columns.Add("Name", 90, HorizontalAlignment.Center);
            this.lv.Columns.Add("Status", 90, HorizontalAlignment.Center);


            ListViewItem lvi = new ListViewItem(new string[] { "1", "127.0.0.1", "8080", "C1", "unknown"});

            this.lv.Items.Add(lvi);

            this.Controls.Add(this.lv);
        }

        private void bnTest_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem lvi in this.lv.Items)
            {
                XTNode node = new XTNode(lvi.SubItems[1].Text, lvi.SubItems[2].Text);
                if (node.IsNodeUp() && node.GetStatus() == XTNode.Status.ServiceUp)
                {
                    lvi.SubItems[4].Text = "OK";
                }
                else
                {
                    lvi.SubItems[4].Text = "Unavailable";
                }
            } 
        }

        private void bnImport_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlgOpen = new OpenFileDialog();
            dlgOpen.Title = "Choose an xml file of uGuru service nodes";
            dlgOpen.Multiselect = false;
            dlgOpen.Filter = "XML file(*.xml)|*.xml|All files (*.*)|*.*";

            if (dlgOpen.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            this.lbImport.Text = dlgOpen.FileName;

            this.load_nodefile(dlgOpen.FileName);
        }

        private void add(string ip, string port, string name)
        {
            ListViewItem lvi = new ListViewItem(new string[] { 
                this.lv.Items.Count.ToString(), ip, port, name, "unknown" });

            this.lv.Items.Add(lvi);
        }

        private void load_nodefile(string fn)
        {
            this.lv.Items.Clear();

            try
            {
                XmlDocument xdoc = new XmlDocument();
                xdoc.Load(fn);

                XmlNodeList nodeList;
                XmlNode root = xdoc.DocumentElement;

                nodeList = root.SelectNodes("descendant::node");

                //Change the price on the books.
                foreach (XmlNode nd in nodeList)
                {
                    this.add(nd["ip"].InnerText, nd["port"].InnerText, nd["name"].InnerText);
                }


            }
            catch (System.Exception ex)
            {
            }

        }

        private void bnExport_Click(object sender, EventArgs e)
        {
            SaveFileDialog dlgSave = new SaveFileDialog();
            dlgSave.Title = "Choose an xml file of uGuru service nodes";
            dlgSave.Filter = "XML file(*.xml)|*.xml|All files (*.*)|*.*";

            if (dlgSave.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            TextWriter tw = new StreamWriter(dlgSave.FileName);

            tw.WriteLine("<Nodes>");

            foreach (ListViewItem lvi in this.lv.Items)
            {
                tw.WriteLine("<node>\n" +
                    "<ip>{0}</ip>\n" +
                    "<port>{1}</port>\n" +
                    "<name>{2}</name>\n" +
                    "</node>",
                    lvi.SubItems[1].Text,
                    lvi.SubItems[2].Text,
                    lvi.SubItems[3].Text);
            }
            tw.WriteLine("</Nodes>");

            tw.Close();
        }
    }
}
