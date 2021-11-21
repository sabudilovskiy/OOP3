//
// Created by MRV on 16.11.2021.
//

#ifndef CARGO_OOP3_H
#define CARGO_OOP3_H
#include "Seller.h"
#include "Organization.h"
class Cargo : public Seller{
protected:
    std::vector<int> orders;
    std::string buy(int index, int count) override;
public:
    Cargo(Organization* owner, const std::string& name);
    std::string hire_employees(int number) override;
    std::string check_hire_employees(int number) override;
    std::string add_item(Item item) override;
    std::string check_add_item() override;
    std::string remove_item(int index) override;
    std::string dismiss_employees(int number) override;
    std::string check_dismiss_employees(int number) override;
    std::string promote_all() override;
    std::string check_promote_all() override;
    std::string promote_item(int index) override;
    std::string check_promote_item(int index) override;
    std::string day() override;
    std::string get_info_about_item(int index) override;
    std::string close() override;
    std::string up_capacity(int index) override;
};
#endif