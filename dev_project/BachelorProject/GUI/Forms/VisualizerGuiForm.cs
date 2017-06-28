using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;
using Newtonsoft.Json;

namespace GUI
{
    public partial class VisualizerGuiForm : Form
    {
        private string configFilePath;
        private Process cppProcess;

        public VisualizerGuiForm()
        {
            InitializeComponent();
        }

        private void VisualizerGui_Load(object sender, EventArgs e)
        {
            var configForm = new ConfigurationForm();
            if (configForm.ShowDialog() == DialogResult.OK)
            {
                configFilePath = configForm.ConfigFilePath;
            }
            runApp();
        }

        [DllImport("user32.dll")]
        private static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);

        [DllImport("user32.dll")]
        private static extern bool MoveWindow(IntPtr handle, int x, int y, int w, int h, bool repaint);

        private void VisualizerGui_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (cppProcess != null && !cppProcess.HasExited)
                cppProcess.Kill();
        }

        private void configurationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var configForm = new ConfigurationForm();
            configForm.ShowDialog();
        }

        private void runAppToolStripMenuItem_Click(object sender, EventArgs e)
        {
            runApp();
        }

        private void openConfigurationToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if (!string.IsNullOrEmpty(openFileDialog1.FileName))
                {
                    var config = JsonConvert.DeserializeObject<Configuration>(File.ReadAllText(openFileDialog1.FileName));
                    var configForm = new ConfigurationForm();
                    configForm.ShowDialog();
                }
            }
        }

        private void runApp()
        {
            cppProcess = null;
            var startInfo = new ProcessStartInfo
            {
                CreateNoWindow = true,
                FileName = "../../../Debug/main.exe",
                LoadUserProfile = true,
                UseShellExecute = false,
                Arguments = $"{configFilePath}",
                WorkingDirectory = "../../../Debug"
            };
            cppProcess = Process.Start(startInfo);
            Thread.Sleep(3000);
            //Wait until viewer is properly initialized
            SetParent(cppProcess.MainWindowHandle, panel1.Handle);
            MoveWindow(cppProcess.MainWindowHandle, panel1.Top, panel1.Left, panel1.Width, panel1.Height, true);
        }
    }
}