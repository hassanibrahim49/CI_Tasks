using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Windows.Forms.DataVisualization.Charting;
using System.Text.RegularExpressions;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {

        private void clearChart(Chart chart)
        {

            chart.Series[0].Points.Clear();
            //chart.Series[0].Points.Add(new DataPoint(0, value));
            
        }

        public Form1()
        {
            InitializeComponent();
            refresh_com();
        }

        string comdata, comtime;
        double i;
        int count;
        int recTime;
        int curTime;
        int ttemp;

        private void button1_Click(object sender, EventArgs e)
        {
            connect();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            refresh_com();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            disconnect();
        }

        private void disconnect()
        {
            try
            {

                if (serialPort1.IsOpen)
                {
                    serialPort1.Close();
                    button1.Enabled = true;
                    button3.Enabled = false;
                    ttemp = recTime;
                }
            }
            catch (Exception e) { }
        }

        private void connect()
        {
            curTime = ttemp;
            count = 0;
            serialPort1.PortName = comboBox1.SelectedItem.ToString();
            serialPort1.BaudRate = 9600;
            serialPort1.DataBits = 8;
            serialPort1.StopBits = StopBits.One;
            serialPort1.Parity = Parity.None;
            serialPort1.Handshake = Handshake.None;
            serialPort1.Encoding = Encoding.ASCII;
            serialPort1.NewLine = ";";
            i = 0.0;
            try {

                if (!serialPort1.IsOpen)
                {
                    serialPort1.Open();
                    button1.Enabled = false;
                    button3.Enabled = true;
                    serialPort1.DiscardInBuffer();
                }
            }
            catch(Exception e) { }
        }

        private void refresh_com()
        {
            comboBox1.DataSource = SerialPort.GetPortNames();
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            comdata = serialPort1.ReadLine();//ReadExisting()
            int seperator = comdata.IndexOf(',');
            comtime = comdata.Substring(seperator+1);
            comdata = comdata.Substring(0,seperator);
            
            int recData = 0;
            
            if (Int32.TryParse(Regex.Replace(comdata, "[^.0-9-]", ""), out recData) && Int32.TryParse(Regex.Replace(comtime, "[^.0-9-]", ""), out recTime))
            {
                if (recTime >= curTime)
                {
                    curTime = recTime;
                    //serialData.Invoke((MethodInvoker)delegate { serialData.AppendText("Received: " + recData); });
                    BeginInvoke(new Delegate_ShowChart(ShowChart1), new Object[] { chart1, read_bit(recData, 0), recTime });
                    BeginInvoke(new Delegate_ShowChart(ShowChart2), new Object[] { chart2, read_bit(recData, 1), recTime });
                    BeginInvoke(new Delegate_ShowChart(ShowChart3), new Object[] { chart3, read_bit(recData, 2), recTime });
                    BeginInvoke(new Delegate_ShowChart(ShowChart4), new Object[] { chart4, read_bit(recData, 3), recTime });
                    BeginInvoke(new Delegate_ShowChart(ShowChart5), new Object[] { chart5, read_bit(recData, 4), recTime });
                    BeginInvoke(new Delegate_ShowChart(ShowChart6), new Object[] { chart6, read_bit(recData, 5), recTime });
                    BeginInvoke(new Delegate_ShowChart(ShowChart7), new Object[] { chart7, read_bit(recData, 6), recTime });
                    BeginInvoke(new Delegate_ShowChart(ShowChart8), new Object[] { chart8, read_bit(recData, 7), recTime });
                    i += 0.15;
                    count++;
                }else
                {
                    BeginInvoke(new Delegate_clearChart(clearChart), new Object[] { chart1 });
                    BeginInvoke(new Delegate_clearChart(clearChart), new Object[] { chart2 });
                    BeginInvoke(new Delegate_clearChart(clearChart), new Object[] { chart3 });
                    BeginInvoke(new Delegate_clearChart(clearChart), new Object[] { chart4 });
                    BeginInvoke(new Delegate_clearChart(clearChart), new Object[] { chart5 });
                    BeginInvoke(new Delegate_clearChart(clearChart), new Object[] { chart6 });
                    BeginInvoke(new Delegate_clearChart(clearChart), new Object[] { chart7 });
                    BeginInvoke(new Delegate_clearChart(clearChart), new Object[] { chart8 });
                    serialPort1.Write("G");
                    curTime = recTime;
                }
            }

            


        }

        private delegate void Delegate_clearChart(Chart chart);
        private delegate void Delegate_ShowChart(Chart chart, int val, int time);

        private int read_bit(int num, int bit_num)
        {
            return (num & (1 << bit_num)) >> bit_num;
        }
        private void ShowChart1(Chart chart, int val, int time)
        {

            //chart.Series[0].Points.Clear();
            chart.Series[0].MarkerStyle = MarkerStyle.Circle;
            chart.Series[0].BorderWidth = 3;
            chart.Series[0].MarkerSize = 6;
            chart.Series[0].Color = Color.Blue;
            chart.ChartAreas[0].AxisY.Minimum = 0;
            chart.ChartAreas[0].AxisX.Minimum = 0;
            chart.ChartAreas[0].AxisX.Maximum = 30;
            chart.Series[0].Points.Add(new DataPoint(time*0.15, val * 5));
            
        }

        private void ShowChart2(Chart chart, int val, int time)
        {

            //chart.Series[0].Points.Clear();
            chart.Series[0].MarkerStyle = MarkerStyle.Circle;
            chart.Series[0].BorderWidth = 3;
            chart.Series[0].MarkerSize = 6;
            chart.Series[0].Color = Color.Blue;
            chart.ChartAreas[0].AxisY.Minimum = 0;
            chart.ChartAreas[0].AxisX.Minimum = 0;
            chart.ChartAreas[0].AxisX.Maximum = 30;
            chart.Series[0].Points.Add(new DataPoint(time * 0.15, val * 5));

        }

        private void ShowChart3(Chart chart, int val, int time)
        {

            //chart.Series[0].Points.Clear();
            chart.Series[0].MarkerStyle = MarkerStyle.Circle;
            chart.Series[0].BorderWidth = 3;
            chart.Series[0].MarkerSize = 6;
            chart.Series[0].Color = Color.Blue;
            chart.ChartAreas[0].AxisY.Minimum = 0;
            chart.ChartAreas[0].AxisX.Minimum = 0;
            chart.ChartAreas[0].AxisX.Maximum = 30;
            chart.Series[0].Points.Add(new DataPoint(time * 0.15, val * 10));

        }

        private void ShowChart4(Chart chart, int val, int time)
        {

            //chart.Series[0].Points.Clear();
            chart.Series[0].MarkerStyle = MarkerStyle.Circle;
            chart.Series[0].BorderWidth = 3;
            chart.Series[0].MarkerSize = 6;
            chart.Series[0].Color = Color.Blue;
            chart.ChartAreas[0].AxisY.Minimum = 0;
            chart.ChartAreas[0].AxisX.Minimum = 0;
            chart.ChartAreas[0].AxisX.Maximum = 30;
            chart.Series[0].Points.Add(new DataPoint(time * 0.15, val * 10));

        }

        private void ShowChart5(Chart chart, int val, int time)
        {

            //chart.Series[0].Points.Clear();
            chart.Series[0].MarkerStyle = MarkerStyle.Circle;
            chart.Series[0].BorderWidth = 3;
            chart.Series[0].MarkerSize = 6;
            chart.Series[0].Color = Color.Blue;
            chart.ChartAreas[0].AxisY.Minimum = 0;
            chart.ChartAreas[0].AxisX.Minimum = 0;
            chart.ChartAreas[0].AxisX.Maximum = 30;
            chart.Series[0].Points.Add(new DataPoint(time * 0.15, val * 10));

        }

        private void ShowChart6(Chart chart, int val, int time)
        {

            //chart.Series[0].Points.Clear();
            chart.Series[0].MarkerStyle = MarkerStyle.Circle;
            chart.Series[0].BorderWidth = 3;
            chart.Series[0].MarkerSize = 6;
            chart.Series[0].Color = Color.Blue;
            chart.ChartAreas[0].AxisY.Minimum = 0;
            chart.ChartAreas[0].AxisX.Minimum = 0;
            chart.ChartAreas[0].AxisX.Maximum = 30;
            chart.Series[0].Points.Add(new DataPoint(time * 0.15, val * 10));

        }

        private void ShowChart7(Chart chart, int val, int time)
        {
            //chart.Series[0].Points.Clear();
            chart.Series[0].MarkerStyle = MarkerStyle.Circle;
            chart.Series[0].BorderWidth = 3;
            chart.Series[0].MarkerSize = 6;
            chart.Series[0].Color = Color.Blue;
            chart.ChartAreas[0].AxisY.Minimum = 0;
            chart.ChartAreas[0].AxisX.Minimum = 0;
            chart.ChartAreas[0].AxisX.Maximum = 30;
            chart.Series[0].Points.Add(new DataPoint(time * 0.15, val * 10));

        }

        private void ShowChart8(Chart chart, int val, int time)
        {

            //chart.Series[0].Points.Clear();
            chart.Series[0].MarkerStyle = MarkerStyle.Circle;
            chart.Series[0].BorderWidth = 3;
            chart.Series[0].MarkerSize = 6;
            chart.Series[0].Color = Color.Blue;
            chart.ChartAreas[0].AxisY.Minimum = 0;
            chart.ChartAreas[0].AxisX.Minimum = 0;
            chart.ChartAreas[0].AxisX.Maximum = 30;
            chart.Series[0].Points.Add(new DataPoint(time * 0.15, val * 10));

        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                if (true == serialPort1.IsOpen) serialPort1.DiscardInBuffer();
                System.Windows.Forms.Application.DoEvents();
                if (serialPort1.IsOpen) serialPort1.Close();
                System.Windows.Forms.Application.DoEvents();
            }
            catch (Exception ex) { }
        }

    }
}
