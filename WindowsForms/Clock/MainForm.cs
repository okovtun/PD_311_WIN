using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Text;
using System.Runtime.InteropServices;
using System.IO;

namespace Clock
{
	public partial class MainForm : Form
	{
		bool controlsVisible;
		public MainForm()
		{
			InitializeComponent();
			//controlsVisible = true;
			SetControlsVisibility(false);
			this.StartPosition = FormStartPosition.Manual;
			int start_x = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Right - this.Right - 25;
			int start_y = 25;
			this.Location = new Point(start_x, start_y);

			///////////////////////////////
			///

			AllocConsole();
			CreateCustomFont();
		}
		void CreateCustomFont()
		{
			Console.WriteLine(Directory.GetCurrentDirectory());
			Directory.SetCurrentDirectory("..\\..\\Fonts");
			Console.WriteLine(Directory.GetCurrentDirectory());

			PrivateFontCollection pfc = new PrivateFontCollection();
			pfc.AddFontFile("Terminat.ttf");
			Font font = new Font(pfc.Families[0], labelTime.Font.Size);
			pfc.Dispose();
			labelTime.Font = font;
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
			this.controlsVisible = visible;
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

		private void labelTime_DoubleClick(object sender, EventArgs e)
		{
			SetControlsVisibility(!controlsVisible);
		}

		private void backgroundColorToolStripMenuItem_Click(object sender, EventArgs e)
		{
			ColorDialog dialog = new ColorDialog();
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				labelTime.BackColor = dialog.Color;
			}
		}

		private void fregroundColorToolStripMenuItem_Click(object sender, EventArgs e)
		{
			ColorDialog dialog = new ColorDialog();
			if (dialog.ShowDialog() == DialogResult.OK)
			{
				labelTime.ForeColor = dialog.Color;
			}
		}
		/// ///////////////////////////////////
		const UInt32 StdOutputHandle = 0xFFFFFFF5;
		[DllImport("kernel32.dll")]
		static extern IntPtr GetStdHandle(UInt32 handle);
		[DllImport("kernel32.dll")]
		static extern void SetStdHandle(UInt32 nStdHandle, IntPtr handle);
		[DllImport("kernel32.dll")]
		static extern bool AllocConsole();

		private void chooseFontToolStripMenuItem_Click(object sender, EventArgs e)
		{
			ChooseFont dialog = new ChooseFont();
			dialog.ShowDialog();
		}
	}
}
