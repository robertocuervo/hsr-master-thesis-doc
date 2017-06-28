using System;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using Newtonsoft.Json;

namespace GUI
{
    public partial class ConfigurationForm : Form
    {
        public string ConfigFilePath { get; set; }
        public ConfigurationForm()
        {
            InitializeComponent();
            saveFileDialog1.InitialDirectory = Directory.GetCurrentDirectory();
            ConfigFilePath = "";

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
                referenceSphere1X = ConvertToFloatOrDefault(reference1XTextBox.Text),
                referenceSphere1Y = ConvertToFloatOrDefault(reference1YTextBox.Text),
                referenceSphere1Z = ConvertToFloatOrDefault(reference1ZTextBox.Text),
                referenceSphere2X = ConvertToFloatOrDefault(reference2XTextBox.Text),
                referenceSphere2Y = ConvertToFloatOrDefault(reference2YTextBox.Text),
                referenceSphere2Z = ConvertToFloatOrDefault(reference2ZTextBox.Text),
                referenceSphere3X = ConvertToFloatOrDefault(reference3XTextBox.Text),
                referenceSphere3Y = ConvertToFloatOrDefault(reference3YTextBox.Text),
                referenceSphere3Z = ConvertToFloatOrDefault(reference3ZTextBox.Text),
                calibrationVertex1X = ConvertToFloatOrDefault(calibration1XTextBox.Text),
                calibrationVertex1Y = ConvertToFloatOrDefault(calibration1YTextBox.Text),
                calibrationVertex1Z = ConvertToFloatOrDefault(calibration1ZTextBox.Text),
                calibrationVertex2X = ConvertToFloatOrDefault(calibration2XTextBox.Text),
                calibrationVertex2Y = ConvertToFloatOrDefault(calibration2YTextBox.Text),
                calibrationVertex2Z = ConvertToFloatOrDefault(calibration2ZTextBox.Text),
                calibrationVertex3X = ConvertToFloatOrDefault(calibration3XTextBox.Text),
                calibrationVertex3Y = ConvertToFloatOrDefault(calibration3YTextBox.Text),
                calibrationVertex3Z = ConvertToFloatOrDefault(calibration3ZTextBox.Text)
            };
            var json = JsonConvert.SerializeObject(configuration);
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                File.WriteAllText(saveFileDialog1.FileName, json);
                ConfigFilePath = saveFileDialog1.FileName;
                this.DialogResult = DialogResult.OK;
                this.Close();
            }
        }

        private void mvmReferenceFileButton_Click(object sender, EventArgs e)
        {
            //var mvmConfigForm = new MvmConfigurationForm();
            //mvmConfigForm.ShowDialog();
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
                reference1XTextBox.Text = config.referenceSphere1X.ToString();
                reference1YTextBox.Text = config.referenceSphere1Y.ToString();
                reference1ZTextBox.Text = config.referenceSphere1Z.ToString();
                reference2XTextBox.Text = config.referenceSphere2X.ToString();
                reference2YTextBox.Text = config.referenceSphere2Y.ToString();
                reference2ZTextBox.Text = config.referenceSphere2Z.ToString();
                reference3XTextBox.Text = config.referenceSphere3X.ToString();
                reference3YTextBox.Text = config.referenceSphere3Y.ToString();
                reference3ZTextBox.Text = config.referenceSphere3Z.ToString();
                calibration1XTextBox.Text = config.calibrationVertex1X.ToString();
                calibration1YTextBox.Text = config.calibrationVertex1Y.ToString();
                calibration1ZTextBox.Text = config.calibrationVertex1Z.ToString();
                calibration2XTextBox.Text = config.calibrationVertex2X.ToString();
                calibration2YTextBox.Text = config.calibrationVertex2Y.ToString();
                calibration2ZTextBox.Text = config.calibrationVertex2Z.ToString();
                calibration3XTextBox.Text = config.calibrationVertex3X.ToString();
                calibration3YTextBox.Text = config.calibrationVertex3Y.ToString();
                calibration3ZTextBox.Text = config.calibrationVertex3Z.ToString();
            }
        }
    }
}