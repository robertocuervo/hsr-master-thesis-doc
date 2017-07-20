using System;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;
using Newtonsoft.Json;

namespace GUI
{
    public partial class ConfigurationForm : Form
    {
        public string ConfigFilePath { get; set; }
        public ConfigurationForm()
        {
            InitializeComponent();
            ConfigFilePath = "";
            addMvmDataRow();
            addStlDataRow();

        }

        private void addStlDataRow()
        {
            var dataRow = new DataGridViewRow();

            var selectFileButtonCell = new DataGridViewButtonCell();
            selectFileButtonCell.Value = "Select...";
            dataRow.Cells.Add(selectFileButtonCell);

            openFileDialog2.InitialDirectory = Directory.GetCurrentDirectory();
            var dataCell = new DataGridViewTextBoxCell();
            dataCell.Value = "stlFilePath/placeholder.stl";
            dataRow.Cells.Add(dataCell);

            var checkboxCell = new DataGridViewCheckBoxCell();
            checkboxCell.Value = true;
            dataRow.Cells.Add(checkboxCell);

            stlFilesDGV.Rows.Add(dataRow);
        }

        private void addMvmDataRow()
        {
            var dataRow = new DataGridViewRow();

            var selectFileButtonCell = new DataGridViewButtonCell();
            selectFileButtonCell.Value = "Select...";
            dataRow.Cells.Add(selectFileButtonCell);

            openFileDialog1.InitialDirectory = Directory.GetCurrentDirectory();
            var dataCell = new DataGridViewTextBoxCell();
            dataCell.Value = "stlFilePath/placeholder.mvm";
            dataRow.Cells.Add(dataCell);

            var configureButtonCell = new DataGridViewButtonCell();
            configureButtonCell.Value = "Configure...";
            dataRow.Cells.Add(configureButtonCell);

            var configDataCell = new DataGridViewTextBoxCell();
            configDataCell.Value = "";
            dataRow.Cells.Add(configDataCell);

            mvmFileDGV.Rows.Add(dataRow);
        }


