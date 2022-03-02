using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;

namespace TestStationAPI
{
    public class TestStationCommandInterface
    {
        // Properties 
        public String SetupCMD = "2:1";
        public enum GetCommandsIndex : int
        {
            flowRate, powerUsage, labTemp, outletTemp, geyserThermistorTemp,
            busTempVector, geyserSurfaceTemp, chamberTemp, chamberFans, sourceWaterTemp,
            inletWaterTemp, freezerTemp, inletTankThermostatTemp, inletValvePosition
        };
        public Dictionary<int, String> GetCommands = new Dictionary<int, String>()
            {
                {(int)GetCommandsIndex.flowRate, "get:" + ((int)GetCommandsIndex.flowRate).ToString()},
                {(int)GetCommandsIndex.powerUsage, "get:" + ((int)GetCommandsIndex.powerUsage).ToString()},
                {(int)GetCommandsIndex.labTemp, "get:" + ((int)GetCommandsIndex.labTemp).ToString()},
                {(int)GetCommandsIndex.outletTemp, "get:" + ((int)GetCommandsIndex.outletTemp).ToString()},
                {(int)GetCommandsIndex.geyserThermistorTemp, "get:" + ((int)GetCommandsIndex.geyserThermistorTemp).ToString()},
                {(int)GetCommandsIndex.geyserSurfaceTemp, "get:" + ((int)GetCommandsIndex.geyserSurfaceTemp).ToString()},
                {(int)GetCommandsIndex.chamberTemp, "get:" + ((int)GetCommandsIndex.chamberTemp).ToString()},
                {(int)GetCommandsIndex.chamberFans, "get:" + ((int)GetCommandsIndex.chamberFans).ToString()},
                {(int)GetCommandsIndex.sourceWaterTemp, "get:" + ((int)GetCommandsIndex.sourceWaterTemp).ToString()},
                {(int)GetCommandsIndex.inletWaterTemp, "get:" + ((int)GetCommandsIndex.inletWaterTemp).ToString()},
                {(int)GetCommandsIndex.freezerTemp, "get:" + ((int)GetCommandsIndex.freezerTemp).ToString()},
                {(int)GetCommandsIndex.inletTankThermostatTemp, "get:" + ((int)GetCommandsIndex.inletTankThermostatTemp).ToString()},
                {(int)GetCommandsIndex.inletValvePosition, "get:" + ((int)GetCommandsIndex.inletValvePosition).ToString()}
            };
        private SerialPort SerialPort_ = new SerialPort();
        private string[] BaudRates_ = { "9600", "115200", "256000" };

        // Constructor
        public TestStationCommandInterface()
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

        public void SetExperimentalParameters(int sampleTime, double geyserSetTemp, double chamberSetTemp, double inletSetTemp, double waterFlowRate)
        {
            var experimentalCommand = new StringBuilder("");
            experimentalCommand.Append(self.SetupCMD).Append(',')
                               .Append(sampleTime).Append(',')
                               .Append(chamberSetTemp).Append(',')
                               .Append(geyserSetTemp).Append(',')
                               .Append(inletSetTemp).Append(',')
                               .Append(waterFlowRate);
            // Send configuration string to controller via serial port
            this.SendCommandPackage(experimentalCommand.ToString());
        }

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


            return busTempString;
        }

        public double GetGeyserThermostatTemperature()
        {
            string thermostatTemperature = "";
            // Get the thermostat temperature from the controller 

            return Double.Parse(thermostatTemperature);
        }

        public double GetElementPowerState()
        {

            return 0;
        }

        public double GetElementPowerUsage()
        {

            return 0;
        }

        public double GetLabTemperature()
        {

            return 0;
        }

        public double GetOutletTemperature()
        {

            return 0;
        }

        public double GetInletTemperature()
        {

            return 0;
        }

        public double GetGeyserSurfaceTemperatures()
        {

            return 0;
        }

        public double GetChamberTemperature()
        {

            return 0;
        }

        public double GetChamberFanStatus()
        {

            return 0;
        }

        public double GetWaterSourceTemperature()
        {

            return 0;
        }

        public double GetInletFreezerTemperature()
        {

            return 0;
        }

        public double GetInletTankThermostatTemperature()
        {

            return 0;
        }

        public double GetInletValveAngle()
        {

            return 0;
        }

        // Set functions for Actuators

        public void SetOutletValveStep(int stepSize, bool direction)
        {

        }

        public void SetElementElectricitySupply(bool state)
        {

        }

        public void SetInletValveAngle(double angle)
        {

        }

        public void SetInletFreezerTemperature(double freezerTemp)
        {

        }
    }
}
