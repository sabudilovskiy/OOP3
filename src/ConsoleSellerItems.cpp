//
// Created by MRV on 18.11.2021.
//

#include "ConsoleSellerItems.h"
#include <iostream>
ConsoleSellerItems::ConsoleSellerItems(Seller *seller, std::vector<Item> &base) : seller(seller), base(base) {}

std::string ConsoleSellerItems::execute_command() {
    int index = 0;
    double new_price = 0;
    switch (current_command) {
        case EXIT:
            return "";
        case REMOVE:
            index = input<int>(
                    [](int x) -> bool { return 1 >= x && x >= -1; },
                    [](std::string x) -> int { return std::stoi(x); },
                    std::string("Введите, пожалуйста, -1, если хотите вернуться назад, 0, если хотите получить информацию о возможности снятия с продаж, 1, если хотите снять с продаж: "),
                    std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
            if (index == 1) {
                index = input<int>(
                        [](int x) -> bool { return x >= -1; },
                        [](std::string x) -> int { return std::stoi(x); },
                        std::string("Введите, пожалуйста, номер товара для закрытия продаж(-1 для возврата назад:) "),
                        std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
                if (index != -1) return "";
                else return seller->remove_item(index);
            } else if (index == 0) {
                index = input<int>(
                        [](int x) -> bool { return x >= -1; },
                        [](std::string x) -> int { return std::stoi(x); },
                        std::string("Введите, пожалуйста, номер товара для получения информации о результатах закрытия продаж(-1 для возврата назад:) "),
                        std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
                if (index != -1) return "";
                else return seller->check_remove_item(index);
            } else return "";
        case ADD:
            index = input<int>(
                    [](int x) -> bool { return 1 >= x && x >= -1; },
                    [](std::string x) -> int { return std::stoi(x); },
                    std::string("Введите, пожалуйста, -1, если хотите вернуться назад, 0, если хотите получить информацию о возможности расширения ассортимента, 1, если хотите расширить ассортимент: "),
                    std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
            if (index == 1) {
                index = input<int>(
                        [](int x) -> bool { return x >= -1; },
                        [](std::string x) -> int { return std::stoi(x); },
                        std::string("Введите, пожалуйста, номер товара для расширения ассортимента(-1 для возврата назад:) "),
                        std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
                if (index != -1) return "";
                else if (index >= 0 && index < base.size()) return seller->add_item(base[index]);
                else return "Введён некорректный номер.";
            } else if (index == 0) {
                return seller->check_add_item();
            } else return "";
        case INFO_ABOUT_ITEM:
            index = input<int>(
                    [](int x) -> bool { return x >= -1; },
                    [](std::string x) -> int { return std::stoi(x); },
                    std::string(
                            "Введите, пожалуйста, номер товара для получения информации о нём(-1 для возврата назад:) "),
                    std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
            if (index != -1) return "";
            else return seller->get_info_about_item(index);
        case INFO_ABOUT_ADD_ITEMS:
            return seller->get_info_about_items_to_add(base);
        case PROMOTE:
            index = input<int>(
                    [](int x) -> bool { return 3 >= x && x >= -1; },
                    [](std::string x) -> int { return std::stoi(x); },
                    std::string("Введите, пожалуйста, -1, если хотите вернуться назад, 0, если хотите получить информацию о цене проведении рекламы товара, 1, если хотите прорекламировать товар, 2, если хотите получить информацию о цене рекламы всего предприятия, 3, если хотите прорекламировать предприятие: "),
                    std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
            if (index == 0) {
                index = input<int>(
                        [](int x) -> bool { return x >= -1; },
                        [](std::string x) -> int { return std::stoi(x); },
                        std::string("Введите, пожалуйста, номер товара для получения информации о цене рекламы(-1 для возврата назад:) "),
                        std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
                if (index != -1) return "";
                else return seller->check_promote_item(index);
            } else if (index == 1) {
                index = input<int>(
                        [](int x) -> bool { return x >= -1; },
                        [](std::string x) -> int { return std::stoi(x); },
                        std::string("Введите, пожалуйста, номер товара, который хотите прорекламировать(-1 для возврата назад:) "),
                        std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
                if (index != -1) return "";
                else return seller->promote_item(index);
            } else if (index == 2) return seller->check_promote_all();
            else if (index == 3) return seller->promote_all();
            else return "";
        case CHANGE_PRICE:
            index = input<int>(
                    [](int x) -> bool { return x >= -1; },
                    [](std::string x) -> int { return std::stoi(x); },
                    std::string("Введите, пожалуйста, номер товара, цену которого вы хотите изменить(-1 чтобы вернуться назад): "),
                    std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
            if (index != -1){
                new_price = input<double>([](double x) -> bool {return x>=0;},
                                          [](std::string x) -> double {return std::stod(x);} ,
                                          std::string("Введите цену товара: "),
                                          std::string("Допущена ошибка при вводе, повторите ввод: "));
                return seller->change_price(index, new_price);
            }
            else return "";
        case REFILL:
            index = input<int>(
                    [](int x) -> bool { return 3 >= x && x >= -1; },
                    [](std::string x) -> int { return std::stoi(x); },
                    std::string("Введите, пожалуйста, -1, если хотите вернуться назад, 0, если хотите получить информацию о цене пополнения запасов товара, 1, если хотите пополнить запасы товара, 2, если хотите получить информацию о цене пополнения товаров всего предприятия, 3, если хотите пополнить все товары: "),
                    std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
            if (index == 0) {
                index = input<int>(
                        [](int x) -> bool { return x >= -1; },
                        [](std::string x) -> int { return std::stoi(x); },
                        std::string("Введите, пожалуйста, номер товара для получения информации о цене пополнения(-1 для возврата назад:) "),
                        std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
                if (index != -1) return "";
                else return seller->check_promote_item(index);
            } else if (index == 1) {
                index = input<int>(
                        [](int x) -> bool { return x >= -1; },
                        [](std::string x) -> int { return std::stoi(x); },
                        std::string("Введите, пожалуйста, номер товара, запасы которого хотите пополнить(-1 для возврата назад:) "),
                        std::string("Допущена ошибка, введите, пожалуйста, корректный номер: "));
                if (index != -1) return "";
                else return seller->refill(index);
            } else if (index == 2) return seller->check_refill_all();
            else if (index == 3) return seller->refill_all();
            else return "";
    }
    return "";
}

void ConsoleSellerItems::start() {
    std::cout << "Вы управляете ассортиментом предприятия " + seller->get_name() + "\n";
    std::string input_text;
    std::string error = "Введён некорректный номер команды, повторите ввод: ";
    input_text = "Введите номер команды: \n";
    input_text += "0) Вернуться в управление предприятием\n";
    input_text += "1) Снять с продаж товар\n";
    input_text += "2) Расширить ассортимент\n";
    input_text += "3) Узнать о вариантах расширения ассортимента\n";
    input_text += "4) Узнать о товарах, которыми можно расширить ассортимент\n";
    input_text += "5) Прорекламировать товар или предприятие\n";
    input_text += "6) Изменить цену товара\n";
    input_text += "7) Пополнить запасы\n";
    while (current_command!=EXIT){
        current_command = input<int>([](int x){return EXIT<=x&&x<=REFILL;}, [](std::string str){return std::stoi(str);}, input_text, error);
        std::cout<<execute_command();
    }
}
