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
using System.Threading;
using Microsoft.Win32;

namespace Clock
{
	public partial class MainForm : Form
	{
		bool controlsVisible;
		public System.Windows.Forms.Label LabelTime { get => labelTime; }
		ChooseFont chooseFontDialog;
		AlarmDialog alarmDialog;
		public string AlarmFile { get; set; }
		public DateTime AlarmTime { get; set; }
		public System.Windows.Forms.NotifyIcon NotifyIcon { get => notifyIconSystemTray; }
		StreamWriter sw;
		public MainForm()
		{
			InitializeComponent();
			//controlsVisible = true;
			SetControlsVisibility(false);
			this.StartPosition = FormStartPosition.Manual;
			int start_x = System.Windows.Forms.Screen.PrimaryScreen.Bounds.Right - this.Right - 25;
			int start_y = 25;
			this.Location = new Point(start_x, start_y);
			this.TopMost = topmostToolStripMenuItem.Checked = true;
			///////////////////////////////
			///
			cbPin.Checked = true;

			AllocConsole();
			CreateCustomFont();

			chooseFontDialog = new ChooseFont(this);
			alarmDialog = new AlarmDialog(this);
			//AlarmTime = DateTime.Now;

			RegistryKey rk = Registry.CurrentUser.OpenSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", false);
			object registryClockEntry = rk.GetValue("Clock");
			if (registryClockEntry != null) loadOnWindowsStartToolStripMenuItem.Checked = true;

			StreamWriter sw = new StreamWriter("session.log");
		}
		~MainForm()
		{
			sw.Close();
		}
		void CreateCustomFont()
		{
			Console.WriteLine(Directory.GetCurrentDirectory());
			Directory.SetCurrentDirectory(Application.ExecutablePath.Substring(0, Application.ExecutablePath.LastIndexOf('\\')));
			Directory.SetCurrentDirectory("..\\..\\Fonts");
			Console.WriteLine(Directory.GetCurrentDirectory());

			PrivateFontCollection pfc = new PrivateFontCollection();
			pfc.AddFontFile("Terminat.ttf");
			Font font = new Font(pfc.Families[0], labelTime.Font.Size);
			pfc.Dispose();
			labelTime.Font = font;
		}
		void SetStartup(bool autostart = false)
		{
			RegistryKey rk = Registry.CurrentUser.OpenSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);
			if (autostart) rk.SetValue("Clock", Application.ExecutablePath);
			else rk.DeleteValue("Clock", false);
			rk.Dispose();
		}

		private void timer1_Tick(object sender, EventArgs e)
		{
			const string TIME_FORMAT = "hh:mm:ss tt";
			const string DATE_FORMAT = "yyyy.MM.dd";
			labelTime.Text = DateTime.Now.ToString(TIME_FORMAT);
			if (cbShowDate.Checked) labelTime.Text += $"\n{DateTime.Now.ToString(DATE_FORMAT)}";

			//			Alarm:
			//if (AlarmTime.ToString(TIME_FORMAT) == labelTime.Text)
			//Console.WriteLine($"{AlarmTime.TimeOfDay}\t{DateTime.Now.TimeOfDay}");
			DateTime currentTime = new DateTime(DateTime.Now.Ticks - DateTime.Now.Ticks % TimeSpan.TicksPerSecond);
			//https://stackoverflow.com/questions/1004698/how-to-truncate-milliseconds-off-of-a-net-datetime#:~:text=%2F%2FRemove%20milliseconds%20DateTime%20date,mm%3Ass%22%2C%20null)%3B
			//Console.WriteLine($"{AlarmTime}\t{currentTime}");
			if (AlarmTime.Equals(currentTime))
			{
				//MessageBox.Show("Пора вставать");
				axWindowsMediaPlayer.URL = AlarmFile;
				axWindowsMediaPlayer.Ctlcontrols.play();
			}
			//Console.WriteLine(Directory.GetCurrentDirectory());
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
			//this.TopMost = !visible;
			btnHideControls.Visible = visible;
			labelTime.BackColor = visible ? this.BackColor : Color.LightBlue;
			showControlsToolStripMenuItem.Checked = visible;
			this.controlsVisible = visible;
			cbPin.Visible = visible;

			axWindowsMediaPlayer.Visible = visible;
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
			//ChooseFont chooseFontDialog = new ChooseFont(this);
			chooseFontDialog.ShowDialog();
		}

		//private void topmostToolStripMenuItem_Click(object sender, EventArgs e)
		//{
		//	this.TopMost = topmostToolStripMenuItem.Checked;
		//}

		private void notifyIconSystemTray_DoubleClick(object sender, EventArgs e)
		{
			Console.WriteLine("Notofy Icon dblclick");
			//topmostToolStripMenuItem_Click(sender, e);
			//if (this.TopMost == false)
			//{
			//	this.TopMost = true;
			//	this.TopMost = false;
			//}
			topmostToolStripMenuItem.Checked = !topmostToolStripMenuItem.Checked;
			topmostToolStripMenuItem.Checked = !topmostToolStripMenuItem.Checked;
		}

		private void topmostToolStripMenuItem_CheckedChanged(object sender, EventArgs e)
		{
			this.TopMost = topmostToolStripMenuItem.Checked;
			cbPin.Checked = topmostToolStripMenuItem.Checked;
		}

		private void cbPin_CheckedChanged(object sender, EventArgs e)
		{
			//cbPin.Checked = !cbPin.Checked;
			topmostToolStripMenuItem.Checked = cbPin.Checked;
			cbPin.BackgroundImage = cbPin.Checked ? Properties.Resources.pinned.ToBitmap() : Properties.Resources.note_thepin.ToBitmap();
		}

		private void alarmToolStripMenuItem_Click(object sender, EventArgs e)
		{
			alarmDialog.ShowDialog();
		}

		private void loadOnWindowsStartToolStripMenuItem_MouseUp(object sender, MouseEventArgs e)
		{
			SetStartup(loadOnWindowsStartToolStripMenuItem.Checked);
		}

		//private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
		//{
		//	sw.Close();
		//}
	}
}
