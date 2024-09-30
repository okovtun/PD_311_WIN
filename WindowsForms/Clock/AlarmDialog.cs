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
		internal CheckedListBox CheckedListBoxPendingAlarms { get => checkedListBoxPendingAlarms; }
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
				Alarm alarm = new Alarm(dateTimePickerAlarmTime.Value, filename);
				//Alarm alarm2 = new Alarm(dateTimePickerAlarmTime.Value, filename);
				//Console.WriteLine(alarm.Equals(alarm2));
				//Console.WriteLine(checkedListBoxPendingAlarms.Items.IndexOf(alarm));
				List<Alarm> all_alarms = new List<Alarm>(checkedListBoxPendingAlarms.Items.OfType<Alarm>().ToList());
				if (!all_alarms.Contains(alarm))
					checkedListBoxPendingAlarms.Items.Add(alarm, true);
				Console.WriteLine(all_alarms.Min());
				List<Alarm> active_alarms = new List<Alarm>(checkedListBoxPendingAlarms.CheckedItems.OfType<Alarm>().ToList());
				owner.Alarm = active_alarms.Min();
				Console.WriteLine(all_alarms.Count + "\t" + active_alarms.Count);
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
			}
		}
	}
}
