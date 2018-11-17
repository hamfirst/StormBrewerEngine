namespace AddComponentWizard2017
{
	partial class AddComponentTab
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

		#region Component Designer generated code

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.label1 = new System.Windows.Forms.Label();
			this.componentName = new System.Windows.Forms.TextBox();
			this.createPath = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.headerFile = new System.Windows.Forms.TextBox();
			this.sourceFile = new System.Windows.Forms.TextBox();
			this.label4 = new System.Windows.Forms.Label();
			this.regFile = new System.Windows.Forms.TextBox();
			this.label5 = new System.Windows.Forms.Label();
			this.metaFile = new System.Windows.Forms.TextBox();
			this.label6 = new System.Windows.Forms.Label();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.initDataName = new System.Windows.Forms.TextBox();
			this.label7 = new System.Windows.Forms.Label();
			this.createInitData = new System.Windows.Forms.CheckBox();
			this.okay = new System.Windows.Forms.Button();
			this.cancel = new System.Windows.Forms.Button();
			this.syncToServerObject = new System.Windows.Forms.CheckBox();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(15, 47);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(92, 13);
			this.label1.TabIndex = 0;
			this.label1.Text = "Component Name";
			// 
			// componentName
			// 
			this.componentName.Location = new System.Drawing.Point(15, 64);
			this.componentName.Name = "componentName";
			this.componentName.Size = new System.Drawing.Size(187, 20);
			this.componentName.TabIndex = 1;
			this.componentName.Text = "Component";
			this.componentName.TextChanged += new System.EventHandler(this.componentName_TextChanged);
			// 
			// createPath
			// 
			this.createPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
			this.createPath.Location = new System.Drawing.Point(12, 294);
			this.createPath.Name = "createPath";
			this.createPath.Size = new System.Drawing.Size(434, 20);
			this.createPath.TabIndex = 2;
			// 
			// label2
			// 
			this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(15, 275);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(94, 13);
			this.label2.TabIndex = 3;
			this.label2.Text = "Source Code Path";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(15, 139);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(61, 13);
			this.label3.TabIndex = 4;
			this.label3.Text = "Header File";
			// 
			// headerFile
			// 
			this.headerFile.Location = new System.Drawing.Point(12, 156);
			this.headerFile.Name = "headerFile";
			this.headerFile.Size = new System.Drawing.Size(190, 20);
			this.headerFile.TabIndex = 5;
			this.headerFile.TextChanged += new System.EventHandler(this.headerFile_TextChanged);
			// 
			// sourceFile
			// 
			this.sourceFile.Location = new System.Drawing.Point(12, 207);
			this.sourceFile.Name = "sourceFile";
			this.sourceFile.Size = new System.Drawing.Size(190, 20);
			this.sourceFile.TabIndex = 7;
			this.sourceFile.TextChanged += new System.EventHandler(this.sourceFile_TextChanged);
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(15, 190);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(60, 13);
			this.label4.TabIndex = 6;
			this.label4.Text = "Source File";
			// 
			// regFile
			// 
			this.regFile.Location = new System.Drawing.Point(221, 207);
			this.regFile.Name = "regFile";
			this.regFile.Size = new System.Drawing.Size(190, 20);
			this.regFile.TabIndex = 11;
			this.regFile.TextChanged += new System.EventHandler(this.regFile_TextChanged);
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(224, 190);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(82, 13);
			this.label5.TabIndex = 10;
			this.label5.Text = "Registration File";
			// 
			// metaFile
			// 
			this.metaFile.Location = new System.Drawing.Point(221, 156);
			this.metaFile.Name = "metaFile";
			this.metaFile.Size = new System.Drawing.Size(190, 20);
			this.metaFile.TabIndex = 9;
			this.metaFile.TextChanged += new System.EventHandler(this.metaFile_TextChanged);
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point(224, 139);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(50, 13);
			this.label6.TabIndex = 8;
			this.label6.Text = "Meta File";
			// 
			// groupBox1
			// 
			this.groupBox1.Anchor = System.Windows.Forms.AnchorStyles.Right;
			this.groupBox1.Controls.Add(this.initDataName);
			this.groupBox1.Controls.Add(this.label7);
			this.groupBox1.Controls.Add(this.createInitData);
			this.groupBox1.Location = new System.Drawing.Point(458, 114);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(205, 139);
			this.groupBox1.TabIndex = 12;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Init Data";
			// 
			// initDataName
			// 
			this.initDataName.Location = new System.Drawing.Point(6, 93);
			this.initDataName.Name = "initDataName";
			this.initDataName.Size = new System.Drawing.Size(190, 20);
			this.initDataName.TabIndex = 14;
			this.initDataName.TextChanged += new System.EventHandler(this.initDataName_TextChanged);
			// 
			// label7
			// 
			this.label7.AutoSize = true;
			this.label7.Location = new System.Drawing.Point(9, 76);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(106, 13);
			this.label7.TabIndex = 13;
			this.label7.Text = "Init Data Class Name";
			// 
			// createInitData
			// 
			this.createInitData.AutoSize = true;
			this.createInitData.Checked = true;
			this.createInitData.CheckState = System.Windows.Forms.CheckState.Checked;
			this.createInitData.Location = new System.Drawing.Point(6, 42);
			this.createInitData.Name = "createInitData";
			this.createInitData.Size = new System.Drawing.Size(100, 17);
			this.createInitData.TabIndex = 0;
			this.createInitData.Text = "Create Init Data";
			this.createInitData.UseVisualStyleBackColor = true;
			this.createInitData.CheckedChanged += new System.EventHandler(this.createInitData_CheckedChanged);
			// 
			// okay
			// 
			this.okay.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.okay.Location = new System.Drawing.Point(545, 291);
			this.okay.Name = "okay";
			this.okay.Size = new System.Drawing.Size(119, 23);
			this.okay.TabIndex = 13;
			this.okay.Text = "Okay";
			this.okay.UseVisualStyleBackColor = true;
			this.okay.Click += new System.EventHandler(this.okay_Click);
			// 
			// cancel
			// 
			this.cancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.cancel.Location = new System.Drawing.Point(464, 291);
			this.cancel.Name = "cancel";
			this.cancel.Size = new System.Drawing.Size(75, 23);
			this.cancel.TabIndex = 14;
			this.cancel.Text = "Cancel";
			this.cancel.UseVisualStyleBackColor = true;
			this.cancel.Click += new System.EventHandler(this.cancel_Click);
			// 
			// syncToServerObject
			// 
			this.syncToServerObject.AutoSize = true;
			this.syncToServerObject.Checked = true;
			this.syncToServerObject.CheckState = System.Windows.Forms.CheckState.Checked;
			this.syncToServerObject.Location = new System.Drawing.Point(14, 245);
			this.syncToServerObject.Name = "syncToServerObject";
			this.syncToServerObject.Size = new System.Drawing.Size(134, 17);
			this.syncToServerObject.TabIndex = 15;
			this.syncToServerObject.Text = "Sync To Server Object";
			this.syncToServerObject.UseVisualStyleBackColor = true;
			// 
			// AddComponentTab
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.syncToServerObject);
			this.Controls.Add(this.cancel);
			this.Controls.Add(this.okay);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.regFile);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.metaFile);
			this.Controls.Add(this.label6);
			this.Controls.Add(this.sourceFile);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.headerFile);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.createPath);
			this.Controls.Add(this.componentName);
			this.Controls.Add(this.label1);
			this.Name = "AddComponentTab";
			this.Size = new System.Drawing.Size(676, 326);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button cancel;
		private System.Windows.Forms.TextBox initDataName;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.CheckBox createInitData;
		private System.Windows.Forms.Button okay;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.TextBox regFile;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.TextBox metaFile;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TextBox sourceFile;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.TextBox headerFile;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox createPath;
		private System.Windows.Forms.TextBox componentName;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.CheckBox syncToServerObject;
	}
}
