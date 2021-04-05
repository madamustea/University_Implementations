using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
namespace DBMSL1
{
    public partial class Form1 : Form
    {
        SqlConnection cs = new SqlConnection("Data Source = DESKTOP-DG5FBLD\\SQLEXPRESS;Initial Catalog=Library;Integrated Security=True");
        SqlDataAdapter da = new SqlDataAdapter();
        DataSet ds = new DataSet();
        DataSet ds1 = new DataSet();
        BindingSource bs = new BindingSource();
        BindingSource bs1 = new BindingSource();
       
        public Form1()
        {
            InitializeComponent();
        }
        private void dataGridViewUpdate()
        {
            dataGridView1.ClearSelection();
            dataGridView1.Rows[bs.Position].Selected = true;
            
        }

        private void dataGridViewUpdate1()
        {
            dataGridView2.ClearSelection();
            dataGridView2.Rows[bs1.Position].Selected = true;

        }
        private void populateLoans()
        {   
           da.SelectCommand = new SqlCommand("SELECT * FROM Loan", cs);
            ds.Clear();
            da.Fill(ds);
            dataGridView1.DataSource = ds.Tables[0];
        }
        private void populateCostumer()
        {
            da.SelectCommand = new SqlCommand("SELECT* FROM Customer", cs);
            ds1.Clear();
            da.Fill(ds1);
            dataGridView2.DataSource = ds1.Tables[0];
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                da.InsertCommand = new SqlCommand("INSERT INTO Loan (LID,CID,BID) VALUES(@l,@c,@b)", cs);
                da.InsertCommand.Parameters.Add("@l", SqlDbType.Int).Value= Int32.Parse(textBoxLID.Text);
                da.InsertCommand.Parameters.Add("@c", SqlDbType.Int).Value= Int32.Parse(textBoxCID.Text);
                da.InsertCommand.Parameters.Add("@b", SqlDbType.Int).Value= Int32.Parse(textBoxBID.Text);
                cs.Open();
                da.InsertCommand.ExecuteNonQuery();
                MessageBox.Show("Inserted succesfull to the database");
                cs.Close();
                populateLoans();

            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
                cs.Close();
            }
           
        }

        

        private void update_Click(object sender, EventArgs e)
        {
            
                int x;
            try
            {
                da.UpdateCommand = new SqlCommand("Update Loan set LID = @l, CID = @c, BID = @b where LOANID = @id", cs);
               
                da.UpdateCommand.Parameters.Add("@l",
               SqlDbType.VarChar).Value = textBoxLID.Text;
                da.UpdateCommand.Parameters.Add("@c",
               SqlDbType.VarChar).Value = textBoxCID.Text;
                da.UpdateCommand.Parameters.Add("@b",
             SqlDbType.VarChar).Value = textBoxBID.Text;
                da.UpdateCommand.Parameters.Add("@id",
               SqlDbType.Int).Value = ds.Tables[0].Rows[bs.Position][0];

                cs.Open();
                x = da.UpdateCommand.ExecuteNonQuery();
            
            cs.Close();
                if (x >= 1)
                {
                    MessageBox.Show("The record has been updated");
               
                }
            populateLoans();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                cs.Close();
            }


        }

        private void delete_Click(object sender, EventArgs e)
        {
            try
            {
                DialogResult dr;
                dr = MessageBox.Show("Are you sure?\n No undo after delete", "Confirm Deletion", MessageBoxButtons.YesNo);
                if (dr == DialogResult.Yes)
                {
                    da.DeleteCommand = new SqlCommand("Delete from Loan where LOANID = @id", cs);


                    da.DeleteCommand.Parameters.Add("@id", SqlDbType.Int).Value = ds.Tables[0].Rows[bs.Position][0];
                    cs.Open();
                    da.DeleteCommand.ExecuteNonQuery();

                    cs.Close();
                    populateLoans();

                }
                else
                {
                    MessageBox.Show("Deletion Aborded");

                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                cs.Close();
            }
        }

            private void Connect_Click(object sender, EventArgs e)
        {
            da.SelectCommand = new SqlCommand("SELECT* FROM Loan", cs);
            ds.Clear();
            da.Fill(ds);
            dataGridView1.DataSource = ds.Tables[0];
            bs.DataSource = ds.Tables[0];

            textBoxLID.DataBindings.Add("Text", bs, "LID");
            textBoxCID.DataBindings.Add("Text", bs, "CID");
            textBoxBID.DataBindings.Add("Text", bs, "BID");

            da.SelectCommand = new SqlCommand("SELECT* FROM Customer", cs);
            ds1.Clear();
            da.Fill(ds1);
            dataGridView2.DataSource = ds1.Tables[0];
            bs1.DataSource = ds1.Tables[0];


        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void First_Click(object sender, EventArgs e)
        {
            bs.MoveFirst();
            dataGridViewUpdate();
        }

        private void Previous_Click(object sender, EventArgs e)
        {
            bs.MovePrevious();
            dataGridViewUpdate();
        }

        private void Next_Click(object sender, EventArgs e)
        {
            
                bs.MoveNext();
                dataGridViewUpdate();


        }

        private void Last_Click(object sender, EventArgs e)
        {
            bs.MoveLast();
            dataGridViewUpdate();


        }

        private void populate_Click(object sender, EventArgs e)
        {
            try { 
            da.SelectCommand = new SqlCommand("SELECT* FROM Loan WHERE CID=@id", cs);
            da.SelectCommand.Parameters.Add("@id", SqlDbType.Int).Value = ds1.Tables[0].Rows[bs1.Position][0];
            cs.Open();
            da.SelectCommand.ExecuteNonQuery();
            cs.Close();
            ds.Clear();
            da.Fill(ds);
            dataGridView1.DataSource = ds.Tables[0];
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                cs.Close();
            }

        }

        private void Previous1_Click(object sender, EventArgs e)
        {

            bs1.MovePrevious();
            dataGridViewUpdate1();
        }

        private void Next1_Click(object sender, EventArgs e)
        {
            bs1.MoveNext();
            dataGridViewUpdate1();
        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
