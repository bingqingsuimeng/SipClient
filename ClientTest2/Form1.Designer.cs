namespace ClientTest2
{
    partial class Form1
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.axSipClient1 = new AxSipClientLib.AxSipClient();
            this.BTN_INIT = new System.Windows.Forms.Button();
            this.BTN_REGISTER = new System.Windows.Forms.Button();
            this.BTN_PLAY = new System.Windows.Forms.Button();
            this.BTN_STOP_PLAY = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.axSipClient1)).BeginInit();
            this.SuspendLayout();
            // 
            // axSipClient1
            // 
            this.axSipClient1.Enabled = true;
            this.axSipClient1.Location = new System.Drawing.Point(1, 1);
            this.axSipClient1.Name = "axSipClient1";
            this.axSipClient1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axSipClient1.OcxState")));
            this.axSipClient1.Size = new System.Drawing.Size(425, 291);
            this.axSipClient1.TabIndex = 0;
            // 
            // BTN_INIT
            // 
            this.BTN_INIT.Location = new System.Drawing.Point(456, 221);
            this.BTN_INIT.Name = "BTN_INIT";
            this.BTN_INIT.Size = new System.Drawing.Size(91, 32);
            this.BTN_INIT.TabIndex = 1;
            this.BTN_INIT.Text = "初始化";
            this.BTN_INIT.UseVisualStyleBackColor = true;
            this.BTN_INIT.Click += new System.EventHandler(this.BTN_INIT_Click);
            // 
            // BTN_REGISTER
            // 
            this.BTN_REGISTER.Location = new System.Drawing.Point(581, 221);
            this.BTN_REGISTER.Name = "BTN_REGISTER";
            this.BTN_REGISTER.Size = new System.Drawing.Size(90, 32);
            this.BTN_REGISTER.TabIndex = 2;
            this.BTN_REGISTER.Text = "注册";
            this.BTN_REGISTER.UseVisualStyleBackColor = true;
            this.BTN_REGISTER.Click += new System.EventHandler(this.BTN_REGISTER_Click);
            // 
            // BTN_PLAY
            // 
            this.BTN_PLAY.Location = new System.Drawing.Point(456, 270);
            this.BTN_PLAY.Name = "BTN_PLAY";
            this.BTN_PLAY.Size = new System.Drawing.Size(91, 34);
            this.BTN_PLAY.TabIndex = 3;
            this.BTN_PLAY.Text = "Play";
            this.BTN_PLAY.UseVisualStyleBackColor = true;
            this.BTN_PLAY.Click += new System.EventHandler(this.BTN_PLAY_Click);
            // 
            // BTN_STOP_PLAY
            // 
            this.BTN_STOP_PLAY.Location = new System.Drawing.Point(581, 270);
            this.BTN_STOP_PLAY.Name = "BTN_STOP_PLAY";
            this.BTN_STOP_PLAY.Size = new System.Drawing.Size(90, 34);
            this.BTN_STOP_PLAY.TabIndex = 4;
            this.BTN_STOP_PLAY.Text = "Stop";
            this.BTN_STOP_PLAY.UseVisualStyleBackColor = true;
            this.BTN_STOP_PLAY.Click += new System.EventHandler(this.BTN_STOP_PLAY_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(710, 399);
            this.Controls.Add(this.BTN_STOP_PLAY);
            this.Controls.Add(this.BTN_PLAY);
            this.Controls.Add(this.BTN_REGISTER);
            this.Controls.Add(this.BTN_INIT);
            this.Controls.Add(this.axSipClient1);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.axSipClient1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private AxSipClientLib.AxSipClient axSipClient1;
        private System.Windows.Forms.Button BTN_INIT;
        private System.Windows.Forms.Button BTN_REGISTER;
        private System.Windows.Forms.Button BTN_PLAY;
        private System.Windows.Forms.Button BTN_STOP_PLAY;
    }
}

