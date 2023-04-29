#include "ShoppingCart.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool ShoppingCart::addItem(std::string name, int amount) {
    // Look for item in stock.csv
    std::ifstream file("stock.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open file: stock.csv" << std::endl;
        return false;
    }

    std::string line;
    bool found = false;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item_name, category;
        double price;
        int stock;

        std::getline(ss, item_name, ',');
        std::getline(ss, category, ',');
        ss >> price >> stock;

        if (item_name == name) {
            // Item found in stock.csv, check if stock is sufficient
            if (amount <= stock) {
                cart.push_back(Item(name, category, price, stock, amount));
                found = true;
            } else {
                std::cerr << "Insufficient stock for " << name << std::endl;
            }
            break;
        }
    }

    if (!found) {
        std::cerr << "Item not found in stock.csv: " << name << std::endl;
        return false;
    }

    return true;
}

bool ShoppingCart::removeItem(std::string name) {
    for (auto it = cart.begin(); it != cart.end(); ++it) {
        if (it->getName() == name) {
            cart.erase(it);
            return true;
        }
    }
    std::cout << "Item not found in cart: " << name << std::endl;
    return false;
}

bool ShoppingCart::displayCart(string username) {
    if (cart.empty()) {
        std::cout << "Cart is empty" << std::endl;
        return false;
    }

    std::cout << "Items in cart for " << username << ":" << std::endl;
    for (const auto& item : cart) {
        item.printInfo();
    }
    return true;
}

bool ShoppingCart::checkout(string username) {
    // Check if cart is empty
    if (cart.empty()) {
        cout << "Cart is empty. Cannot proceed to checkout.\n";
        return false;
    }
    
    // Calculate total price
    double total = 0.0;
    for (const auto& item : cart) {
        total += item.getPrice() * item.getAmount();
    }
    
    // Write to order.csv
    ofstream file("order.csv", ios::app);
    if (!file) {
        cerr << "Error: Could not open file 'order.csv' for writing.\n";
        return false;
    }
    
    file << username << "," << total << endl;
    for (const auto& item : cart) {
        file << item.getName() << "," << item.getPrice() << "," << item.getAmount() << endl;
        
        // Update stock
        if (!item.setStock(item.getName(), item.getAmount())) {
            cout << "Error: Could not update stock for " << item.getName() << endl;
            return false;
        }
    }
    file.close();
    
    // Clear cart
    cart.clear();
    return true;
}