#pragma once
#include <string>

using namespace std;

class User {
private:
    string username;
    string password;

public:
    User();
    bool registerUser(string username, string password);
    bool login(string username, string password);
    bool editPayment(string username, string cardName, string cardNumber, string cardExpiration, string cardCVV);
    bool editShipping(string username, string address, string city, string state, string zip);
    bool getPayment(string username);
    bool getShipping(string username);
    bool getOrder(string username);
    bool deleteAccount(string username, string password);
};
