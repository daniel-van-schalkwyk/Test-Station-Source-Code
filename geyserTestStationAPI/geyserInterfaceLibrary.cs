using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;

namespace geyserTestStationAPI
{
    public class geyserTestStationAPI
    {
        // Properties 
        public String SetupCMD = "2:1";
        private double PowerUsage_;
        public enum GetCommandsIndex : int
        {
            flowRate, powerUsage, labTemp, outletTemp, geyserThermistorTemp,
            busTempVector, geyserSurfaceTemp, chamberTemp, chamberFans, sourceWaterTemp,
            inletWaterTemp, freezerTemp, inletTankThermostatTemp, inletValvePosition
        };
        public enum SetCommandsIndex : int
        {
            outletValveSet, powerAvailSet, setInletValve, setInletFreezerTemp, setExpParams, setInletGeyserTemp
        };
        public Dictionary<int, String> GetCommands = new Dictionary<int, String>()
            {
                {(int)GetCommandsIndex.flowRate, "get:" + ((int)GetCommandsIndex.flowRate).ToString()},
                {(int)GetCommandsIndex.powerUsage, "get:" + ((int)GetCommandsIndex.powerUsage).ToString()},
                {(int)GetCommandsIndex.labTemp, "get:" + ((int)GetCommandsIndex.labTemp).ToString()},
                {(int)GetCommandsIndex.outletTemp, "get:" + ((int)GetCommandsIndex.outletTemp).ToString()},
                {(int)GetCommandsIndex.geyserThermistorTemp, "get:" + ((int)GetCommandsIndex.geyserThermistorTemp).ToString()},
                {(int)GetCommandsIndex.busTempVector, "get:" + ((int)GetCommandsIndex.busTempVector).ToString()},
                {(int)GetCommandsIndex.geyserSurfaceTemp, "get:" + ((int)GetCommandsIndex.geyserSurfaceTemp).ToString()},
                {(int)GetCommandsIndex.chamberTemp, "get:" + ((int)GetCommandsIndex.chamberTemp).ToString()},
                {(int)GetCommandsIndex.chamberFans, "get:" + ((int)GetCommandsIndex.chamberFans).ToString()},
                {(int)GetCommandsIndex.sourceWaterTemp, "get:" + ((int)GetCommandsIndex.sourceWaterTemp).ToString()},
                {(int)GetCommandsIndex.inletWaterTemp, "get:" + ((int)GetCommandsIndex.inletWaterTemp).ToString()},
                {(int)GetCommandsIndex.freezerTemp, "get:" + ((int)GetCommandsIndex.freezerTemp).ToString()},
                {(int)GetCommandsIndex.inletTankThermostatTemp, "get:" + ((int)GetCommandsIndex.inletTankThermostatTemp).ToString()},
                {(int)GetCommandsIndex.inletValvePosition, "get:" + ((int)GetCommandsIndex.inletValvePosition).ToString()}
            };

        public Dictionary<int, String> SetCommands = new Dictionary<int, String>()
            {
                {(int)SetCommandsIndex.outletValveSet, "set:" + ((int)SetCommandsIndex.outletValveSet).ToString()},
                {(int)SetCommandsIndex.powerAvailSet, "set:" + ((int)SetCommandsIndex.powerAvailSet).ToString()},
                {(int)SetCommandsIndex.setInletValve, "set:" + ((int)SetCommandsIndex.setInletValve).ToString()},
                {(int)SetCommandsIndex.setInletFreezerTemp, "set:" + ((int)SetCommandsIndex.setInletFreezerTemp).ToString()},
                {(int)SetCommandsIndex.setExpParams, "set:" + ((int)SetCommandsIndex.setExpParams).ToString()},
                {(int)SetCommandsIndex.setInletGeyserTemp, "set:" + ((int)SetCommandsIndex.setInletGeyserTemp).ToString()}
            };
        public SerialPort SerialPort = new SerialPort();
        private string[] BaudRates_ = { "9600", "115200", "256000" };

        // Constructor
        public geyserTestStationAPI()
        {
            //SerialPortSetup();  // Configure Serial Port for controller communication
        }

        // General commands
        private void SendCommandPackage(String commandString)
        {
            // Use serial port to send requested command to controller
            if (SerialPort.IsOpen)
                SerialPort.WriteLine(commandString);
            else
                Console.WriteLine("Serial port has not been not been opened");
        }

        public void CloseSerialPort()
        {
            if (SerialPort.IsOpen)
                SerialPort.Close();
            else
                Console.WriteLine("Serial port already closed");
        }

        public SerialPort OpenSerialPort(String portName)
        {
            if(!SerialPort.IsOpen)
            {
                SerialPort.BaudRate = int.Parse(BaudRates_[1]);
                SerialPort.PortName = portName;
                SerialPort.Handshake = Handshake.None;
                SerialPort.Parity = Parity.None;
                SerialPort.Open();
            }
            else
            {
                Console.WriteLine("Serial port already open");
            }
            return SerialPort;
        }

        // *** Get functions for sensor measurements ***

        // User / Eskom / Atmospheric commands
        public String GetFlowRate()
        {
            String getMessage = this.GetCommands[(int)GetCommandsIndex.flowRate];
            // Get the flow rate from the controller 
            this.SendCommandPackage(getMessage);
            return getMessage;
        }

