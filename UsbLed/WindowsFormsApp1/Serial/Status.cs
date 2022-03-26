using System.Runtime.InteropServices;

namespace UsbLed.Serial {

    [StructLayout(LayoutKind.Explicit, Size = 10, Pack = 1)]
    public struct Status {
        [MarshalAs(UnmanagedType.U1)]
        [FieldOffset(0)]
        public uint EEPROM_BRIGHTNESS;

        [MarshalAs(UnmanagedType.U1)]
        [FieldOffset(1)]
        public uint EEPROM_MODE;

        [MarshalAs(UnmanagedType.Struct)]
        [FieldOffset(2)]
        public Color EEPROM_COLOR;

        [MarshalAs(UnmanagedType.U1)]
        [FieldOffset(5)]
        public uint BRIGHTNESS;

        [MarshalAs(UnmanagedType.U1)]
        [FieldOffset(6)]
        public uint MODE;

        [MarshalAs(UnmanagedType.Struct)]
        [FieldOffset(7)]
        public Color COLOR;

        //[MarshalAs(UnmanagedType.U4)]
        //[FieldOffset(20)]
        //public uint TimeStamp;

        //[MarshalAs(UnmanagedType.U4)]
        //[FieldOffset(24)]
        //public uint Sequence;

        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 16)]
        //[FieldOffset(28)]
        //public string Tracking;
    }
}
