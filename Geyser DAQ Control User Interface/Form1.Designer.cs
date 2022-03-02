
namespace Geyser_DAQ_Control_User_Interface
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.label1 = new System.Windows.Forms.Label();
            this.chamberTempRegCheckBox = new System.Windows.Forms.CheckBox();
            this.geyserWaterTempRegCheckBox = new System.Windows.Forms.CheckBox();
            this.inletWaterTempRegCheckBox = new System.Windows.Forms.CheckBox();
            this.configSysButton = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.label2 = new System.Windows.Forms.Label();
            this.samplingTimeTextBox = new System.Windows.Forms.TextBox();
            this.chamberSetTempTextBox = new System.Windows.Forms.TextBox();
            this.geyserSetTempTextBox = new System.Windows.Forms.TextBox();
            this.inletWaterSetTempTextBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.serialReceiveTextBox = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.portComboBox = new System.Windows.Forms.ComboBox();
            this.baudRateComboBox = new System.Windows.Forms.ComboBox();
            this.connectPortButton = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.disconnectPortButton = new System.Windows.Forms.Button();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.connectStatusTextBox = new System.Windows.Forms.TextBox();
            this.stopButton = new System.Windows.Forms.Button();
            this.startButton = new System.Windows.Forms.Button();
            this.configCMDTextBox = new System.Windows.Forms.TextBox();
            this.powerScheduleTextBox = new System.Windows.Forms.TextBox();
            this.waterScheduleTextBox = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.resetMCUButton = new System.Windows.Forms.Button();
            this.showConfigTextButton = new System.Windows.Forms.Button();
            this.waterScheduleInfoTextBox = new System.Windows.Forms.TextBox();
            this.powerScheduleInfoTextBox = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.waterManualcheckBox = new System.Windows.Forms.CheckBox();
            this.waterScheduledcheckBox = new System.Windows.Forms.CheckBox();
            this.powerAlwaysOncheckBox = new System.Windows.Forms.CheckBox();
            this.powerScheduledcheckBox = new System.Windows.Forms.CheckBox();
            this.controlTypeComboBox = new System.Windows.Forms.ComboBox();
            this.label9 = new System.Windows.Forms.Label();
            this.recordDataToFileCheckBox = new System.Windows.Forms.CheckBox();
            this.InletEnergyInputSelectComboBox = new System.Windows.Forms.ComboBox();
            this.geyserWaterTempTextBox = new System.Windows.Forms.TextBox();
            this.ChamberTempTextBox = new System.Windows.Forms.TextBox();
            this.outletWaterTempTextBox = new System.Windows.Forms.TextBox();
            this.ExperimentDurTextBox = new System.Windows.Forms.TextBox();
            this.inletWaterTempTextBox = new System.Windows.Forms.TextBox();
            this.waterFlowRateTextBox = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.labTemperatureTextBox = new System.Windows.Forms.TextBox();
            this.geyserElementStateTextBox = new System.Windows.Forms.TextBox();
            this.energyUsedTextBox = new System.Windows.Forms.TextBox();
            this.label21 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.flowRateSetTextBox = new System.Windows.Forms.TextBox();
            this.label25 = new System.Windows.Forms.Label();
            this.flowRateRegCheckBox = new System.Windows.Forms.CheckBox();
            this.label26 = new System.Windows.Forms.Label();
            this.label27 = new System.Windows.Forms.Label();
            this.OpenBallValveButton = new System.Windows.Forms.Button();
            this.closeBallValveButton = new System.Windows.Forms.Button();
            this.servoValvePosSlider = new System.Windows.Forms.HScrollBar();
            this.label28 = new System.Windows.Forms.Label();
            this.label29 = new System.Windows.Forms.Label();
            this.label30 = new System.Windows.Forms.Label();
            this.label31 = new System.Windows.Forms.Label();
            this.label32 = new System.Windows.Forms.Label();
            this.label33 = new System.Windows.Forms.Label();
            this.ActualElementStateTextBox = new System.Windows.Forms.TextBox();
            this.label34 = new System.Windows.Forms.Label();
            this.label35 = new System.Windows.Forms.Label();
            this.label36 = new System.Windows.Forms.Label();
            this.label37 = new System.Windows.Forms.Label();
            this.label38 = new System.Windows.Forms.Label();
            this.hScrollBar1 = new System.Windows.Forms.HScrollBar();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Georgia Pro Cond", 28F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(448, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(526, 43);
            this.label1.TabIndex = 0;
            this.label1.Text = "EWH Test Station Control UI";
            // 
            // chamberTempRegCheckBox
            // 
            this.chamberTempRegCheckBox.AutoSize = true;
            this.chamberTempRegCheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.chamberTempRegCheckBox.Location = new System.Drawing.Point(328, 140);
            this.chamberTempRegCheckBox.Name = "chamberTempRegCheckBox";
            this.chamberTempRegCheckBox.Size = new System.Drawing.Size(189, 20);
            this.chamberTempRegCheckBox.TabIndex = 1;
            this.chamberTempRegCheckBox.Text = "Chamber Temp Regulation";
            this.chamberTempRegCheckBox.UseVisualStyleBackColor = true;
            // 
            // geyserWaterTempRegCheckBox
            // 
            this.geyserWaterTempRegCheckBox.AutoSize = true;
            this.geyserWaterTempRegCheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.geyserWaterTempRegCheckBox.Location = new System.Drawing.Point(328, 166);
            this.geyserWaterTempRegCheckBox.Name = "geyserWaterTempRegCheckBox";
            this.geyserWaterTempRegCheckBox.Size = new System.Drawing.Size(211, 20);
            this.geyserWaterTempRegCheckBox.TabIndex = 2;
            this.geyserWaterTempRegCheckBox.Text = "Geyser Water Temp regulation";
            this.geyserWaterTempRegCheckBox.UseVisualStyleBackColor = true;
            // 
            // inletWaterTempRegCheckBox
            // 
            this.inletWaterTempRegCheckBox.AutoSize = true;
            this.inletWaterTempRegCheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.inletWaterTempRegCheckBox.Location = new System.Drawing.Point(328, 192);
            this.inletWaterTempRegCheckBox.Name = "inletWaterTempRegCheckBox";
            this.inletWaterTempRegCheckBox.Size = new System.Drawing.Size(197, 20);
            this.inletWaterTempRegCheckBox.TabIndex = 3;
            this.inletWaterTempRegCheckBox.Text = "Inlet Water Temp Regulation";
            this.inletWaterTempRegCheckBox.UseVisualStyleBackColor = true;
            // 
            // configSysButton
            // 
            this.configSysButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.configSysButton.Location = new System.Drawing.Point(569, 570);
            this.configSysButton.Name = "configSysButton";
            this.configSysButton.Size = new System.Drawing.Size(169, 32);
            this.configSysButton.TabIndex = 5;
            this.configSysButton.Text = "Configure System ";
            this.configSysButton.UseVisualStyleBackColor = true;
            this.configSysButton.Click += new System.EventHandler(this.configSysButton_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 115200;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Georgia Pro Cond", 16F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(114, 70);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(336, 27);
            this.label2.TabIndex = 7;
            this.label2.Text = "System Experimental Paramters";
            // 
            // samplingTimeTextBox
            // 
            this.samplingTimeTextBox.Location = new System.Drawing.Point(198, 111);
            this.samplingTimeTextBox.Name = "samplingTimeTextBox";
            this.samplingTimeTextBox.Size = new System.Drawing.Size(100, 20);
            this.samplingTimeTextBox.TabIndex = 8;
            this.samplingTimeTextBox.Text = "5";
            this.samplingTimeTextBox.TextChanged += new System.EventHandler(this.samplingTimeTextBox_TextChanged);
            // 
            // chamberSetTempTextBox
            // 
            this.chamberSetTempTextBox.Location = new System.Drawing.Point(198, 137);
            this.chamberSetTempTextBox.Name = "chamberSetTempTextBox";
            this.chamberSetTempTextBox.Size = new System.Drawing.Size(100, 20);
            this.chamberSetTempTextBox.TabIndex = 9;
            this.chamberSetTempTextBox.Text = "30";
            // 
            // geyserSetTempTextBox
            // 
            this.geyserSetTempTextBox.Location = new System.Drawing.Point(198, 163);
            this.geyserSetTempTextBox.Name = "geyserSetTempTextBox";
            this.geyserSetTempTextBox.Size = new System.Drawing.Size(100, 20);
            this.geyserSetTempTextBox.TabIndex = 10;
            this.geyserSetTempTextBox.Text = "60";
            // 
            // inletWaterSetTempTextBox
            // 
            this.inletWaterSetTempTextBox.Location = new System.Drawing.Point(198, 189);
            this.inletWaterSetTempTextBox.Name = "inletWaterSetTempTextBox";
            this.inletWaterSetTempTextBox.Size = new System.Drawing.Size(100, 20);
            this.inletWaterSetTempTextBox.TabIndex = 11;
            this.inletWaterSetTempTextBox.Text = "25";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(11, 111);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(181, 16);
            this.label3.TabIndex = 12;
            this.label3.Text = "Data Sampling Time [Ts]";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(20, 140);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(171, 16);
            this.label4.TabIndex = 13;
            this.label4.Text = "Chamber Set Temp [*C]";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(33, 166);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(159, 16);
            this.label5.TabIndex = 14;
            this.label5.Text = "Geyser Set Temp [*C]";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(12, 192);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(183, 16);
            this.label6.TabIndex = 15;
            this.label6.Text = "Inlet Water Set Temp [*C]";
            // 
            // serialReceiveTextBox
            // 
            this.serialReceiveTextBox.Location = new System.Drawing.Point(569, 277);
            this.serialReceiveTextBox.Multiline = true;
            this.serialReceiveTextBox.Name = "serialReceiveTextBox";
            this.serialReceiveTextBox.Size = new System.Drawing.Size(836, 260);
            this.serialReceiveTextBox.TabIndex = 16;
            this.serialReceiveTextBox.TextChanged += new System.EventHandler(this.textBox5_TextChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Georgia Pro Cond", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(565, 251);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(157, 23);
            this.label7.TabIndex = 17;
            this.label7.Text = "Serial Port Data ";
            this.label7.Click += new System.EventHandler(this.label7_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Georgia Pro Cond", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(1025, 79);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(230, 23);
            this.label8.TabIndex = 20;
            this.label8.Text = "Serial Setup and Connect";
            this.label8.Click += new System.EventHandler(this.label8_Click);
            // 
            // portComboBox
            // 
            this.portComboBox.FormattingEnabled = true;
            this.portComboBox.Location = new System.Drawing.Point(1108, 110);
            this.portComboBox.Name = "portComboBox";
            this.portComboBox.Size = new System.Drawing.Size(147, 21);
            this.portComboBox.TabIndex = 21;
            this.portComboBox.Text = "COM12";
            this.portComboBox.SelectedIndexChanged += new System.EventHandler(this.portComboBox_SelectedIndexChanged);
            // 
            // baudRateComboBox
            // 
            this.baudRateComboBox.FormattingEnabled = true;
            this.baudRateComboBox.Location = new System.Drawing.Point(1108, 138);
            this.baudRateComboBox.Name = "baudRateComboBox";
            this.baudRateComboBox.Size = new System.Drawing.Size(147, 21);
            this.baudRateComboBox.TabIndex = 22;
            this.baudRateComboBox.Text = "115200";
            this.baudRateComboBox.SelectedIndexChanged += new System.EventHandler(this.baudRateComboBox_SelectedIndexChanged);
            // 
            // connectPortButton
            // 
            this.connectPortButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.connectPortButton.Location = new System.Drawing.Point(1030, 165);
            this.connectPortButton.Name = "connectPortButton";
            this.connectPortButton.Size = new System.Drawing.Size(147, 34);
            this.connectPortButton.TabIndex = 23;
            this.connectPortButton.Text = "Connect to port";
            this.connectPortButton.UseVisualStyleBackColor = true;
            this.connectPortButton.Click += new System.EventHandler(this.connectPortButton_Click);
            // 
            // button5
            // 
            this.button5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button5.Location = new System.Drawing.Point(1266, 107);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(135, 23);
            this.button5.TabIndex = 25;
            this.button5.Text = "Refresh Available Ports";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.refreshPortsButton_Click);
            // 
            // disconnectPortButton
            // 
            this.disconnectPortButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.disconnectPortButton.Location = new System.Drawing.Point(1183, 166);
            this.disconnectPortButton.Name = "disconnectPortButton";
            this.disconnectPortButton.Size = new System.Drawing.Size(164, 33);
            this.disconnectPortButton.TabIndex = 26;
            this.disconnectPortButton.Text = "Disconnect from Port";
            this.disconnectPortButton.UseVisualStyleBackColor = true;
            this.disconnectPortButton.Click += new System.EventHandler(this.disconnectPortButton_Click);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.Location = new System.Drawing.Point(1027, 112);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(81, 16);
            this.label10.TabIndex = 27;
            this.label10.Text = "Port Name";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label11.Location = new System.Drawing.Point(1027, 139);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(75, 16);
            this.label11.TabIndex = 28;
            this.label11.Text = "Baud rate";
            // 
            // connectStatusTextBox
            // 
            this.connectStatusTextBox.Location = new System.Drawing.Point(1266, 139);
            this.connectStatusTextBox.Name = "connectStatusTextBox";
            this.connectStatusTextBox.Size = new System.Drawing.Size(135, 20);
            this.connectStatusTextBox.TabIndex = 29;
            this.connectStatusTextBox.TextChanged += new System.EventHandler(this.connectStatusTextBox_TextChanged);
            // 
            // stopButton
            // 
            this.stopButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.stopButton.Location = new System.Drawing.Point(743, 570);
            this.stopButton.Name = "stopButton";
            this.stopButton.Size = new System.Drawing.Size(169, 32);
            this.stopButton.TabIndex = 30;
            this.stopButton.Text = "Stop System ";
            this.stopButton.UseVisualStyleBackColor = true;
            this.stopButton.Click += new System.EventHandler(this.stopButton_Click);
            // 
            // startButton
            // 
            this.startButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.startButton.ForeColor = System.Drawing.Color.ForestGreen;
            this.startButton.Location = new System.Drawing.Point(918, 570);
            this.startButton.Name = "startButton";
            this.startButton.Size = new System.Drawing.Size(169, 32);
            this.startButton.TabIndex = 31;
            this.startButton.Text = "Start System ";
            this.startButton.UseVisualStyleBackColor = true;
            this.startButton.Click += new System.EventHandler(this.startButton_Click);
            // 
            // configCMDTextBox
            // 
            this.configCMDTextBox.Location = new System.Drawing.Point(17, 454);
            this.configCMDTextBox.Name = "configCMDTextBox";
            this.configCMDTextBox.Size = new System.Drawing.Size(490, 20);
            this.configCMDTextBox.TabIndex = 32;
            this.configCMDTextBox.TextChanged += new System.EventHandler(this.configCMDTextBox_TextChanged);
            // 
            // powerScheduleTextBox
            // 
            this.powerScheduleTextBox.Location = new System.Drawing.Point(11, 386);
            this.powerScheduleTextBox.Name = "powerScheduleTextBox";
            this.powerScheduleTextBox.Size = new System.Drawing.Size(138, 20);
            this.powerScheduleTextBox.TabIndex = 34;
            this.powerScheduleTextBox.Text = "How many events?";
            this.powerScheduleTextBox.TextChanged += new System.EventHandler(this.powerScheduleTextBox_TextChanged);
            // 
            // waterScheduleTextBox
            // 
            this.waterScheduleTextBox.AcceptsReturn = true;
            this.waterScheduleTextBox.Location = new System.Drawing.Point(11, 340);
            this.waterScheduleTextBox.Name = "waterScheduleTextBox";
            this.waterScheduleTextBox.Size = new System.Drawing.Size(138, 20);
            this.waterScheduleTextBox.TabIndex = 35;
            this.waterScheduleTextBox.Text = "How many events?";
            this.waterScheduleTextBox.TextChanged += new System.EventHandler(this.waterScheduleTextBox_TextChanged);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Georgia Pro Cond", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label13.Location = new System.Drawing.Point(11, 321);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(138, 18);
            this.label13.TabIndex = 36;
            this.label13.Text = "Water Scheduling";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Georgia Pro Cond", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label14.Location = new System.Drawing.Point(11, 368);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(140, 18);
            this.label14.TabIndex = 37;
            this.label14.Text = "Power Scheduling";
            // 
            // resetMCUButton
            // 
            this.resetMCUButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.resetMCUButton.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
            this.resetMCUButton.Location = new System.Drawing.Point(1093, 570);
            this.resetMCUButton.Name = "resetMCUButton";
            this.resetMCUButton.Size = new System.Drawing.Size(198, 32);
            this.resetMCUButton.TabIndex = 41;
            this.resetMCUButton.Text = "Reset Microcontroller";
            this.resetMCUButton.UseVisualStyleBackColor = true;
            this.resetMCUButton.Click += new System.EventHandler(this.resetMCUButton_Click);
            // 
            // showConfigTextButton
            // 
            this.showConfigTextButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.showConfigTextButton.Location = new System.Drawing.Point(14, 423);
            this.showConfigTextButton.Margin = new System.Windows.Forms.Padding(2);
            this.showConfigTextButton.Name = "showConfigTextButton";
            this.showConfigTextButton.Size = new System.Drawing.Size(262, 26);
            this.showConfigTextButton.TabIndex = 42;
            this.showConfigTextButton.Text = "Generate Config Command";
            this.showConfigTextButton.UseVisualStyleBackColor = true;
            this.showConfigTextButton.Click += new System.EventHandler(this.showConfigTextButton_Click);
            // 
            // waterScheduleInfoTextBox
            // 
            this.waterScheduleInfoTextBox.AcceptsReturn = true;
            this.waterScheduleInfoTextBox.Location = new System.Drawing.Point(199, 340);
            this.waterScheduleInfoTextBox.Name = "waterScheduleInfoTextBox";
            this.waterScheduleInfoTextBox.Size = new System.Drawing.Size(307, 20);
            this.waterScheduleInfoTextBox.TabIndex = 43;
            this.waterScheduleInfoTextBox.Text = "<- Provide schedule information ->";
            // 
            // powerScheduleInfoTextBox
            // 
            this.powerScheduleInfoTextBox.Location = new System.Drawing.Point(199, 386);
            this.powerScheduleInfoTextBox.Name = "powerScheduleInfoTextBox";
            this.powerScheduleInfoTextBox.Size = new System.Drawing.Size(307, 20);
            this.powerScheduleInfoTextBox.TabIndex = 44;
            this.powerScheduleInfoTextBox.Text = "<- Provide schedule information ->";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Georgia Pro Cond", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label12.Location = new System.Drawing.Point(312, 477);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(195, 16);
            this.label12.TabIndex = 33;
            this.label12.Text = "Configuration Command String";
            this.label12.Click += new System.EventHandler(this.label12_Click);
            // 
            // waterManualcheckBox
            // 
            this.waterManualcheckBox.AutoSize = true;
            this.waterManualcheckBox.Checked = true;
            this.waterManualcheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.waterManualcheckBox.Location = new System.Drawing.Point(199, 318);
            this.waterManualcheckBox.Margin = new System.Windows.Forms.Padding(2);
            this.waterManualcheckBox.Name = "waterManualcheckBox";
            this.waterManualcheckBox.Size = new System.Drawing.Size(97, 17);
            this.waterManualcheckBox.TabIndex = 45;
            this.waterManualcheckBox.Text = "Manual Events";
            this.waterManualcheckBox.UseVisualStyleBackColor = true;
            this.waterManualcheckBox.CheckedChanged += new System.EventHandler(this.waterManualcheckBox_CheckedChanged);
            // 
            // waterScheduledcheckBox
            // 
            this.waterScheduledcheckBox.AutoSize = true;
            this.waterScheduledcheckBox.Location = new System.Drawing.Point(337, 318);
            this.waterScheduledcheckBox.Margin = new System.Windows.Forms.Padding(2);
            this.waterScheduledcheckBox.Name = "waterScheduledcheckBox";
            this.waterScheduledcheckBox.Size = new System.Drawing.Size(113, 17);
            this.waterScheduledcheckBox.TabIndex = 46;
            this.waterScheduledcheckBox.Text = "Scheduled Events";
            this.waterScheduledcheckBox.UseVisualStyleBackColor = true;
            this.waterScheduledcheckBox.CheckedChanged += new System.EventHandler(this.waterScheduledcheckBox_CheckedChanged);
            // 
            // powerAlwaysOncheckBox
            // 
            this.powerAlwaysOncheckBox.AutoSize = true;
            this.powerAlwaysOncheckBox.Checked = true;
            this.powerAlwaysOncheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.powerAlwaysOncheckBox.Location = new System.Drawing.Point(199, 369);
            this.powerAlwaysOncheckBox.Margin = new System.Windows.Forms.Padding(2);
            this.powerAlwaysOncheckBox.Name = "powerAlwaysOncheckBox";
            this.powerAlwaysOncheckBox.Size = new System.Drawing.Size(76, 17);
            this.powerAlwaysOncheckBox.TabIndex = 47;
            this.powerAlwaysOncheckBox.Text = "Always On";
            this.powerAlwaysOncheckBox.UseVisualStyleBackColor = true;
            // 
            // powerScheduledcheckBox
            // 
            this.powerScheduledcheckBox.AutoSize = true;
            this.powerScheduledcheckBox.Location = new System.Drawing.Point(337, 369);
            this.powerScheduledcheckBox.Margin = new System.Windows.Forms.Padding(2);
            this.powerScheduledcheckBox.Name = "powerScheduledcheckBox";
            this.powerScheduledcheckBox.Size = new System.Drawing.Size(162, 17);
            this.powerScheduledcheckBox.TabIndex = 48;
            this.powerScheduledcheckBox.Text = "Scheduled Power Availability";
            this.powerScheduledcheckBox.UseVisualStyleBackColor = true;
            // 
            // controlTypeComboBox
            // 
            this.controlTypeComboBox.FormattingEnabled = true;
            this.controlTypeComboBox.Items.AddRange(new object[] {
            "Automatic ",
            "Manual"});
            this.controlTypeComboBox.Location = new System.Drawing.Point(198, 286);
            this.controlTypeComboBox.Margin = new System.Windows.Forms.Padding(2);
            this.controlTypeComboBox.Name = "controlTypeComboBox";
            this.controlTypeComboBox.Size = new System.Drawing.Size(92, 21);
            this.controlTypeComboBox.TabIndex = 49;
            this.controlTypeComboBox.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(75, 288);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(97, 16);
            this.label9.TabIndex = 50;
            this.label9.Text = "Control Type";
            // 
            // recordDataToFileCheckBox
            // 
            this.recordDataToFileCheckBox.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            this.recordDataToFileCheckBox.AutoSize = true;
            this.recordDataToFileCheckBox.Checked = true;
            this.recordDataToFileCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.recordDataToFileCheckBox.Font = new System.Drawing.Font("Times New Roman", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.recordDataToFileCheckBox.Location = new System.Drawing.Point(571, 543);
            this.recordDataToFileCheckBox.Name = "recordDataToFileCheckBox";
            this.recordDataToFileCheckBox.Size = new System.Drawing.Size(403, 21);
            this.recordDataToFileCheckBox.TabIndex = 51;
            this.recordDataToFileCheckBox.Text = "Save data to excel file (Check before clicking \"start\" button)";
            this.recordDataToFileCheckBox.UseVisualStyleBackColor = true;
            this.recordDataToFileCheckBox.CheckedChanged += new System.EventHandler(this.recordDataToFileCheckBox_CheckedChanged);
            // 
            // InletEnergyInputSelectComboBox
            // 
            this.InletEnergyInputSelectComboBox.FormattingEnabled = true;
            this.InletEnergyInputSelectComboBox.Items.AddRange(new object[] {
            "None",
            "Cooling",
            "Heating"});
            this.InletEnergyInputSelectComboBox.Location = new System.Drawing.Point(350, 211);
            this.InletEnergyInputSelectComboBox.Name = "InletEnergyInputSelectComboBox";
            this.InletEnergyInputSelectComboBox.Size = new System.Drawing.Size(136, 21);
            this.InletEnergyInputSelectComboBox.TabIndex = 52;
            this.InletEnergyInputSelectComboBox.SelectedIndexChanged += new System.EventHandler(this.inletEnergyInputComboBox);
            // 
            // geyserWaterTempTextBox
            // 
            this.geyserWaterTempTextBox.Location = new System.Drawing.Point(569, 96);
            this.geyserWaterTempTextBox.Name = "geyserWaterTempTextBox";
            this.geyserWaterTempTextBox.Size = new System.Drawing.Size(123, 20);
            this.geyserWaterTempTextBox.TabIndex = 53;
            // 
            // ChamberTempTextBox
            // 
            this.ChamberTempTextBox.Location = new System.Drawing.Point(569, 153);
            this.ChamberTempTextBox.Name = "ChamberTempTextBox";
            this.ChamberTempTextBox.Size = new System.Drawing.Size(123, 20);
            this.ChamberTempTextBox.TabIndex = 54;
            // 
            // outletWaterTempTextBox
            // 
            this.outletWaterTempTextBox.Location = new System.Drawing.Point(722, 96);
            this.outletWaterTempTextBox.Name = "outletWaterTempTextBox";
            this.outletWaterTempTextBox.Size = new System.Drawing.Size(116, 20);
            this.outletWaterTempTextBox.TabIndex = 55;
            // 
            // ExperimentDurTextBox
            // 
            this.ExperimentDurTextBox.Location = new System.Drawing.Point(722, 153);
            this.ExperimentDurTextBox.Name = "ExperimentDurTextBox";
            this.ExperimentDurTextBox.Size = new System.Drawing.Size(116, 20);
            this.ExperimentDurTextBox.TabIndex = 56;
            // 
            // inletWaterTempTextBox
            // 
            this.inletWaterTempTextBox.Location = new System.Drawing.Point(866, 96);
            this.inletWaterTempTextBox.Name = "inletWaterTempTextBox";
            this.inletWaterTempTextBox.Size = new System.Drawing.Size(119, 20);
            this.inletWaterTempTextBox.TabIndex = 57;
            // 
            // waterFlowRateTextBox
            // 
            this.waterFlowRateTextBox.Location = new System.Drawing.Point(866, 153);
            this.waterFlowRateTextBox.Name = "waterFlowRateTextBox";
            this.waterFlowRateTextBox.Size = new System.Drawing.Size(119, 20);
            this.waterFlowRateTextBox.TabIndex = 58;
            // 
            // label15
            // 
            this.label15.Location = new System.Drawing.Point(0, 0);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(100, 23);
            this.label15.TabIndex = 71;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label16.Location = new System.Drawing.Point(566, 137);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(151, 15);
            this.label16.TabIndex = 60;
            this.label16.Text = "Chamber Temperature";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label17.Location = new System.Drawing.Point(719, 79);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(133, 15);
            this.label17.TabIndex = 61;
            this.label17.Text = "Geyser Outlet Temp";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label18.Location = new System.Drawing.Point(863, 79);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(123, 15);
            this.label18.TabIndex = 62;
            this.label18.Text = "Geyser Inlet Temp";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label19.Location = new System.Drawing.Point(719, 137);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(139, 15);
            this.label19.TabIndex = 63;
            this.label19.Text = "Experiment Duration";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label20.Location = new System.Drawing.Point(864, 137);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(151, 15);
            this.label20.TabIndex = 64;
            this.label20.Text = "Water Flow Rate [L/Ts]";
            // 
            // labTemperatureTextBox
            // 
            this.labTemperatureTextBox.Location = new System.Drawing.Point(568, 211);
            this.labTemperatureTextBox.Name = "labTemperatureTextBox";
            this.labTemperatureTextBox.Size = new System.Drawing.Size(119, 20);
            this.labTemperatureTextBox.TabIndex = 67;
            // 
            // geyserElementStateTextBox
            // 
            this.geyserElementStateTextBox.Location = new System.Drawing.Point(722, 211);
            this.geyserElementStateTextBox.Name = "geyserElementStateTextBox";
            this.geyserElementStateTextBox.Size = new System.Drawing.Size(89, 20);
            this.geyserElementStateTextBox.TabIndex = 66;
            // 
            // energyUsedTextBox
            // 
            this.energyUsedTextBox.Location = new System.Drawing.Point(867, 211);
            this.energyUsedTextBox.Name = "energyUsedTextBox";
            this.energyUsedTextBox.Size = new System.Drawing.Size(123, 20);
            this.energyUsedTextBox.TabIndex = 65;
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label21.Location = new System.Drawing.Point(864, 194);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(139, 15);
            this.label21.TabIndex = 68;
            this.label21.Text = "Energy Used [Wh/Ts]";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label22.Location = new System.Drawing.Point(721, 195);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(108, 15);
            this.label22.TabIndex = 69;
            this.label22.Text = "Geyser Element";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label23.Location = new System.Drawing.Point(566, 195);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(117, 15);
            this.label23.TabIndex = 70;
            this.label23.Text = "Lab Temperature";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label24.Location = new System.Drawing.Point(566, 79);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(132, 15);
            this.label24.TabIndex = 72;
            this.label24.Text = "Geyser Water Temp";
            // 
            // flowRateSetTextBox
            // 
            this.flowRateSetTextBox.Location = new System.Drawing.Point(197, 238);
            this.flowRateSetTextBox.Name = "flowRateSetTextBox";
            this.flowRateSetTextBox.Size = new System.Drawing.Size(100, 20);
            this.flowRateSetTextBox.TabIndex = 73;
            this.flowRateSetTextBox.Text = "8";
            this.flowRateSetTextBox.TextChanged += new System.EventHandler(this.flowRateSetTextBox_TextChanged);
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label25.Location = new System.Drawing.Point(36, 240);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(155, 16);
            this.label25.TabIndex = 74;
            this.label25.Text = "Set Flow Rate [L/min]";
            // 
            // flowRateRegCheckBox
            // 
            this.flowRateRegCheckBox.AutoSize = true;
            this.flowRateRegCheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.flowRateRegCheckBox.Location = new System.Drawing.Point(327, 239);
            this.flowRateRegCheckBox.Name = "flowRateRegCheckBox";
            this.flowRateRegCheckBox.Size = new System.Drawing.Size(155, 20);
            this.flowRateRegCheckBox.TabIndex = 75;
            this.flowRateRegCheckBox.Text = "Flow Rate Regulation";
            this.flowRateRegCheckBox.UseVisualStyleBackColor = true;
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Font = new System.Drawing.Font("Georgia Pro Cond", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label26.Location = new System.Drawing.Point(99, 261);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(173, 14);
            this.label26.TabIndex = 76;
            this.label26.Text = "Max: 12L/min and Min: 4L/min";
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Font = new System.Drawing.Font("Georgia Pro Cond", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label27.Location = new System.Drawing.Point(339, 549);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(140, 18);
            this.label27.TabIndex = 77;
            this.label27.Text = "Actuate Ball Valve";
            this.label27.Click += new System.EventHandler(this.label27_Click);
            // 
            // OpenBallValveButton
            // 
            this.OpenBallValveButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.OpenBallValveButton.ForeColor = System.Drawing.Color.Green;
            this.OpenBallValveButton.Location = new System.Drawing.Point(254, 570);
            this.OpenBallValveButton.Name = "OpenBallValveButton";
            this.OpenBallValveButton.Size = new System.Drawing.Size(147, 32);
            this.OpenBallValveButton.TabIndex = 78;
            this.OpenBallValveButton.Text = "Open Valve";
            this.OpenBallValveButton.UseVisualStyleBackColor = true;
            this.OpenBallValveButton.Click += new System.EventHandler(this.OpenBallValveButton_Click);
            // 
            // closeBallValveButton
            // 
            this.closeBallValveButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.closeBallValveButton.ForeColor = System.Drawing.Color.Red;
            this.closeBallValveButton.Location = new System.Drawing.Point(407, 570);
            this.closeBallValveButton.Name = "closeBallValveButton";
            this.closeBallValveButton.Size = new System.Drawing.Size(147, 32);
            this.closeBallValveButton.TabIndex = 79;
            this.closeBallValveButton.Text = "Close Valve";
            this.closeBallValveButton.UseVisualStyleBackColor = true;
            this.closeBallValveButton.Click += new System.EventHandler(this.closeBallValveButton_Click);
            // 
            // servoValvePosSlider
            // 
            this.servoValvePosSlider.Location = new System.Drawing.Point(59, 570);
            this.servoValvePosSlider.Maximum = 90;
            this.servoValvePosSlider.Name = "servoValvePosSlider";
            this.servoValvePosSlider.Size = new System.Drawing.Size(156, 31);
            this.servoValvePosSlider.TabIndex = 81;
            this.servoValvePosSlider.Value = 45;
            this.servoValvePosSlider.Scroll += new System.Windows.Forms.ScrollEventHandler(this.servoValvePosSlider_Scroll);
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Font = new System.Drawing.Font("Georgia Pro Cond", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label28.Location = new System.Drawing.Point(924, 234);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(61, 14);
            this.label28.TabIndex = 82;
            this.label28.Text = "5s average";
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Font = new System.Drawing.Font("Georgia Pro Cond", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label29.Location = new System.Drawing.Point(924, 176);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(61, 14);
            this.label29.TabIndex = 83;
            this.label29.Text = "5s average";
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Font = new System.Drawing.Font("Georgia Pro Cond", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label30.Location = new System.Drawing.Point(72, 547);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(143, 18);
            this.label30.TabIndex = 84;
            this.label30.Text = "Servo Valve Adjust";
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Font = new System.Drawing.Font("Georgia Pro Cond", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label31.Location = new System.Drawing.Point(218, 578);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(24, 16);
            this.label31.TabIndex = 85;
            this.label31.Text = "90";
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.Font = new System.Drawing.Font("Georgia Pro Cond", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label32.Location = new System.Drawing.Point(40, 578);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(16, 16);
            this.label32.TabIndex = 86;
            this.label32.Text = "0";
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.Font = new System.Drawing.Font("Georgia Pro Cond", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label33.ForeColor = System.Drawing.Color.Red;
            this.label33.Location = new System.Drawing.Point(276, 430);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(280, 14);
            this.label33.TabIndex = 87;
            this.label33.Text = "Press this before pressing \"Configure System\" button";
            // 
            // ActualElementStateTextBox
            // 
            this.ActualElementStateTextBox.Location = new System.Drawing.Point(722, 236);
            this.ActualElementStateTextBox.Name = "ActualElementStateTextBox";
            this.ActualElementStateTextBox.Size = new System.Drawing.Size(89, 20);
            this.ActualElementStateTextBox.TabIndex = 88;
            // 
            // label34
            // 
            this.label34.AutoSize = true;
            this.label34.Font = new System.Drawing.Font("Georgia Pro Cond", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label34.Location = new System.Drawing.Point(810, 214);
            this.label34.Name = "label34";
            this.label34.Size = new System.Drawing.Size(42, 14);
            this.label34.TabIndex = 89;
            this.label34.Text = "Virtual";
            // 
            // label35
            // 
            this.label35.AutoSize = true;
            this.label35.Font = new System.Drawing.Font("Georgia Pro Cond", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label35.Location = new System.Drawing.Point(810, 240);
            this.label35.Name = "label35";
            this.label35.Size = new System.Drawing.Size(38, 14);
            this.label35.TabIndex = 90;
            this.label35.Text = "Actual";
            // 
            // label36
            // 
            this.label36.AutoSize = true;
            this.label36.Font = new System.Drawing.Font("Georgia Pro Cond", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label36.Location = new System.Drawing.Point(8, 514);
            this.label36.Name = "label36";
            this.label36.Size = new System.Drawing.Size(48, 16);
            this.label36.TabIndex = 94;
            this.label36.Text = "Closed";
            // 
            // label37
            // 
            this.label37.AutoSize = true;
            this.label37.Font = new System.Drawing.Font("Georgia Pro Cond", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label37.Location = new System.Drawing.Point(218, 514);
            this.label37.Name = "label37";
            this.label37.Size = new System.Drawing.Size(41, 16);
            this.label37.TabIndex = 93;
            this.label37.Text = "Open";
            // 
            // label38
            // 
            this.label38.AutoSize = true;
            this.label38.Font = new System.Drawing.Font("Georgia Pro Cond", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label38.Location = new System.Drawing.Point(72, 483);
            this.label38.Name = "label38";
            this.label38.Size = new System.Drawing.Size(148, 18);
            this.label38.TabIndex = 92;
            this.label38.Text = "Outlet Valve Adjust";
            // 
            // hScrollBar1
            // 
            this.hScrollBar1.Location = new System.Drawing.Point(59, 506);
            this.hScrollBar1.Maximum = 5000;
            this.hScrollBar1.Name = "hScrollBar1";
            this.hScrollBar1.Size = new System.Drawing.Size(156, 31);
            this.hScrollBar1.TabIndex = 91;
            this.hScrollBar1.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar1_Scroll);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlLight;
            this.ClientSize = new System.Drawing.Size(1417, 612);
            this.Controls.Add(this.label36);
            this.Controls.Add(this.label37);
            this.Controls.Add(this.label38);
            this.Controls.Add(this.hScrollBar1);
            this.Controls.Add(this.label35);
            this.Controls.Add(this.label34);
            this.Controls.Add(this.ActualElementStateTextBox);
            this.Controls.Add(this.label33);
            this.Controls.Add(this.label32);
            this.Controls.Add(this.label31);
            this.Controls.Add(this.label30);
            this.Controls.Add(this.label29);
            this.Controls.Add(this.label28);
            this.Controls.Add(this.servoValvePosSlider);
            this.Controls.Add(this.closeBallValveButton);
            this.Controls.Add(this.OpenBallValveButton);
            this.Controls.Add(this.label27);
            this.Controls.Add(this.label26);
            this.Controls.Add(this.flowRateRegCheckBox);
            this.Controls.Add(this.label25);
            this.Controls.Add(this.flowRateSetTextBox);
            this.Controls.Add(this.label24);
            this.Controls.Add(this.label23);
            this.Controls.Add(this.label22);
            this.Controls.Add(this.label21);
            this.Controls.Add(this.labTemperatureTextBox);
            this.Controls.Add(this.geyserElementStateTextBox);
            this.Controls.Add(this.energyUsedTextBox);
            this.Controls.Add(this.label20);
            this.Controls.Add(this.label19);
            this.Controls.Add(this.label18);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.waterFlowRateTextBox);
            this.Controls.Add(this.inletWaterTempTextBox);
            this.Controls.Add(this.ExperimentDurTextBox);
            this.Controls.Add(this.outletWaterTempTextBox);
            this.Controls.Add(this.ChamberTempTextBox);
            this.Controls.Add(this.geyserWaterTempTextBox);
            this.Controls.Add(this.InletEnergyInputSelectComboBox);
            this.Controls.Add(this.recordDataToFileCheckBox);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.controlTypeComboBox);
            this.Controls.Add(this.powerScheduledcheckBox);
            this.Controls.Add(this.powerAlwaysOncheckBox);
            this.Controls.Add(this.waterScheduledcheckBox);
            this.Controls.Add(this.waterManualcheckBox);
            this.Controls.Add(this.powerScheduleInfoTextBox);
            this.Controls.Add(this.waterScheduleInfoTextBox);
            this.Controls.Add(this.showConfigTextButton);
            this.Controls.Add(this.resetMCUButton);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.waterScheduleTextBox);
            this.Controls.Add(this.powerScheduleTextBox);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.configCMDTextBox);
            this.Controls.Add(this.startButton);
            this.Controls.Add(this.stopButton);
            this.Controls.Add(this.connectStatusTextBox);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.disconnectPortButton);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.connectPortButton);
            this.Controls.Add(this.baudRateComboBox);
            this.Controls.Add(this.portComboBox);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.serialReceiveTextBox);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.inletWaterSetTempTextBox);
            this.Controls.Add(this.geyserSetTempTextBox);
            this.Controls.Add(this.chamberSetTempTextBox);
            this.Controls.Add(this.samplingTimeTextBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.configSysButton);
            this.Controls.Add(this.inletWaterTempRegCheckBox);
            this.Controls.Add(this.geyserWaterTempRegCheckBox);
            this.Controls.Add(this.chamberTempRegCheckBox);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox chamberTempRegCheckBox;
        private System.Windows.Forms.CheckBox geyserWaterTempRegCheckBox;
        private System.Windows.Forms.CheckBox inletWaterTempRegCheckBox;
        private System.Windows.Forms.Button configSysButton;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox samplingTimeTextBox;
        private System.Windows.Forms.TextBox chamberSetTempTextBox;
        private System.Windows.Forms.TextBox geyserSetTempTextBox;
        private System.Windows.Forms.TextBox inletWaterSetTempTextBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox serialReceiveTextBox;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.ComboBox portComboBox;
        private System.Windows.Forms.ComboBox baudRateComboBox;
        private System.Windows.Forms.Button connectPortButton;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button disconnectPortButton;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox connectStatusTextBox;
        private System.Windows.Forms.Button stopButton;
        private System.Windows.Forms.Button startButton;
        private System.Windows.Forms.TextBox configCMDTextBox;
        private System.Windows.Forms.TextBox powerScheduleTextBox;
        private System.Windows.Forms.TextBox waterScheduleTextBox;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Button resetMCUButton;
        private System.Windows.Forms.Button showConfigTextButton;
        private System.Windows.Forms.TextBox waterScheduleInfoTextBox;
        private System.Windows.Forms.TextBox powerScheduleInfoTextBox;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.CheckBox waterManualcheckBox;
        private System.Windows.Forms.CheckBox waterScheduledcheckBox;
        private System.Windows.Forms.CheckBox powerAlwaysOncheckBox;
        private System.Windows.Forms.CheckBox powerScheduledcheckBox;
        private System.Windows.Forms.ComboBox controlTypeComboBox;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.CheckBox recordDataToFileCheckBox;
        private System.Windows.Forms.ComboBox InletEnergyInputSelectComboBox;
        private System.Windows.Forms.TextBox geyserWaterTempTextBox;
        private System.Windows.Forms.TextBox ChamberTempTextBox;
        private System.Windows.Forms.TextBox outletWaterTempTextBox;
        private System.Windows.Forms.TextBox ExperimentDurTextBox;
        private System.Windows.Forms.TextBox inletWaterTempTextBox;
        private System.Windows.Forms.TextBox waterFlowRateTextBox;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.TextBox labTemperatureTextBox;
        private System.Windows.Forms.TextBox geyserElementStateTextBox;
        private System.Windows.Forms.TextBox energyUsedTextBox;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.TextBox flowRateSetTextBox;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.CheckBox flowRateRegCheckBox;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.Button OpenBallValveButton;
        private System.Windows.Forms.Button closeBallValveButton;
        private System.Windows.Forms.HScrollBar servoValvePosSlider;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.Label label32;
        private System.Windows.Forms.Label label33;
        private System.Windows.Forms.TextBox ActualElementStateTextBox;
        private System.Windows.Forms.Label label34;
        private System.Windows.Forms.Label label35;
        private System.Windows.Forms.Label label36;
        private System.Windows.Forms.Label label37;
        private System.Windows.Forms.Label label38;
        private System.Windows.Forms.HScrollBar hScrollBar1;
    }
}

