//
// Created by MRV on 16.11.2021.
//

#ifndef SHOP_OOP3_H
#define SHOP_OOP3_H
#include "Item.h"
#include "Seller.h"
class Shop : public Seller{
protected:
    std::string buy(int index, int count) override;
public:
    Shop(Organization* owner, std::string name);
    std::string add_item(Item item) override;
    std::string check_add_item() override;
    std::string remove_item(int index) override;
    std::string dismiss_employees(int number) override;
    std::string check_dismiss_employees(int number) override;
    std::string promote_all() override;
    std::string check_promote_all() override;
    std::string promote_item(int index) override;
    std::string check_promote_item(int index) override;
    std::string up_capacity(int index) override;
    std::string day() override;
};
#endif
