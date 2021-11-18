//
// Created by MRV on 18.11.2021.
//

#ifndef OOP3_CONSOLESELLERFINANCE_H
#define OOP3_CONSOLESELLERFINANCE_H
#include "Item.h"
#include "Seller.h"

class ConsoleSellerFinance {
    Seller* seller = nullptr;
    int current_command = GET_BALANCE;
    enum commands{
        EXIT, GET_BALANCE, TAKE_MONEY, RECEIVE_MONEY
    };
    std::string execute_command();
public:
    ConsoleSellerFinance(Seller *seller);
    void start();
};


#endif //OOP3_CONSOLESELLERFINANCE_H
