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
        SerialPort serialPort = new SerialPort();
        private string[] BaudRates_ = { "9600", "115200", "256000" };

        // Constructor
        public TestStationCommandInterface()
        {

        }

        // General commands
        private void SendCommandPackage(String commandString)
        {
            // Use serial port to send requested command to controller
        }

        // Get functions for sensor measurements

        static void GetExperimentalParameters(int sampleTime, double geyserSetTemp, double chamberSetTemp, double inletSetTemp, double waterFlowRate)
        {
            var self = new TestStationCommandInterface();
            var experimentalCommand = new StringBuilder("");
            experimentalCommand.Append(self.SetupCMD).Append(',')
                               .Append(sampleTime).Append(',')
                               .Append(chamberSetTemp).Append(',')
                               .Append(geyserSetTemp).Append(',')
                               .Append(inletSetTemp).Append(',')
                               .Append(waterFlowRate);
            // Send configuration string to controller via serial port
            self.SendCommandPackage(experimentalCommand.ToString());
        }

        // User / Eskom / Atmospheric commands
        static public double GetFlowRate()
        {
            String flowRate = "";
            var self = new TestStationCommandInterface();
            // Get the flow rate from the controller 
            self.SendCommandPackage(self.GetCommands[(int)GetCommandsIndex.flowRate]);
            return Double.Parse(flowRate);
        }

        public String RequestTemperatureBus(int busNumber)
        {
            String busTempString = "";


            return busTempString;
        }

        static public double GetGeyserThermostatTemperature()
        {
            string thermostatTemperature = "";
            // Get the thermostat temperature from the controller 

            return Double.Parse(thermostatTemperature);
        }

        static public double GetElementPowerState()
        {

            return 0;
        }

        static public double GetElementPowerUsage()
        {

            return 0;
        }

        static public double GetLabTemperature()
        {

            return 0;
        }

        static public double GetOutletTemperature()
        {

            return 0;
        }

        static public double GetInletTemperature()
        {

            return 0;
        }

        static public double GetGeyserSurfaceTemperatures()
        {

            return 0;
        }

        static public double GetChamberTemperature()
        {

            return 0;
        }

        static public double GetChamberFanStatus()
        {

            return 0;
        }

        static public double GetWaterSourceTemperature()
        {

            return 0;
        }

        static public double GetInletFreezerTemperature()
        {

            return 0;
        }

        static public double GetInletTankThermostatTemperature()
        {

            return 0;
        }

        static public double GetInletValveAngle()
        {

            return 0;
        }

        // Set functions for Actuators

        static public void SetOutletValveStep(int stepSize, bool direction)
        {

        }

        static public void SetElementElectricitySupply(bool state)
        {

        }

        static public void SetInletValveAngle(double angle)
        {

        }

        static public void SetInletFreezerTemperature(double freezerTemp)
        {

        }
    }
}
