using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI_CW1
{
    public partial class frmMain : Form
    {

        //initialising variables
        const int LIST_MAX = 30; // const int for max number of items in list
        const int MAX_VALUE = 100; // highest value that the user can input
        const int LOW_VALUE = 0; // Lowest number a user can input

        int listCount = 0; // counter for items in stored values list
        int regens = 0; // counter for the amount of times that random function had generated an already existing value
        int comparisons = 0; // counter for the amount of times values are compared in sort and search methods
        int edits = 0; // counter for the amount of times values are edited in sort methods
        int val1 = 0, val2 = 0; // temporary values for use in sort methods
        int index = 0; // temporary index for use in sort methods

        static Random rng = new Random(); // initialising random number generator seed

        public frmMain()
        {
            InitializeComponent();
        }

        //custom functions
        private void Submit()// function for submit button
        {
            if (string.IsNullOrEmpty(txtValue.Text)) // return error message if textbox is empty
            {
                MessageBox.Show("ERROR: No value entered");
            }
            else if (Search(1, Convert.ToInt32(txtValue.Text))) // return error if textboxes value is already in list
            {
                MessageBox.Show("ERROR: Number already entered");
            }
            else if (txtValue.Text.Contains(" ")) // retuns error if user has inputted a blank value infornt of their value
            {
                MessageBox.Show("ERROR: Check the syntax of the number submitted, make sure there are no '_' before the number");
            }
            else if (listCount == LIST_MAX) // returns error if the list is already full
            {
                MessageBox.Show("ERROR: List is limited to size of " + LIST_MAX + ", remove items before adding more");
            }
            else if (Convert.ToInt16(txtValue.Text) > MAX_VALUE) // returns error if inputted value is too high
            {
                MessageBox.Show("ERROR: Value too high, enter a value between 0 and 100");
            }
            else // if all rules are followed then the value will be entered
            {
                lstStoredValues.Items.Add(txtValue.Text);
                listCount++;
                UpdateStats();
                txtValue.Clear();
            }


            Sort();
        }

        private void UpdateStats()// funtion for updating the stats window
        {
            // clears stats list so updated stats can be written out
            lstStats.Items.Clear();

            // listing stats realted to amount of items in list
            lstStats.Items.Add("Values stored: " + listCount);
            lstStats.Items.Add("Values remaining: " + (LIST_MAX - listCount));
            lstStats.Items.Add("");

            // checking which values in the list are the larges and lowest
            int highestVal = LOW_VALUE;
            int lowestVal = MAX_VALUE;
            int totalValue = 0;
            for (int i = 0; i < listCount; i++)
            {

                lstStoredValues.SetSelected(i, true);

                int tempVal = Convert.ToInt32(lstStoredValues.SelectedItems[0]);

                totalValue += tempVal;

                if (tempVal < lowestVal)
                {
                    lowestVal = tempVal;
                }

                if (tempVal > highestVal)
                {
                    highestVal = tempVal;
                }

            }

            // stat informing user how many times a randomly generaterd number had to be regenerated due to that value already being in the list
            lstStats.Items.Add("Random gen restarts: " + regens);
            lstStats.Items.Add("");

            // stat informing user the total value of the list
            lstStats.Items.Add("Values total: " + totalValue);

            // stats informing user which values are the highest, .lowest, first in list and last in list
            if (listCount != 0)
            {
                lstStats.Items.Add("");
                lstStoredValues.SetSelected(0, true);
                lstStats.Items.Add("First Value: " + lstStoredValues.SelectedItems[0]);

                lstStoredValues.SetSelected(listCount - 1, true);
                lstStats.Items.Add("Last Value: " + lstStoredValues.SelectedItems[0]);

                lstStats.Items.Add("");
                lstStats.Items.Add("Values lowest: " + lowestVal);
                lstStats.Items.Add("Values highest: " + highestVal);
            }

            lstStats.Items.Add("");

            // stat informing user how many comparisons was made during the last function (only displayed if the last function had comparisons)
            if (comparisons > 0)
            {
                lstStats.Items.Add("List comparisons: " + comparisons);
                comparisons = 0;
            }

            // stat informing user how many edits was made during the last function (only displayed if the last function had edits)
            if (edits > 0)
            {
                lstStats.Items.Add("List edits: " + edits);
                edits = 0;
            }

            UpdateForm();

        }

        private void UpdateForm()// function for updating the form
        {
            //updates form unsing the amount of values that are in the "values" list
            if (listCount == 0)
            {
                btnRemove.Enabled = false;
                btnClear.Enabled = false;
                btnSearch.Enabled = false;
            }
            else
            {
                btnSearch.Enabled = true;
            }

            if (listCount > 1)
            {
                btnRemove.Enabled = true;
                btnClear.Enabled = true;
            }

            if (listCount < 2)
            {
                btnShuffle.Enabled = false;
                chkSorted.Enabled = false;
                cboSortStyleSelect.Enabled = false;

                chkSorted.Checked = false;
                chkUnsorted.Checked = true;
            }
            if (listCount >= 2)
            {
                btnShuffle.Enabled = true;
                chkSorted.Enabled = true;
            }

            if (listCount < 30)
            {
                btnInsert.Enabled = true;
                btnInitialise.Enabled = true;
            }
            if (listCount == 30)
            {
                btnInsert.Enabled = false;
                btnInitialise.Enabled = false;
            }

            // ensuring that you can't shuffle the list if you have binary search checked
            if (chkBinary.Checked)
            {
                btnShuffle.Enabled = false;
            }
        }

        private int GenerateNum()// function to generate and return a random number
        {
            int rgn = 0;
            do
            {
                rgn = rng.Next(MAX_VALUE);
                while (Search(1, rgn))
                //while (lstStoredValues.Items.Contains(rgn))
                {
                    rgn = rng.Next(MAX_VALUE);
                    //rgn++;
                    regens++;
                }
            }
            while (lstStoredValues.Items.Contains(rgn));


            return rgn;
        }

        private void Unselect() // function that un-selects an item in the value list
        {
            if (listCount != 0)
            {
                lstStoredValues.SetSelected(0, true);
                lstStoredValues.SetSelected(0, false);
            }
        }

        private bool Search(int searchType, int input) // search type 0 is requested search, search type 1 is unrequested; input is the value being searched
        {
            bool found = false;

            if (listCount == 0 && searchType == 0)
            {
                MessageBox.Show("Error: No values in list");
            }
            if (listCount != 0)
            {

                if (searchType == 0)
                {
                    input = Convert.ToInt32(txtValue.Text);
                }

                if (chkLinear.Checked)
                {
                    found = Linear(searchType, input);
                }
                else if (chkBinary.Checked)
                {
                    found = Binary(searchType, input);
                }
                else
                {
                    MessageBox.Show("Error: issue with reading search type."); // informs dev&user if there is an issue with selecting sort type
                }

                // Informing user if the value has been found or not
                if (found && searchType == 0)
                {
                    MessageBox.Show("Input has been found and is highlighted");
                }
                if (!found && searchType == 0)
                {
                    MessageBox.Show("Input was not found");
                }
            }

            UpdateStats();
            return found;
        }

        private void Sort()
        {
            if (cboSortStyleSelect.Enabled)
            {
                if (cboSortStyleSelect.SelectedIndex == 0)
                {
                    SelectionSort();
                }
                else if (cboSortStyleSelect.SelectedIndex == 1)
                {
                    BubbleSort();
                }
                else if (cboSortStyleSelect.SelectedIndex == 2)
                {
                    InsertionSort();
                }
                else
                {
                    MessageBox.Show("Error: issue with reading sort type."); // informs dev&user if there is an issue with selecting sort type
                }
            }

            UpdateStats();
            Unselect();
        }

        private void PreSort() // run before a sort so the sort can run properly
        {
            val1 = 0;
            val2 = 0;
            index = 0;
        }

        // Sort methods
        private void SelectionSort() // sort method 0 function
        {

            PreSort(); // setting temporary ints

            // compairing values for sort
            for (int i = 0; i < listCount - 1; i++)
            {

                lstStoredValues.SetSelected(i, true);
                val1 = Convert.ToInt32(lstStoredValues.SelectedItems[0]);

                index = i;

                for (int j = i + 1; j < listCount; j++)
                {

                    lstStoredValues.SetSelected(j, true);
                    val2 = Convert.ToInt32(lstStoredValues.SelectedItems[0]);

                    if (val2 < val1)
                    {
                        index = j;
                        val1 = val2;
                    }
                    comparisons++;
                }

                lstStoredValues.Items.Insert(i, val1);
                lstStoredValues.Items.RemoveAt(index + 1);
                edits++;

            }
        }

        private void BubbleSort() // sort method 1 function
        {
            PreSort(); // setting temporary ints

            // compairing values for sort
            for (int i = 0; i < listCount; i++)
            {
                for (int j = 0; j < listCount - 1; j++)
                {
                    lstStoredValues.SetSelected(j, true);
                    val1 = Convert.ToInt32(lstStoredValues.SelectedItems[0]);

                    lstStoredValues.SetSelected(j + 1, true);
                    val2 = Convert.ToInt32(lstStoredValues.SelectedItems[0]);

                    if (val1 > val2)
                    {
                        index = j;
                        lstStoredValues.Items.RemoveAt(j);
                        lstStoredValues.Items.Insert(j + 1, val1);
                        edits++;
                    }
                    comparisons++;
                }
            }
        }

        private void InsertionSort() // sort method 2 function
        {
            PreSort(); // setting temporary ints

            // compairing values for sort
            for (int i =  0; i < listCount - 1; i++)
            {
                int j = i + 1;

                while (j > 0)
                {
                    lstStoredValues.SetSelected(j - 1, true);
                    val1 = Convert.ToInt32(lstStoredValues.SelectedItems[0]);

                    lstStoredValues.SetSelected(j, true);
                    val2 = Convert.ToInt32(lstStoredValues.SelectedItems[0]);
                    if  (val1 > val2)
                    {
                        index = j - 1;
                        lstStoredValues.Items.RemoveAt(index);
                        lstStoredValues.Items.Insert(index + 1, val1);
                        edits++;
                    }
                    j--;
                    comparisons++;
                    comparisons++;
                }
            }
        }

        // Search methods
        private bool Linear(int searchType, int input) // unsorted & sorted search method function
        {
            bool found = false;

            // checking if search is requested
            if (searchType == 0)
            {
                input = Convert.ToInt32(txtValue.Text);
            }
             // searching list
            for (int i = 0; i < listCount; i++)
            {

                lstStoredValues.SetSelected(i, true);
                int tempVal = Convert.ToInt32(lstStoredValues.SelectedItems[0]);

                if (input == tempVal)
                {
                    found = true;
                    i = listCount;
                }
                // incrementing comparisons counter
                comparisons++;
            }
            // returning if value has been found or not
            return found;
        }

        private bool Binary(int searchType, int input) // sorted search method function
        {
            bool found = false;
            bool complete = false;
            int high = listCount - 1;
            int low = 0;
            int mid = high / 2;
            int value = 0;
            int oldMid = 0;

            // initial test of value to make sure it's within list range
            lstStoredValues.SetSelected(low, true);
            value = Convert.ToInt32(lstStoredValues.SelectedItems[0]);
            if (input < value)
            {
                complete = true;
            }

            lstStoredValues.SetSelected(high, true);
            value = Convert.ToInt32(lstStoredValues.SelectedItems[0]);
            if (input >= value)
            {
                complete = true;

                if (input == value)
                {
                    found = true;
                }
            }

            // Checking list
            while (!complete)
            {
                lstStoredValues.SetSelected(mid, true);
                value = Convert.ToInt32(lstStoredValues.SelectedItems[0]);

                oldMid = mid;

                if (input < value)
                {
                    high = mid;
                    mid = (low + high) / 2;
                }
                else if (input > value)
                {
                    low = mid;
                    mid = (low + high) / 2;
                    comparisons++;
                }
                comparisons++;

                if (input == value)
                {
                    found = true;
                    complete = true;
                }
                else if (oldMid == mid)
                {

                    lstStoredValues.SetSelected(mid + 1, true);
                    value = Convert.ToInt32(lstStoredValues.SelectedItems[0]);
                    if (input == value)
                    {
                        found = true;

                    }
                    else
                    {
                        lstStoredValues.SetSelected(mid - 1, true);
                        value = Convert.ToInt32(lstStoredValues.SelectedItems[0]);

                        if (input == value)
                        {
                            found = true;

                        }

                        complete = true;
                        comparisons++;
                    }
                    comparisons++;
                }
                comparisons++;
            }

            return found;
        }

        //automatically made functions
        private void frmMain_Load(object sender, EventArgs e) // gets run on form load
        {
            UpdateStats();
            picBin.AllowDrop = true;
            cboSortStyleSelect.SelectedIndex = 0;
        }

        private void btnExit_Click(object sender, EventArgs e) // closes program
        {
            Close();
        }

        private void btnInsert_Click(object sender, EventArgs e) // submits values via button press
        {
            Submit();
        }

        private void txtValue_KeyPress(object sender, KeyPressEventArgs e) // submits values via keypress
        {
            if (e.KeyChar == (char)13)
            {
                Submit();
            }
        }

        private void btnClear_Click(object sender, EventArgs e) // clears values in list
        {
            lstStoredValues.Items.Clear();
            listCount = 0;
            UpdateStats();
        }

        private void btnRemove_Click(object sender, EventArgs e) // removes a value in the list
        {
            if (lstStoredValues.SelectedItems.Count == 0)
            {
                MessageBox.Show("ERROR: No item(s) in list selected");
            }
            else
            {
                listCount -= lstStoredValues.SelectedItems.Count;
                lstStoredValues.Items.Remove(lstStoredValues.SelectedItems[0]);
                UpdateStats();
            }
            Unselect();
        }

        private void btnSearch_Click(object sender, EventArgs e) // searches for value in list
        {
            Search(0, 0);
        }

        private void btnInitialise_Click(object sender, EventArgs e) // generates random unique numbers
        {
            int tempListCount = listCount;

            edits = 0;

            for (int i = 0; i < LIST_MAX - tempListCount; i++)
            {

                int tempGen = GenerateNum();

                lstStoredValues.Items.Add("" + tempGen);
                listCount++;
                edits = LIST_MAX - tempListCount;
            }

            Sort();
            Unselect();
        }

        private void chkSorted_CheckedChanged(object sender, EventArgs e) // checks which sort radio buttons are selected
        {
            if (chkSorted.Checked)
            {
                cboSortStyleSelect.Enabled = true;
                chkBinary.Enabled = true;
                Sort();
            }
            else
            {
                cboSortStyleSelect.Enabled = false;
                chkBinary.Enabled = false;
                chkBinary.Checked = false;
                chkLinear.Checked = true;
                btnShuffle.Enabled = true;

            }
        }

        private void cboSortStyleSelect_SelectedIndexChanged(object sender, EventArgs e) // sorts the list on radio button change
        {
            Sort();
        }

        private void lstStoredValues_MouseDown(object sender, MouseEventArgs e) // mousedown for drag & drop deletion
        {
            lstStoredValues.DoDragDrop(lstStoredValues.Text, DragDropEffects.Copy);
        }

        private void picBin_DragEnter(object sender, DragEventArgs e) // bin image drag drop enter function
        {
            picBin.Image = Properties.Resources.binOpen;
            e.Effect = DragDropEffects.Copy;
        }

        private void picBin_DragLeave(object sender, EventArgs e) // bin image drag drop leave function
        {
            picBin.Image = Properties.Resources.binClosed;
        }

        private void picBin_DragDrop(object sender, DragEventArgs e) // bin image drag drop drop function
        {
            int tempValue = Convert.ToInt16((string)e.Data.GetData(DataFormats.StringFormat));
            Search(1, tempValue);
            lstStoredValues.Items.Remove(lstStoredValues.SelectedItems[0]);
            listCount--;
            UpdateStats();
            picBin.Image = Properties.Resources.binClosed;

            Unselect();
        }

        private void btnShuffle_Click(object sender, EventArgs e) // shuffles list of values
        {
            int index1 = 0; // generated index that is going to get swapped
            int index2 = 0; // generated index that is going to get swapped
            int tempInt1 = 0; // tempory storage of number at "index1"
            int tempInt2 = 0; // tempory storage of number at "index2"

            for (int i = 0; i < listCount * 7; i++)
            {
                index1 = rng.Next(listCount); // generating random numbers within range, generated numbers will be used to randomly select two indexes...
                index2 = rng.Next(listCount); // ... for the shuffle function to swap the two numbers (corresponding to the index)

                // selecting and storing value at index1 to temp storage
                lstStoredValues.SetSelected(index1, true);
                tempInt1 = Convert.ToInt32(lstStoredValues.SelectedItems[0]);

                // selecting and storing value at index2 to index1
                lstStoredValues.SetSelected(index2, true);
                tempInt2 = Convert.ToInt32(lstStoredValues.SelectedItems[0]);
                lstStoredValues.Items.RemoveAt(index1);
                lstStoredValues.Items.Insert(index1, tempInt2);

                // selecting index2 and storing temp value into it
                lstStoredValues.Items.RemoveAt(index2);
                lstStoredValues.Items.Insert(index2, tempInt1);

                // showing user the amount of edits done in this function
                edits++;
                edits++;
            }
            UpdateStats(); // makes sure that nothing is wrong (for dev&debug purposes) < now used for all the edit++
        }

        private void chkSorted_Click(object sender, EventArgs e) // sorts list of values
        {
            if (chkSorted.Checked)
            {
                Sort();

            }
        }

        private void chkBinary_CheckedChanged(object sender, EventArgs e) // sorts list of values
        {
            Sort();
        }
    }
}