//
// Created by MRV on 18.11.2021.
//

#ifndef OOP3_CONSOLESELLER_H
#define OOP3_CONSOLESELLER_H

#include "Seller.h"
class ConsoleSeller{
    Seller* seller = nullptr;
    int current_command = FINANCE;
    std::vector<Item>&base;
    enum commands{
        EXIT, FINANCE, ITEMS, EMPLOYEES, SWITCH_AUTOREFILL, RENAME
    };
    std::string execute_command();
public:
    ConsoleSeller(Seller *seller, std::vector<Item> &base);
    void start();
};

#endif //OOP3_CONSOLESELLER_H
