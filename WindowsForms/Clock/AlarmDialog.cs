using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Clock
{
	public partial class AlarmDialog : Form
	{
		MainForm owner;
		string filename;
		public AlarmDialog()
		{
			InitializeComponent();
		}
		public AlarmDialog(MainForm owner) : this()
		{
			this.owner = owner;
		}

		private void buttonOK_Click(object sender, EventArgs e)
		{
			owner.AlarmTime = dateTimePickerAlarmTime.Value;
			Console.WriteLine(owner.AlarmTime);
			owner.AlarmFile = filename;
			owner.NotifyIcon.Text = $"{dateTimePickerAlarmTime.Value.TimeOfDay}";
			this.Close();
		}

		private void buttonBrowse_Click(object sender, EventArgs e)
		{
			OpenFileDialog dialog = new OpenFileDialog();
			dialog.ShowDialog();
			filename = dialog.FileName;
		}

		private void buttonAdd_Click(object sender, EventArgs e)
		{
			try
			{
				checkedListBoxPendingAlarms.Items.Add(new Alarm(dateTimePickerAlarmTime.Value, filename), true);
				List<Alarm> alarms = new List<Alarm>(checkedListBoxPendingAlarms.Items.OfType<Alarm>().ToList());
				Console.WriteLine(alarms.Min());
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
			}
		}
	}
}
