#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

class Account {
public:
    int accNo;
    char name[50];
    float balance;

    void create() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void display() {
        cout << "\nAccount No: " << accNo;
        cout << "\nName: " << name;
        cout << "\nBalance: " << balance << endl;
    }
};

void createAccount() {
    Account a;
    ofstream file("bank.txt", ios::app);
    a.create();
    file << a.accNo << " " << a.name << " " << a.balance << endl;
    file.close();
    cout << "Account Created!\n";
}

void displayAll() {
    Account a;
    ifstream file("bank.txt");

    while (file >> a.accNo >> a.name >> a.balance) {
        a.display();
    }
    file.close();
}

void searchAccount() {
    int no, found = 0;
    Account a;
    ifstream file("bank.txt");

    cout << "Enter Account Number: ";
    cin >> no;

    while (file >> a.accNo >> a.name >> a.balance) {
        if (a.accNo == no) {
            a.display();
            found = 1;
        }
    }

    if (!found)
        cout << "Account Not Found!\n";

    file.close();
}

void depositMoney() {
    int no;
    float amt;
    Account a;
    ifstream file("bank.txt");
    ofstream temp("temp.txt");

    cout << "Enter Account Number: ";
    cin >> no;
    cout << "Enter Amount to Deposit: ";
    cin >> amt;

    while (file >> a.accNo >> a.name >> a.balance) {
        if (a.accNo == no) {
            a.balance += amt;
            cout << "Deposit Successful!\n";
        }
        temp << a.accNo << " " << a.name << " " << a.balance << endl;
    }

    file.close();
    temp.close();
    remove("bank.txt");
    rename("temp.txt", "bank.txt");
}

void withdrawMoney() {
    int no;
    float amt;
    Account a;
    ifstream file("bank.txt");
    ofstream temp("temp.txt");

    cout << "Enter Account Number: ";
    cin >> no;
    cout << "Enter Amount to Withdraw: ";
    cin >> amt;

    while (file >> a.accNo >> a.name >> a.balance) {
        if (a.accNo == no) {
            if (a.balance >= amt) {
                a.balance -= amt;
                cout << "Withdraw Successful!\n";
            } else {
                cout << "Insufficient Balance!\n";
            }
        }
        temp << a.accNo << " " << a.name << " " << a.balance << endl;
    }

    file.close();
    temp.close();
    remove("bank.txt");
    rename("temp.txt", "bank.txt");
}

void deleteAccount() {
    int no;
    Account a;
    ifstream file("bank.txt");
    ofstream temp("temp.txt");

    cout << "Enter Account Number to Delete: ";
    cin >> no;

    while (file >> a.accNo >> a.name >> a.balance) {
        if (a.accNo != no) {
            temp << a.accNo << " " << a.name << " " << a.balance << endl;
        }
    }

    file.close();
    temp.close();
    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    cout << "Account Deleted!\n";
}

int main() {
    int choice;

    do {
        cout << "\n--- Bank Management System ---\n";
        cout << "1. Create Account\n";
        cout << "2. Display All\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit\n";
        cout << "5. Withdraw\n";
        cout << "6. Delete Account\n";
        cout << "7. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: displayAll(); break;
            case 3: searchAccount(); break;
            case 4: depositMoney(); break;
            case 5: withdrawMoney(); break;
            case 6: deleteAccount(); break;
            case 7: cout << "Exit...\n"; break;
            default: cout << "Invalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}
