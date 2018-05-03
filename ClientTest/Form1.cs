using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ClientTest
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void CLIENTINIT_Click(object sender, EventArgs e)
        {
            string clientId = "11010000004000000001";
            string clientIp = "10.11.1.208";
            ushort clientPort = 6000;
            string svrId = "11010000002000000001";
            string svrIp = "10.11.1.131";
            string authPwd = "12345678a";
            ushort svrPort = 5060;

            this.axSipClient1.MediaInit(clientId, clientIp, clientPort,
                svrId, svrIp, svrPort, authPwd);
            
        }

        private void CLIENTREGISTER_Click(object sender, EventArgs e)
        {
            this.axSipClient1.doRegister(3600);
        }

        private void MEDIAPLAY_Click(object sender, EventArgs e)
        {
            this.axSipClient1.doInvite("11010000001310000002");
        }

        private void MEDIASTOP_Click(object sender, EventArgs e)
        {
            this.axSipClient1.doBye();
        }
    }
}
