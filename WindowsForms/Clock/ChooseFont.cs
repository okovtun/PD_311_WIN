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
using System.Drawing.Text;

namespace Clock
{
	public partial class ChooseFont : Form
	{
		public ChooseFont()
		{
			InitializeComponent();
			Console.WriteLine(Directory.GetCurrentDirectory());
			string[] ttf_files = Directory.GetFiles(Directory.GetCurrentDirectory(), "*.ttf");
			string[] otf_files = Directory.GetFiles(Directory.GetCurrentDirectory(), "*.otf");
			string[] files = new string[ttf_files.Length + otf_files.Length];
			ttf_files.CopyTo(files, 0);
			otf_files.CopyTo(files, ttf_files.Length);
			for (int i = 0; i < files.Length; i++)
			{
				comboBoxFonts.Items.Add(files[i].Split('\\').Last());
			}

			//string[] extensions = new string[] { ".ttf", ".otf" };
			//string[] files = Directory.GetFiles(Directory.GetCurrentDirectory()).Where(item=>extensions.Contains(item.Split('.').Last()))
		}

		private void buttonOK_Click(object sender, EventArgs e)
		{
			//this.Parent.la
		}

		private void comboBoxFonts_SelectedIndexChanged(object sender, EventArgs e)
		{
			PrivateFontCollection pfc = new PrivateFontCollection();
			pfc.AddFontFile(comboBoxFonts.SelectedItem.ToString());
			Font font = new Font(pfc.Families[0], Convert.ToUInt32(numericUpDownFontSize.Value));
			pfc.Dispose();
			labelSample.Font = font;
		}
	}
}