        public String RequestTemperatureBus(int busNumber)
        {
            String getMessage = this.GetCommands[(int)GetCommandsIndex.busTempVector] + ":" + busNumber.ToString();
            // Get the flow rate from the controller 
            this.SendCommandPackage(getMessage);
            return getMessage;
        }

        public String GetGeyserThermostatTemperature()
        {
            String getMessage = this.GetCommands[(int)GetCommandsIndex.geyserThermistorTemp];
            // Get the thermostat temperature from the controller 
            this.SendCommandPackage(getMessage);
            return getMessage;
        }

        public bool GetElementPowerState()
        {
            if (this.PowerUsage_ > 0) { return true; }
            return false;
        }

        public String GetElementPowerUsage()
        {
            String getMessage = this.GetCommands[(int)GetCommandsIndex.powerUsage];
            this.SendCommandPackage(getMessage);
            return getMessage;
        }

        public String GetLabTemperature()
        {
            String getMessage = this.GetCommands[(int)GetCommandsIndex.labTemp];
            this.SendCommandPackage(getMessage);
            return getMessage;
        }

        public String GetOutletTemperature()
        {
            String getMessage = this.GetCommands[(int)GetCommandsIndex.outletTemp];
           this.SendCommandPackage(getMessage);
            return getMessage;
        }

        public String GetInletTemperature()
        {
            String getMessage = this.GetCommands[(int)GetCommandsIndex.inletWaterTemp];
            this.SendCommandPackage(getMessage);
            return getMessage;
        }

        public String GetGeyserSurfaceTemperatures()
        {
            String getMessage = this.GetCommands[(int)GetCommandsIndex.geyserSurfaceTemp];
            this.SendCommandPackage(getMessage);
            return getMessage;
        }

        public String GetChamberTemperature()
        {
            String getMessage = this.GetCommands[(int)GetCommandsIndex.chamberTemp];
            this.SendCommandPackage(getMessage);
            return getMessage;
        }

        public String GetChamberFanStatus()
        {
            String getMessage = this.GetCommands[(int)GetCommandsIndex.chamberFans];
            this.SendCommandPackage(getMessage);
            return getMessage;
        }

        public String GetWaterSourceTemperature()
        {
            String getMessage = this.GetCommands[(int)GetCommandsIndex.sourceWaterTemp];
            this.SendCommandPackage(getMessage);
            return getMessage;
        }

        public String GetInletFreezerTemperature()
        {
            String getMessage = this.GetCommands[(int)GetCommandsIndex.freezerTemp];
            this.SendCommandPackage(getMessage);
            return getMessage;
        }

        public String GetInletTankThermostatTemperature()
        {
            String getMessage = this.GetCommands[(int)GetCommandsIndex.inletTankThermostatTemp];
            this.SendCommandPackage(getMessage);
            return getMessage;
        }

        public String GetInletValveAngle()
        {
            String getMessage = this.GetCommands[(int)GetCommandsIndex.inletValvePosition];
            this.SendCommandPackage(getMessage);
            return getMessage;
        }

        // Set functions for Actuators

        public String SetOutletValveStep(int stepSize, int direction)
        {
            String setMessage = this.SetCommands[(int)SetCommandsIndex.outletValveSet] + ":" + direction.ToString() + ":" + stepSize.ToString();
            this.SendCommandPackage(setMessage);
            return setMessage;
        }

        public String SetElementElectricitySupply(int state)
        {
            String setMessage = this.SetCommands[(int)SetCommandsIndex.powerAvailSet] + ":" + state.ToString();
            this.SendCommandPackage(setMessage);
            return setMessage;
        }

        public String SetInletValveAngle(double angle)
        {
            String setMessage = this.SetCommands[(int)SetCommandsIndex.powerAvailSet] + ":" + angle.ToString();
            if (angle > 90 || angle < 0)
                Console.WriteLine("Inlet servo valve angle must be in the range of 0 to 90 degrees");
            else
                this.SendCommandPackage(setMessage);
            return setMessage;
        }

        public String SetInletFreezerTemperature(double freezerTemp)
        {
            String setMessage = this.SetCommands[(int)SetCommandsIndex.setInletFreezerTemp] + ":" + freezerTemp.ToString();
            this.SendCommandPackage(setMessage);
            return setMessage;
        }

        public String SetInletGeyserTemperature(double inletGeyserTemp)
        {
            String setMessage = this.SetCommands[(int)SetCommandsIndex.setInletGeyserTemp] + ":" + inletGeyserTemp.ToString(); 
            this.SendCommandPackage(setMessage);
            return setMessage;
        }

        public String SetExperimentalParameters(int sampleTime, double geyserSetTemp, double chamberSetTemp, double inletSetTemp, double waterFlowRate)
        {
            var experimentalCommand = new StringBuilder("");
            experimentalCommand.Append(this.SetupCMD).Append(',')
                               .Append(sampleTime).Append(',')
                               .Append(chamberSetTemp).Append(',')
                               .Append(geyserSetTemp).Append(',')
                               .Append(inletSetTemp).Append(',')
                               .Append(waterFlowRate);
            String setMessage = this.SetCommands[(int)SetCommandsIndex.setExpParams] + ":" + experimentalCommand.ToString();
            // Send configuration string to controller via serial port
            this.SendCommandPackage(setMessage);
            return setMessage;
        }
    }
}
