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
	public partial class AlarmDialog : Form
	{
		MainForm owner;
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
			this.Close();
		}
	}
}
