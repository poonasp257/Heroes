namespace DummyClient {
	partial class Form {
		/// <summary>
		/// 필수 디자이너 변수입니다.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		/// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form 디자이너에서 생성한 코드

		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다. 
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
		/// </summary>
		private void InitializeComponent()
		{
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.label1 = new System.Windows.Forms.Label();
			this.textBoxIP = new System.Windows.Forms.TextBox();
			this.textBoxPort = new System.Windows.Forms.TextBox();
			this.textBox13 = new System.Windows.Forms.TextBox();
			this.label12 = new System.Windows.Forms.Label();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.label4 = new System.Windows.Forms.Label();
			this.textBoxDummyCount = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.buttonStartAction = new System.Windows.Forms.Button();
			this.button1 = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.button1);
			this.groupBox1.Controls.Add(this.buttonStartAction);
			this.groupBox1.Controls.Add(this.textBox13);
			this.groupBox1.Controls.Add(this.label12);
			this.groupBox1.Controls.Add(this.textBox1);
			this.groupBox1.Controls.Add(this.label4);
			this.groupBox1.Controls.Add(this.textBoxDummyCount);
			this.groupBox1.Controls.Add(this.label3);
			this.groupBox1.Controls.Add(this.textBoxPort);
			this.groupBox1.Controls.Add(this.textBoxIP);
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Location = new System.Drawing.Point(12, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(460, 194);
			this.groupBox1.TabIndex = 0;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Dummy Info";
			this.groupBox1.Enter += new System.EventHandler(this.groupBox1_Enter);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.label1.Location = new System.Drawing.Point(22, 43);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(86, 12);
			this.label1.TabIndex = 2;
			this.label1.Text = "Server IP, Port";
			// 
			// textBoxIP
			// 
			this.textBoxIP.Location = new System.Drawing.Point(114, 40);
			this.textBoxIP.Name = "textBoxIP";
			this.textBoxIP.Size = new System.Drawing.Size(81, 21);
			this.textBoxIP.TabIndex = 3;
			this.textBoxIP.Text = "127.0.0.1";
			// 
			// textBoxPort
			// 
			this.textBoxPort.Location = new System.Drawing.Point(201, 40);
			this.textBoxPort.Name = "textBoxPort";
			this.textBoxPort.Size = new System.Drawing.Size(61, 21);
			this.textBoxPort.TabIndex = 5;
			this.textBoxPort.Text = "32452";
			this.textBoxPort.TextChanged += new System.EventHandler(this.textBoxPort_TextChanged);
			// 
			// textBox13
			// 
			this.textBox13.Location = new System.Drawing.Point(393, 68);
			this.textBox13.Name = "textBox13";
			this.textBox13.Size = new System.Drawing.Size(40, 21);
			this.textBox13.TabIndex = 18;
			this.textBox13.Text = "5000";
			// 
			// label12
			// 
			this.label12.AutoSize = true;
			this.label12.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.label12.Location = new System.Drawing.Point(248, 73);
			this.label12.Name = "label12";
			this.label12.Size = new System.Drawing.Size(135, 12);
			this.label12.TabIndex = 17;
			this.label12.Text = "Max Packet Size(byte)";
			// 
			// textBox1
			// 
			this.textBox1.Enabled = false;
			this.textBox1.Location = new System.Drawing.Point(393, 36);
			this.textBox1.Name = "textBox1";
			this.textBox1.ReadOnly = true;
			this.textBox1.Size = new System.Drawing.Size(40, 21);
			this.textBox1.TabIndex = 16;
			this.textBox1.Text = "0";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.label4.Location = new System.Drawing.Point(313, 40);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(73, 12);
			this.label4.TabIndex = 15;
			this.label4.Text = "현재 접속 수";
			// 
			// textBoxDummyCount
			// 
			this.textBoxDummyCount.Location = new System.Drawing.Point(114, 64);
			this.textBoxDummyCount.Name = "textBoxDummyCount";
			this.textBoxDummyCount.Size = new System.Drawing.Size(44, 21);
			this.textBoxDummyCount.TabIndex = 14;
			this.textBoxDummyCount.Text = "400";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.label3.Location = new System.Drawing.Point(22, 71);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(86, 12);
			this.label3.TabIndex = 13;
			this.label3.Text = "Dummy Count";
			this.label3.Click += new System.EventHandler(this.label3_Click);
			// 
			// buttonStartAction
			// 
			this.buttonStartAction.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.buttonStartAction.Location = new System.Drawing.Point(114, 140);
			this.buttonStartAction.Name = "buttonStartAction";
			this.buttonStartAction.Size = new System.Drawing.Size(75, 23);
			this.buttonStartAction.TabIndex = 20;
			this.buttonStartAction.Text = "Start";
			this.buttonStartAction.UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this.button1.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.button1.Location = new System.Drawing.Point(277, 140);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(75, 23);
			this.button1.TabIndex = 21;
			this.button1.Text = "Stop";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// Form
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(486, 224);
			this.Controls.Add(this.groupBox1);
			this.ForeColor = System.Drawing.SystemColors.ControlLightLight;
			this.Name = "Form";
			this.Text = "Form1";
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.TextBox textBox13;
		private System.Windows.Forms.Label label12;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.TextBox textBoxDummyCount;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox textBoxPort;
		private System.Windows.Forms.TextBox textBoxIP;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Button buttonStartAction;
	}
}

