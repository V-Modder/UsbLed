using System;
using System.IO.Ports;
using System.Threading;
using System.Windows.Forms;
using UsbLed.Serial;

namespace UsbLed {
    public partial class UsbLed : Form {
        private const int BAUD_RATE = 9600;
        private const int CONTROLLER_ID = 1511511541;

        public UsbLed() {
            InitializeComponent();
        }

        private void btn_connect_Click(object sender, EventArgs e) {
            string portName = GetPort();
            SerialPort port = new SerialPort(portName, BAUD_RATE);
            port.Open();
            port.Write(new byte[] { 0xFD }, 0, 0);
            Thread.Sleep(100);
            if (port.BytesToRead > 0) {
                byte[] response = new byte[4];
                if (port.Read(response, 0, 4) == 4) {
                    if (BitConverter.IsLittleEndian)
                        Array.Reverse(response);

                    return BitConverter.ToInt32(response, 0) == CONTROLLER_ID;
                }
            }
        }

        private string GetPort() {
            foreach (string port in SerialPort.GetPortNames()) {
                if (CheckPortForLedController(port)) {
                    return port;
                }
            }

            return null;
        }

        private bool CheckPortForLedController(string portName) {
            try {
                //port = new SerialPort(portName, BAUD_RATE);
                //port.Open();
                //port.Write(new byte[] { 0xFE }, 0, 0);
                //Thread.Sleep(100);
                //if(port.BytesToRead > 0) {
                //    byte[] response = new byte[4];
                //    if(port.Read(response, 0, 4) == 4) {
                //        if (BitConverter.IsLittleEndian)
                //            Array.Reverse(response);

                //        return BitConverter.ToInt32(response, 0) == CONTROLLER_ID;
                //    }
                //}
                using (LedController port = new LedController(portName))
                    return port.IsLedController();
            }
            finally {
            }
            return false;
        }
    }
}
