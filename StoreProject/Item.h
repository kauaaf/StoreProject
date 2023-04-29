#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    // Constructors
    Item(std::string name, std::string category, double price, int stock);
    Item(std::string name, std::string category, double price, int stock, int amount);

    // Accessors
    std::string getName() const;
    std::string getCategory() const;
    double getPrice() const;
    int getStock() const;
    int getAmount() const;

    // Member functions
    void printInfo() const;
    bool setStock(std::string name, int amount);
    static void viewCategory(std::string category);



private:
    std::string name;
    double price;
    int stock;
    std::string category;
    int amount;
};

#endif