#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#include <string>
#include <vector>
#include "Item.h"

class ShoppingCart {
public:
    ShoppingCart(std::string username);

    bool addItem(std::string name, int amount);
    bool removeItem();
    bool displayCart(std::string username);
    bool checkout(std::string username);
    bool editstock(std::string name, int amount);

private:
    std::string username;
    std::vector<Item> cart;
};

#endif // SHOPPING_CART_H