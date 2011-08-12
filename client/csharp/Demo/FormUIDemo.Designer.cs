﻿namespace test_UI
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
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.bnQuery = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.lbFilename = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // tbUrl
            // 
            this.tbUrl.Location = new System.Drawing.Point(111, 132);
            this.tbUrl.Name = "tbUrl";
            this.tbUrl.Size = new System.Drawing.Size(349, 20);
            this.tbUrl.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(43, 135);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "URL";
            // 
            // tbData
            // 
            this.tbData.Location = new System.Drawing.Point(87, 189);
            this.tbData.Multiline = true;
            this.tbData.Name = "tbData";
            this.tbData.Size = new System.Drawing.Size(472, 63);
            this.tbData.TabIndex = 2;
            // 
            // tbResponse
            // 
            this.tbResponse.Location = new System.Drawing.Point(98, 407);
            this.tbResponse.Multiline = true;
            this.tbResponse.Name = "tbResponse";
            this.tbResponse.Size = new System.Drawing.Size(473, 127);
            this.tbResponse.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(43, 180);
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
            this.button1.Location = new System.Drawing.Point(498, 124);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(61, 35);
            this.button1.TabIndex = 6;
            this.button1.Text = "Submit";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // bnNode
            // 
            this.bnNode.Location = new System.Drawing.Point(286, 31);
            this.bnNode.Name = "bnNode";
            this.bnNode.Size = new System.Drawing.Size(89, 33);
            this.bnNode.TabIndex = 7;
            this.bnNode.Text = "Node";
            this.bnNode.UseVisualStyleBackColor = true;
            this.bnNode.Click += new System.EventHandler(this.bnNode_Click);
            // 
            // bnSubmitTest
            // 
            this.bnSubmitTest.Location = new System.Drawing.Point(286, 80);
            this.bnSubmitTest.Name = "bnSubmitTest";
            this.bnSubmitTest.Size = new System.Drawing.Size(89, 32);
            this.bnSubmitTest.TabIndex = 8;
            this.bnSubmitTest.Text = "Test Submit";
            this.bnSubmitTest.UseVisualStyleBackColor = true;
            this.bnSubmitTest.Click += new System.EventHandler(this.bnSubmitTest_Click);
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(25, 41);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(230, 35);
            this.label4.TabIndex = 9;
            this.label4.Text = "First Step: Test availability of remote nodes";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(25, 90);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(158, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "Second Step:  Submit your jobs.";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(28, 287);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(173, 13);
            this.label6.TabIndex = 11;
            this.label6.Text = "Third Step: Query the status of jobs";
            // 
            // bnQuery
            // 
            this.bnQuery.Location = new System.Drawing.Point(289, 275);
            this.bnQuery.Name = "bnQuery";
            this.bnQuery.Size = new System.Drawing.Size(86, 36);
            this.bnQuery.TabIndex = 12;
            this.bnQuery.Text = "Query";
            this.bnQuery.UseVisualStyleBackColor = true;
            this.bnQuery.Click += new System.EventHandler(this.bnQuery_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(286, 340);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(92, 46);
            this.button2.TabIndex = 13;
            this.button2.Text = "UploadFile";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // lbFilename
            // 
            this.lbFilename.AutoSize = true;
            this.lbFilename.Location = new System.Drawing.Point(37, 357);
            this.lbFilename.Name = "lbFilename";
            this.lbFilename.Size = new System.Drawing.Size(0, 13);
            this.lbFilename.TabIndex = 14;
            // 
            // FormUIDemo
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(645, 561);
            this.Controls.Add(this.lbFilename);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.bnQuery);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
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
            this.Text = "uGuru Client Demo";
            this.Load += new System.EventHandler(this.FormUIDemo_Load);
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
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button bnQuery;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Label lbFilename;
    }
}

