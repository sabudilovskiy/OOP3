//
// Created by MRV on 18.11.2021.
//

#include "ConsoleSellerFinance.h"
#include <iostream>
std::string ConsoleSellerFinance::execute_command() {
    double argument;
    switch (current_command) {
        case EXIT: {
            return "";
        }
        case GET_BALANCE: {
            return "На балансе предприятия " + to_string(my_round(seller->get_balance(), 2)) + "$\n";
        }
        case TAKE_MONEY: {
            argument = input<double>([](double x) { return x >= 0; }, [](std::string str) { return stod(str); },
                                     "Введите количество денег для перевода со счетов предприятия на счета компании: ",
                                     "Допущена ошибка, повторите ввод: ");
            return seller->take_money(argument) + "\n";
        }
        case RECEIVE_MONEY: {
            argument = input<double>([](double x) { return x >= 0; }, [](std::string str) { return stod(str); },
                                     "Введите количество денег для перевода со счетов компании на счета предприятия: ",
                                     "Допущена ошибка, повторите ввод: ");
            return seller->receive_money(argument) + "\n";
        }
    }
}

void ConsoleSellerFinance::start() {
    std::cout << "Вы управляете финансами предприятия " + seller->get_name() + "\n";
    std::string input_text;
    std::string error = "Введён некорректный номер команды, повторите ввод: ";
    input_text = "Введите номер команды: \n";
    input_text += "0) Вернуться в управление предприятием\n";
    input_text += "1) Узнать баланс предприятия\n";
    input_text += "2) Перевести деньги со счёта предприятия\n";
    input_text += "3) Перевести деньги на счёт предприятия\n";
    while (current_command!=EXIT){
        current_command = input<int>([](int x){return EXIT<=x&&x<=RECEIVE_MONEY;}, [](std::string str){return std::stoi(str);}, input_text, error);
        std::cout<<execute_command();
    }
}

ConsoleSellerFinance::ConsoleSellerFinance(Seller *seller) : seller(seller){}
