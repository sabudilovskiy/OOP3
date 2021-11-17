#include <iostream>
#include "Organization.h"
#include "Support.h"
#include <string>

class ConsoleOrganization{
    Organization* organization = nullptr;
    int current_command;
    enum commands{
        EXIT, CREATE_SHOP, CREATE_CARGO, REMOVE_SELLER, CHECK_REMOVE_SELLER, GET_INFO, NEXT_DAY
    };
public:
    ConsoleOrganization(Organization* organization):organization(organization);
    void start(){
        while (current_command != EXIT){
            current_command = input<int>(
                    [](int x) -> bool {return EXIT<=x&&x<=NEXT_DAY;},
                    [](std::string x) -> int {return std::stoi(x);} ,
                    std::string( "Введите, пожалуйста, номер того, что вы хотите сделать: \n0) Закончить игру. \n1)Открыть магазин\n2)Открыть склад\n3)Ликвидировать предприятие\n4)Проверить предеприятие на возможность ликвидации\n5)Получить сводку по балансу на счетах предприятий\n6)Начать следующий день"),
                    std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
            std::cout << execute_command();
        }
    }
    std::string execute_command(){
        std::string answer;
        std::string name;
        int index;
        switch (current_command) {
            case EXIT:
                return "";
            case CREATE_SHOP:
                std::cout << "Введите название магазина. ";
                std::cin >> name;
                return organization->create_shop(name);
            case CREATE_CARGO:
                std::cout << "Введите название магазина. ";
                std::cin >> name;
                return organization->create_cargo(name);
            case REMOVE_SELLER:
                index = input<int>(
                        [](int x) -> bool {return x>=-1;},
                        [](std::string x) -> int {return std::stoi(x);} ,
                        std::string( "Введите, пожалуйста, номер ликвидируемого предприятия(-1 для отмены): "),
                        std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
                if (index != -1){
                    return organization->remove_seller(index);
                }
                else return std::string("Вы решили не ликвидировать предприятие.");
            case CHECK_REMOVE_SELLER:
                index = input<int>(
                        [](int x) -> bool {return x>=-1;},
                        [](std::string x) -> int {return std::stoi(x);} ,
                        std::string( "Введите, пожалуйста, номер предприятия для проверки на возможность его ликвидации(-1 для отмены): "),
                        std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
                if (index != -1){
                    return organization->remove_seller(index);
                }
                else return std::string("Вы решили не проверять предприятие на возможность ликвидации.");
            case GET_INFO:

            case NEXT_DAY:
                return organization->day();
            default:
                return "Ошибка.";
        }
    }
};
class ConsoleSeller{

};


int main(){
    Organization* test;
    test->day();
}