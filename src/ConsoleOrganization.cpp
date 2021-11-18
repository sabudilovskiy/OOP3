//
// Created by MRV on 18.11.2021.
//
#include "ConsoleOrganization.h"
#include <iostream>

std::string ConsoleOrganization::execute_command() {
    std::string answer;
    std::string name;
    int index;
    switch (current_command) {
        case EXIT:
            return "";
        case CREATE_SHOP:
            std::cout << "Введите название магазина(-1 для возврата назад):";
            std::cin >> name;
            if (name!="-1") return organization->create_shop(name);
            else return "";
        case CREATE_CARGO:
            std::cout << "Введите название склада(-1 для возврата назад): ";
            std::cin >> name;
            if (name!="-1") return organization->create_cargo(name);
            else return "";
        case REMOVE_SELLER:
            index = input<int>(
                    [](int x) -> bool {return x>=-1;},
                    [](std::string x) -> int {return std::stoi(x);} ,
                    std::string( "Введите, пожалуйста, номер ликвидируемого предприятия(-1 для возврата назад): "),
                    std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
            if (index != -1){
                return organization->remove_seller(index);
            }
            else return std::string("Вы решили не ликвидировать предприятие.");
        case CHECK_REMOVE_SELLER:
            index = input<int>(
                    [](int x) -> bool {return x>=-1;},
                    [](std::string x) -> int {return std::stoi(x);} ,
                    std::string( "Введите, пожалуйста, номер предприятия для проверки на возможность его ликвидации(-1 для возврата назад): "),
                    std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
            if (index != -1){
                return organization->remove_seller(index);
            }
            else return std::string("Вы решили не проверять предприятие на возможность ликвидации.");
        case GET_INFO:
             return "Баланс компании: " + std::to_string(organization->get_balance()) + "\n" + organization->get_info() + "\n";
        case MANAGE_SELLER:
            index = input<int>(
                    [](int x) -> bool {return x>=-1;},
                    [](std::string x) -> int {return std::stoi(x);} ,
                    std::string( "Введите, пожалуйста, номер предприятия для управления им(-1 для возврата назад:) "),
                    std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
            if (index>=0 && index < organization->get_own_numbers()) organization->start_seller_console(index, base);
            else if (index!=-1) return "Некорректный номер предприятия";
            else return "";
        case NEXT_DAY:
            return organization->day();
        default:
            return "Ошибка.";
    }
}
void ConsoleOrganization::start() {
    std::string input_text = "Введите, пожалуйста, номер того, что вы хотите сделать: \n0)Закончить игру \n1)Открыть магазин\n2)Открыть склад\n3)Ликвидировать предприятие\n4)Проверить предприятие на возможность ликвидации\n5)Получить сводку по балансу на счетах предприятий\n6)Управлять предприятием\n7)Начать следующий день\n";
    std::string error_text = "Допущена ошибка, введите, пожалуйста, корректный номер: ";
    while (current_command != EXIT){
        current_command = input<int>(
                [](int x) -> bool {return EXIT<=x&&x<=NEXT_DAY;},
                [](std::string x) -> int {return std::stoi(x);} ,
                input_text,
                error_text);
        std::cout << execute_command();
    }
}
