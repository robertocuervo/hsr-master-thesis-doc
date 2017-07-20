using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using GUI.DTO;

namespace GUI
{
    public partial class MvmConfigurationForm : Form
    {
        public LedTriangle LedTriangle { get; set; }
        public MvmConfigurationForm(int number = 1)
        {
            InitializeComponent();
            nameTextBox.Text += number;
        }

        private void MvmConfigurationForm_Load(object sender, EventArgs e)
        {
            
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            if (!(listBox1.SelectedIndex != -1 && listBox2.SelectedIndex != -1 && listBox3.SelectedIndex != -1))
                MessageBox.Show(this, "Please select a LED in each box.", "Invalid Selection", MessageBoxButtons.OK);
            else if (
                !(listBox1.SelectedIndex.CompareTo(listBox2.SelectedIndex) != 0 &&
                  listBox1.SelectedIndex.CompareTo(listBox3.SelectedIndex) != 0 &&
                  listBox2.SelectedIndex.CompareTo(listBox3.SelectedIndex) != 0))
                MessageBox.Show(this, "Each LED can only appear once in a triangle. Please correct your selection.",
                    "Invalid Selection", MessageBoxButtons.OK);
            else
            {
                LedTriangle = new LedTriangle(nameTextBox.Text, 
                    (float) listBox1.SelectedIndex + 1,
                    (float) listBox2.SelectedIndex + 1, 
                    (float) listBox3.SelectedIndex + 1);
                this.DialogResult = DialogResult.OK;
            }
        }

        private void cancelButton_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.Cancel;
            this.Close();
        }
    }
}
