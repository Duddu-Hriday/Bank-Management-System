#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class customer
{
public:
    string name;
    string account_num;
    int amount;
    string phone_num;
    int password;
    string account_type;
    customer *next;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void linked_list_intialize(customer *main_cust)
{
    customer *temp_cust = main_cust;
    ifstream file("customer_data.txt");
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        int count = 0;
        string temp;
        string cust_info[6];
        while (getline(ss, temp, ','))
        {
            cust_info[count] = temp;
            count++;
        }

        temp_cust->name = cust_info[0];
        temp_cust->account_num = cust_info[1];
        temp_cust->amount = stoi(cust_info[2]);
        temp_cust->phone_num = cust_info[3];
        temp_cust->password = stoi(cust_info[4]);
        temp_cust->account_type = cust_info[5];
        temp_cust->next = new customer();
        temp_cust = temp_cust->next;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void print(customer *main_cust)
{
    customer *new_cust = main_cust;
    cout << "Name\tAcountNumber\tAmount\tphoneNumber\tpswd\taccountType" << endl;
    while (new_cust->next)
    {
        cout << new_cust->name << "\t" << new_cust->account_num << "\t" << new_cust->amount << "\t" << new_cust->phone_num << "\t" << new_cust->password << "\t" << new_cust->account_type << endl;
        new_cust = new_cust->next;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

customer *mid(customer *main_cust)
{
    if (main_cust == NULL || main_cust->next == NULL)
    {
        return main_cust;
    }
    customer *slow = main_cust;
    customer *fast = main_cust->next;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

customer *merge(customer *left, customer *right)
{
    if (left == NULL)
    {
        return right;
    }
    if (right == NULL)
    {
        return right;
    }
    customer *ans = new customer();
    ans->amount = -1;
    customer *temp = ans;
    while (left && right)
    {
        if (left->amount < right->amount)
        {
            temp->next = left;
            temp = left;
            left = left->next;
        }
        else
        {
            temp->next = right;
            temp = right;
            right = right->next;
        }
    }
    while (left)
    {
        temp->next = left;
        temp = left;
        left = left->next;
    }
    while (right)
    {
        temp->next = right;
        temp = right;
        right = right->next;
    }
    ans = ans->next;
    return ans;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

customer *mergesort(customer *main_cust)
{
    if (main_cust == NULL || main_cust->next == NULL)
    {
        return main_cust;
    }
    customer *temp = mid(main_cust);
    customer *left = main_cust;
    customer *right = temp->next;
    temp->next = NULL;
    left = mergesort(left);
    right = mergesort(right);
    customer *ans = merge(left, right);
    return ans;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void delete_cust(customer *main_cust, string acc_num)
{
    if (main_cust == NULL)
    {
        cout << "Data entered not found" << endl
             << endl;
        return;
    }
    if (main_cust->next == NULL && main_cust->account_num != acc_num)
    {
        cout << "Data entered not found" << endl
             << endl;
        return;
    }
    customer *temp_cust = main_cust;
    while (temp_cust->next->account_num != acc_num)
    {
        temp_cust = temp_cust->next;
        if (temp_cust == NULL)
        {
            cout << "Data entered not found" << endl
                 << endl;
            return;
        }
    }
    customer *del = temp_cust->next;
    temp_cust->next = temp_cust->next->next;
    delete del;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void data_entry(customer *main_cust)
{
    if (main_cust == NULL)
    {
        cout << "Data entered not found!!!!" << endl;
    }
    customer *temp = main_cust;
    ofstream myfile("customer_data.txt");
    while (temp->next)
    {
        myfile << temp->name << "," << temp->account_num << "," << temp->amount << "," << temp->phone_num << "," << temp->password << "," << temp->account_type << endl;
        temp = temp->next;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void edit_details(customer *main_cust, string acc_num)
{
    if (main_cust == NULL)
    {
        cout << "Data entered not found" << endl
             << endl;
        return;
    }
    customer *temp = main_cust;
    while (temp->account_num != acc_num)
    {
        temp = temp->next;
        if (temp == NULL)
        {
            cout << "Data entered not found" << endl
                 << endl;
            return;
        }
    }
    cout << "What would you like to edit" << endl
         << endl;
    cout << "1.Name               2.Phone Number" << endl
         << endl;
    cout << "3.Account Type       4.Exit" << endl
         << endl;
    int n;
    cin >> n;
    if (n == 1)
    {
        cout << "Enter the new name: ";
        cin >> temp->name;
    }
    else if (n == 2)
    {
        cout << "Enter the new phone number: ";
        cin >> temp->phone_num;
    }
    else if (n == 3)
    {
        cout << "Enter the new account type" << endl;
        cout << "1.Savings " << endl
             << "2.Checkings" << endl
             << "3.Investments" << endl;
        int m;
        cin >> m;
        if (m == 1)
        {
            temp->account_type = "Savings";
        }
        else if (m == 2)
        {
            temp->account_type = "Checkings";
        }
        else if (m == 3)
        {
            temp->account_type = "Investments";
        }
        else
        {
            cout << "Invalid choice!!!!!" << endl;
            return;
        }
    }
    else
    {
        cout << "Invalid choice!!!!!" << endl;
        return;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    string admin_id = "123";
    string admin_password = "123";
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "|                                                                               |" << endl;
    cout << "|                         Welcome to Our Bank                                   |" << endl;
    cout << "|                                                                               |" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl
         << endl
         << endl;
    cout << "              Enter the Admin Id: ";
    string id;
    string password;
    cin >> id;
    cout << "              Enter the password: ";
    cin >> password;
    if (id != admin_id || password != admin_password)
    {
        cout << "Incorrect id or password!!!!!!!!!!" << endl;
        return 0;
    }
    cout << "-----------------------------------------------" << endl;
    cout << "         |       Welcome Admin         |        " << endl;
    cout << "-----------------------------------------------" << endl;
    cout << endl
         << endl;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    while (true)
    {
        cout << "1.View Customers list                    2.View Transactions" << endl
             << endl;
        cout << "3.Sort Customers by balance amount       4.Delete Customer" << endl
             << endl;
        cout << "5.Edit Customer details                  6.Logout" << endl
             << endl;
        int n;
        cin >> n;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (n == 1)
        {
            customer *main_cust = new customer();
            customer *temp_cust = main_cust;
            linked_list_intialize(main_cust);
            print(main_cust);
            cout << endl
                 << endl
                 << endl;
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (n == 2)
        {
            ifstream myfile("transactions.txt");
            string data;
            while (getline(myfile, data))
            {
                cout << data << endl
                     << endl;
            }
        }
        else if (n == 3)
        {
            customer *main_cust = new customer();
            linked_list_intialize(main_cust);
            main_cust = mergesort(main_cust);
            print(main_cust);
            cout << endl
                 << endl;
        }
        else if (n == 4)
        {
            cout << "Enter the account number of the customer you would like to delete: ";
            string acc_num;
            cin >> acc_num;
            customer *main_cust = new customer();
            linked_list_intialize(main_cust);
            delete_cust(main_cust, acc_num);
            data_entry(main_cust);
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        else if (n == 5)
        {
            cout << "Enter the account number of the person to edit his/her details: ";
            string acc_num;
            cin >> acc_num;
            customer *main_cust = new customer();
            linked_list_intialize(main_cust);
            edit_details(main_cust, acc_num);
            data_entry(main_cust);
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (n == 6)
        {
            break;
        }
    }

    return 0;
}
