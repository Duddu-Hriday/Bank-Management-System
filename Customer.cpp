#include <iostream>
#include <fstream>
#include <sstream>
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

void replacer(customer *main_cust, string accountNumber, int money)
{
    if (main_cust == NULL)
    {
        cout << "Data does not exist";
        return;
    }
    customer *temp = main_cust;
    while (temp->account_num != accountNumber)
    {
        temp = temp->next;
        if (temp == NULL)
        {
            cout << "Data does not exist";
            return;
        }
    }
    temp->amount -= money;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void data_entry(customer *main_cust)
{
    customer *temp = main_cust;
    ofstream myfile("customer_data.txt");
    while (temp->next)
    {
        myfile << temp->name << "," << temp->account_num << "," << temp->amount << "," << temp->phone_num << "," << temp->password << "," << temp->account_type << endl;
        temp = temp->next;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void transfer_entry(string acc1, string acc2, int money)
{
    ofstream myfile("transactions.txt", ios::app);
    myfile << acc1 << "," << acc2 << "," << money << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void money_transfer(customer *main_cust, string debit, string credit, int money)
{
    customer *cred = main_cust;
    customer *deb = main_cust;
    while (cred->account_num != credit)
    {
        cred = cred->next;
        if (cred == NULL)
        {
            cout << "invalid Credentials";
            return;
        }
    }
    while (deb->account_num != debit)
    {
        deb = deb->next;
        if (deb == NULL)
        {
            cout << "Invalid credentials" << endl;
            return;
        }
    }
    cred->amount = cred->amount + money;
    deb->amount = deb->amount - money;
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
string acc_num(customer* main_cust)
{
    if (main_cust == NULL)
    {
        return "94906310001";
    }

    customer* temp_cust = main_cust;
    while (temp_cust->next->next)
    {
        temp_cust = temp_cust->next;
    }

    string str = temp_cust->account_num;

    string sub = str.substr(7, 4);
    int num = stoi(sub) + 1;
    string numstr=to_string(num);
    if(numstr.length()==1)
    {
        numstr="000"+numstr;
    }
    else if(numstr.length()==2)
    {
        numstr="00"+numstr;
    }
    else if(numstr.length()==3)
    {
        numstr="0"+numstr;
    }
    return "9490631" + numstr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "|                                                                               |" << endl;
    cout << "|                         Welcome to Our Bank                                   |" << endl;
    cout << "|                         Hyderabad Branch                                      |" << endl;
    cout << "|                         Bank Code:9490                                        |" << endl;
    cout << "|                         Branch Code:631                                       |" << endl;
    cout << "|                                                                               |" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl
         << endl
         << endl;

    cout << "Press 1, if you are an existing user" << endl;
    cout << "Press 2, if you want to open an account" << endl;
    int ch;
    cin >> ch;
    customer *temp_cust = new customer();
    if (ch == 1)
    {
        cout << "Please enter your account details as specified below" << endl
             << endl;
        cout << "Account Number: ";
        string acc_num;
        int acc_password;
        cin >> acc_num;
        cout << endl
             << endl
             << "4-digit Password: ";
        cin >> acc_password;
        customer *main_cust = new customer();
        temp_cust = main_cust;
        linked_list_intialize(main_cust);
        while (temp_cust->account_num != acc_num && temp_cust->password != acc_password)
        {
            temp_cust = temp_cust->next;
            if (temp_cust == NULL)
            {
                cout << "Incorrect Account Number or Password ";
                cout << endl
                     << endl;
                return 0;
            }
        }
        cout << endl
             << endl;
        cout << "Welcome " << temp_cust->name << endl
             << endl;
        cout << "What can we do for you? " << endl
             << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "|1.Withdraw Money       |          2.Check Balance amount|" << endl;
        cout << "|--------------------------------------------------------|" << endl;
        cout << "|3.Make a transfer      |          4.View Details        |" << endl;
        cout << "|--------------------------------------------------------|" << endl;
        cout << "|5.Edit Details         |          6. Logout             |" << endl;
        cout << "---------------------------------------------------------" << endl
             << endl;
    }
    if (ch == 2)
    {
        ofstream myfile("customer_data.txt", ios::app);
        customer *cust = new customer();
        cout << "Enter your name: ";
        cin >> cust->name;
        cout << endl
             << endl;
        cout << "Which account would you like to open? " << endl;
        cout << "1. Savings" << endl
             << "2.Checkings " << endl
             << "3.Investments " << endl;
        int ac;
        cin >> ac;
        while (ac != 1 && ac != 2 && ac != 3)
        {
            cout << "Wrong choice entered..Try again";
            cin >> ac;
        }
        if (ac == 1)
        {
            cust->account_type = "Savings";
        }
        if (ac == 2)
        {
            cust->account_type = "Checkings";
        }
        if (ac == 3)
        {
            cust->account_type = "Investments";
        }
        cout << endl
             << endl;
        cin.clear();
        cout << "Enter your phone number: ";
        cin >> cust->phone_num;
        cout << endl
             << endl;
        cin.clear();
        cout << "Enter the 4 digit password you want to set: ";
        cin >> cust->password;
        cout << endl
             << endl;
        cout << "How much amount would you like to keep in this account? ";
        cin >> cust->amount;
        cout << endl
             << endl;
             customer*main_cust=new customer();
             linked_list_intialize(main_cust);
             cust->account_num=acc_num(main_cust);
        myfile << cust->name << "," << cust->account_num << "," << cust->amount << "," << cust->phone_num << "," << cust->password << "," << cust->account_type << endl;

        cout << "Hello there " << cust->name <<". Your Account Number is: "<<cust->account_num<<" .What can we do for you?";
        cout << endl
             << endl;
        temp_cust = cust;
        cout << "---------------------------------------------------------" << endl;
        cout << "|1.Withdraw Money       |          2.Check Balance amount|" << endl;
        cout << "|--------------------------------------------------------|" << endl;
        cout << "|3.Make a transfer      |          4.View Details        |" << endl;
        cout << "|--------------------------------------------------------|" << endl;
        cout << "|5.Edit Details         |          6. Logout             |" << endl;
        cout << "---------------------------------------------------------" << endl
             << endl;
    }
    int choice;
    cout << "Enter your choice: " << endl;
    cin >> choice;
    if (choice == 1)
    {
        int money;
        cout << "Enter the amount of money you would like to withdraw: ";
        cin >> money;
        if (money > temp_cust->amount)
        {
            cout << "No enough money in your account..Try again";
            return 0;
        }
        // temp_cust->amount=temp_cust->amount-money;
        customer *main_cust = new customer();
        linked_list_intialize(main_cust);
        replacer(main_cust, temp_cust->account_num, money);
        data_entry(main_cust);
        cout << "Money withdraw Successful" << endl
             << endl;
        cout << "-------------------------" << endl;
        cout << "|Thank you :) Visit Again|" << endl;
        cout << "-------------------------" << endl;

        // cout<<temp_cust->amount;
    }
    if (choice == 2)
    {
        cout << "Your account balance is Rs." << temp_cust->amount << endl
             << endl;
    }
    if (choice == 3)
    {
        cout << "Enter the account number of the person you would like to transfer money: ";
        string acc_num;
        int money;
        cin >> acc_num;
        cout << endl
             << endl;
        cout << "Enter the amount of money you would like to transfer: ";
        cin >> money;
        if (money > temp_cust->amount)
        {
            cout << "No Enough Balance" << endl;
            return 0;
        }
        customer *main_cust = new customer();
        linked_list_intialize(main_cust);
        money_transfer(main_cust, temp_cust->account_num, acc_num, money);
        data_entry(main_cust);
        transfer_entry(temp_cust->account_num, acc_num, money);
        cout << endl
             << "Money Transfer Successful" << endl
             << endl;
        cout << "Thank you :) Visit Again" << endl;
    }
    if (choice == 4)
    {
        cout << "Your Details are as follows" << endl
             << endl;
        cout << "Name: " << temp_cust->name << endl
             << endl;
        cout << "Account Number: " << temp_cust->account_num << endl
             << endl;
        cout << "Account Type: " << temp_cust->account_type << endl
             << endl;
        cout << "Phone Number: " << temp_cust->phone_num << endl
             << endl;
    }
    if (choice == 5)
    {
        customer *main_cust = new customer();
        linked_list_intialize(main_cust);
        edit_details(main_cust, temp_cust->account_num);
        data_entry(main_cust);
    }
    if (choice == 6)
    {
        cout << "Logout Successful.." << endl;
        cout << "Thank you :) Visit Again" << endl;
    }

    return 0;
}
