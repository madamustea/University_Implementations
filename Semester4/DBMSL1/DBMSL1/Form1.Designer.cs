
using System;
using System.Windows.Forms;

namespace DBMSL1
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
            this.add = new System.Windows.Forms.Button();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.update = new System.Windows.Forms.Button();
            this.delete = new System.Windows.Forms.Button();
            this.LidTxt = new System.Windows.Forms.Label();
            this.textBoxLID = new System.Windows.Forms.TextBox();
            this.connect = new System.Windows.Forms.Button();
            this.First = new System.Windows.Forms.Button();
            this.Previous = new System.Windows.Forms.Button();
            this.Next = new System.Windows.Forms.Button();
            this.Last = new System.Windows.Forms.Button();
            this.CidTxt = new System.Windows.Forms.Label();
            this.textBoxCID = new System.Windows.Forms.TextBox();
            this.textBoxBID = new System.Windows.Forms.TextBox();
            this.BidTxt = new System.Windows.Forms.Label();
            this.dataGridView2 = new System.Windows.Forms.DataGridView();
            this.populate = new System.Windows.Forms.Button();
            this.Previous1 = new System.Windows.Forms.Button();
            this.Next1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
            this.SuspendLayout();
            // 
            // add
            // 
            this.add.Location = new System.Drawing.Point(12, 203);
            this.add.Name = "add";
            this.add.Size = new System.Drawing.Size(142, 40);
            this.add.TabIndex = 0;
            this.add.Text = "add";
            this.add.UseVisualStyleBackColor = true;
            this.add.Click += new System.EventHandler(this.button1_Click);
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(12, 260);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersWidth = 62;
            this.dataGridView1.RowTemplate.Height = 28;
            this.dataGridView1.Size = new System.Drawing.Size(628, 263);
            this.dataGridView1.TabIndex = 1;
            this.dataGridView1.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellContentClick);
            // 
            // update
            // 
            this.update.Location = new System.Drawing.Point(239, 203);
            this.update.Name = "update";
            this.update.Size = new System.Drawing.Size(150, 40);
            this.update.TabIndex = 2;
            this.update.Text = "update";
            this.update.UseVisualStyleBackColor = true;
            this.update.Click += new System.EventHandler(this.update_Click);
            // 
            // delete
            // 
            this.delete.Location = new System.Drawing.Point(480, 203);
            this.delete.Name = "delete";
            this.delete.Size = new System.Drawing.Size(160, 40);
            this.delete.TabIndex = 3;
            this.delete.Text = "delete";
            this.delete.UseVisualStyleBackColor = true;
            this.delete.Click += new System.EventHandler(this.delete_Click);
            // 
            // LidTxt
            // 
            this.LidTxt.AutoSize = true;
            this.LidTxt.Location = new System.Drawing.Point(43, 92);
            this.LidTxt.Name = "LidTxt";
            this.LidTxt.Size = new System.Drawing.Size(30, 20);
            this.LidTxt.TabIndex = 6;
            this.LidTxt.Text = "Lid";
            // 
            // textBoxLID
            // 
            this.textBoxLID.Location = new System.Drawing.Point(120, 86);
            this.textBoxLID.Name = "textBoxLID";
            this.textBoxLID.Size = new System.Drawing.Size(408, 26);
            this.textBoxLID.TabIndex = 7;
            this.textBoxLID.TextChanged += new System.EventHandler(this.textBox2_TextChanged);
            // 
            // connect
            // 
            this.connect.Location = new System.Drawing.Point(1054, 2);
            this.connect.Name = "connect";
            this.connect.Size = new System.Drawing.Size(145, 33);
            this.connect.TabIndex = 8;
            this.connect.Text = "connect";
            this.connect.UseVisualStyleBackColor = true;
            this.connect.Click += new System.EventHandler(this.Connect_Click);
            // 
            // First
            // 
            this.First.Location = new System.Drawing.Point(12, 529);
            this.First.Name = "First";
            this.First.Size = new System.Drawing.Size(119, 37);
            this.First.TabIndex = 9;
            this.First.Text = "First";
            this.First.UseVisualStyleBackColor = true;
            this.First.Click += new System.EventHandler(this.First_Click);
            // 
            // Previous
            // 
            this.Previous.Location = new System.Drawing.Point(173, 529);
            this.Previous.Name = "Previous";
            this.Previous.Size = new System.Drawing.Size(114, 37);
            this.Previous.TabIndex = 10;
            this.Previous.Text = "Previous";
            this.Previous.UseVisualStyleBackColor = true;
            this.Previous.Click += new System.EventHandler(this.Previous_Click);
            // 
            // Next
            // 
            this.Next.Location = new System.Drawing.Point(362, 529);
            this.Next.Name = "Next";
            this.Next.Size = new System.Drawing.Size(114, 37);
            this.Next.TabIndex = 11;
            this.Next.Text = "Next";
            this.Next.UseVisualStyleBackColor = true;
            this.Next.Click += new System.EventHandler(this.Next_Click);
            // 
            // Last
            // 
            this.Last.Location = new System.Drawing.Point(525, 529);
            this.Last.Name = "Last";
            this.Last.Size = new System.Drawing.Size(115, 37);
            this.Last.TabIndex = 12;
            this.Last.Text = "Last";
            this.Last.UseVisualStyleBackColor = true;
            this.Last.Click += new System.EventHandler(this.Last_Click);
            // 
            // CidTxt
            // 
            this.CidTxt.AutoSize = true;
            this.CidTxt.Location = new System.Drawing.Point(43, 124);
            this.CidTxt.Name = "CidTxt";
            this.CidTxt.Size = new System.Drawing.Size(32, 20);
            this.CidTxt.TabIndex = 13;
            this.CidTxt.Text = "Cid";
            // 
            // textBoxCID
            // 
            this.textBoxCID.Location = new System.Drawing.Point(120, 118);
            this.textBoxCID.Name = "textBoxCID";
            this.textBoxCID.Size = new System.Drawing.Size(408, 26);
            this.textBoxCID.TabIndex = 14;
            // 
            // textBoxBID
            // 
            this.textBoxBID.Location = new System.Drawing.Point(120, 150);
            this.textBoxBID.Name = "textBoxBID";
            this.textBoxBID.Size = new System.Drawing.Size(408, 26);
            this.textBoxBID.TabIndex = 15;
            // 
            // BidTxt
            // 
            this.BidTxt.AutoSize = true;
            this.BidTxt.Location = new System.Drawing.Point(43, 156);
            this.BidTxt.Name = "BidTxt";
            this.BidTxt.Size = new System.Drawing.Size(32, 20);
            this.BidTxt.TabIndex = 16;
            this.BidTxt.Text = "Bid";
            // 
            // dataGridView2
            // 
            this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView2.Location = new System.Drawing.Point(701, 65);
            this.dataGridView2.Name = "dataGridView2";
            this.dataGridView2.RowHeadersWidth = 62;
            this.dataGridView2.RowTemplate.Height = 28;
            this.dataGridView2.Size = new System.Drawing.Size(422, 406);
            this.dataGridView2.TabIndex = 17;
            this.dataGridView2.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView2_CellContentClick);
            // 
            // populate
            // 
            this.populate.Location = new System.Drawing.Point(837, 488);
            this.populate.Name = "populate";
            this.populate.Size = new System.Drawing.Size(137, 44);
            this.populate.TabIndex = 18;
            this.populate.Text = "Show loans";
            this.populate.UseVisualStyleBackColor = true;
            this.populate.Click += new System.EventHandler(this.populate_Click);
            // 
            // Previous1
            // 
            this.Previous1.Location = new System.Drawing.Point(701, 488);
            this.Previous1.Name = "Previous1";
            this.Previous1.Size = new System.Drawing.Size(118, 44);
            this.Previous1.TabIndex = 19;
            this.Previous1.Text = "Previous";
            this.Previous1.UseVisualStyleBackColor = true;
            this.Previous1.Click += new System.EventHandler(this.Previous1_Click);
            // 
            // Next1
            // 
            this.Next1.Location = new System.Drawing.Point(992, 488);
            this.Next1.Name = "Next1";
            this.Next1.Size = new System.Drawing.Size(131, 44);
            this.Next1.TabIndex = 20;
            this.Next1.Text = "Next";
            this.Next1.UseVisualStyleBackColor = true;
            this.Next1.Click += new System.EventHandler(this.Next1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(870, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(142, 20);
            this.label1.TabIndex = 21;
            this.label1.Text = "Customers(parent)";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(273, 46);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(95, 20);
            this.label2.TabIndex = 22;
            this.label2.Text = "Loans(child)";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1200, 578);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Next1);
            this.Controls.Add(this.Previous1);
            this.Controls.Add(this.populate);
            this.Controls.Add(this.dataGridView2);
            this.Controls.Add(this.BidTxt);
            this.Controls.Add(this.textBoxBID);
            this.Controls.Add(this.textBoxCID);
            this.Controls.Add(this.CidTxt);
            this.Controls.Add(this.Last);
            this.Controls.Add(this.Next);
            this.Controls.Add(this.Previous);
            this.Controls.Add(this.First);
            this.Controls.Add(this.connect);
            this.Controls.Add(this.textBoxLID);
            this.Controls.Add(this.LidTxt);
            this.Controls.Add(this.delete);
            this.Controls.Add(this.update);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.add);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            throw new NotImplementedException();
        }

        #endregion

        private System.Windows.Forms.Button add;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Button update;
        private System.Windows.Forms.Button delete;
        private System.Windows.Forms.Label LidTxt;
        private System.Windows.Forms.TextBox textBoxLID;
        private System.Windows.Forms.Button connect;
        private System.Windows.Forms.Button First;
        private System.Windows.Forms.Button Previous;
        private System.Windows.Forms.Button Next;
        private System.Windows.Forms.Button Last;
        private System.Windows.Forms.Label CidTxt;
        private System.Windows.Forms.TextBox textBoxCID;
        private System.Windows.Forms.TextBox textBoxBID;
        private System.Windows.Forms.Label BidTxt;
        private System.Windows.Forms.DataGridView dataGridView2;
        private Button populate;
        private Button Previous1;
        private Button Next1;
        private Label label1;
        private Label label2;
    }
}

