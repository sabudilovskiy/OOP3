//
// Created by MRV on 18.11.2021.
//
#include "ConsoleSeller.h"
#include <iostream>
#include "ConsoleSellerEmployees.h"
#include "ConsoleSellerFinance.h"
#include "ConsoleSellerItems.h"
ConsoleSeller::ConsoleSeller(Seller *seller, std::vector<Item> &base) : seller(seller),base(base) {}
void ConsoleSeller::start() {
    std::cout << "Вы управляете предприятием " + seller->get_name() + "\n";
    std::string input_text;
    std::string error = "Введён некорректный номер команды, повторите ввод: ";
    input_text = "Введите номер команды: \n";
    input_text += "0) Вернуться в управление компанией\n";
    input_text += "1) Перейти к управлению и получению информации о финансовом состоянии предприятия\n";
    input_text += "2) Перейти к получении информации об ассортименте и управлении им(добавление новых товаров, снятие с продаж, пополнение запасов)\n";
    input_text += "3) Перейти к управление персоналом\n";
    input_text += "4) Включить или выключить автопополнение\n";
    input_text += "5) Переименовать предприятие\n";
    while (current_command!=EXIT){
        current_command = input<int>([](int x){return EXIT<=x&&x<=RENAME;}, [](std::string str){return std::stoi(str);}, input_text, error);
        std::cout<<execute_command();
    }
}

std::string ConsoleSeller::execute_command() {
    int index;
    double argument;
    std::string name;
    switch (current_command) {
        case EXIT:
            return "";
        case FINANCE:
            ConsoleSellerFinance(seller).start();
            return "";
        case ITEMS:
            ConsoleSellerItems(seller, base).start();
            return "";
        case EMPLOYEES:
            ConsoleSellerEmployees(seller).start();
            return "";
        case SWITCH_AUTOREFILL:
            seller->switch_autorefill();
        case RENAME:
            std::cout << "Введите новое название: ";
            std::cin >> name;
            seller->set_name(name);
            return "Вы успешно переименовали предприятие.";
    }
}
