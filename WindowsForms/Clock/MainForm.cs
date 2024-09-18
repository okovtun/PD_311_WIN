using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Clock
{
	public partial class MainForm : Form
	{
		bool controlsVisible;
		public MainForm()
		{
			InitializeComponent();
			controlsVisible = true;
		}

		private void timer1_Tick(object sender, EventArgs e)
		{
			labelTime.Text = DateTime.Now.ToString("hh:mm:ss tt");
			if (cbShowDate.Checked) labelTime.Text += $"\n{DateTime.Now.ToString("yyyy.MM.dd")}";
		}

		private void btnHideControls_Click(object sender, EventArgs e)
		{
			SetControlsVisibility(false);
		}
		void SetControlsVisibility(bool visible)
		{
			this.FormBorderStyle = visible ? FormBorderStyle.Sizable : FormBorderStyle.None;
			this.TransparencyKey = visible ? Color.Empty : this.BackColor;
			this.ShowInTaskbar = visible;
			this.cbShowDate.Visible = visible;
			this.TopMost = !visible;
			btnHideControls.Visible = visible;
			labelTime.BackColor = visible ? this.BackColor : Color.LightBlue;
			showControlsToolStripMenuItem.Checked = visible;
		}

		private void quitToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		private void showDateToolStripMenuItem_Click(object sender, EventArgs e)
		{
			cbShowDate.Checked = showDateToolStripMenuItem.Checked;
		}

		private void cbShowDate_CheckedChanged(object sender, EventArgs e)
		{
			showDateToolStripMenuItem.Checked = cbShowDate.Checked;
		}

		private void showControlsToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.controlsVisible = showControlsToolStripMenuItem.Checked;
			SetControlsVisibility(controlsVisible);
		}
	}
}
