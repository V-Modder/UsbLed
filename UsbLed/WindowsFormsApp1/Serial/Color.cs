using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace UsbLed.Serial {
    [StructLayout(LayoutKind.Explicit, Size = 3, Pack = 1)]
    public struct Color {
        [MarshalAs(UnmanagedType.U1)]
        [FieldOffset(0)]
        public uint RED;

        [MarshalAs(UnmanagedType.U1)]
        [FieldOffset(1)]
        public uint GREEN;

        [MarshalAs(UnmanagedType.U1)]
        [FieldOffset(2)]
        public uint BLUE;
    }
}
