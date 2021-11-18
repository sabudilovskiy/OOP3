//
// Created by MRV on 16.11.2021.
//

#ifndef ORGANIZATION_OOP3_H
#define ORGANIZATION_OOP3_H
#include <vector>
#include <string>
#include "Shop.h"
#include "Cargo.h"
class Seller;
class Organization{
    double balance = 0;
    std::vector<Seller*> own;
    int own_numbers = 0;
public:
    Organization(double balance);
    double get_balance() const;
    std::string get_balance_seller(int index);
    double take_money(double money);
    void recieve_money(double money);
    std::string create_shop(std::string name);
    std::string create_cargo(std::string name);
    std::string remove_seller(int index);
    std::string check_remove_seller(int index);
    std::string day();
    int get_own_numbers() const;
    std::string get_info();
    void start_seller_console(int index, std::vector<Item> &base);
};
#endif

