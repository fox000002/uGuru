using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace huys.UI
{
    public partial class CustomListView : ListView
    {
        private TextBox EmEdit;
        private ComboBox EmCombo;

        private ListViewItem lvi = null;
        private Point pt;
        private int nSubItemSelected = 0;
        //private string SubItemText = "";

        //
        private int row;
        private int col;

        //
        private Hashtable customCells = new Hashtable(); 

        //
        ContextMenuStrip MenuContext = new ContextMenuStrip();

        ArrayList ToolStripMenuItemList = new ArrayList(); 
        //
        [StructLayout(LayoutKind.Sequential)]
        internal struct RECT
        {
            public int left;
            public int top;
            public int right;
            public int bottom;
        }

        internal class Win32
        {
            //
            public const int LVM_GETSUBITEMRECT = (0x1000) + 56;
            //
            public const int LVIR_BOUNDS = 0;
            //
            [DllImport("User32.dll", EntryPoint = "SendMessageA")]
            public static extern int SendMessage(IntPtr hWnd, int MessageId, int wParam, ref RECT lParam);
        }

        internal class SubItem
        {
            public readonly int row;
            public readonly int col;
            public SubItem(int row, int col)
            {
                this.row = row;
                this.col = col;
            }
        }

        internal enum CellType
        {
            PLAIN_CELL    = 0x00,
            EDITABLE_CELL = 0x01,
            COMBOBOX_CELL = 0x02
        }

        public static string symEnable = "√";
        public static string symDisable = "X";

        internal class CellData
        {
            public CellType t = CellType.PLAIN_CELL;
            public object data = null;

            public CellData(CellType t)
            {
                this.t = t;
            }

            public CellData(CellType t, object data)
            {
                this.t = t;
                this.data = data;
            }
        }

        public CustomListView()
        {
            InitializeComponent();

            this.EmEdit = new TextBox();
            this.EmEdit.Size = new Size(0, 0);
            this.EmEdit.Location = new Point(0, 0);
            this.EmEdit.Font = new Font("SimSun", 10F, FontStyle.Regular, GraphicsUnit.Point, 0);
            this.EmEdit.BackColor = Color.LightYellow;
            this.EmEdit.BorderStyle = BorderStyle.Fixed3D;
            this.EmEdit.Text = "";
            this.EmEdit.KeyPress += new KeyPressEventHandler(this.EmEdit_KeyPress);
            this.EmEdit.LostFocus += new EventHandler(this.EmEdit_LostFocus);

            this.Controls.Add(this.EmEdit);

            //
            this.EmCombo = new ComboBox();
            this.EmCombo.Size = new Size(0, 0);
            this.EmCombo.Location = new Point(0, 0);
            this.EmCombo.Font = new Font("SimSun", 10F, FontStyle.Regular, GraphicsUnit.Point, 0);
            this.EmCombo.BackColor = Color.SkyBlue;
            this.EmCombo.DropDownStyle = ComboBoxStyle.DropDownList;
            this.EmCombo.SelectedIndexChanged += new EventHandler(this.EmCombo_SelectedIndexChanged);
            this.EmCombo.LostFocus += new EventHandler(EmCombo_LostFocus);
            this.EmCombo.KeyPress += new KeyPressEventHandler(EmCombo_KeyPress);

            this.Controls.Add(this.EmCombo);

            //this.Dock = DockStyle.Fill;
            this.Font = new Font("SimSun", 9.75F, FontStyle.Regular, GraphicsUnit.Point, 0);
            this.FullRowSelect = true;
            this.Name = "CustomListView";
            this.Size = new Size(0, 0);
            this.TabIndex = 0;
            this.View = View.Details;
            this.GridLines = true;
            this.ShowGroups = true;
            this.MouseDown += new MouseEventHandler(OnMouseDown);
            this.MouseUp += new MouseEventHandler(this.OnMouseUp);
            this.MouseDoubleClick += new MouseEventHandler(this.OnMouseDoubleClick);
        }

        void OnMouseDown(object sender, MouseEventArgs e)
        {
            //this.EmEdit.Hide();
            //this.EmCombo.Hide();

            ListViewHitTestInfo info = this.HitTest(e.X, e.Y);

            if (null == info || this.lvi != info.Item)
            {
                this.EmEdit.Hide();
                this.EmCombo.Hide();
            }
        }

        void EmCombo_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 13 || e.KeyChar == 27)
            {
                this.EmCombo.Hide();
            }
        }

        void EmCombo_LostFocus(object sender, EventArgs e)
        {
            this.EmCombo.Size = new Size(0, 0);
            this.EmCombo.Hide();
        }

        //
        private void EmCombo_SelectedIndexChanged(object sender, EventArgs e)
        {
            int sel = this.EmCombo.SelectedIndex;
            if (sel != -1)
            {
                string ItemText = this.EmCombo.Items[sel].ToString();
                this.lvi.SubItems[nSubItemSelected].Text = ItemText;
            }
        }

        private void OnMouseUp(object sender, MouseEventArgs e)
        {
            //this.lvi = this.GetItemAt(e.X, e.Y);
            this.pt = new Point(e.X, e.Y);

            if (e.Button == MouseButtons.Right)
            {
                ListViewHitTestInfo info = this.HitTest(e.X, e.Y);

                ListViewItem item = info.Item;

                if (null != item)
                {
                    ListViewGroup lvg = item.Group;
                    if (null != lvg)
                    {
                        
                        //ToolStripMenuItem header = new ToolStripMenuItem(lvg.Header);

                        //MenuContext.Items.AddRange(new ToolStripItem[]{
                        //    header,
                        //    new ToolStripSeparator(),
                        //    new ToolStripMenuItem("Enable This Item"),
                        //    new ToolStripMenuItem("Enable All")
                        //});

                        //header.Checked = true;
                        this.MenuContext.Items.Clear();
                        this.AddContextMenuHeader(lvg.Header);
                        //this.AddContextMenuItem("Enable This Item", null);
                        //this.AddContextMenuItem("Enable All", null);
                        foreach (ToolStripMenuItem m in this.ToolStripMenuItemList)
                        {
                            this.MenuContext.Items.Add(m);
                        }


                        MenuContext.Show(this, pt);
                    }
                }               
            }
        }

        private void OnMouseDoubleClick(object sender, MouseEventArgs e)
        {
            //
            this.lvi = this.GetItemAt(e.X, e.Y);
            this.pt = new Point(e.X, e.Y);
            ////
            //int nStart = this.pt.X;
            //int spos = 0;
            //int epos = this.Columns[0].Width;
            //for (int i = 0; i < this.Columns.Count; ++i)
            //{
            //    if (nStart >= spos && nStart <= epos)
            //    {
            //        nSubItemSelected = i;
            //        break;
            //    }
            //    //
            //    spos = epos;
            //    epos += this.Columns[i].Width;
            //}

            ////
            //ListViewItem.ListViewSubItem lvsi = this.lvi.SubItems[nSubItemSelected];

            //this.SubItemText = lvsi.Text;

            ////
            ////Rectangle r = new Rectangle(spos, this.lvi.Bounds.Y, epos, this.lvi.Bounds.Bottom);
            //if (0 == nSubItemSelected)
            //{
            //    this.EmEdit.Size = new Size(epos - spos, this.lvi.Bounds.Bottom - this.lvi.Bounds.Top);
            //    this.EmEdit.Location = new Point(spos, this.lvi.Bounds.Y);
            //}
            //else
            //{
            //    this.EmEdit.Size = new Size(lvsi.Bounds.Right - lvsi.Bounds.Left, lvsi.Bounds.Bottom - lvsi.Bounds.Top);
            //    this.EmEdit.Location = new Point(lvsi.Bounds.Left, this.lvi.Bounds.Top);
            //}

            RECT subitemRect = this.GetSubItemRect(this.pt);

            this.nSubItemSelected = this.col;

            //this.EmEdit.Size = new Size(this.Columns[this.col].Width, subitemRect.bottom-subitemRect.top);
            //this.EmEdit.Location = new Point(0==this.col?0:subitemRect.left, subitemRect.top);

            //this.EmEdit.TextAlign = this.Columns[this.col].TextAlign;
            //this.EmEdit.Show();
            //this.EmEdit.Text = this.lvi.SubItems[this.col].Text;
            //this.EmEdit.SelectAll();
            //this.EmEdit.Focus();

            if (this.row != -1 && this.col != -1)
            {
                SubItem cell = this.GetKey(new SubItem(this.row, this.col));

                if (null != cell)
                {
                    CellData d = this.customCells[cell] as CellData;

                    Size sz = new Size(this.Columns[this.col].Width, subitemRect.bottom - subitemRect.top);
                    Point p = new Point(0 == this.col ? 0 : subitemRect.left, subitemRect.top);
                
                    if (d.t == CellType.EDITABLE_CELL)
                    {
                        this.ShowTextBox(p, sz);
                    }
                    else if (CellType.COMBOBOX_CELL == d.t)
                    {
                        this.ShowComboBox(p, sz, d.data as StringCollection);
                    }
                    else
                    {
                        this.EmEdit.Hide();
                        this.EmCombo.Hide();
                    }
                }
            }
            else
            {
                this.EmEdit.Hide();
                this.EmCombo.Hide();
            }



        }

        private void EmEdit_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 13)
            {
                this.lvi.SubItems[nSubItemSelected].Text = this.EmEdit.Text;
                this.EmEdit.Hide();
            }
            else if (e.KeyChar == 27)
            {
                this.EmEdit.Hide();
            }
        }

        private void EmEdit_LostFocus(object sender, EventArgs e)
        {
            this.lvi.SubItems[nSubItemSelected].Text = this.EmEdit.Text;
            this.EmEdit.Size = new Size(0, 0);
            this.EmEdit.Hide();
        }

        //
        private RECT GetSubItemRect(Point pt)
        {
            //
            RECT subItemRect = new RECT();

            //
            this.row = this.col = -1;

            //
            ListViewItem lvi = this.GetItemAt(pt.X, pt.Y);

            if (null != lvi)
            {
                for (int index = 0; index < this.Columns.Count; ++index)
                {
                    //
                    subItemRect.top = index + 1;

                    //
                    subItemRect.left = Win32.LVIR_BOUNDS;

                    try
                    {
                        int result = Win32.SendMessage(this.Handle, Win32.LVM_GETSUBITEMRECT, lvi.Index, ref subItemRect);

                        if (result != 0)
                        {
                            if (pt.X < subItemRect.left)
                            {
                                this.row = lvi.Index;
                                this.col = 0;
                                break;
                            }
                            
                            if (pt.X >= subItemRect.left && pt.X <= subItemRect.right)
                            {
                                this.row = lvi.Index;
                                this.col = index + 1;
                                break;
                            }
                            
                        }
                        else
                        {
                            throw new Win32Exception();
                        }
                        
                    }
                    catch (Win32Exception ex)
                    {
                        MessageBox.Show(ex.ToString());
                    }
                }          
            }

            return subItemRect;          
        }

        //
        public void AddEditableCell(int row, int col)
        {
            this.customCells[new SubItem(row, col)] = new CellData(CellType.EDITABLE_CELL);
        }

        public void AddComboboxCell(int row, int col, StringCollection data)
        {
            this.customCells[new SubItem(row, col)] = new CellData(CellType.COMBOBOX_CELL, data);
        }

        public void AddComboboxCell(int row, int col, String[] data)
        {
            try 
            {
                StringCollection param = new StringCollection();
                param.AddRange(data);
                this.customCells[new SubItem(row, col)] = new CellData(CellType.COMBOBOX_CELL, param);
            }
            catch (Exception ex)
            {
                Trace.WriteLine(ex.ToString());
            }
        }

        private void ShowComboBox(Point location, Size sz, StringCollection data)
        {
            try
            {
                this.EmCombo.Size = sz;
                this.EmCombo.Location = location;
                //
                this.EmCombo.Items.Clear();
                foreach(String text in data)
                {
                    this.EmCombo.Items.Add(text);
                }
                //
                this.EmCombo.Text = this.Items[this.row].SubItems[this.col].Text;
                this.EmCombo.DropDownWidth = this.GetDropDownWidth(data);
                //
                this.EmCombo.Show();
                this.EmCombo.DroppedDown = true;
            }
            catch (ArgumentOutOfRangeException)
            {
                //sink
            }
        }

        private void ShowTextBox(Point location, Size sz)
        {
            try
            {
                this.EmEdit.Size = sz;
                this.EmEdit.Location = location;
                //
                this.EmEdit.TextAlign = this.Columns[this.col].TextAlign;
                //
                this.EmEdit.Text = this.Items[this.row].SubItems[this.col].Text;
                //
                this.EmEdit.Show();
                this.EmEdit.SelectAll();
                this.EmEdit.Focus();
            }
            catch (ArgumentOutOfRangeException)
            {
                //sink
            }
        }

        //
        private int GetDropDownWidth(StringCollection data)
        {
            if (data.Count == 0)
            {
                return this.EmCombo.Width;
            }

            string maximum = data[0];
            //
            foreach (string text in data)
            {
                if (maximum.Length < text.Length)
                {
                    maximum = text;
                }
            }

            return (int)(this.CreateGraphics().MeasureString(maximum, this.Font).Width);
        }

        //
        private SubItem GetKey(SubItem cell)
        {
            try
            {
                foreach (SubItem key in this.customCells.Keys)
                {
                    if (key.row == cell.row && key.col == cell.col)
                    {
                        return key;
                    } 
                    else if (key.row == -1 && key.col == cell.col)
                    {
                        return key;
                    }
                    else if (key.row == cell.row && key.col == -1)
                    {
                        return key;
                    }
                    else if (key.row == -1 && key.col == -1)
                    {
                        return key;
                    }
                }
            }
            catch (Exception ex)
            {
                Trace.WriteLine(ex.ToString());
            }

            return null;
        }

        //
        public ListViewGroup addLVGroup(string gheader)
        {
            ListViewGroup lvg = null;
            for (int i = 0; i < this.Groups.Count; ++i)
            {
                if (this.Groups[i].Header == gheader)
                {
                    lvg = this.Groups[i];
                    break;
                }
            }

            if (null == lvg)
            {
                lvg = new ListViewGroup(gheader, gheader);
                this.Groups.Add(lvg);

                //this.listCons.Items.Add(gheader);
            }

            return lvg;
        }

        public void addLVGroupAndItems(string gheader, string[] item)
        {

            ListViewGroup lvg = this.addLVGroup(gheader);

            item[0] = (lvg.Items.Count + 1).ToString();

            ListViewItem lvi = new ListViewItem(item, -1);
            lvi.Group = lvg;

            this.Items.Add(lvi);
        }

        public ListViewItem addItemToGroup(string gheader, string[] item)
        {
            ListViewGroup lvg = this.addLVGroup(gheader);

            if (null == lvg)
            {
                MessageBox.Show("Cannot Find Group : " + gheader);
                return null;
            }

            ListViewItem lvi = new ListViewItem(item, -1);
            lvi.Group = lvg;
            this.Items.Add(lvi);

            return lvi;
       }

        public void removeItemFromGroup(string gheader, string key)
        {
            ListViewGroup lvg = this.addLVGroup(gheader);

            if (null == lvg)
            {
                MessageBox.Show("Cannot Find Group : " + gheader);
            }

            foreach (ListViewItem lvi in lvg.Items)
            {
                if (key == lvi.SubItems[0].Text)
                {
                    this.Items.Remove(lvi);
                    return;
                }
            }
        }

        public void AddContextMenuItem(string name, EventHandler eh)
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Name = name;
            item.Text = name;
            item.Tag = this;
            item.Click += eh;
            //this.MenuContext.Items.Add(item);

            this.ToolStripMenuItemList.Add(item);
        }

        public void AddContextMenuHeader(string name)
        {
            ToolStripMenuItem item = new ToolStripMenuItem();
            item.Name = name;
            item.Text = name;
            this.MenuContext.Items.AddRange(new ToolStripItem[] {item, new ToolStripSeparator()});
        }


        public string GetSubItemText(string gheader, int index, int col)
        {
            ListViewGroup lvg = null;
            for (int i = 0; i < this.Groups.Count; ++i)
            {
                if (this.Groups[i].Header == gheader)
                {
                    lvg = this.Groups[i];
                    break;
                }
            }

            if (null == lvg)
            {
                Trace.WriteLine("Failed to find Group : " + gheader);
                return null;
            }

            foreach (ListViewItem lvi in lvg.Items)
            {
                if (index.ToString() == lvi.SubItems[0].Text.Trim())
                {
                    return lvi.SubItems[col].Text;
                }
            }

            return null;
        }
    }
}
