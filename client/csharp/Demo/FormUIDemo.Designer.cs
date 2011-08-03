namespace test_UI
{
    partial class FormUIDemo
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
            this.tbUrl = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tbData = new System.Windows.Forms.TextBox();
            this.tbResponse = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.bnNode = new System.Windows.Forms.Button();
            this.bnSubmitTest = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // tbUrl
            // 
            this.tbUrl.Location = new System.Drawing.Point(87, 213);
            this.tbUrl.Name = "tbUrl";
            this.tbUrl.Size = new System.Drawing.Size(424, 20);
            this.tbUrl.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(40, 216);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "URL";
            // 
            // tbData
            // 
            this.tbData.Location = new System.Drawing.Point(86, 253);
            this.tbData.Multiline = true;
            this.tbData.Name = "tbData";
            this.tbData.Size = new System.Drawing.Size(472, 63);
            this.tbData.TabIndex = 2;
            // 
            // tbResponse
            // 
            this.tbResponse.Location = new System.Drawing.Point(86, 354);
            this.tbResponse.Multiline = true;
            this.tbResponse.Name = "tbResponse";
            this.tbResponse.Size = new System.Drawing.Size(473, 127);
            this.tbResponse.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(42, 273);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Data";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(25, 410);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(55, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Response";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(533, 205);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(61, 35);
            this.button1.TabIndex = 6;
            this.button1.Text = "Submit";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // bnNode
            // 
            this.bnNode.Location = new System.Drawing.Point(43, 164);
            this.bnNode.Name = "bnNode";
            this.bnNode.Size = new System.Drawing.Size(89, 33);
            this.bnNode.TabIndex = 7;
            this.bnNode.Text = "Node";
            this.bnNode.UseVisualStyleBackColor = true;
            this.bnNode.Click += new System.EventHandler(this.bnNode_Click);
            // 
            // bnSubmitTest
            // 
            this.bnSubmitTest.Location = new System.Drawing.Point(206, 167);
            this.bnSubmitTest.Name = "bnSubmitTest";
            this.bnSubmitTest.Size = new System.Drawing.Size(79, 29);
            this.bnSubmitTest.TabIndex = 8;
            this.bnSubmitTest.Text = "Test Submit";
            this.bnSubmitTest.UseVisualStyleBackColor = true;
            this.bnSubmitTest.Click += new System.EventHandler(this.bnSubmitTest_Click);
            // 
            // FormUIDemo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(620, 508);
            this.Controls.Add(this.bnSubmitTest);
            this.Controls.Add(this.bnNode);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tbResponse);
            this.Controls.Add(this.tbData);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tbUrl);
            this.Name = "FormUIDemo";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbUrl;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbData;
        private System.Windows.Forms.TextBox tbResponse;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button bnNode;
        private System.Windows.Forms.Button bnSubmitTest;
    }
}

