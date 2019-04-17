using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Steam_Gem_Calculator
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void lnkSteam_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://steamcommunity.com/market/listings/753/753-Sack%20of%20Gems");
        }

        private void btnCalculate_Click(object sender, EventArgs e)
        {

            float bagValue = 0;

            float itemCurValue = 0;
            float itemGemValue = 0;

            float trueGemValue = 0;

            if (txtGemBuyValue.Text == "" || txtItemCurValue.Text == "" || txtItemGemValue.Text == "") {

                MessageBox.Show("ERROR: Fill out all feilds");

            } else {

                bagValue = (float)Convert.ToDouble(txtGemBuyValue.Text);
                itemCurValue = (float)Convert.ToDouble(txtItemCurValue.Text);
                itemGemValue = (float)Convert.ToDouble(txtItemGemValue.Text);

                trueGemValue = bagValue / 1000 * itemGemValue;

                if (trueGemValue > itemCurValue) {

                    MessageBox.Show("Turn the item into gems!");

                } else if (trueGemValue < itemCurValue) {

                    MessageBox.Show("Sell the item!");

                } else if (trueGemValue == itemCurValue) {

                    MessageBox.Show("Do what ever you want with the item");

                } else {
            
                    MessageBox.Show("ERROR: You shouldn't be able to see this message...");

                }
            }
        }

        private void btnInfo_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Calculations: \n\ntrueGemValue = Input1 / 1000 * Input3 \n\nif (trueGemValue > itemCurValue), Gem \nif (trueGemValue < itemCurValue), Sell \nif (trueGemValue == itemCurValue) Gem or Sell");
        }

        private void btnSteve_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Just turn it into gems");
        }
    }
}
