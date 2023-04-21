#pragma once
#include <string>

using namespace std;

class User {
private:
    string username;
    string password;

public:
    User();

    //Setters
    bool registerUser(string username, string password);
    bool editPayment(string username, string cardName, string cardNumber, string cardExpiration, string cardCVV);
    bool editShipping(string username, string address, string city, string state, string zip);
    bool editPayment(string username, string cardName, string cardNumber, string cardExpiration, string cardCVV);
    bool editShipping(string username, string address, string city, string state, string zip);

    //Getters
    bool login(string username, string password); 
    bool getPayment(string username);
    bool getShipping(string username);
    bool getOrder(string username);

    //Function
    bool deleteAccount(string username, string password);
};