        private void referenceCubeCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            if (referenceCubeCheckBox.Checked)
                referenceCubeCheckBox.Text = "(shown)";
            else
                referenceCubeCheckBox.Text = "(hidden)";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var configuration = new Configuration
            {
                mvmFilePath = mvmFileTextBox.Text,
                mvmReferenceFilePath = mvmReferenceTextBox.Text,
                frequency = (int) frequencyUpDown.Value,
                stlFilePaths = stlFilesListBox.Items.OfType<string>().ToList(),
                displayReferenceCube = referenceCubeCheckBox.Checked,
                referenceSphere1X = (float)reference1X.Value,
                referenceSphere1Y = (float)reference1Y.Value,
                referenceSphere1Z = (float)reference1Z.Value,
                referenceSphere2X = (float)reference2X.Value,
                referenceSphere2Y = (float)reference2Y.Value,
                referenceSphere2Z = (float)reference2Z.Value,
                referenceSphere3X = (float)reference3X.Value,
                referenceSphere3Y = (float)reference3Y.Value,
                referenceSphere3Z = (float)reference3Z.Value,
                calibrationVertex1X = (float)calibration1X.Value,
                calibrationVertex1Y = (float)calibration1Y.Value,
                calibrationVertex1Z = (float)calibration1Z.Value,
                calibrationVertex2X = (float)calibration2X.Value,
                calibrationVertex2Y = (float)calibration2Y.Value,
                calibrationVertex2Z = (float)calibration2Z.Value,
                calibrationVertex3X = (float)calibration3X.Value,
                calibrationVertex3Y = (float)calibration3Y.Value,
                calibrationVertex3Z = (float)calibration3Z.Value
            };
            var json = JsonConvert.SerializeObject(configuration);
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                Properties.Settings.Default.Configuration = json;
                Properties.Settings.Default.Save();
                File.WriteAllText(saveFileDialog1.FileName, json);
                ConfigFilePath = saveFileDialog1.FileName;
                this.DialogResult = DialogResult.OK;
                this.Close();
            }
        }

        private void mvmReferenceFileButton_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
                if (!string.IsNullOrEmpty(openFileDialog1.FileName))
                    mvmReferenceTextBox.Text = openFileDialog1.FileName;
        }

        private float ConvertToFloatOrDefault(string input)
        {
            float res;
            if (string.IsNullOrEmpty(input) || !float.TryParse(input, out res))
                return 0.0f;
            return res;
        }

        private void mvmFileButton_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
                if (!string.IsNullOrEmpty(openFileDialog1.FileName))
                    mvmFileTextBox.Text = openFileDialog1.FileName;
        }

        private void stlFileAdd_Click(object sender, EventArgs e)
        {
            if (openFileDialog2.ShowDialog() == DialogResult.OK)
                if (!string.IsNullOrEmpty(openFileDialog2.FileName))
                    stlFilesListBox.Items.Add(openFileDialog2.FileName);
        }

        private void stlFileRemove_Click(object sender, EventArgs e)
        {
            if (stlFilesListBox.SelectedIndex != -1)
                stlFilesListBox.Items.RemoveAt(stlFilesListBox.SelectedIndex);
        }

        private void initializeValues(Configuration config = null)
        {
            if (config != null)
            {
                mvmFileTextBox.Text = config.mvmFilePath;
                mvmReferenceTextBox.Text = config.mvmReferenceFilePath;
                frequencyUpDown.Value = config.frequency;
                stlFilesListBox.Items.Clear();
                stlFilesListBox.Items.AddRange(config.stlFilePaths.ToArray());
                referenceCubeCheckBox.Checked = config.displayReferenceCube;
                reference1X.Value = (decimal)config.referenceSphere1X;
                reference1Y.Value = (decimal)config.referenceSphere1Y;
                reference1Z.Value = (decimal)config.referenceSphere1Z;
                reference2X.Value = (decimal)config.referenceSphere2X;
                reference2Y.Value = (decimal)config.referenceSphere2Y;
                reference2Z.Value = (decimal)config.referenceSphere2Z;
                reference3X.Value = (decimal)config.referenceSphere3X;
                reference3Y.Value = (decimal)config.referenceSphere3Y;
                reference3Z.Value = (decimal)config.referenceSphere3Z;
                calibration1X.Value = (decimal)config.calibrationVertex1X;
                calibration1Y.Value = (decimal)config.calibrationVertex1Y;
                calibration1Z.Value = (decimal)config.calibrationVertex1Z;
                calibration2X.Value = (decimal)config.calibrationVertex2X;
                calibration2Y.Value = (decimal)config.calibrationVertex2Y;
                calibration2Z.Value = (decimal)config.calibrationVertex2Z;
                calibration3X.Value = (decimal)config.calibrationVertex3X;
                calibration3Y.Value = (decimal)config.calibrationVertex3Y;
                calibration3Z.Value = (decimal)config.calibrationVertex3Z;
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            var senderGrid = (DataGridView)sender;
            if (senderGrid.Columns[e.ColumnIndex] is DataGridViewButtonColumn &&
                e.RowIndex >= 0)
            {
                if (e.ColumnIndex == 0)
                {
                    if (!String.IsNullOrEmpty((string) senderGrid.Rows[e.RowIndex].Cells[1].Value))
                        openFileDialog2.InitialDirectory = senderGrid.Rows[e.RowIndex].Cells[1].Value.ToString();
                    if (openFileDialog2.ShowDialog() == DialogResult.OK)
                    {
                        if (!String.IsNullOrEmpty(openFileDialog2.FileName))
                        {
                            senderGrid.Rows[e.RowIndex].Cells[1].Value = openFileDialog2.FileName;
                        }
                    }
                }
            }
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }

        private void ConfigurationForm_Load(object sender, EventArgs e)
        {
            Configuration config = null;
            if (!String.IsNullOrEmpty(Properties.Settings.Default.Configuration))
                config = JsonConvert.DeserializeObject<Configuration>(Properties.Settings.Default.Configuration);
            initializeValues(config);
        }

        private void mvmFileDGV_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            var senderGrid = (DataGridView)sender;
            if (senderGrid.Columns[e.ColumnIndex] is DataGridViewButtonColumn &&
                e.RowIndex >= 0)
            {
                if (e.ColumnIndex == 0)
                {
                    if (!String.IsNullOrEmpty((string) senderGrid.Rows[e.RowIndex].Cells[1].Value))
                        openFileDialog1.InitialDirectory = senderGrid.Rows[e.RowIndex].Cells[1].Value.ToString();
                    if (openFileDialog1.ShowDialog() == DialogResult.OK)
                    {
                        if (!String.IsNullOrEmpty(openFileDialog1.FileName))
                        {
                            senderGrid.Rows[e.RowIndex].Cells[1].Value = openFileDialog1.FileName;
                        }
                    }
                }
                else if (e.ColumnIndex == 2)
                {
                    var mvmConfigForm = new MvmConfigurationForm();
                    if (mvmConfigForm.ShowDialog() == DialogResult.OK)
                    {
                        senderGrid.Rows[e.RowIndex].Cells[3].Value += mvmConfigForm.LedTriangle + ";";
                    }
                }
            }
        }
    }
}