/*-----------------------------------
 Column names collide with form name, 
 so name change on headers allowed 
 this to work.
 ----------------------------------*/ 
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Web.Script.Serialization;

namespace Stock_Market_Price_Reciever
{

    public partial class Form1 : Form
    {

        TcpClient m_client;
        const int port = 1000;
        const int STOCK_COUNT = 5;
        public Form1()
        {
            InitializeComponent();
            dataGridView1.Rows.Add(STOCK_COUNT - 1);
            cbo_DataRecieved.SelectedIndex = 0;

            DataReciever data = new DataReciever();
            data.DataRecieved += UpdateGrid;

        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            ////////////////////////////////////////////////////////
            // Connect to specified IP address and port.

            DataReciever data = new DataReciever();

            data.connect(txtIpAddress.Text, txtPort.Text);

            ////////////////////////////////////////////////////////
            // TODO: Start Listening for received messages on new thread.
            // assign thread to listeningThread so we can destroy it.

        }

        private void UpdateGrid(StockDetails data, int count)
        {

            dataGridView1.Rows[data.StockId].Cells[0].Value = data.StockName;
            dataGridView1.Rows[data.StockId].Cells[1].Value = data.StockPrice;
            dataGridView1.Rows[data.StockId].Cells[2].Value = data.StockChange;

            lblCount.Invoke(new Action(() => lblCount.Text = count.ToString()));
            lblTime.Invoke(new Action(() => lblTime.Text = data.Time.ToString()));

        }




    }
}
        public struct StockDetails
{
    public int StockId;
    public string StockName;
    public double StockPrice;
    public double StockChange;
    public DateTime Time;

}

public class DataReciever
{

    public delegate void UpdateGrid(StockDetails stockData, int counter);
    public event UpdateGrid DataRecieved;

    StockDetails stocks;

    TcpClient m_client;

    Thread listeningThread = null;

    int dataCount = 0;

    public void connect(string ip, string port)
    {

        m_client = new TcpClient();
        m_client.Connect(IPAddress.Parse(ip), int.Parse(port));

        MessageBox.Show("Connected to: " + ip + ":" + port);

        listeningThread = new Thread(new ThreadStart(Listen));
        listeningThread.Start();

    }

    public void Listen()
    {
        NetworkStream stream = m_client.GetStream();

        while (true)
        {

            byte[] buffer = new byte[256];
            int n_bytes = stream.Read(buffer, 0, 256);

            JavaScriptSerializer Serializer = new JavaScriptSerializer();
            stocks = Serializer.Deserialize<StockDetails>(Encoding.ASCII.GetString(buffer, 0, n_bytes));

            MessageBox.Show(Convert.ToString(stocks.StockId));

            dataCount++;

            OnDataRecieved();

        }
    }

    protected virtual void OnDataRecieved()
    {
        DataRecieved(stocks, dataCount);
    }

}