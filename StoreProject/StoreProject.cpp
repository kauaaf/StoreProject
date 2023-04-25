#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "User.h"

using namespace std;

int main()
{
    cout << "Welcome to the Store" << endl << endl;
    User ppl;
   
    while (1)
    {
        int pass = 0;
        string option = "";
        string option2 = "";
        string newUsername = "";
        string newPassword = "";
        string username = "";
        string password = "";
        string editOption = "";
        string cardName, cardNumber, cardExp, cardCVV = "";
        string address, city, state, zip = "";
        string confirmPassword = "";
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
        else {
            cout << "Not a valid option, Try again" << endl;
        }
        if (pass == 1) {
            while (pass == 1) {//Continue Menuing with the other options
                option2 = 0;
                editOption = "";
                cardName, cardNumber, cardExp, cardCVV = "";
                address, city, state, zip = "";
                confirmPassword = "";
                cout << "Menu: " << endl;
                cout << "0. Exit" << endl;
                cout << "1. Logout" << endl;
                cout << "3. Catelog Search" << endl;
                cout << "4. Add Item From Catalog to Cart" << endl;
                cout << "5. Remove Item From Cart" << endl;
                cout << "6. Checkout" << endl;
                cout << "7. View Order History" << endl;
                cout << "8. Edit Account" << endl;
                cout << "9. Delete Account" << endl;

                cout << "Enter choice: ";
                cin >> option2;

                cout << endl;

                // exit
                if (option2 == "0")
                {
                    pass = -1;

                }
                if (option2 == "1") {
                    pass = 1;
                }
                if (option2 == "2") {

                }
                if (option2 == "3") {

                }
                if (option2 == "4") {

                }
                if (option2 == "5") {

                }
                if (option2 == "6") {

                }
                if (option2 == "7") {
                    ppl.getOrder(username);
                }
                if (option2 == "8") {
                    cout << "\t0. Back (PRESS ANY OTHER KEY TO GO BACK)" << endl;
                    cout << "\t1. Edit Payment" << endl;
                    cout << "\t2. Edit Shipping" << endl;

                    cin >> editOption;

                    if (editOption == "1") {
                        cout << "\t\tEnter the Name on the Card:\t";
                        cin >> cardName;
                        cout << "\t\tEnter the Card Number:\t";
                        cin >> cardNumber;
                        cout << "\t\tEnter the Expiration (MM/DD):\t";
                        cin >> cardExp;
                        cout << "\t\tEnter the CVV:\t";
                        cin >> cardCVV;
                        ppl.editPayment(username, cardName, cardNumber, cardExp, cardCVV);
                    }
                    if (editOption == "2") {
                        cout << "\t\tEnter Your Shipping Address (Just the street address):\t";
                        cin >> address;
                        cout << "\t\tEnter the City:\t";
                        cin >> city;
                        cout << "\t\tEnter the State (Abbreviation):\t";
                        cin >> state;
                        cout << "\t\tEnter the Zip Code:\t";
                        cin >> zip;
                        ppl.editShipping(username, address, city, state, zip);
                    }

                }
                if (option2 == "9") {
                    cout << "\t\tTo Confirm, type your Password:\t" << endl;
                    cin >> confirmPassword;
                    if (password == confirmPassword) {
                        cout << "\t\tDeleting Account.." << endl;
                        if (ppl.deleteAccount(username, password)) {
                            cout << "\t\t Account Deletion Succesfful!" << endl;
                            pass == 1;
                        }
                        else {
                            cout << "\t\t There was an error with the deletion, please try again" << endl;
                        }

                    }

                }
                else {
                    cout << "Not a valid option, Try again" << endl;
                }
            }
        }
        if (pass == -1) {
            break;
        }
    cout << endl;
        
    }

    return 0;
}
