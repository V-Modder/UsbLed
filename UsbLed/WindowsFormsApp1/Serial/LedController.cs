using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace UsbLed.Serial {
    class LedController : IDisposable {
        private const short CONTROLLER_ID = 11455;
        private const int READ_TIMEOUT = 3000;

        private SerialPort port;

        public LedController(string serialPort) {
            port = new SerialPort(serialPort, 9600);
            port.Open();
        }

        public Status GetStatus() {
            Write(0xFD);
            Thread.Sleep(100);
            return Read<Status>();
        }

        public short GetId() {
            Write(0xFE);
            Thread.Sleep(100);
            return Read<short>();
        }

        public bool IsLedController() {
            return GetId() == CONTROLLER_ID;
        }

        private T Read<T>() {
            int size = GetSize(typeof(T));
            byte[] buffer = ReadWithTimeout(size);

            BinaryFormatter Formatter = new BinaryFormatter();
            T obj;
            try {
                MemoryStream ms = new MemoryStream(buffer);
                obj = (T)Formatter.Deserialize(ms);
                ms.Close();
            }
            catch (Exception) {
                return default;
            }

            return obj; 
        }

        private byte[] ReadWithTimeout(int size) {
            byte[] buffer = new byte[size];
            Thread t = new Thread(() => port.Read(buffer, 0, size));
            t.Start();
            int i = 0;
            while(t.IsAlive && i < READ_TIMEOUT) {
                Thread.Sleep(10);
                i += 10;
            }

            return buffer;
        }

        private int GetSize(Type type) {
            return Marshal.SizeOf(type);
        }

        private void Write(byte b) {
            port.Write(new byte[] { b }, 0, 1);
        }

        public void Dispose() {
            if (port.IsOpen) {
                port.Close();
            }
        }
    }
}
