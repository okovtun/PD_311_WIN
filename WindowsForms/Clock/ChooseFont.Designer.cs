namespace Clock
{
	partial class ChooseFont
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ChooseFont));
			this.comboBoxFonts = new System.Windows.Forms.ComboBox();
			this.labelChooseFont = new System.Windows.Forms.Label();
			this.labelSample = new System.Windows.Forms.Label();
			this.numericUpDownFontSize = new System.Windows.Forms.NumericUpDown();
			this.buttonOK = new System.Windows.Forms.Button();
			this.buttonCancel = new System.Windows.Forms.Button();
			this.labelFontSize = new System.Windows.Forms.Label();
			this.buttonApply = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownFontSize)).BeginInit();
			this.SuspendLayout();
			// 
			// comboBoxFonts
			// 
			this.comboBoxFonts.FormattingEnabled = true;
			this.comboBoxFonts.Location = new System.Drawing.Point(12, 39);
			this.comboBoxFonts.Name = "comboBoxFonts";
			this.comboBoxFonts.Size = new System.Drawing.Size(277, 21);
			this.comboBoxFonts.TabIndex = 0;
			this.comboBoxFonts.SelectedIndexChanged += new System.EventHandler(this.comboBoxFonts_SelectedIndexChanged);
			// 
			// labelChooseFont
			// 
			this.labelChooseFont.AutoSize = true;
			this.labelChooseFont.Location = new System.Drawing.Point(12, 20);
			this.labelChooseFont.Name = "labelChooseFont";
			this.labelChooseFont.Size = new System.Drawing.Size(64, 13);
			this.labelChooseFont.TabIndex = 1;
			this.labelChooseFont.Text = "ChooseFont";
			// 
			// labelSample
			// 
			this.labelSample.AutoSize = true;
			this.labelSample.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.labelSample.Location = new System.Drawing.Point(8, 85);
			this.labelSample.Name = "labelSample";
			this.labelSample.Size = new System.Drawing.Size(194, 37);
			this.labelSample.TabIndex = 2;
			this.labelSample.Text = "Font sample";
			// 
			// numericUpDownFontSize
			// 
			this.numericUpDownFontSize.Increment = new decimal(new int[] {
            4,
            0,
            0,
            0});
			this.numericUpDownFontSize.Location = new System.Drawing.Point(295, 40);
			this.numericUpDownFontSize.Maximum = new decimal(new int[] {
            50,
            0,
            0,
            0});
			this.numericUpDownFontSize.Minimum = new decimal(new int[] {
            24,
            0,
            0,
            0});
			this.numericUpDownFontSize.Name = "numericUpDownFontSize";
			this.numericUpDownFontSize.Size = new System.Drawing.Size(80, 20);
			this.numericUpDownFontSize.TabIndex = 3;
			this.numericUpDownFontSize.Value = new decimal(new int[] {
            24,
            0,
            0,
            0});
			// 
			// buttonOK
			// 
			this.buttonOK.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.buttonOK.Location = new System.Drawing.Point(219, 142);
			this.buttonOK.Name = "buttonOK";
			this.buttonOK.Size = new System.Drawing.Size(75, 23);
			this.buttonOK.TabIndex = 4;
			this.buttonOK.Text = "OK";
			this.buttonOK.UseVisualStyleBackColor = true;
			this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
			// 
			// buttonCancel
			// 
			this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonCancel.Location = new System.Drawing.Point(300, 142);
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.Size = new System.Drawing.Size(75, 23);
			this.buttonCancel.TabIndex = 5;
			this.buttonCancel.Text = "Cancel";
			this.buttonCancel.UseVisualStyleBackColor = true;
			// 
			// labelFontSize
			// 
			this.labelFontSize.AutoSize = true;
			this.labelFontSize.Location = new System.Drawing.Point(297, 20);
			this.labelFontSize.Name = "labelFontSize";
			this.labelFontSize.Size = new System.Drawing.Size(30, 13);
			this.labelFontSize.TabIndex = 6;
			this.labelFontSize.Text = "Size:";
			// 
			// buttonApply
			// 
			this.buttonApply.Location = new System.Drawing.Point(295, 66);
			this.buttonApply.Name = "buttonApply";
			this.buttonApply.Size = new System.Drawing.Size(75, 23);
			this.buttonApply.TabIndex = 7;
			this.buttonApply.Text = "Применить";
			this.buttonApply.UseVisualStyleBackColor = true;
			this.buttonApply.Click += new System.EventHandler(this.buttonApply_Click);
			// 
			// ChooseFont
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(387, 177);
			this.Controls.Add(this.buttonApply);
			this.Controls.Add(this.labelFontSize);
			this.Controls.Add(this.buttonCancel);
			this.Controls.Add(this.buttonOK);
			this.Controls.Add(this.numericUpDownFontSize);
			this.Controls.Add(this.labelSample);
			this.Controls.Add(this.labelChooseFont);
			this.Controls.Add(this.comboBoxFonts);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "ChooseFont";
			this.ShowInTaskbar = false;
			this.Text = "ChooseFont";
			((System.ComponentModel.ISupportInitialize)(this.numericUpDownFontSize)).EndInit();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ComboBox comboBoxFonts;
		private System.Windows.Forms.Label labelChooseFont;
		private System.Windows.Forms.Label labelSample;
		private System.Windows.Forms.NumericUpDown numericUpDownFontSize;
		private System.Windows.Forms.Button buttonOK;
		private System.Windows.Forms.Button buttonCancel;
		private System.Windows.Forms.Label labelFontSize;
		private System.Windows.Forms.Button buttonApply;
	}
}