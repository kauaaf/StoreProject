#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "User.h"
#include "Item.h"
#include "ShoppingCart.h"

using namespace std;

int main()
{
    cout << "Welcome to the Store" << endl << endl;
    User ppl;
    //Item thing;
   
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
            if (!ppl.login(username, password)) {
                cout << "Login Not Successful, Try Again" << endl;

            }
            else {
                cout << "Login Successful" << endl;
                pass = 1;
                ShoppingCart cart(username);
            }
        }

        else if (option == "2") {
            cout << "Please Enter your Desired Username:\t";
            cin >> newUsername;
            cout << endl;
            cout << "Please Enter your Desired Password:\t";
            cin >> newPassword;
            cout << endl;
            if (!ppl.registerUser(newUsername, newPassword)) {
                cout << "There was an error, Try again" << endl;
            }
          else {
            cout << "Account Creation Succesfull, Proceed to Login" << endl;
          }
        }
        else {
            cout << "Not a valid option, Try again" << endl;
        }
       
        if (pass == 1) {
            while (pass == 1) {//Continue Menuing with the other options
                option2 = "";
                editOption = "";
                cardName, cardNumber, cardExp, cardCVV = "";
                address, city, state, zip = "";
                confirmPassword = "";
                cout << "Menu: " << endl;
                cout << "0. Exit" << endl;
                cout << "1. Logout" << endl;
                cout << "2. Catelog Search" << endl;
                cout << "3. Add Item From Catalog to Cart" << endl;
                cout << "4. Remove Item From Cart" << endl;
                cout << "5. Checkout" << endl;
                cout << "6. View Order History" << endl;
                cout << "7. Edit Account(Add/Edit Payment or Shipping Method)" << endl;
                cout << "8. Delete Account" << endl;

                cout << "Enter choice: ";
                cin >> option2;

                cout << endl;

                // exit
              
                if (option2 == "0")
                {
                    pass = -1;

                }
                else if (option2 == "1") {
                    pass = 0;
                }

                else if (option2 == "2") {
                  string itemSearch;
                  cout << "Enter the Category for your search(food, toys):\t" << endl;
                  cin >> itemSearch;
                  
                }
                else if (option2 == "3") {
                  string item_name ;
                  int item_amount ;
                  cout << "\t Enter the name of the Item you want to [ ADD TO CART ]:\t";
                  cin >> item_name;
                  cout << "\t Enter the amount :\t";
                  cin >> item_amount ;
                  if(!cart.addItem(item_name,item_amount)){ cout << "\t !OOPS! " << endl;}
                  else{ cout << "\t ADDED! " << endl;  }
                }
                else if (option2 == "4") {
                  if(cart.displayCart(username)){
                      cout << endl;
                      if(!cart.removeItem()){ cout << "\t OOPS!" << endl;}
                      else{ cout << "\t REMOVED! " << endl; }
                  }
                  else { cout << "\t ERROR! " << endl; }
                }
                else if (option2 == "5") {
                  if(!cart.checkout(username)){ cout << "\t Error!" << endl; }
                  else { cout << "\t CHECKOUT SUCCESSFULL ! " << endl;  }
                }
                else if (option2 == "6") {
                    ppl.getOrder(username);
                }
                else if (option2 == "7") {
                    cout << "\t0. Back (PRESS ANY OTHER KEY Then Enter TO GO BACK)" << endl;
                    cout << "\t1. Edit Payment" << endl;
                    cout << "\t2. Edit Shipping" << endl;
                    cout << "\t3. Add Payment" << endl;
                    cout << "\t4. Add Shipping" << endl;

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
                        if(!ppl.editPayment(username, cardName, cardNumber, cardExp, cardCVV)) {
                          cout << "There was an error, Please try again" << endl;
                        }
                        else {
                          cout << "Payment Changed Succesffuly" << endl;
                        }
                    }
                   if (editOption == "2") {
                        cout << "\t\tEnter Your Shipping Address (Just the street address):\t";
                        cin.ignore();
                        getline(cin, address);
                        cout << "\t\tEnter the City:\t";
                        cin >> city;
                        cout << "\t\tEnter the State (Abbreviation):\t";
                        cin >> state;
                        cout << "\t\tEnter the Zip Code:\t";
                        cin >> zip;
                        if(!ppl.editShipping(username, address, city, state, zip)) {
                           cout << "There was an error, Please try again" << endl;
                           
                        }
                        else {
                          cout << "Shipping Changed Succesffuly" << endl;
                        }
                    }
                  if (editOption == "3") {
                        cout << "\t\tEnter the Name on the Card:\t";
                        cin >> cardName;
                        cout << "\t\tEnter the Card Number:\t";
                        cin >> cardNumber;
                        cout << "\t\tEnter the Expiration (MM/DD):\t";
                        cin >> cardExp;
                        cout << "\t\tEnter the CVV:\t";
                        cin >> cardCVV;
                        if(!ppl.makePayment(username, cardName, cardNumber, cardExp, cardCVV)) {
                          cout << "There was an error, Please try again" << endl;
                        }
                        else {
                          cout << "Payment Method Added Succesffuly" << endl;                        }
                    }
                    if (editOption == "4") {
                        cout << "\t\tEnter Your Shipping Address (Just the street address):\t";
                        cin.ignore();
                        getline(cin, address);
                        cout << "\t\tEnter the City:\t";
                        cin >> city;
                        cout << "\t\tEnter the State (Abbreviation):\t";
                        cin >> state;
                        cout << "\t\tEnter the Zip Code:\t";
                        cin >> zip;
                        if(!ppl.makeShipping(username, address, city, state, zip)) {
                           cout << "There was an error, Please try again" << endl;
                        }
                        else {
                          cout << "Shipping Address Added" << endl;
                      }

                    }

                }
                else if (option2 == "8") {
                    cout << "\t\tTo Confirm, type your Password:\t" << endl;
                    cin >> confirmPassword;
                    if (password == confirmPassword) {
                        cout << "\t\tDeleting Account.." << endl;
                        if (!ppl.deleteAccount(username, password)) {
                          cout << "\t\t There was an error with the deletion, please try again" << endl;

                        }
                        else {
                            cout << "\t\t Account Deletion Succesfful!" << endl;
                            pass = 1;
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
