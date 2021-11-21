//
// Created by MRV on 18.11.2021.
//

#include "ConsoleSellerEmployees.h"
#include <iostream>
ConsoleSellerEmployees::ConsoleSellerEmployees(Seller *seller) : seller(seller){}

void ConsoleSellerEmployees::start() {
    std::cout << "Вы управляете ассортиментом предприятия " + seller->get_name() + "\n";
    std::string input_text;
    std::string error = "Введён некорректный номер команды, повторите ввод: ";
    input_text = "Введите номер команды: \n";
    input_text += "0) Вернуться в управление предприятием\n";
    input_text += "1) Узнать о возможности увольнения сотрудников\n";
    input_text += "2) Уволить сотрудников\n";
    input_text += "3) Узнать о возможности наёма сотрудников\n";
    input_text += "4) Нанять сотрудников\n";
    while (current_command!=EXIT){
        current_command = input<int>([](int x){return EXIT<=x&&x<=HIRE;}, [](std::string str){return std::stoi(str);}, input_text, error);
        std::cout<<execute_command();
    }
}

std::string ConsoleSellerEmployees::execute_command() {
    int argument;
    switch (current_command){
        case EXIT: {
            return "";
        }
        case CHECK_DISMISS: {
            argument = input<int>([](int x) { return x >= -1; }, [](std::string str) { return stoi(str); },
                                  "Введите количество сотрудников, возможность увольнения которых Вы бы хотели узнать (-1 для возврата назад): ",
                                  "Допущена ошибка, повторите ввод: ");
            if (argument != -1) return seller->check_dismiss_employees(argument) + "\n";
            else return "";
        }
        case DISMISS: {
            argument = input<int>([](int x) { return x >= -1; }, [](std::string str) { return stoi(str); },
                                  "Введите количество сотрудников, которые Вы бы хотели уволить (-1 для возврата назад): ",
                                  "Допущена ошибка, повторите ввод: ");
            if (argument != -1) return seller->dismiss_employees(argument) + "\n";
            else return "";
        }
        case CHECK_HIRE: {
            argument = input<int>([](int x) { return x >= -1; }, [](std::string str) { return stoi(str); },
                                  "Введите количество сотрудников, возможность наёма которых Вы бы хотели узнать (-1 для возврата назад): ",
                                  "Допущена ошибка, повторите ввод: ");
            if (argument != -1) return seller->check_hire_employees(argument) + "\n";
            else return "";
        }
        case HIRE: {
            argument = input<int>([](int x) { return x >= -1; }, [](std::string str) { return stoi(str); },
                                  "Введите количество сотрудников, которые Вы бы хотели нанять (-1 для возврата назад): ",
                                  "Допущена ошибка, повторите ввод: ");
            if (argument != -1) return seller->hire_employees(argument) + "\n";
            else return "";
        }
    }
    return "";
}
