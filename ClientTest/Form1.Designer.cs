namespace ClientTest
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
            this.CLIENTINIT = new System.Windows.Forms.Button();
            this.CLIENTREGISTER = new System.Windows.Forms.Button();
            this.MEDIAPLAY = new System.Windows.Forms.Button();
            this.MEDIASTOP = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.axSipClient1)).BeginInit();
            this.SuspendLayout();
            // 
            // axSipClient1
            // 
            this.axSipClient1.Enabled = true;
            this.axSipClient1.Location = new System.Drawing.Point(0, 0);
            this.axSipClient1.Name = "axSipClient1";
            this.axSipClient1.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axSipClient1.OcxState")));
            this.axSipClient1.Size = new System.Drawing.Size(663, 499);
            this.axSipClient1.TabIndex = 0;
            // 
            // CLIENTINIT
            // 
            this.CLIENTINIT.Location = new System.Drawing.Point(690, 292);
            this.CLIENTINIT.Name = "CLIENTINIT";
            this.CLIENTINIT.Size = new System.Drawing.Size(75, 23);
            this.CLIENTINIT.TabIndex = 1;
            this.CLIENTINIT.Text = "初始化";
            this.CLIENTINIT.UseVisualStyleBackColor = true;
            this.CLIENTINIT.Click += new System.EventHandler(this.CLIENTINIT_Click);
            // 
            // CLIENTREGISTER
            // 
            this.CLIENTREGISTER.Location = new System.Drawing.Point(798, 292);
            this.CLIENTREGISTER.Name = "CLIENTREGISTER";
            this.CLIENTREGISTER.Size = new System.Drawing.Size(75, 23);
            this.CLIENTREGISTER.TabIndex = 2;
            this.CLIENTREGISTER.Text = "注册";
            this.CLIENTREGISTER.UseVisualStyleBackColor = true;
            this.CLIENTREGISTER.Click += new System.EventHandler(this.CLIENTREGISTER_Click);
            // 
            // MEDIAPLAY
            // 
            this.MEDIAPLAY.Location = new System.Drawing.Point(690, 330);
            this.MEDIAPLAY.Name = "MEDIAPLAY";
            this.MEDIAPLAY.Size = new System.Drawing.Size(75, 23);
            this.MEDIAPLAY.TabIndex = 3;
            this.MEDIAPLAY.Text = "播放";
            this.MEDIAPLAY.UseVisualStyleBackColor = true;
            this.MEDIAPLAY.Click += new System.EventHandler(this.MEDIAPLAY_Click);
            // 
            // MEDIASTOP
            // 
            this.MEDIASTOP.Location = new System.Drawing.Point(798, 329);
            this.MEDIASTOP.Name = "MEDIASTOP";
            this.MEDIASTOP.Size = new System.Drawing.Size(75, 23);
            this.MEDIASTOP.TabIndex = 4;
            this.MEDIASTOP.Text = "停止";
            this.MEDIASTOP.UseVisualStyleBackColor = true;
            this.MEDIASTOP.Click += new System.EventHandler(this.MEDIASTOP_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(904, 497);
            this.Controls.Add(this.MEDIASTOP);
            this.Controls.Add(this.MEDIAPLAY);
            this.Controls.Add(this.CLIENTREGISTER);
            this.Controls.Add(this.CLIENTINIT);
            this.Controls.Add(this.axSipClient1);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.axSipClient1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private AxSipClientLib.AxSipClient axSipClient1;
        private System.Windows.Forms.Button CLIENTINIT;
        private System.Windows.Forms.Button CLIENTREGISTER;
        private System.Windows.Forms.Button MEDIAPLAY;
        private System.Windows.Forms.Button MEDIASTOP;
    }
}

