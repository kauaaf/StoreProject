#include "ShoppingCart.h"
#include "Item.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

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
    int commma;
    std::string str_double, str_int;
    std::getline(ss, item_name, ',');
    std::getline(ss, category, ',');
    std::getline(ss, str_double, ',');
    std::getline(ss, str_int, ',');
    price = std::stod(str_double);
    stock = std::stoi(str_int);

    // Do something with the extracted data here

    if (item_name == name) {
      if (amount <= stock) {
        Item myitem(name, category, price, stock, amount);
        cart.push_back(myitem);
        found = true;
      } else {
        std::cerr << "Insufficient stock for " << name << std::endl;
        return false;
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

bool ShoppingCart::removeItem() {
  string name;
  cout << "\t Enter the name of the Item you want to remove :";
  cin >> name;
  for (auto it = cart.begin(); it != cart.end(); ++it) {
    if (it->getName() == name) {
      cart.erase(it);
      return true;
    }
  }
  std::cout << "\tItem not found in cart: " << name << std::endl;
  return false;
}

bool ShoppingCart::displayCart(string username) {
  if (cart.empty()) {
    std::cout << "Cart is empty" << std::endl;
    return false;
  }

  std::cout << "Items in cart for " << username << ":" << std::endl;
  for (const auto &item : cart) {
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
  for (const auto &item : cart) {
    cout << item.getName() << item.getAmount() << "*" << item.getPrice() <<  endl;
    total += item.getPrice() * item.getAmount();
  }
  
  cout << " Total : $" << total << endl;

  // Write to order.csv
  ofstream file("order.csv", ios::app);
  if (!file) {
    cerr << "Error: Could not open file 'order.csv' for writing.\n";
    return false;
  }

  file << username << "," << total << endl;
  for (const auto &item : cart) {
    file << item.getName() << "," << item.getPrice() << "," << item.getAmount() << endl;
    /*
    // Update stock
    if (!item.setStock(item.getName(), item.getAmount())) {
        cout << "Error: Could not update stock for " << item.getName() << endl;
        return false;
    }
    */
    if (!editstock(item.getName(),item.getAmount())){
        cout << "Error: Could not update stock for " << item.getName() << endl;
        return false;
    }   
  }
  file.close();

  // Clear cart
  cart.clear();
  return true;
}
bool ShoppingCart::editstock(string name, int amount){
    
    std::ifstream input("stock.csv");

    // Check if files were opened successfully
    if (!input.is_open()) {
        std::cerr << "Failed to open input file" << std::endl;
        return 1;
    }

    // Read items from input file and modify them as necessary
    std::vector<string> lines;
    std::string line;
    bool found = false;
    while (std::getline(input, line)) 
    {
        std::stringstream ss(line);
        std::string item_name, category;
        double price;
        int stock = 0;

        std::string str_double, str_int;
        std::getline(ss, item_name, ',');
        std::getline(ss, category, ',');
        std::getline(ss, str_double, ',');
        std::getline(ss, str_int, ',');
        price = std::stod(str_double);
        stock = std::stoi(str_int);
        cout << stock << endl;

        // Modify the item if it's the one we're looking for
        if (item_name == name) {
            stock = stock - amount;
            found = true;
        }
        line = item_name + "," + category + "," + std::to_string(price) + "," + std::to_string(stock);
        lines.push_back(line);
    }
    input.close();

    if (found) {
    std::ofstream output("stock.csv");

    if (!output.is_open()) {
        std::cerr << "Failed to open output file" << std::endl;
        return false;
    }

    // Write the modified items to the output file
    for (const auto& line : lines) {
        output << line << "\n";
    }
    output.close();
    return true;
    }

  return false;
}