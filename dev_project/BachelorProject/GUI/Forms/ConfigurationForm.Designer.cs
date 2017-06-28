namespace GUI
{
    partial class ConfigurationForm
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
            this.saveButton = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.stlFileRemove = new System.Windows.Forms.Button();
            this.stlFileAdd = new System.Windows.Forms.Button();
            this.mvmReferenceFileButton = new System.Windows.Forms.Button();
            this.mvmReferenceTextBox = new System.Windows.Forms.TextBox();
            this.mvmFileButton = new System.Windows.Forms.Button();
            this.mvmFileTextBox = new System.Windows.Forms.TextBox();
            this.frequencyUpDown = new System.Windows.Forms.NumericUpDown();
            this.reference3ZTextBox = new System.Windows.Forms.TextBox();
            this.reference3YTextBox = new System.Windows.Forms.TextBox();
            this.reference3XTextBox = new System.Windows.Forms.TextBox();
            this.reference3Label = new System.Windows.Forms.Label();
            this.reference2ZTextBox = new System.Windows.Forms.TextBox();
            this.reference2YTextBox = new System.Windows.Forms.TextBox();
            this.reference2XTextBox = new System.Windows.Forms.TextBox();
            this.reference2Label = new System.Windows.Forms.Label();
            this.calibration3ZTextBox = new System.Windows.Forms.TextBox();
            this.calibration3YTextBox = new System.Windows.Forms.TextBox();
            this.calibration3XTextBox = new System.Windows.Forms.TextBox();
            this.calibration3Label = new System.Windows.Forms.Label();
            this.calibration2ZTextBox = new System.Windows.Forms.TextBox();
            this.calibration2YTextBox = new System.Windows.Forms.TextBox();
            this.calibration2XTextBox = new System.Windows.Forms.TextBox();
            this.calibration2Label = new System.Windows.Forms.Label();
            this.reference1ZTextBox = new System.Windows.Forms.TextBox();
            this.reference1YTextBox = new System.Windows.Forms.TextBox();
            this.reference1XTextBox = new System.Windows.Forms.TextBox();
            this.calibration1ZTextBox = new System.Windows.Forms.TextBox();
            this.calibration1YTextBox = new System.Windows.Forms.TextBox();
            this.calibration1XTextBox = new System.Windows.Forms.TextBox();
            this.stlFilesListBox = new System.Windows.Forms.ListBox();
            this.referenceCubeCheckBox = new System.Windows.Forms.CheckBox();
            this.stlFilesLabel = new System.Windows.Forms.Label();
            this.calibration1Label = new System.Windows.Forms.Label();
            this.referenceSphere1Label = new System.Windows.Forms.Label();
            this.referenceCubeLabel = new System.Windows.Forms.Label();
            this.frequencyLabel = new System.Windows.Forms.Label();
            this.mvmReferenceFileLabel = new System.Windows.Forms.Label();
            this.mvmFileLabel = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.openFileDialog2 = new System.Windows.Forms.OpenFileDialog();
            this.cancelButton = new System.Windows.Forms.Button();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.frequencyUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Location = new System.Drawing.Point(12, 596);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(612, 111);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "internal values";
            this.groupBox1.Visible = false;
            // 
            // saveButton
            // 
            this.saveButton.Location = new System.Drawing.Point(253, 567);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(75, 23);
            this.saveButton.TabIndex = 0;
            this.saveButton.Text = "Save As...";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.button1_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.stlFileRemove);
            this.groupBox2.Controls.Add(this.stlFileAdd);
            this.groupBox2.Controls.Add(this.mvmReferenceFileButton);
            this.groupBox2.Controls.Add(this.mvmReferenceTextBox);
            this.groupBox2.Controls.Add(this.mvmFileButton);
            this.groupBox2.Controls.Add(this.mvmFileTextBox);
            this.groupBox2.Controls.Add(this.frequencyUpDown);
            this.groupBox2.Controls.Add(this.reference3ZTextBox);
            this.groupBox2.Controls.Add(this.reference3YTextBox);
            this.groupBox2.Controls.Add(this.reference3XTextBox);
            this.groupBox2.Controls.Add(this.reference3Label);
            this.groupBox2.Controls.Add(this.reference2ZTextBox);
            this.groupBox2.Controls.Add(this.reference2YTextBox);
            this.groupBox2.Controls.Add(this.reference2XTextBox);
            this.groupBox2.Controls.Add(this.reference2Label);
            this.groupBox2.Controls.Add(this.calibration3ZTextBox);
            this.groupBox2.Controls.Add(this.calibration3YTextBox);
            this.groupBox2.Controls.Add(this.calibration3XTextBox);
            this.groupBox2.Controls.Add(this.calibration3Label);
            this.groupBox2.Controls.Add(this.calibration2ZTextBox);
            this.groupBox2.Controls.Add(this.calibration2YTextBox);
            this.groupBox2.Controls.Add(this.calibration2XTextBox);
            this.groupBox2.Controls.Add(this.calibration2Label);
            this.groupBox2.Controls.Add(this.reference1ZTextBox);
            this.groupBox2.Controls.Add(this.reference1YTextBox);
            this.groupBox2.Controls.Add(this.reference1XTextBox);
            this.groupBox2.Controls.Add(this.calibration1ZTextBox);
            this.groupBox2.Controls.Add(this.calibration1YTextBox);
            this.groupBox2.Controls.Add(this.calibration1XTextBox);
            this.groupBox2.Controls.Add(this.stlFilesListBox);
            this.groupBox2.Controls.Add(this.referenceCubeCheckBox);
            this.groupBox2.Controls.Add(this.stlFilesLabel);
            this.groupBox2.Controls.Add(this.calibration1Label);
            this.groupBox2.Controls.Add(this.referenceSphere1Label);
            this.groupBox2.Controls.Add(this.referenceCubeLabel);
            this.groupBox2.Controls.Add(this.frequencyLabel);
            this.groupBox2.Controls.Add(this.mvmReferenceFileLabel);
            this.groupBox2.Controls.Add(this.mvmFileLabel);
            this.groupBox2.Controls.Add(this.groupBox3);
            this.groupBox2.Controls.Add(this.groupBox4);
            this.groupBox2.Controls.Add(this.groupBox5);
            this.groupBox2.Location = new System.Drawing.Point(13, 13);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(611, 537);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "UserConfiguration";
            // 
            // stlFileRemove
            // 
            this.stlFileRemove.Location = new System.Drawing.Point(517, 354);
            this.stlFileRemove.Name = "stlFileRemove";
            this.stlFileRemove.Size = new System.Drawing.Size(75, 23);
            this.stlFileRemove.TabIndex = 40;
            this.stlFileRemove.Text = "Remove";
            this.stlFileRemove.UseVisualStyleBackColor = true;
            this.stlFileRemove.Click += new System.EventHandler(this.stlFileRemove_Click);
            // 
            // stlFileAdd
            // 
            this.stlFileAdd.Location = new System.Drawing.Point(517, 324);
            this.stlFileAdd.Name = "stlFileAdd";
            this.stlFileAdd.Size = new System.Drawing.Size(75, 23);
            this.stlFileAdd.TabIndex = 39;
            this.stlFileAdd.Text = "Add";
            this.stlFileAdd.UseVisualStyleBackColor = true;
            this.stlFileAdd.Click += new System.EventHandler(this.stlFileAdd_Click);
            // 
            // mvmReferenceFileButton
            // 
            this.mvmReferenceFileButton.Location = new System.Drawing.Point(517, 27);
            this.mvmReferenceFileButton.Name = "mvmReferenceFileButton";
            this.mvmReferenceFileButton.Size = new System.Drawing.Size(75, 23);
            this.mvmReferenceFileButton.TabIndex = 38;
            this.mvmReferenceFileButton.Text = "Select...";
            this.mvmReferenceFileButton.UseVisualStyleBackColor = true;
            this.mvmReferenceFileButton.Click += new System.EventHandler(this.mvmReferenceFileButton_Click);
            // 
            // mvmReferenceTextBox
            // 
            this.mvmReferenceTextBox.Location = new System.Drawing.Point(154, 29);
            this.mvmReferenceTextBox.Name = "mvmReferenceTextBox";
            this.mvmReferenceTextBox.Size = new System.Drawing.Size(344, 20);
            this.mvmReferenceTextBox.TabIndex = 37;
            this.mvmReferenceTextBox.Text = "../Viewer/DemoData/mvm_File/tmjright1.mvm";
            // 
            // mvmFileButton
            // 
            this.mvmFileButton.Location = new System.Drawing.Point(517, 53);
            this.mvmFileButton.Name = "mvmFileButton";
            this.mvmFileButton.Size = new System.Drawing.Size(75, 23);
            this.mvmFileButton.TabIndex = 36;
            this.mvmFileButton.Text = "Select...";
            this.mvmFileButton.UseVisualStyleBackColor = true;
            this.mvmFileButton.Click += new System.EventHandler(this.mvmFileButton_Click);
            // 
            // mvmFileTextBox
            // 
            this.mvmFileTextBox.Location = new System.Drawing.Point(154, 55);
            this.mvmFileTextBox.Name = "mvmFileTextBox";
            this.mvmFileTextBox.Size = new System.Drawing.Size(344, 20);
            this.mvmFileTextBox.TabIndex = 32;
            this.mvmFileTextBox.Text = "../Viewer/DemoData/mvm_File/tmjright7.mvm";
            // 
            // frequencyUpDown
            // 
            this.frequencyUpDown.Location = new System.Drawing.Point(154, 85);
            this.frequencyUpDown.Maximum = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.frequencyUpDown.Name = "frequencyUpDown";
            this.frequencyUpDown.Size = new System.Drawing.Size(120, 20);
            this.frequencyUpDown.TabIndex = 31;
            this.frequencyUpDown.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
            // 
            // reference3ZTextBox
            // 
            this.reference3ZTextBox.Location = new System.Drawing.Point(398, 209);
            this.reference3ZTextBox.Name = "reference3ZTextBox";
            this.reference3ZTextBox.Size = new System.Drawing.Size(100, 20);
            this.reference3ZTextBox.TabIndex = 30;
            this.reference3ZTextBox.Text = "76.69";
            // 
            // reference3YTextBox
            // 
            this.reference3YTextBox.Location = new System.Drawing.Point(275, 209);
            this.reference3YTextBox.Name = "reference3YTextBox";
            this.reference3YTextBox.Size = new System.Drawing.Size(100, 20);
            this.reference3YTextBox.TabIndex = 29;
            this.reference3YTextBox.Text = "-0.21";
            // 
            // reference3XTextBox
            // 
            this.reference3XTextBox.Location = new System.Drawing.Point(152, 209);
            this.reference3XTextBox.Name = "reference3XTextBox";
            this.reference3XTextBox.Size = new System.Drawing.Size(100, 20);
            this.reference3XTextBox.TabIndex = 28;
            this.reference3XTextBox.Text = "52.59";
            // 
            // reference3Label
            // 
            this.reference3Label.AutoSize = true;
            this.reference3Label.Location = new System.Drawing.Point(6, 216);
            this.reference3Label.Name = "reference3Label";
            this.reference3Label.Size = new System.Drawing.Size(100, 13);
            this.reference3Label.TabIndex = 27;
            this.reference3Label.Text = "ReferenceSphere3:";
            // 
            // reference2ZTextBox
            // 
            this.reference2ZTextBox.Location = new System.Drawing.Point(398, 183);
            this.reference2ZTextBox.Name = "reference2ZTextBox";
            this.reference2ZTextBox.Size = new System.Drawing.Size(100, 20);
            this.reference2ZTextBox.TabIndex = 26;
            this.reference2ZTextBox.Text = "76.82";
            // 
            // reference2YTextBox
            // 
            this.reference2YTextBox.Location = new System.Drawing.Point(275, 183);
            this.reference2YTextBox.Name = "reference2YTextBox";
            this.reference2YTextBox.Size = new System.Drawing.Size(100, 20);
            this.reference2YTextBox.TabIndex = 25;
            this.reference2YTextBox.Text = "-22.26";
            // 
            // reference2XTextBox
            // 
            this.reference2XTextBox.Location = new System.Drawing.Point(152, 183);
            this.reference2XTextBox.Name = "reference2XTextBox";
            this.reference2XTextBox.Size = new System.Drawing.Size(100, 20);
            this.reference2XTextBox.TabIndex = 24;
            this.reference2XTextBox.Text = "55.58";
            // 
            // reference2Label
            // 
            this.reference2Label.AutoSize = true;
            this.reference2Label.Location = new System.Drawing.Point(6, 190);
            this.reference2Label.Name = "reference2Label";
            this.reference2Label.Size = new System.Drawing.Size(100, 13);
            this.reference2Label.TabIndex = 23;
            this.reference2Label.Text = "ReferenceSphere2:";
            // 
            // calibration3ZTextBox
            // 
            this.calibration3ZTextBox.Location = new System.Drawing.Point(398, 294);
            this.calibration3ZTextBox.Name = "calibration3ZTextBox";
            this.calibration3ZTextBox.Size = new System.Drawing.Size(100, 20);
            this.calibration3ZTextBox.TabIndex = 22;
            this.calibration3ZTextBox.Text = "35.88";
            // 
            // calibration3YTextBox
            // 
            this.calibration3YTextBox.Location = new System.Drawing.Point(275, 294);
            this.calibration3YTextBox.Name = "calibration3YTextBox";
            this.calibration3YTextBox.Size = new System.Drawing.Size(100, 20);
            this.calibration3YTextBox.TabIndex = 21;
            this.calibration3YTextBox.Text = "8.04";
            // 
            // calibration3XTextBox
            // 
            this.calibration3XTextBox.Location = new System.Drawing.Point(152, 294);
            this.calibration3XTextBox.Name = "calibration3XTextBox";
            this.calibration3XTextBox.Size = new System.Drawing.Size(100, 20);
            this.calibration3XTextBox.TabIndex = 20;
            this.calibration3XTextBox.Text = "0.33";
            // 
            // calibration3Label
            // 
            this.calibration3Label.AutoSize = true;
            this.calibration3Label.Location = new System.Drawing.Point(8, 297);
            this.calibration3Label.Name = "calibration3Label";
            this.calibration3Label.Size = new System.Drawing.Size(95, 13);
            this.calibration3Label.TabIndex = 19;
            this.calibration3Label.Text = "CalibrationVertex3:";
            // 
            // calibration2ZTextBox
            // 
            this.calibration2ZTextBox.Location = new System.Drawing.Point(398, 268);
            this.calibration2ZTextBox.Name = "calibration2ZTextBox";
            this.calibration2ZTextBox.Size = new System.Drawing.Size(100, 20);
            this.calibration2ZTextBox.TabIndex = 18;
            this.calibration2ZTextBox.Text = "14.26";
            // 
            // calibration2YTextBox
            // 
            this.calibration2YTextBox.Location = new System.Drawing.Point(275, 268);
            this.calibration2YTextBox.Name = "calibration2YTextBox";
            this.calibration2YTextBox.Size = new System.Drawing.Size(100, 20);
            this.calibration2YTextBox.TabIndex = 17;
            this.calibration2YTextBox.Text = "-11.9";
            // 
            // calibration2XTextBox
            // 
            this.calibration2XTextBox.Location = new System.Drawing.Point(152, 268);
            this.calibration2XTextBox.Name = "calibration2XTextBox";
            this.calibration2XTextBox.Size = new System.Drawing.Size(100, 20);
            this.calibration2XTextBox.TabIndex = 16;
            this.calibration2XTextBox.Text = "9.76";
            // 
            // calibration2Label
            // 
            this.calibration2Label.AutoSize = true;
            this.calibration2Label.Location = new System.Drawing.Point(8, 271);
            this.calibration2Label.Name = "calibration2Label";
            this.calibration2Label.Size = new System.Drawing.Size(95, 13);
            this.calibration2Label.TabIndex = 15;
            this.calibration2Label.Text = "CalibrationVertex2:";
            // 
            // reference1ZTextBox
            // 
            this.reference1ZTextBox.Location = new System.Drawing.Point(398, 157);
            this.reference1ZTextBox.Name = "reference1ZTextBox";
            this.reference1ZTextBox.Size = new System.Drawing.Size(100, 20);
            this.reference1ZTextBox.TabIndex = 14;
            this.reference1ZTextBox.Text = "76.66";
            // 
            // reference1YTextBox
            // 
            this.reference1YTextBox.Location = new System.Drawing.Point(275, 157);
            this.reference1YTextBox.Name = "reference1YTextBox";
            this.reference1YTextBox.Size = new System.Drawing.Size(100, 20);
            this.reference1YTextBox.TabIndex = 13;
            this.reference1YTextBox.Text = "-15.84";
            // 
            // reference1XTextBox
            // 
            this.reference1XTextBox.Location = new System.Drawing.Point(152, 157);
            this.reference1XTextBox.Name = "reference1XTextBox";
            this.reference1XTextBox.Size = new System.Drawing.Size(100, 20);
            this.reference1XTextBox.TabIndex = 12;
            this.reference1XTextBox.Text = "36.9";
            // 
            // calibration1ZTextBox
            // 
            this.calibration1ZTextBox.Location = new System.Drawing.Point(398, 242);
            this.calibration1ZTextBox.Name = "calibration1ZTextBox";
            this.calibration1ZTextBox.Size = new System.Drawing.Size(100, 20);
            this.calibration1ZTextBox.TabIndex = 11;
            this.calibration1ZTextBox.Text = "35.24";
            // 
            // calibration1YTextBox
            // 
            this.calibration1YTextBox.Location = new System.Drawing.Point(275, 242);
            this.calibration1YTextBox.Name = "calibration1YTextBox";
            this.calibration1YTextBox.Size = new System.Drawing.Size(100, 20);
            this.calibration1YTextBox.TabIndex = 10;
            this.calibration1YTextBox.Text = "-11.84";
            // 
            // calibration1XTextBox
            // 
            this.calibration1XTextBox.Location = new System.Drawing.Point(152, 242);
            this.calibration1XTextBox.Name = "calibration1XTextBox";
            this.calibration1XTextBox.Size = new System.Drawing.Size(100, 20);
            this.calibration1XTextBox.TabIndex = 9;
            this.calibration1XTextBox.Text = "-9.96";
            // 
            // stlFilesListBox
            // 
            this.stlFilesListBox.FormattingEnabled = true;
            this.stlFilesListBox.Items.AddRange(new object[] {
            "../Viewer/DemoData/stl_File/CR.stl",
            "../Viewer/DemoData/stl_File/CL.stl",
            "../Viewer/DemoData/stl_File/FR.stl",
            "../Viewer/DemoData/stl_File/FL.stl",
            "../Viewer/DemoData/stl_File/Mandibular2_red_bin.stl",
            "../Viewer/DemoData/stl_File/Maxillary2_red_bin.stl",
            "../Viewer/DemoData/stl_File/cube.stl"});
            this.stlFilesListBox.Location = new System.Drawing.Point(154, 324);
            this.stlFilesListBox.Name = "stlFilesListBox";
            this.stlFilesListBox.Size = new System.Drawing.Size(344, 199);
            this.stlFilesListBox.TabIndex = 8;
            // 
            // referenceCubeCheckBox
            // 
            this.referenceCubeCheckBox.AutoSize = true;
            this.referenceCubeCheckBox.Checked = true;
            this.referenceCubeCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.referenceCubeCheckBox.Location = new System.Drawing.Point(154, 112);
            this.referenceCubeCheckBox.Name = "referenceCubeCheckBox";
            this.referenceCubeCheckBox.Size = new System.Drawing.Size(63, 17);
            this.referenceCubeCheckBox.TabIndex = 7;
            this.referenceCubeCheckBox.Text = "(shown)";
            this.referenceCubeCheckBox.UseVisualStyleBackColor = true;
            this.referenceCubeCheckBox.CheckedChanged += new System.EventHandler(this.referenceCubeCheckBox_CheckedChanged);
            // 
            // stlFilesLabel
            // 
            this.stlFilesLabel.AutoSize = true;
            this.stlFilesLabel.Location = new System.Drawing.Point(8, 324);
            this.stlFilesLabel.Name = "stlFilesLabel";
            this.stlFilesLabel.Size = new System.Drawing.Size(51, 13);
            this.stlFilesLabel.TabIndex = 6;
            this.stlFilesLabel.Text = "STLFiles:";
            // 
            // calibration1Label
            // 
            this.calibration1Label.AutoSize = true;
            this.calibration1Label.Location = new System.Drawing.Point(8, 245);
            this.calibration1Label.Name = "calibration1Label";
            this.calibration1Label.Size = new System.Drawing.Size(95, 13);
            this.calibration1Label.TabIndex = 5;
            this.calibration1Label.Text = "CalibrationVertex1:";
            // 
            // referenceSphere1Label
            // 
            this.referenceSphere1Label.AutoSize = true;
            this.referenceSphere1Label.Location = new System.Drawing.Point(6, 164);
            this.referenceSphere1Label.Name = "referenceSphere1Label";
            this.referenceSphere1Label.Size = new System.Drawing.Size(100, 13);
            this.referenceSphere1Label.TabIndex = 4;
            this.referenceSphere1Label.Text = "ReferenceSphere1:";
            // 
            // referenceCubeLabel
            // 
            this.referenceCubeLabel.AutoSize = true;
            this.referenceCubeLabel.Location = new System.Drawing.Point(6, 113);
            this.referenceCubeLabel.Name = "referenceCubeLabel";
            this.referenceCubeLabel.Size = new System.Drawing.Size(85, 13);
            this.referenceCubeLabel.TabIndex = 3;
            this.referenceCubeLabel.Text = "ReferenceCube:";
            // 
            // frequencyLabel
            // 
            this.frequencyLabel.AutoSize = true;
            this.frequencyLabel.Location = new System.Drawing.Point(6, 87);
            this.frequencyLabel.Name = "frequencyLabel";
            this.frequencyLabel.Size = new System.Drawing.Size(94, 13);
            this.frequencyLabel.TabIndex = 2;
            this.frequencyLabel.Text = "DisplayFrequency:";
            // 
            // mvmReferenceFileLabel
            // 
            this.mvmReferenceFileLabel.AutoSize = true;
            this.mvmReferenceFileLabel.Location = new System.Drawing.Point(6, 32);
            this.mvmReferenceFileLabel.Name = "mvmReferenceFileLabel";
            this.mvmReferenceFileLabel.Size = new System.Drawing.Size(99, 13);
            this.mvmReferenceFileLabel.TabIndex = 1;
            this.mvmReferenceFileLabel.Text = "MvmReferenceFile:";
            // 
            // mvmFileLabel
            // 
            this.mvmFileLabel.AutoSize = true;
            this.mvmFileLabel.Location = new System.Drawing.Point(6, 58);
            this.mvmFileLabel.Name = "mvmFileLabel";
            this.mvmFileLabel.Size = new System.Drawing.Size(49, 13);
            this.mvmFileLabel.TabIndex = 0;
            this.mvmFileLabel.Text = "MvmFile:";
            // 
            // groupBox3
            // 
            this.groupBox3.Location = new System.Drawing.Point(148, 136);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(107, 182);
            this.groupBox3.TabIndex = 33;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "X";
            // 
            // groupBox4
            // 
            this.groupBox4.Location = new System.Drawing.Point(269, 136);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(113, 182);
            this.groupBox4.TabIndex = 34;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Y";
            // 
            // groupBox5
            // 
            this.groupBox5.Location = new System.Drawing.Point(394, 136);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(110, 182);
            this.groupBox5.TabIndex = 35;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Z";
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.DefaultExt = "mvm";
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.RestoreDirectory = true;
            this.openFileDialog1.Title = "Select MVM File";
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.DefaultExt = "json";
            this.saveFileDialog1.FileName = "config";
            this.saveFileDialog1.Filter = "JSON files (*.json)|*.json|txt files (*.txt)|*.txt";
            this.saveFileDialog1.RestoreDirectory = true;
            this.saveFileDialog1.Title = "Save Configuration";
            // 
            // openFileDialog2
            // 
            this.openFileDialog2.DefaultExt = "stl";
            this.openFileDialog2.FileName = "openFileDialog1";
            this.openFileDialog2.RestoreDirectory = true;
            this.openFileDialog2.Title = "Select STL File";
            // 
            // cancelButton
            // 
            this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton.Location = new System.Drawing.Point(335, 567);
            this.cancelButton.Name = "cancelButton";
            this.cancelButton.Size = new System.Drawing.Size(75, 23);
            this.cancelButton.TabIndex = 1;
            this.cancelButton.Text = "Cancel";
            this.cancelButton.UseVisualStyleBackColor = true;
            // 
            // ConfigurationForm
            // 
            this.AcceptButton = this.saveButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.cancelButton;
            this.ClientSize = new System.Drawing.Size(638, 722);
            this.Controls.Add(this.cancelButton);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.groupBox1);
            this.Name = "ConfigurationForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Configuration";
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.frequencyUpDown)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox reference1ZTextBox;
        private System.Windows.Forms.TextBox reference1YTextBox;
        private System.Windows.Forms.TextBox reference1XTextBox;
        private System.Windows.Forms.TextBox calibration1ZTextBox;
        private System.Windows.Forms.TextBox calibration1YTextBox;
        private System.Windows.Forms.TextBox calibration1XTextBox;
        private System.Windows.Forms.ListBox stlFilesListBox;
        private System.Windows.Forms.CheckBox referenceCubeCheckBox;
        private System.Windows.Forms.Label stlFilesLabel;
        private System.Windows.Forms.Label calibration1Label;
        private System.Windows.Forms.Label referenceSphere1Label;
        private System.Windows.Forms.Label referenceCubeLabel;
        private System.Windows.Forms.Label frequencyLabel;
        private System.Windows.Forms.Label mvmReferenceFileLabel;
        private System.Windows.Forms.Label mvmFileLabel;
        private System.Windows.Forms.TextBox mvmFileTextBox;
        private System.Windows.Forms.NumericUpDown frequencyUpDown;
        private System.Windows.Forms.TextBox reference3ZTextBox;
        private System.Windows.Forms.TextBox reference3YTextBox;
        private System.Windows.Forms.TextBox reference3XTextBox;
        private System.Windows.Forms.Label reference3Label;
        private System.Windows.Forms.TextBox reference2ZTextBox;
        private System.Windows.Forms.TextBox reference2YTextBox;
        private System.Windows.Forms.TextBox reference2XTextBox;
        private System.Windows.Forms.Label reference2Label;
        private System.Windows.Forms.TextBox calibration3ZTextBox;
        private System.Windows.Forms.TextBox calibration3YTextBox;
        private System.Windows.Forms.TextBox calibration3XTextBox;
        private System.Windows.Forms.Label calibration3Label;
        private System.Windows.Forms.TextBox calibration2ZTextBox;
        private System.Windows.Forms.TextBox calibration2YTextBox;
        private System.Windows.Forms.TextBox calibration2XTextBox;
        private System.Windows.Forms.Label calibration2Label;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Button mvmReferenceFileButton;
        private System.Windows.Forms.TextBox mvmReferenceTextBox;
        private System.Windows.Forms.Button mvmFileButton;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Button stlFileRemove;
        private System.Windows.Forms.Button stlFileAdd;
        private System.Windows.Forms.OpenFileDialog openFileDialog2;
        private System.Windows.Forms.Button cancelButton;
    }
}