//
// Created by MRV on 18.11.2021.
//

#ifndef OOP3_CONSOLESELLEREMPLOYEES_H
#define OOP3_CONSOLESELLEREMPLOYEES_H


#include "Seller.h"

class ConsoleSellerEmployees {
    Seller* seller = nullptr;
    int current_command = CHECK_DISMISS;
    enum commands{
        EXIT, CHECK_DISMISS, DISMISS, CHECK_HIRE, HIRE
    };
    std::string execute_command();
public:
    ConsoleSellerEmployees(Seller *seller);
    void start();
};


#endif //OOP3_CONSOLESELLEREMPLOYEES_H
