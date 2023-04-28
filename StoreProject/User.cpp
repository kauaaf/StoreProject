#include "User.h"
#include <string> 
#include <fstream>
#include <iostream>
#include <vector> 

User::User() {
    username = "";
    password = "";
}

/*
    The overall workings of the login() function was commented in details for each part.
    Other functions that are performing similar tasks will follow approximately the same procedure,
    to avoid over-commenting, these other functions won't be commented in the same places.
*/
bool User::login(string username, string password) {
    ifstream inFile("login.csv"); //Opens file

    //Standard error handler
    if (!inFile.is_open()) {
        cerr << "Error: Could not open file" << endl;
        return false;
    }
    string line;
    while (getline(inFile, line)) {   //Loop will parse through words until it finds a comma
        size_t comma = line.find(',');  //That's the only way I come up to find the comma
        if (comma != string::npos) {    //string::npos is assigned to comma if the comma is not found in the line
            string file_username = line.substr(0, comma);   //Stores the left-hand side of the comma
            string file_password = line.substr(comma + 1);  //Stores the right-hand side of the comma
            if (file_username == username && file_password == password) {   //Checks if the line contains parameters passed
                inFile.close();
                return true;
            }
        }
    }
    inFile.close();
    return false;
}

/*
    The workings of the redisterUser consists in a while loop similar to the one above. 
*/
bool User::registerUser(string username, string password) {
    ifstream inFile;
    inFile.open("login.csv");
    string line;
    while (getline(inFile, line)) { //This loop checks if username is already being used.
        size_t pos = line.find(",");
        string existingUsername = line.substr(0, pos);
        if (existingUsername == username) {
            cout << "Username already in use. Try another" << endl;
            inFile.close();
            return false;   //Returns false if the username already exists in the login.csv file
        }
    }
    inFile.close();

    //If username is not already in use, then the function will simply ofstream the username, password to the file.
    ofstream outFile;
    outFile.open("login.csv", ios::app);
    if (outFile.is_open()) {
        outFile << username << "," << password << endl;
        outFile.close();
        return true;
    }
    return false;
}

bool User::editPayment(string username, string cardName, string cardNumber, string cardExpiration, string cardCVV) {
    ifstream inFile("payment.csv");

    //Standard error handler
    if (!inFile.is_open()) {
        return false;
    }

    vector<string> lines;   //Uses a vector to store data pulled from file
    string line;
    bool found = false;

    while (getline(inFile, line)) {   //This while loop works the same way as the login, except that it pushes the line to the vector
        size_t comma = line.find(',');
        if (comma != string::npos) {
            string file_username = line.substr(0, comma);
            if (file_username == username) {
                line = username + "," + cardName + "," + cardNumber + "," + cardExpiration + "," + cardCVV;
                found = true;
            }
        }
        lines.push_back(line);
    }
    inFile.close();

    if (found) {
        ofstream outFile("payment.csv");    //Re-opens file in ofstream mode to ofstream contents of vector to file

        //Standard error handler
        if (!outFile.is_open()) {
            return false;
        }
        for (const string& line : lines) {  //Ofstreams contents of the vector to the file
            outFile << line << "\n";
        }
        outFile.close();    //Closes file
        return true;
    }
    else {
        return false;
    }
}

//The implementation of editShipping() is the same as editPayment(), but with parameters being different
bool User::editShipping(string username, string address, string city, string state, string zip) {
    ifstream inFile("shipping.csv");

    //Standard error handler
    if (!inFile.is_open()) {
        return false;
    }

    vector<string> lines;   //Uses a vector to store data pulled from file
    string line;
    bool found = false;

    while (getline(inFile, line)) { //This while loop works the same way as the login, except that it pushes the line to the vector
        size_t comma = line.find(',');
        if (comma != string::npos) {
            string file_username = line.substr(0, comma);
            if (file_username == username) {
                line = username + "," + address + "," + city + "," + state + "," + zip;
                found = true;
            }
        }
        lines.push_back(line);
    }
    inFile.close();

    if (found) {
        ofstream outFile("shipping.csv");   //Re-opens file in ofstream mode to ofstream contents of vector to file

        //Standard error handler
        if (!outFile.is_open()) {   
            return false;
        }
        for (const string& line : lines) {  //Ofstreams contents of the vector to the file
            outFile << line << "\n";
        }
        outFile.close();
        return true;
    }
    else {
        return false;
    }
}

