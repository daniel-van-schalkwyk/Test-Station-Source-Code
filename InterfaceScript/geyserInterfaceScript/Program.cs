using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using geyserTestStationAPI;
using System.IO.Ports;
using System.ComponentModel;
using System.Data;
using System.Drawing;

namespace geyserInterfaceScript
{
    class Program
    {
        enum states { On, Off };
        static void Main(string[] args)
        {
            var geyserObject = new geyserTestStationAPI.geyserTestStationAPI();
            String serialPortName = "COM8";
            geyserObject.OpenSerialPort(serialPortName);
            // ** Add get and set messages here ** 
            // Example: 
            geyserObject.SetElementElectricitySupply((int)states.On);
            
            var mcuResponse = geyserObject.CaptureSerialResponse(); // Read response (Might need to use a delegate for this)

        }
    }
}
