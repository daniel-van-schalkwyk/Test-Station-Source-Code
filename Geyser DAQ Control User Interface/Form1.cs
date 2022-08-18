using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Geyser_DAQ_Control_User_Interface
{
    public partial class Form1 : Form
    {
        SerialPort serialPort = new SerialPort();
        private string[] BaudRates = {"9600", "115200", "256000" };
        String[] dataArray;
        bool waterScheduleStringReady = false;
        bool powerScheduleStringReady = false;
        string stopCMD = "0:1";
        string startCMD = "1:1";
        string configCMD = "2:1";
        string resetMcuCMD = "3:1";
        string openValveCommand = "V:1";
        string closeValveCommand = "V:0";
        StringBuilder configString = new StringBuilder();
        public delegate void AddDataDelegate(String myString);
        public AddDataDelegate mySerialReadDelegate;
        String fileName = "";
        String path = "";
        String dataFileHeaders = "TimeStamp,ChamberSetTemp,GeyserWaterSetTemp,InletWaterSetTemp,DesiredFlowRate," +
                                "ChamberAirTempReg,GeyserWaterTempReg,InletWaterTempReg,FlowRateReg,WaterScheduleControl,PowerScheduleControl," +
                                "ChamberHeatingFans,ChamberVentingFans,CirculationFans,ChamberHeatingElement," +
                                "WaterValveState,GeyserHeatingFlag,PowerConsumed,WaterConsumed," +
                                "TotalWaterConsumed,GeyserWaterThermostatTemp,InletWaterTemp," +
                                "OutletWaterTemp,TopGeyserSurfaceTemp,BotGeyserSurfaceTemp,LabTemp,ChamberTemp1,ChamberTemp2,ChamberTempMean";

        StringBuilder dataUnits = new StringBuilder("YYYY-MM-DDTHH:mm:ss,°C,°C,°C,L/min,Bool,Bool,Bool,Bool,Bool,Bool,Bool,Bool,Bool,Bool,Bool,Bool,kWh,mL,mL,°C,°C,°C,°C,°C,°C,°C,°C,°C");

        public Form1()
        {
            InitializeComponent();
            string[] portNames = SerialPort.GetPortNames();
            portComboBox.Items.AddRange(portNames);
            portComboBox.SelectedItem = portNames[portNames.Length - 1];
            baudRateComboBox.Items.AddRange(BaudRates);
            baudRateComboBox.SelectedItem = "115200";   // Default Baud rate for serial connection
            samplingTimeTextBox.Text = "5";    // Default sampling time value for system [10s]
            this.mySerialReadDelegate = new AddDataDelegate(AddDataMethod);
        }

        public void AddDataMethod(String myString)
        {
            serialReceiveTextBox.AppendText(myString);
            if (myString.StartsWith("2")) 
            { 
                dataArray = myString.Split(',');
                geyserWaterTempTextBox.Text = (dataArray[20].StartsWith("-1")) ? ("Not Connected") : dataArray[20] + " °C";
                inletWaterTempTextBox.Text = (dataArray[21].StartsWith("-127")) ? ("Not Connected") : dataArray[21] + " °C";
                outletWaterTempTextBox.Text = (dataArray[22].StartsWith("-127")) ? ("Not Connected") : dataArray[22] + " °C";
                ChamberTempTextBox.Text = (dataArray[28].StartsWith("-")) ? ("Not Connected") : dataArray[28] + " °C";
                waterFlowRateTextBox.Text = dataArray[18] + " mL/Ts";
                energyUsedTextBox.Text = dataArray[17] + " Wh/Ts";
                try
                {
                    ActualElementStateTextBox.Text = (double.Parse(dataArray[17]) > 1) ? ("On") : ("Off");
                }
                catch
                {

                }
                geyserElementStateTextBox.Text = (dataArray[16].StartsWith("1")) ? ("On") : ("Off");
                labTemperatureTextBox.Text = (dataArray[25].StartsWith("-")) ? ("Not Connected") : dataArray[25] + " °C";
                ExperimentDurTextBox.Text = "";
            }

        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        public String generateBoilerColumnHeaders()
        {
            String finalColumnHeaders = "";
            var unitsAppnedString = new StringBuilder(",");
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    finalColumnHeaders += "B";
                    finalColumnHeaders += i.ToString();
                    finalColumnHeaders += "-T";
                    finalColumnHeaders += j.ToString();
                    finalColumnHeaders += ",";
                    unitsAppnedString.Append("°C");
                    unitsAppnedString.Append(",");
                }
            }
            dataUnits.Append(unitsAppnedString);
            return finalColumnHeaders;
        }
            private void connectPortButton_Click(object sender, EventArgs e)
        {
            serialPort.BaudRate = int.Parse(baudRateComboBox.GetItemText(baudRateComboBox.SelectedItem));
            serialPort.PortName = portComboBox.GetItemText(portComboBox.SelectedItem);
            serialPort.Handshake = Handshake.None;
            serialPort.Parity = Parity.None;
            try
            {
                serialPort.Open();
                serialPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);
            }
            catch(Exception ex)
            {
                throw ex;
            }

            if (serialPort.IsOpen)
            {
                connectStatusTextBox.Text = "Connected to " + serialPort.PortName;
            }
            else
            {
                connectStatusTextBox.Text = "Not Connected";
            }
        }
        
        private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string receivedData = sp.ReadLine();
            serialReceiveTextBox.Invoke(this.mySerialReadDelegate, new Object[] { receivedData });
            if (receivedData.StartsWith("2") )
            {
                if (recordDataToFileCheckBox.Checked)
                {
                    using (var w = new System.IO.StreamWriter(path, true))
                    {
                        w.Write(receivedData);
                        w.Flush();
                    }
                }
            }
        }

        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {

        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {

        }

        private void portComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void baudRateComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void disconnectPortButton_Click(object sender, EventArgs e)
        {
            serialPort.Close();
            connectStatusTextBox.Text = "Disconnected from COM";
        }

        private void refreshPortsButton_Click(object sender, EventArgs e)
        {
            portComboBox.Items.Clear();
            portComboBox.Items.AddRange(SerialPort.GetPortNames());
        }

        private void connectStatusTextBox_TextChanged(object sender, EventArgs e)
        {
           
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {

        }

        private void stopButton_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen) { serialPort.WriteLine(stopCMD); serialReceiveTextBox.Clear(); }
            else
            {
                MessageBox.Show("The serial port is not open. First connect before sending stop command");
            }
        }

        private void startButton_Click(object sender, EventArgs e)
        {
            if (recordDataToFileCheckBox.Checked)
            {
                DateTime dt = DateTime.Now;
                fileName = String.Format("{0}_{1}_{2}T{3}_{4}_{5}_Data.csv", dt.Year, dt.Month, dt.Day, dt.Hour, dt.Minute, dt.Second);
                path = @"C:\Users\pdvs1\OneDrive - Stellenbosch University\Master's Thesis\Data\" + fileName;
                using (var w = new System.IO.StreamWriter(path, true))
                {
                    w.WriteLine(dataFileHeaders + "," + generateBoilerColumnHeaders());
                    w.WriteLine(dataUnits);
                    w.Flush();
                }
            }
            if (serialPort.IsOpen) 
            { 
                serialPort.WriteLine(startCMD); 
            }
            else
            {
                MessageBox.Show("The serial port is not open. First connect before sending start command");
            }
        }

        private void waterScheduleTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void powerScheduleTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void configSysButton_Click(object sender, EventArgs e)
        {
            // Send the configuration command to the MCU
            try
            {
                // Send the configuration command to the MCU
                serialPort.WriteLine(configCMDTextBox.Text);
            }
            catch
            {
                MessageBox.Show("The configuration string is empty. First generate string before sending to microcontroller.");
            }
            configString.Clear();   // Clear the current config string
        }

        private void samplingTimeTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void resetMCUButton_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen) { serialPort.WriteLine(resetMcuCMD); }
            else
            {
                MessageBox.Show("The serial port is not open. First connect before sending start command");
            }
            serialReceiveTextBox.Clear();
        }

        private void showConfigTextButton_Click(object sender, EventArgs e)
        {
            int inletEnergyValue;
            if (InletEnergyInputSelectComboBox.SelectedItem.Equals("None")) { inletEnergyValue = 0; }
            else if (InletEnergyInputSelectComboBox.SelectedItem.Equals("Cooling")) { inletEnergyValue = 1; }
            else if (InletEnergyInputSelectComboBox.SelectedItem.Equals("Heating")) { inletEnergyValue = 2; }
            else { inletEnergyValue = -1; }
            configCMDTextBox.Clear();
            configString.Clear();
            if (!inletWaterTempRegCheckBox.Checked) {inletEnergyValue = 0; }
            configString.Append(configCMD)
                        .Append(':')
                        .Append(samplingTimeTextBox.Text)
                        .Append(':')
                        .Append((chamberTempRegCheckBox.Checked) ? chamberSetTempTextBox.Text : "0")
                        .Append(',')
                        .Append((geyserWaterTempRegCheckBox.Checked) ? geyserSetTempTextBox.Text : "0")
                        .Append(',')
                        .Append((inletWaterTempRegCheckBox.Checked) ? inletWaterSetTempTextBox.Text : "0")
                        .Append(',')
                        .Append((flowRateRegCheckBox.Checked) ? flowRateSetTextBox.Text : "0")
                        .Append(':')
                        .Append(inletEnergyValue.ToString());
            configCMDTextBox.Text = configString.ToString();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void waterManualcheckBox_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void waterScheduledcheckBox_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void recordDataToFileCheckBox_CheckedChanged(object sender, EventArgs e)
        {
   
        }

        private void inletEnergyInputComboBox(object sender, EventArgs e)
        {

        }

        private void flowRateSetTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void label27_Click(object sender, EventArgs e)
        {

        }

        private void OpenBallValveButton_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                serialPort.WriteLine(openValveCommand + ":" + flowRateRegCheckBox.Checked.ToString());
                configCMDTextBox.Text = openValveCommand + ":" + flowRateRegCheckBox.Checked.ToString();
            }
            else
            {
                MessageBox.Show("The serial port is not open. No connection to controller. Connect to serial port before sending commands.");
            }
        }

        private void closeBallValveButton_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                serialPort.WriteLine(closeValveCommand + ":" + flowRateRegCheckBox.Checked.ToString());
                configCMDTextBox.Text = closeValveCommand + ":" + flowRateRegCheckBox.Checked.ToString();
            }
            else
            {
                MessageBox.Show("The serial port is not open. No connection to controller. Connect to serial port before sending commands.");
            }
        }

        private void servoValvePosSlider_Scroll(object sender, ScrollEventArgs e)
        {
            if (serialPort.IsOpen)
            {
                serialPort.WriteLine("SVP:" + servoValvePosSlider.Value.ToString());
            }
            else
            {
                MessageBox.Show("The serial port is not open. No connection to controller. Connect to serial port before sending commands.");
            }
        }

        private void servoValvePosSlider_MouseDown(object sender, MouseEventArgs e)
        {

        }

        private void servoValvePosSlider_MouseUp(object sender, MouseEventArgs e)
        {

        }

        private void configCMDTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void label12_Click(object sender, EventArgs e)
        {

        }

        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            if (serialPort.IsOpen)
            {
                serialPort.WriteLine("OVP:" + servoValvePosSlider.Value.ToString());
            }
            else
            {
                MessageBox.Show("The serial port is not open. No connection to controller. Connect to serial port before sending commands.");
            }
        }
    }
}
