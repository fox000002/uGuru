using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.IO;
using System.Xml.XPath;

using CustomListView = huys.UI.CustomListView;
using XTTransfer = huys.XTTransfer;


namespace test_UI
{
    public partial class FormUIDemo : Form
    {
        //private CustomListView lv = new CustomListView();

        public FormUIDemo()
        {
            //this.lv.Dock = DockStyle.Top;
            //this.lv.Height = this.Height / 2;
            //this.lv.Columns.Add("No", 90, HorizontalAlignment.Left);
            //this.lv.Columns.Add("Column 1", 90, HorizontalAlignment.Center);
            //this.lv.Columns.Add("Column 2", 90, HorizontalAlignment.Center);
            //this.lv.Columns.Add("Column 3", 90, HorizontalAlignment.Center);

            //ListViewItem lvi = new ListViewItem(new string[] { "1", "item1", "item2", "item3" });
            //ListViewGroup lvg = new ListViewGroup("Group1");

            //lvi.Group = lvg;

            //this.lv.Groups.Add(lvg);
            //this.lv.Items.Add(lvi);

            //this.Controls.Add(this.lv);

            //this.lv.AddEditableCell(-1, 1);

            //this.lv.AddComboboxCell(-1, 3, new string[] { "item1", "item2", "item3" });

            InitializeComponent();

            this.tbUrl.Text = "http://localhost:8080/submit";
        }

        private void button1_Click(object sender, EventArgs e)
        {

            try
            {   
            XmlDocument xdoc = new XmlDocument();

            xdoc.Load(new StringReader(XTTransfer.ExchangeData(this.tbUrl.Text,
                this.tbData.Text)));

            
            XPathNavigator navigator = xdoc.CreateNavigator();

            XPathExpression xpath = XPathExpression.Compile("/data[1]");

            XPathNodeIterator it = navigator.Select(xpath);;


                byte[] binaryData = Convert.FromBase64String(it.Current.Value);

                this.tbResponse.Text = Encoding.ASCII.GetString(binaryData);
                //this.tbResponse.Text = XTTransfer.ExchangeData(this.tbUrl.Text, this.tbData.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void bnNode_Click(object sender, EventArgs e)
        {
            FormNode frm = new FormNode();
            frm.ShowDialog(this);
        }

        private void bnSubmitTest_Click(object sender, EventArgs e)
        {
            try
            {    
            
            huys.Request request = new huys.Request("127.0.0.1", "8080");

            XmlDocument xdoc = new XmlDocument();

            System.Net.IPAddress ip = huys.XTHost.GetHostIP();

            string xml = string.Format("<Tasks><task from=\"{0}:{1}\"><id>1</id><name>EE</name><sid>1</sid><subdir>EXXX</subdir></task></Tasks>", 
                ip.ToString(), 8080);

            xdoc.Load(new StringReader(request.Submit(xml)));


            XPathNavigator navigator = xdoc.CreateNavigator();

            XPathExpression xpath = XPathExpression.Compile("/data[1]");

            XPathNodeIterator it = navigator.Select(xpath); ;


                byte[] binaryData = Convert.FromBase64String(it.Current.Value);

                this.tbResponse.Text = Encoding.ASCII.GetString(binaryData);
                //this.tbResponse.Text = XTTransfer.ExchangeData(this.tbUrl.Text, this.tbData.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void FormUIDemo_Load(object sender, EventArgs e)
        {

        }

        private void bnQuery_Click(object sender, EventArgs e)
        {
            try
            {
                string data = XTTransfer.DownloadData(this.tbUrl.Text);

                this.tbResponse.Text = data;
            }
            catch (Exception ex)
            {

            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofdlg = new OpenFileDialog();

            DialogResult result = ofdlg.ShowDialog();

            if (DialogResult.OK == result)
            {
                try
                {
                    byte[] data = File.ReadAllBytes(ofdlg.FileName);


                    string resp = XTTransfer.UploadData(this.tbUrl.Text, data);

                    this.tbResponse.Text = resp;
                }
                catch (Exception ex)
                {

                }
            }
        }

        private void btnPrepare_Click(object sender, EventArgs e)
        {
            try
            {
                string data = XTTransfer.DownloadData(this.tbUrl.Text);

                this.tbResponse.Text = data;
            }
            catch (Exception ex)
            {

            }
        }

        private void btnDownload_Click(object sender, EventArgs e)
        {
            try
            {
                string data = XTTransfer.DownloadData(this.tbUrl.Text);

                this.tbResponse.Text = data;
            }
            catch (Exception ex)
            {

            }
        }


    }
}
