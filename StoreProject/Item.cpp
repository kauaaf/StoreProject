#include "Item.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Constructor that takes in name, category, price, and stock
Item::Item(string name, string category, double price, int stock)
    : name(name), price(price), stock(stock), category(category), amount(0) {}

// Constructor that takes in name, category, price, stock, and amount
Item::Item(string name, string category, double price, int stock, int amount)
    : name(name), price(price), stock(stock), category(category), amount(amount) {}

// Accessor for name
string Item::getName() const {
    return name;
}

// Accessor for category
string Item::getCategory() const {
    return category;
}

// Accessor for price
double Item::getPrice() const {
    return price;
}

// Accessor for stock
int Item::getStock() const {
    return stock;
}

// Accessor for amount
int Item::getAmount() const {
    return amount;
}

// Member function that prints out the info of an item
void Item::printInfo() const {
    cout << "Name: " << name << endl;
    cout << "Category: " << category << endl;
    cout << "Price: " << price << endl;
    cout << "Stock: " << stock << endl;
    cout << "Amount: " << amount << endl;
}
/*
bool Item::setStock(string name, int amount){
    // Open the stock.csv file for input and output
    fstream file("stock.csv", ios::in | ios::out);

    // Check if the file was opened successfully
    if (!file.is_open()) {
        cout << "Failed to open stock.csv" << endl;
        return false;
    }

    // Read and process each line of the file
    string line;
    vector<string> lines;
    bool item_found = false;
    while (getline(file, line)) {
        // Split the line into fields
        stringstream ss(line);
        string item_name;
        int item_stock;
        getline(ss, item_name, ',');
        ss >> item_stock;

        // Update the stock if the item name matches
        if (item_name == name) {
            item_stock = amount;
            item_found = true;
            // Move the get pointer to the beginning of the line
            file.seekg(-(line.length() + 1), ios::cur);
            // Write the updated line to the file
            file << item_name << "," << item_stock << endl;
        }

        // Store the line in a vector
        lines.push_back(line);
    }

    // Item not found in the file
    if (!item_found) {
        cout << "Item not found in stock.csv" << endl;
        return false;
    }

    // Truncate the file by writing an empty string at the current position
    file.seekp(0, ios::end);
    file.seekp(file.tellp() - 1);
    file << "";

    // Write the remaining lines back to the file
    file.seekp(0, ios::end);
    for (const string& line : lines) {
        if (line != "") {
            file << line << endl;
        }
    }

    file.close();

    return true;
}

*/

void Item::viewCategory(string category) {
    // Open the stock.csv file
    ifstream file("stock.csv");
    if (!file) {
        cout << "Error: stock.csv could not be opened." << endl;
        return;
    }

    // Parse through the file to find the items with matching category
    string line;
    vector<string> row;
    cout << "Items in category \"" << category << "\":" << endl;
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        if (row[1] == category) {
            // Display the item information
            cout << row[0] << " (" << row[2] << " in stock, $" << row[3] << ")" << endl;
        }
        row.clear();
    }
    file.close();
}
