#include <iostream>
#include <vector>
#include "Item.h"
#include "Support.h"
#include <string>
#include <Organization.h>
#include "ConsoleOrganization.h"
#include <Windows.h>
int main(){
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n = input<int>(
            [](int x) -> bool {return x>=0;},
            [](std::string x) -> int {return std::stoi(x);} ,
            "Введите число доступных в игре товаров: ",
            "Допущена ошибка при вводе, повторите ввод: ");
    std::vector<Item> base;
    for (int i = 0; i < n; i++){
        std::cout << "Введите название товара: ";
        std::string name;
        std::cin >> name;
        double price = input<double>(
                [](double x) -> bool {return x>=0;},
                [](std::string x) -> double {return std::stod(x);} ,
                std::string("Введите цену товара: "),
                std::string("Допущена ошибка при вводе, повторите ввод: "));
        double involvement = input<double>(
                [](double x) -> bool {return x>=0;},
                [](std::string x) -> double {return std::stod(x);} ,
                std::string("Введите вовлечённость товара: "),
                std::string("Допущена ошибка при вводе, повторите ввод: "));
        double popularity = input<double>(
                [](double x) -> bool {return x>=0;},
                [](std::string x) -> double {return std::stod(x);} ,
                std::string("Введите популярность товара: "),
                std::string("Допущена ошибка при вводе, повторите ввод: "));
        while (popularity < involvement){
            popularity = input<double>(
                    [](double x) -> bool {return x>=0;},
                    [](std::string x) -> double {return std::stod(x);} ,
                    std::string("Популярность должна быть не меньше вовлечённости. Повторите ввод: "),
                    std::string("Допущена ошибка при вводе, повторите ввод: "));
        }
        int capacity = input<int>(
                [](int x) -> bool {return x>=0;},
                [](std::string x) -> int {return std::stoi(x);} ,
                std::string("Введите вместимость товара: "),
                std::string("Допущена ошибка при вводе, повторите ввод: "));
        int effectiveness = input<int>(
                [](int x) -> bool {return x>=0;},
                [](std::string x) -> int {return std::stoi(x);} ,
                std::string("Введите эффективность товара: "),
                std::string("Допущена ошибка при вводе, повторите ввод: "));
        base.emplace_back(name, price, involvement, popularity, capacity, effectiveness);
    }
    double start_capital = input<double>(
            [](double x) -> bool {return x>=0;},
            [](std::string x) -> double {return std::stod(x);} ,
            std::string("Введите стартовый капитал: "),
            std::string("Допущена ошибка при вводе, повторите ввод: "));
    Organization* org = new Organization(start_capital);
    ConsoleOrganization(org, base).start();
}