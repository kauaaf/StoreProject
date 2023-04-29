#include "ShoppingCart.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

ShoppingCart::ShoppingCart(std::string username) : username(username) {}

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
                cart.emplace_back(Item(name, category, price, stock, amount));
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
    std::cerr << "Item not found in cart: " << name << std::endl;
    return false;
}

bool ShoppingCart::displayCart() {
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

bool ShoppingCart::checkout() {
    if (cart.empty()) {
        std::cerr << "Cart is empty" << std::endl;
        return false;
    }

    // Calculate total price
    double total_price = calculateTotalPrice();

    // Write order to order.csv
    std::ofstream file("order.csv", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: order.csv" << std::endl;
        return false;
    }

    file << username << "," << total_price << std::endl;
    file.close();

    // Update stock in stock.csv
    if (!editStock()) {
        std::cerr << "Failed to update stock in stock.csv" << std::endl;
        return false;
    }

    // Clear cart
    cart.clear();

cout << "Order successfully checked out!" << endl;
cout << "Total price: $" << total_price << endl;

return true;