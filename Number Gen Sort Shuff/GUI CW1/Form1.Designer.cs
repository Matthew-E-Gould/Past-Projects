namespace GUI_CW1
{
    partial class frmMain
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
            this.lstStoredValues = new System.Windows.Forms.ListBox();
            this.chkBinary = new System.Windows.Forms.RadioButton();
            this.chkLinear = new System.Windows.Forms.RadioButton();
            this.chkSorted = new System.Windows.Forms.RadioButton();
            this.chkUnsorted = new System.Windows.Forms.RadioButton();
            this.grpSearch = new System.Windows.Forms.GroupBox();
            this.grpSort = new System.Windows.Forms.GroupBox();
            this.lblSortStyle = new System.Windows.Forms.Label();
            this.cboSortStyleSelect = new System.Windows.Forms.ComboBox();
            this.btnInitialise = new System.Windows.Forms.Button();
            this.btnClear = new System.Windows.Forms.Button();
            this.btnShuffle = new System.Windows.Forms.Button();
            this.btnRemove = new System.Windows.Forms.Button();
            this.btnInsert = new System.Windows.Forms.Button();
            this.btnSearch = new System.Windows.Forms.Button();
            this.btnExit = new System.Windows.Forms.Button();
            this.grpAddOrSearch = new System.Windows.Forms.GroupBox();
            this.txtValue = new System.Windows.Forms.MaskedTextBox();
            this.grpFunctions = new System.Windows.Forms.GroupBox();
            this.lstStats = new System.Windows.Forms.ListBox();
            this.picBin = new System.Windows.Forms.PictureBox();
            this.grpSearch.SuspendLayout();
            this.grpSort.SuspendLayout();
            this.grpAddOrSearch.SuspendLayout();
            this.grpFunctions.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picBin)).BeginInit();
            this.SuspendLayout();
            // 
            // lstStoredValues
            // 
            this.lstStoredValues.FormattingEnabled = true;
            this.lstStoredValues.Location = new System.Drawing.Point(193, 12);
            this.lstStoredValues.Name = "lstStoredValues";
            this.lstStoredValues.Size = new System.Drawing.Size(53, 394);
            this.lstStoredValues.TabIndex = 0;
            this.lstStoredValues.MouseDown += new System.Windows.Forms.MouseEventHandler(this.lstStoredValues_MouseDown);
            // 
            // chkBinary
            // 
            this.chkBinary.AutoSize = true;
            this.chkBinary.Enabled = false;
            this.chkBinary.Location = new System.Drawing.Point(6, 42);
            this.chkBinary.Name = "chkBinary";
            this.chkBinary.Size = new System.Drawing.Size(54, 17);
            this.chkBinary.TabIndex = 1;
            this.chkBinary.TabStop = true;
            this.chkBinary.Text = "Binary";
            this.chkBinary.UseVisualStyleBackColor = true;
            this.chkBinary.CheckedChanged += new System.EventHandler(this.chkBinary_CheckedChanged);
            // 
            // chkLinear
            // 
            this.chkLinear.AutoSize = true;
            this.chkLinear.Checked = true;
            this.chkLinear.Location = new System.Drawing.Point(6, 19);
            this.chkLinear.Name = "chkLinear";
            this.chkLinear.Size = new System.Drawing.Size(54, 17);
            this.chkLinear.TabIndex = 2;
            this.chkLinear.TabStop = true;
            this.chkLinear.Text = "Linear";
            this.chkLinear.UseVisualStyleBackColor = true;
            // 
            // chkSorted
            // 
            this.chkSorted.AutoSize = true;
            this.chkSorted.Enabled = false;
            this.chkSorted.Location = new System.Drawing.Point(6, 42);
            this.chkSorted.Name = "chkSorted";
            this.chkSorted.Size = new System.Drawing.Size(56, 17);
            this.chkSorted.TabIndex = 3;
            this.chkSorted.TabStop = true;
            this.chkSorted.Text = "Sorted";
            this.chkSorted.UseVisualStyleBackColor = true;
            this.chkSorted.CheckedChanged += new System.EventHandler(this.chkSorted_CheckedChanged);
            this.chkSorted.Click += new System.EventHandler(this.chkSorted_Click);
            // 
            // chkUnsorted
            // 
            this.chkUnsorted.AutoSize = true;
            this.chkUnsorted.Checked = true;
            this.chkUnsorted.Location = new System.Drawing.Point(6, 19);
            this.chkUnsorted.Name = "chkUnsorted";
            this.chkUnsorted.Size = new System.Drawing.Size(68, 17);
            this.chkUnsorted.TabIndex = 4;
            this.chkUnsorted.TabStop = true;
            this.chkUnsorted.Text = "Unsorted";
            this.chkUnsorted.UseVisualStyleBackColor = true;
            // 
            // grpSearch
            // 
            this.grpSearch.Controls.Add(this.chkLinear);
            this.grpSearch.Controls.Add(this.chkBinary);
            this.grpSearch.Location = new System.Drawing.Point(12, 218);
            this.grpSearch.Name = "grpSearch";
            this.grpSearch.Size = new System.Drawing.Size(175, 67);
            this.grpSearch.TabIndex = 5;
            this.grpSearch.TabStop = false;
            this.grpSearch.Text = "Search Type";
            // 
            // grpSort
            // 
            this.grpSort.Controls.Add(this.lblSortStyle);
            this.grpSort.Controls.Add(this.cboSortStyleSelect);
            this.grpSort.Controls.Add(this.chkSorted);
            this.grpSort.Controls.Add(this.chkUnsorted);
            this.grpSort.Location = new System.Drawing.Point(12, 95);
            this.grpSort.Name = "grpSort";
            this.grpSort.Size = new System.Drawing.Size(175, 117);
            this.grpSort.TabIndex = 6;
            this.grpSort.TabStop = false;
            this.grpSort.Text = "Sort";
            // 
            // lblSortStyle
            // 
            this.lblSortStyle.AutoSize = true;
            this.lblSortStyle.Location = new System.Drawing.Point(7, 71);
            this.lblSortStyle.Name = "lblSortStyle";
            this.lblSortStyle.Size = new System.Drawing.Size(53, 13);
            this.lblSortStyle.TabIndex = 6;
            this.lblSortStyle.Text = "Sort style:";
            // 
            // cboSortStyleSelect
            // 
            this.cboSortStyleSelect.Enabled = false;
            this.cboSortStyleSelect.FormattingEnabled = true;
            this.cboSortStyleSelect.Items.AddRange(new object[] {
            "Selection Sort",
            "Bubble Sort",
            "Insertion Sort"});
            this.cboSortStyleSelect.Location = new System.Drawing.Point(6, 90);
            this.cboSortStyleSelect.Name = "cboSortStyleSelect";
            this.cboSortStyleSelect.Size = new System.Drawing.Size(156, 21);
            this.cboSortStyleSelect.TabIndex = 5;
            this.cboSortStyleSelect.SelectedIndexChanged += new System.EventHandler(this.cboSortStyleSelect_SelectedIndexChanged);
            // 
            // btnInitialise
            // 
            this.btnInitialise.Location = new System.Drawing.Point(6, 48);
            this.btnInitialise.Name = "btnInitialise";
            this.btnInitialise.Size = new System.Drawing.Size(75, 23);
            this.btnInitialise.TabIndex = 5;
            this.btnInitialise.Text = "Initialise";
            this.btnInitialise.UseVisualStyleBackColor = true;
            this.btnInitialise.Click += new System.EventHandler(this.btnInitialise_Click);
            // 
            // btnClear
            // 
            this.btnClear.Enabled = false;
            this.btnClear.Location = new System.Drawing.Point(87, 48);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(75, 23);
            this.btnClear.TabIndex = 7;
            this.btnClear.Text = "Clear";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // btnShuffle
            // 
            this.btnShuffle.Enabled = false;
            this.btnShuffle.Location = new System.Drawing.Point(6, 19);
            this.btnShuffle.Name = "btnShuffle";
            this.btnShuffle.Size = new System.Drawing.Size(75, 23);
            this.btnShuffle.TabIndex = 8;
            this.btnShuffle.Text = "Shuffle";
            this.btnShuffle.UseVisualStyleBackColor = true;
            this.btnShuffle.Click += new System.EventHandler(this.btnShuffle_Click);
            // 
            // btnRemove
            // 
            this.btnRemove.Enabled = false;
            this.btnRemove.Location = new System.Drawing.Point(87, 19);
            this.btnRemove.Name = "btnRemove";
            this.btnRemove.Size = new System.Drawing.Size(75, 23);
            this.btnRemove.TabIndex = 9;
            this.btnRemove.Text = "Remove";
            this.btnRemove.UseVisualStyleBackColor = true;
            this.btnRemove.Click += new System.EventHandler(this.btnRemove_Click);
            // 
            // btnInsert
            // 
            this.btnInsert.Location = new System.Drawing.Point(87, 45);
            this.btnInsert.Name = "btnInsert";
            this.btnInsert.Size = new System.Drawing.Size(75, 20);
            this.btnInsert.TabIndex = 10;
            this.btnInsert.Text = "Insert";
            this.btnInsert.UseVisualStyleBackColor = true;
            this.btnInsert.Click += new System.EventHandler(this.btnInsert_Click);
            // 
            // btnSearch
            // 
            this.btnSearch.Location = new System.Drawing.Point(6, 45);
            this.btnSearch.Name = "btnSearch";
            this.btnSearch.Size = new System.Drawing.Size(75, 20);
            this.btnSearch.TabIndex = 11;
            this.btnSearch.Text = "Search";
            this.btnSearch.UseVisualStyleBackColor = true;
            this.btnSearch.Click += new System.EventHandler(this.btnSearch_Click);
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(12, 383);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(175, 23);
            this.btnExit.TabIndex = 12;
            this.btnExit.Text = "Exit";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // grpAddOrSearch
            // 
            this.grpAddOrSearch.Controls.Add(this.txtValue);
            this.grpAddOrSearch.Controls.Add(this.btnInsert);
            this.grpAddOrSearch.Controls.Add(this.btnSearch);
            this.grpAddOrSearch.Location = new System.Drawing.Point(12, 12);
            this.grpAddOrSearch.Name = "grpAddOrSearch";
            this.grpAddOrSearch.Size = new System.Drawing.Size(175, 77);
            this.grpAddOrSearch.TabIndex = 14;
            this.grpAddOrSearch.TabStop = false;
            this.grpAddOrSearch.Text = "List Adding / Searching";
            // 
            // txtValue
            // 
            this.txtValue.Location = new System.Drawing.Point(6, 19);
            this.txtValue.Mask = "000";
            this.txtValue.Name = "txtValue";
            this.txtValue.Size = new System.Drawing.Size(156, 20);
            this.txtValue.TabIndex = 16;
            this.txtValue.TextMaskFormat = System.Windows.Forms.MaskFormat.ExcludePromptAndLiterals;
            this.txtValue.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtValue_KeyPress);
            // 
            // grpFunctions
            // 
            this.grpFunctions.Controls.Add(this.btnShuffle);
            this.grpFunctions.Controls.Add(this.btnRemove);
            this.grpFunctions.Controls.Add(this.btnInitialise);
            this.grpFunctions.Controls.Add(this.btnClear);
            this.grpFunctions.Location = new System.Drawing.Point(12, 291);
            this.grpFunctions.Name = "grpFunctions";
            this.grpFunctions.Size = new System.Drawing.Size(175, 86);
            this.grpFunctions.TabIndex = 15;
            this.grpFunctions.TabStop = false;
            this.grpFunctions.Text = "List Functions";
            // 
            // lstStats
            // 
            this.lstStats.FormattingEnabled = true;
            this.lstStats.Location = new System.Drawing.Point(252, 12);
            this.lstStats.Name = "lstStats";
            this.lstStats.SelectionMode = System.Windows.Forms.SelectionMode.None;
            this.lstStats.Size = new System.Drawing.Size(202, 199);
            this.lstStats.TabIndex = 16;
            // 
            // picBin
            // 
            this.picBin.Image = global::GUI_CW1.Properties.Resources.binClosed;
            this.picBin.InitialImage = global::GUI_CW1.Properties.Resources.binClosed;
            this.picBin.Location = new System.Drawing.Point(252, 217);
            this.picBin.Name = "picBin";
            this.picBin.Size = new System.Drawing.Size(36, 84);
            this.picBin.TabIndex = 18;
            this.picBin.TabStop = false;
            this.picBin.DragDrop += new System.Windows.Forms.DragEventHandler(this.picBin_DragDrop);
            this.picBin.DragEnter += new System.Windows.Forms.DragEventHandler(this.picBin_DragEnter);
            this.picBin.DragLeave += new System.EventHandler(this.picBin_DragLeave);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(501, 421);
            this.Controls.Add(this.picBin);
            this.Controls.Add(this.lstStats);
            this.Controls.Add(this.grpFunctions);
            this.Controls.Add(this.grpAddOrSearch);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.grpSort);
            this.Controls.Add(this.grpSearch);
            this.Controls.Add(this.lstStoredValues);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "frmMain";
            this.Text = "GUI CW1 - 15065456";
            this.Load += new System.EventHandler(this.frmMain_Load);
            this.grpSearch.ResumeLayout(false);
            this.grpSearch.PerformLayout();
            this.grpSort.ResumeLayout(false);
            this.grpSort.PerformLayout();
            this.grpAddOrSearch.ResumeLayout(false);
            this.grpAddOrSearch.PerformLayout();
            this.grpFunctions.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picBin)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox lstStoredValues;
        private System.Windows.Forms.RadioButton chkBinary;
        private System.Windows.Forms.RadioButton chkLinear;
        private System.Windows.Forms.RadioButton chkSorted;
        private System.Windows.Forms.RadioButton chkUnsorted;
        private System.Windows.Forms.GroupBox grpSearch;
        private System.Windows.Forms.GroupBox grpSort;
        private System.Windows.Forms.Button btnInitialise;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Button btnShuffle;
        private System.Windows.Forms.Button btnRemove;
        private System.Windows.Forms.Button btnInsert;
        private System.Windows.Forms.Button btnSearch;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.GroupBox grpAddOrSearch;
        private System.Windows.Forms.GroupBox grpFunctions;
        private System.Windows.Forms.MaskedTextBox txtValue;
        private System.Windows.Forms.ListBox lstStats;
        private System.Windows.Forms.Label lblSortStyle;
        private System.Windows.Forms.ComboBox cboSortStyleSelect;
        private System.Windows.Forms.PictureBox picBin;
    }
}

