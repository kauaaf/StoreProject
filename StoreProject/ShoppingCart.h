#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include <string>
#include <vector>
#include "Item.h"

class ShoppingCart {
public:
    ShoppingCart() {};
    ShoppingCart(std::string username) : username(username) {};

    bool addItem(std::string name, int amount);
    bool removeItem(std::string name);
    bool displayCart(std::string username);
    bool checkout(std::string username);

private:
    std::string username;
    std::vector<Item> cart;

    double calculateTotalPrice();
    bool editStock();
};

#endif // SHOPPING_CART_H