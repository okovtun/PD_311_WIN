using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Clock
{
	class Alarm:IComparable
	{
		string Filename { get; set; }
		DateTime alarmTime;
		public DateTime AlarmTime
		{
			get => alarmTime;
			set
			{
				if (value > DateTime.Now) alarmTime = value;
				else throw new Exception("Смотрите в будущее");
			}
		}
		public Alarm(DateTime alarmTime, string filename)
		{
			AlarmTime = alarmTime;
			if (filename == null) throw new Exception("Выберите звековой файл");
			Filename = filename;
		}
		public override string ToString()
		{
			return $"{AlarmTime} - {Filename.Split('\\').Last()}";
		}
		public int CompareTo(object other)
		{
			return AlarmTime.CompareTo((other as Alarm).AlarmTime);
		}
	}
}
