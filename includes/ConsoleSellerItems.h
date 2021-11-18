//
// Created by MRV on 18.11.2021.
//

#ifndef OOP3_CONSOLESELLERITEMS_H
#define OOP3_CONSOLESELLERITEMS_H

#include "Seller.h"

class ConsoleSellerItems {
    Seller* seller = nullptr;
    int current_command = REMOVE;
    std::vector<Item>&base;
    enum commands{
        EXIT, REMOVE, ADD, INFO_ABOUT_ITEM, INFO_ABOUT_ADD_ITEMS, PROMOTE, CHANGE_PRICE, REFILL
    };
    std::string execute_command();
public:
    ConsoleSellerItems(Seller *seller, std::vector<Item> &base);
    void start();
};


#endif //OOP3_CONSOLESELLERITEMS_H