/* 
    The implementation of the get functions are essentially the same, the only difference the data being displayed and file opened.
    For the sake of simplicity, only getPayment() will be commented out in depth.
*/
bool User::getPayment(string username) {
    ifstream file("payment.csv"); //Opens file in ifstream mode to retrieve data
    if (!file.is_open()) {  //Standard error handler
        return false;
    }

    string line;
    while (getline(file, line)) {   //Loop will parse through words until it finds a comma
        size_t comma = line.find(',');  //line.find() will assign either an index or npos to comma
        if (comma != string::npos) {
            string file_username = line.substr(0, comma); //Stores the left-hand side of the comma  
            if (file_username == username) { //Checks if the username in the file is the same as the parameter
                cout << line << endl;   //Cout contents of the line as it is in the file
                file.close();   //Close file
                return true;
            }
        }
    }
    file.close();   //Close file
    return false;
}

bool User::getShipping(string username) {   //See getPayment() comment for reference
    ifstream file("shipping.csv"); 
    if (!file.is_open()) {
        return false;
    }

    string line;
    while (getline(file, line)) {
        size_t comma = line.find(',');
        if (comma != string::npos) {
            string file_username = line.substr(0, comma);
            if (file_username == username) {
                cout << line << endl;
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}

bool User::getOrder(string username) {  //See getPayment() comment for reference
    ifstream file("order.csv");
    if (!file.is_open()) {
        return false;
    }

    string line;
    while (getline(file, line)) {
        size_t comma = line.find(',');
        if (comma != string::npos) {
            string file_username = line.substr(0, comma);
            if (file_username == username) {
                cout << line << endl;
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}


bool User::deleteAccount(string username, string password) {
    ifstream loginFile("login.csv");
    if (!loginFile.is_open()) {
        return false;
    }

    //Acts exactly like the login function. Could've used the login() itself, but it's better to not mix these two together.
    bool authenticated = false; //If false, the the rest of the deleting process stops.
    string line;
    while (getline(loginFile, line)) { //This will loop through the file, and it username and password matches, then continue with the deleting process.
        size_t comma = line.find(',');
        if (comma != string::npos) {
            string file_username = line.substr(0, comma);
            string file_password = line.substr(comma + 1);
            if (file_username == username && file_password == password) {
                authenticated = true;
                break;
            }
        }
    }
    loginFile.close();

    if (!authenticated) {   //This quits the function if the authentication process is false.
        return false;
    }

    /*
        The loop bellow works the following way: the vector filenames stores the filenames, and the for loop will loop through these files.
        Each interaction of the loop will open a different file, and since the procedure to delete is the same for all the files,
        (open in ifstream, find username, psuhback lines where username is different from paramter to vector, then ofstream vector to file) 
        it's possible to use a loop like the one bellow.
    */
    vector<string> filenames = { "payment.csv", "shipping.csv", "order.csv", "login.csv" };
    for (const string& filename : filenames) {
        ifstream inFile(filename);
        if (!inFile.is_open()) {    //Standard error handler
            return false;
        }

        line.clear();   //Clears content of line before using the variable again
        vector<string> lines; //Stores lines to be ofstreamed to file
        while (getline(inFile, line)) {
            size_t comma = line.find(',');
            if (comma != string::npos) {
                string file_username = line.substr(0, comma);   //Stores left-hand side of the comma
                if (file_username != username) {    //Instead of checking for equal, the loop pushes back only lines that doesn't contain the username passed, thus deleting it from the file when the vector is ofstreamed
                    lines.push_back(line);
                }
            }
        }
        inFile.close();

        ofstream outFile(filename); //Opens file for ofstream
        if (!outFile.is_open()) {
            return false;
        }
        for (const string& line : lines) {  //Ofstreams the line to the file.
            outFile << line << "\n";
        }
        outFile.close();    //Closes file
    }
    return true;
}


/*
    Both the function bellow work the same way, only the file and parameters being written are different.
    So comments are the same for each respective place.
*/
bool User::makePayment(string username, string cardName, string cardNumber, string cardExpiration, string cardCVV) {
    ofstream outFile;  
    outFile.open("payment.csv", ios::app); //Opens file in ofstream mode
    if (!outFile.is_open()) {   //Default error handler
        return false;
    }
    outFile << username << "," << cardName << "," << cardNumber << "," << cardExpiration << "," << cardCVV << endl; //Write information to file
    outFile.close();    //Closes file
    return true;
}

bool User::makeShipping(string username, string address, string city, string state, string zip) {
    ofstream outFile;
    outFile.open("shipping.csv", ios::app);
    if (!outFile.is_open()) {
        return false;
    }
    outFile << username << "," << address << "," << city << "," << state << "," << zip << endl;
    outFile.close();
    return true;
}
