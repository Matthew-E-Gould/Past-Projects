namespace Steam_Gem_Calculator
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.txtGemBuyValue = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.lnkSteam = new System.Windows.Forms.LinkLabel();
            this.label1 = new System.Windows.Forms.Label();
            this.txtItemCurValue = new System.Windows.Forms.TextBox();
            this.txtItemGemValue = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.btnCalculate = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.btnInfo = new System.Windows.Forms.Button();
            this.btnSteve = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // txtGemBuyValue
            // 
            this.txtGemBuyValue.Location = new System.Drawing.Point(157, 13);
            this.txtGemBuyValue.Name = "txtGemBuyValue";
            this.txtGemBuyValue.Size = new System.Drawing.Size(100, 20);
            this.txtGemBuyValue.TabIndex = 1;
            this.txtGemBuyValue.Text = "0.00";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 38);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(76, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "(Any Currency)";
            // 
            // lnkSteam
            // 
            this.lnkSteam.AutoSize = true;
            this.lnkSteam.Location = new System.Drawing.Point(12, 16);
            this.lnkSteam.Name = "lnkSteam";
            this.lnkSteam.Size = new System.Drawing.Size(114, 13);
            this.lnkSteam.TabIndex = 3;
            this.lnkSteam.TabStop = true;
            this.lnkSteam.Text = "Current gem sell value:";
            this.lnkSteam.VisitedLinkColor = System.Drawing.Color.Black;
            this.lnkSteam.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.lnkSteam_LinkClicked);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 75);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(103, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Item currency value:";
            // 
            // txtItemCurValue
            // 
            this.txtItemCurValue.Location = new System.Drawing.Point(157, 72);
            this.txtItemCurValue.Name = "txtItemCurValue";
            this.txtItemCurValue.Size = new System.Drawing.Size(100, 20);
            this.txtItemCurValue.TabIndex = 5;
            this.txtItemCurValue.Text = "0.00";
            // 
            // txtItemGemValue
            // 
            this.txtItemGemValue.Location = new System.Drawing.Point(157, 131);
            this.txtItemGemValue.Name = "txtItemGemValue";
            this.txtItemGemValue.Size = new System.Drawing.Size(100, 20);
            this.txtItemGemValue.TabIndex = 6;
            this.txtItemGemValue.Text = "0";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 134);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(82, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Item gem value:";
            // 
            // btnCalculate
            // 
            this.btnCalculate.Location = new System.Drawing.Point(12, 157);
            this.btnCalculate.Name = "btnCalculate";
            this.btnCalculate.Size = new System.Drawing.Size(245, 23);
            this.btnCalculate.TabIndex = 8;
            this.btnCalculate.Text = "Calculate!";
            this.btnCalculate.UseVisualStyleBackColor = true;
            this.btnCalculate.Click += new System.EventHandler(this.btnCalculate_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 95);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(214, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "(Same as First Currency) (What you recieve)";
            // 
            // btnInfo
            // 
            this.btnInfo.Location = new System.Drawing.Point(157, 226);
            this.btnInfo.Name = "btnInfo";
            this.btnInfo.Size = new System.Drawing.Size(102, 23);
            this.btnInfo.TabIndex = 11;
            this.btnInfo.Text = "Info";
            this.btnInfo.UseVisualStyleBackColor = true;
            this.btnInfo.Click += new System.EventHandler(this.btnInfo_Click);
            // 
            // btnSteve
            // 
            this.btnSteve.Location = new System.Drawing.Point(12, 226);
            this.btnSteve.Name = "btnSteve";
            this.btnSteve.Size = new System.Drawing.Size(139, 23);
            this.btnSteve.TabIndex = 12;
            this.btnSteve.Text = "Steve Mode";
            this.btnSteve.UseVisualStyleBackColor = true;
            this.btnSteve.Click += new System.EventHandler(this.btnSteve_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(271, 261);
            this.Controls.Add(this.btnSteve);
            this.Controls.Add(this.btnInfo);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.btnCalculate);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtItemGemValue);
            this.Controls.Add(this.txtItemCurValue);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lnkSteam);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtGemBuyValue);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "SGC V1.1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtGemBuyValue;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.LinkLabel lnkSteam;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtItemCurValue;
        private System.Windows.Forms.TextBox txtItemGemValue;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btnCalculate;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button btnInfo;
        private System.Windows.Forms.Button btnSteve;
    }
}

