using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using geyserTestStationAPI;

namespace geyserInterfaceScript
{
    class Program
    {
        static void Main(string[] args)
        {
            var geyserObject = new geyserTestStationAPI.geyserTestStationAPI();
            String serialPortName = "COM8";
            geyserObject.OpenSerialPort(serialPortName);        
            // ** Add get and set messages here ** 
        }
    }
}
