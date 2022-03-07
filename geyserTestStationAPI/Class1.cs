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
        private SerialPort SerialPort_ = new SerialPort();
        private string[] BaudRates_ = { "9600", "115200", "256000" };

        // Constructor
        public geyserTestStationAPI()
        {
            SerialPortSetup();  // Configure Serial Port for controller communication
        }

        // General commands
        private void SendCommandPackage(String commandString)
        {
            // Use serial port to send requested command to controller
            SerialPort_.WriteLine(commandString);
        }

        private void SerialPortSetup()
        {
            SerialPort_.BaudRate = int.Parse(BaudRates_[1]);
            string[] portNames = SerialPort.GetPortNames();
            SerialPort_.PortName = portNames[portNames.Length - 1];
            SerialPort_.Handshake = Handshake.None;
            SerialPort_.Parity = Parity.None;
            SerialPort_.Open();
        }

        public void CloseSerialPort()
        {
            SerialPort_.Close();
        }

        // *** Get functions for sensor measurements ***

        // User / Eskom / Atmospheric commands
        public double GetFlowRate()
        {
            String flowRate = "";
            // Get the flow rate from the controller 
            this.SendCommandPackage(this.GetCommands[(int)GetCommandsIndex.flowRate]);
            return Double.Parse(flowRate);
        }

        public String RequestTemperatureBus(int busNumber)
        {
            String busTempString = "";
            // Get the flow rate from the controller 
            this.SendCommandPackage(this.GetCommands[(int)GetCommandsIndex.busTempVector] + ":" + busNumber.ToString());

            return busTempString;
        }

        public double GetGeyserThermostatTemperature()
        {
            string thermostatTemperature = "";
            // Get the thermostat temperature from the controller 
            this.SendCommandPackage(this.GetCommands[(int)GetCommandsIndex.geyserThermistorTemp]);
            return Double.Parse(thermostatTemperature);
        }

        public bool GetElementPowerState()
        {
            if (this.PowerUsage_ > 0) { return true; }
            return false;
        }

        public double GetElementPowerUsage()
        {
            this.SendCommandPackage(this.GetCommands[(int)GetCommandsIndex.powerUsage]);

            return 0;
        }

        public double GetLabTemperature()
        {
            this.SendCommandPackage(this.GetCommands[(int)GetCommandsIndex.labTemp]);

            return 0;
        }

        public double GetOutletTemperature()
        {
            this.SendCommandPackage(this.GetCommands[(int)GetCommandsIndex.outletTemp]);

            return 0;
        }

        public double GetInletTemperature()
        {
            this.SendCommandPackage(this.GetCommands[(int)GetCommandsIndex.inletWaterTemp]);
            return 0;
        }

        public double GetGeyserSurfaceTemperatures()
        {
            this.SendCommandPackage(this.GetCommands[(int)GetCommandsIndex.geyserSurfaceTemp]);
            return 0;
        }

        public double GetChamberTemperature()
        {
            this.SendCommandPackage(this.GetCommands[(int)GetCommandsIndex.chamberTemp]);

            return 0;
        }

        public double GetChamberFanStatus()
        {
            this.SendCommandPackage(this.GetCommands[(int)GetCommandsIndex.chamberFans]);

            return 0;
        }

        public double GetWaterSourceTemperature()
        {
            this.SendCommandPackage(this.GetCommands[(int)GetCommandsIndex.sourceWaterTemp]);

            return 0;
        }

        public double GetInletFreezerTemperature()
        {
            this.SendCommandPackage(this.GetCommands[(int)GetCommandsIndex.freezerTemp]);

            return 0;
        }

        public double GetInletTankThermostatTemperature()
        {
            this.SendCommandPackage(this.GetCommands[(int)GetCommandsIndex.inletTankThermostatTemp]);

            return 0;
        }

        public double GetInletValveAngle()
        {
            this.SendCommandPackage(this.GetCommands[(int)GetCommandsIndex.inletValvePosition]);

            return 0;
        }

        // Set functions for Actuators

        public void SetOutletValveStep(int stepSize, bool direction)
        {
            this.SendCommandPackage(this.SetCommands[(int)SetCommandsIndex.outletValveSet] + "," + direction.ToString() + "," + stepSize.ToString());
        }

        public void SetElementElectricitySupply(bool state)
        {
            this.SendCommandPackage(this.SetCommands[(int)SetCommandsIndex.powerAvailSet] + "," + state.ToString());
        }

        public void SetInletValveAngle(double angle)
        {
            if (angle > 90 || angle < 0)
                Console.WriteLine("Inlet servo valve angle must be in the range of 0 to 90 degrees");
            else
                this.SendCommandPackage(this.SetCommands[(int)SetCommandsIndex.powerAvailSet] + "," + angle.ToString());
        }

        public void SetInletFreezerTemperature(double freezerTemp)
        {
            this.SendCommandPackage(this.SetCommands[(int)SetCommandsIndex.setInletFreezerTemp] + "," + freezerTemp.ToString());
        }

        public void SetInletGeyserTemperature(double inletGeyserTemp)
        {
            this.SendCommandPackage(this.SetCommands[(int)SetCommandsIndex.setInletGeyserTemp] + "," + inletGeyserTemp.ToString());
        }

        public void SetExperimentalParameters(int sampleTime, double geyserSetTemp, double chamberSetTemp, double inletSetTemp, double waterFlowRate)
        {
            var experimentalCommand = new StringBuilder("");
            experimentalCommand.Append(this.SetupCMD).Append(',')
                               .Append(sampleTime).Append(',')
                               .Append(chamberSetTemp).Append(',')
                               .Append(geyserSetTemp).Append(',')
                               .Append(inletSetTemp).Append(',')
                               .Append(waterFlowRate);
            // Send configuration string to controller via serial port
            this.SendCommandPackage(this.SetCommands[(int)SetCommandsIndex.setExpParams] + "," + experimentalCommand.ToString());
        }
    }
}
