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
            short clientPort = 6000;
            string svrId = "11010000002000000001";
            string svrIp = "10.11.1.131";
            string authPwd = "12345678a";
            short svrPort = 5060;

            //this.axSipClient1.MediaInit(clientId, clientIp, clientPort,
            //    svrId, svrIp, svrPort, authPwd);
        }
    }
}
