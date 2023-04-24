#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "User.h"

using namespace std;

int main()
{
    cout << "Welcome to Store" << endl << endl;
    User ppl;
   
    while (1)
    {
        int pass = 0;
        string option;
        string newUsername = "";
        string newPassword = "";
        string username = "";
        string password = "";
        // displays menu
        cout << "Menu: " << endl;
        cout << "0. Exit" << endl;
        cout << "1. Login" << endl;
        cout << "2. Create Account" << endl;
        cout << "Enter choice: ";
        cin >> option;

        cout << endl;

        // exit
        if (option == "0")
        {
            pass = -1;
            break;
        }

        if (option == "1") {
            cout << "Please Enter your Username:\t";
            cin >> username;
            cout << endl;
            cout << "Please Enter your Password:\t";
            cin >> password;
            cout << endl;
            if (ppl.login(username, password)) {
                cout << "Login Successful" << endl;
                pass = 1;
            }
            else {
                cout << "Login Not Successful, Try Again" << endl;
            }
        }

        if (option == "2") {
            cout << "Please Enter your Desired Username:\t";
            cin >> newUsername;
            cout << endl;
            cout << "Please Enter your Desired Password:\t";
            cin >> newPassword;
            cout << endl;
            if (ppl.registerUser(newUsername, newPassword)) {
                cout << "Account Creation Succesfull, Proceed to Login" << endl;
            }
        }
        if (pass == 1) {
            //Continue Menuing with the other options
        }
        if (pass == -1) {
            break;
        }
        cout << endl;
    }

    return 0;
}
