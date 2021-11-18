//
// Created by MRV on 18.11.2021.
//

#ifndef OOP3_CONSOLEORGANIZATION_H
#define OOP3_CONSOLEORGANIZATION_H
#include "Organization.h"
class ConsoleOrganization{
    Organization* organization = nullptr;
    int current_command = NEXT_DAY;
    std::vector<Item>& base;
    enum commands{
        EXIT, CREATE_SHOP, CREATE_CARGO, REMOVE_SELLER, CHECK_REMOVE_SELLER, GET_INFO, MANAGE_SELLER, NEXT_DAY
    };
    std::string execute_command();
public:
    ConsoleOrganization(Organization *organization, std::vector<Item> &base) : organization(organization), base(base) {}
    void start();
};
#endif //OOP3_CONSOLEORGANIZATION_H
