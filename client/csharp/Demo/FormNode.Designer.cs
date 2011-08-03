namespace test_UI
{
    partial class FormNode
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.bnTest = new System.Windows.Forms.Button();
            this.bnImport = new System.Windows.Forms.Button();
            this.lbImport = new System.Windows.Forms.Label();
            this.bnExport = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // bnTest
            // 
            this.bnTest.Location = new System.Drawing.Point(564, 43);
            this.bnTest.Name = "bnTest";
            this.bnTest.Size = new System.Drawing.Size(105, 48);
            this.bnTest.TabIndex = 0;
            this.bnTest.Text = "Test";
            this.bnTest.UseVisualStyleBackColor = true;
            this.bnTest.Click += new System.EventHandler(this.bnTest_Click);
            // 
            // bnImport
            // 
            this.bnImport.Location = new System.Drawing.Point(66, 43);
            this.bnImport.Name = "bnImport";
            this.bnImport.Size = new System.Drawing.Size(105, 48);
            this.bnImport.TabIndex = 1;
            this.bnImport.Text = "Import Nodes";
            this.bnImport.UseVisualStyleBackColor = true;
            this.bnImport.Click += new System.EventHandler(this.bnImport_Click);
            // 
            // lbImport
            // 
            this.lbImport.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.lbImport.Location = new System.Drawing.Point(66, 104);
            this.lbImport.Name = "lbImport";
            this.lbImport.Size = new System.Drawing.Size(386, 30);
            this.lbImport.TabIndex = 2;
            // 
            // bnExport
            // 
            this.bnExport.Location = new System.Drawing.Point(215, 43);
            this.bnExport.Name = "bnExport";
            this.bnExport.Size = new System.Drawing.Size(105, 48);
            this.bnExport.TabIndex = 3;
            this.bnExport.Text = "Export Nodes";
            this.bnExport.UseVisualStyleBackColor = true;
            this.bnExport.Click += new System.EventHandler(this.bnExport_Click);
            // 
            // FormNode
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(764, 569);
            this.Controls.Add(this.bnExport);
            this.Controls.Add(this.lbImport);
            this.Controls.Add(this.bnImport);
            this.Controls.Add(this.bnTest);
            this.Name = "FormNode";
            this.Text = "FormNode";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button bnTest;
        private System.Windows.Forms.Button bnImport;
        private System.Windows.Forms.Label lbImport;
        private System.Windows.Forms.Button bnExport;
    }
}