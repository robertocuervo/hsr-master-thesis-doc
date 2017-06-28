namespace GUI
{
    partial class MvmConfigurationForm
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.listBox2 = new System.Windows.Forms.ListBox();
            this.listBox3 = new System.Windows.Forms.ListBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.listBox3);
            this.groupBox1.Controls.Add(this.listBox2);
            this.groupBox1.Controls.Add(this.listBox1);
            this.groupBox1.Location = new System.Drawing.Point(13, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(1157, 467);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Triangle Configuration";
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Items.AddRange(new object[] {
            "LED 1",
            "LED 2",
            "LED 3",
            "LED 4",
            "LED 5",
            "LED 6",
            "LED 7",
            "LED 8",
            "LED 9",
            "LED 10",
            "LED 11",
            "LED 12",
            "LED 13",
            "LED 14",
            "LED 15",
            "LED 16",
            "LED 17",
            "LED 18"});
            this.listBox1.Location = new System.Drawing.Point(7, 20);
            this.listBox1.Name = "listBox1";
            this.listBox1.SelectionMode = System.Windows.Forms.SelectionMode.MultiSimple;
            this.listBox1.Size = new System.Drawing.Size(46, 238);
            this.listBox1.TabIndex = 0;
            // 
            // listBox2
            // 
            this.listBox2.FormattingEnabled = true;
            this.listBox2.Items.AddRange(new object[] {
            "LED 1",
            "LED 2",
            "LED 3",
            "LED 4",
            "LED 5",
            "LED 6",
            "LED 7",
            "LED 8",
            "LED 9",
            "LED 10",
            "LED 11",
            "LED 12",
            "LED 13",
            "LED 14",
            "LED 15",
            "LED 16",
            "LED 17",
            "LED 18"});
            this.listBox2.Location = new System.Drawing.Point(90, 20);
            this.listBox2.Name = "listBox2";
            this.listBox2.SelectionMode = System.Windows.Forms.SelectionMode.MultiSimple;
            this.listBox2.Size = new System.Drawing.Size(46, 238);
            this.listBox2.TabIndex = 1;
            // 
            // listBox3
            // 
            this.listBox3.FormattingEnabled = true;
            this.listBox3.Items.AddRange(new object[] {
            "LED 1",
            "LED 2",
            "LED 3",
            "LED 4",
            "LED 5",
            "LED 6",
            "LED 7",
            "LED 8",
            "LED 9",
            "LED 10",
            "LED 11",
            "LED 12",
            "LED 13",
            "LED 14",
            "LED 15",
            "LED 16",
            "LED 17",
            "LED 18"});
            this.listBox3.Location = new System.Drawing.Point(173, 20);
            this.listBox3.Name = "listBox3";
            this.listBox3.SelectionMode = System.Windows.Forms.SelectionMode.MultiSimple;
            this.listBox3.Size = new System.Drawing.Size(46, 238);
            this.listBox3.TabIndex = 2;
            // 
            // MvmConfigurationForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1361, 842);
            this.Controls.Add(this.groupBox1);
            this.Name = "MvmConfigurationForm";
            this.Text = "MvmConfigurationForm";
            this.groupBox1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.ListBox listBox3;
        private System.Windows.Forms.ListBox listBox2;
    }
}