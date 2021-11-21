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
        case EXIT: {
            return "";
        }
        case INFO_ABOUT_ITEM: {
            index = input<int>(
                    [](int x) -> bool { return x >= -1; },
                    [](std::string x) -> int { return std::stoi(x); },
                    std::string(
                            "�������, ����������, ����� ������ ��� ��������� ���������� � ��(-1 ��� �������� �����:) "),
                    std::string("�������� ������, �������, ����������, ���������� �����: "));
            if (index == -1) return "";
            else return seller->get_info_about_item(index)+"\n";
        }
        case INFO_ABOUT_ITEMS: {
            return seller->get_info_about_items() + "\n";
        }
        case REMOVE: {
            index = input<int>(
                    [](int x) -> bool { return 1 >= x && x >= -1; },
                    [](std::string x) -> int { return std::stoi(x); },
                    std::string(
                            "�������, ����������, -1, ���� ������ ��������� �����, 0, ���� ������ �������� ���������� � ����������� ������ � ������, 1, ���� ������ ����� � ������: "),
                    std::string("�������� ������, �������, ����������, ���������� �����: "));
            if (index == 1) {
                index = input<int>(
                        [](int x) -> bool { return x >= -1; },
                        [](std::string x) -> int { return std::stoi(x); },
                        std::string("�������, ����������, ����� ������ ��� �������� ������(-1 ��� �������� �����:) "),
                        std::string("�������� ������, �������, ����������, ���������� �����: "));
                if (index == -1) return "";
                else return seller->remove_item(index) + "\n";
            } else if (index == 0) {
                index = input<int>(
                        [](int x) -> bool { return x >= -1; },
                        [](std::string x) -> int { return std::stoi(x); },
                        std::string(
                                "�������, ����������, ����� ������ ��� ��������� ���������� � ����������� �������� ������(-1 ��� �������� �����:) "),
                        std::string("�������� ������, �������, ����������, ���������� �����: "));
                if (index == -1) return "";
                else return seller->check_remove_item(index) + "\n";
            } else return "";
        }
        case ADD: {
            index = input<int>(
                    [](int x) -> bool { return 1 >= x && x >= -1; },
                    [](std::string x) -> int { return std::stoi(x); },
                    std::string(
                            "�������, ����������, -1, ���� ������ ��������� �����, 0, ���� ������ �������� ���������� � ����������� ���������� ������������, 1, ���� ������ ��������� �����������: "),
                    std::string("�������� ������, �������, ����������, ���������� �����: "));
            if (index == 1) {
                index = input<int>(
                        [](int x) -> bool { return x >= -1; },
                        [](std::string x) -> int { return std::stoi(x); },
                        std::string(
                                "�������, ����������, ����� ������ ��� ���������� ������������(-1 ��� �������� �����:) "),
                        std::string("�������� ������, �������, ����������, ���������� �����: "));
                if (index == -1) return "";
                else if (index >= 0 && index < base.size()) return seller->add_item(base[index]) + "\n";
                else return "����� ������������ �����. \n";
            } else if (index == 0) {
                return seller->check_add_item() + "\n";
            } else return "";
        }
        case INFO_ABOUT_ADD_ITEMS: {
            return seller->get_info_about_items_to_add(base) + "\n";
        }
        case PROMOTE: {
            index = input<int>(
                    [](int x) -> bool { return 3 >= x && x >= -1; },
                    [](std::string x) -> int { return std::stoi(x); },
                    std::string(
                            "�������, ����������, -1, ���� ������ ��������� �����, 0, ���� ������ �������� ���������� � ���� ���������� ������� ������, 1, ���� ������ ���������������� �����, 2, ���� ������ �������� ���������� � ���� ������� ����� �����������, 3, ���� ������ ���������������� �����������: "),
                    std::string("�������� ������, �������, ����������, ���������� �����: "));
            if (index == 0) {
                index = input<int>(
                        [](int x) -> bool { return x >= -1; },
                        [](std::string x) -> int { return std::stoi(x); },
                        std::string(
                                "�������, ����������, ����� ������ ��� ��������� ���������� � ���� �������(-1 ��� �������� �����:) "),
                        std::string("�������� ������, �������, ����������, ���������� �����: "));
                if (index == -1) return "";
                else return seller->check_promote_item(index) + "\n";
            }
            else if (index == 1) {
                index = input<int>(
                        [](int x) -> bool { return x >= -1; },
                        [](std::string x) -> int { return std::stoi(x); },
                        std::string(
                                "�������, ����������, ����� ������, ������� ������ ����������������(-1 ��� �������� �����:) "),
                        std::string("�������� ������, �������, ����������, ���������� �����: "));
                if (index == -1) return "";
                else return seller->promote_item(index) + "\n";
            }
            else if (index == 2) return seller->check_promote_all() + "\n";
            else if (index == 3) return seller->promote_all() + "\n";
            else return "";
        }
        case CHANGE_PRICE: {
            index = input<int>(
                    [](int x) -> bool { return x >= -1; },
                    [](std::string x) -> int { return std::stoi(x); },
                    std::string(
                            "�������, ����������, ����� ������, ���� �������� �� ������ ��������(-1 ����� ��������� �����): "),
                    std::string("�������� ������, �������, ����������, ���������� �����: "));
            if (index != -1) {
                new_price = input<double>([](double x) -> bool { return x >= 0; },
                                          [](std::string x) -> double { return std::stod(x); },
                                          std::string("������� ���� ������: "),
                                          std::string("�������� ������ ��� �����, ��������� ����: "));
                return seller->change_price(index, new_price) + "\n";
            } else return "";
        }
        case UP_CAPACITY:{
            index = input<int>(
                    [](int x) -> bool { return x >= -1; },
                    [](std::string x) -> int { return std::stoi(x); },
                    std::string(
                            "�������, ����������, ����� ������, ����������� �������� �� ������ ���������(-1 ����� ��������� �����): "),
                    std::string("�������� ������, �������, ����������, ���������� �����: "));
            if (index != -1) {
                return seller->up_capacity(index) +"\n";
            } else return "";
        }
        case REFILL: {
            index = input<int>(
                    [](int x) -> bool { return 3 >= x && x >= -1; },
                    [](std::string x) -> int { return std::stoi(x); },
                    std::string(
                            "�������, ����������, -1, ���� ������ ��������� �����, 0, ���� ������ �������� ���������� � ���� ���������� ������� ������, 1, ���� ������ ��������� ������ ������, 2, ���� ������ �������� ���������� � ���� ���������� ������� ����� �����������, 3, ���� ������ ��������� ��� ������: "),
                    std::string("�������� ������, �������, ����������, ���������� �����: "));
            if (index == 0) {
                index = input<int>(
                        [](int x) -> bool { return x >= -1; },
                        [](std::string x) -> int { return std::stoi(x); },
                        std::string(
                                "�������, ����������, ����� ������ ��� ��������� ���������� � ���� ����������(-1 ��� �������� �����:) "),
                        std::string("�������� ������, �������, ����������, ���������� �����: "));
                if (index == -1) return "";
                else return seller->check_promote_item(index) + "\n";
            } else if (index == 1) {
                index = input<int>(
                        [](int x) -> bool { return x >= -1; },
                        [](std::string x) -> int { return std::stoi(x); },
                        std::string(
                                "�������, ����������, ����� ������, ������ �������� ������ ���������(-1 ��� �������� �����:) "),
                        std::string("�������� ������, �������, ����������, ���������� �����: "));
                if (index == -1) return "";
                else return seller->refill(index) + "\n";
            } else if (index == 2) return seller->check_refill_all()+ "\n";
            else if (index == 3) return seller->refill_all()+ "\n";
            else return "";
        }
    }
    return "";
}

void ConsoleSellerItems::start() {
    std::cout << "�� ���������� ������������� ����������� " + seller->get_name() + "\n";
    std::string input_text;
    std::string error = "����� ������������ ����� �������, ��������� ����: ";
    input_text = "������� ����� �������: \n";
    input_text += "0) ��������� � ���������� ������������\n";
    input_text += "1) �������� ���������� � ����\n";
    input_text += "2) �������� ���������� � ���� �����\n";
    input_text += "3) ����� � ������\n";
    input_text += "4) ��������� �����������\n";
    input_text += "5) ������ � ��������� ���������� ������������\n";
    input_text += "6) ���������������� ����� ��� �����������\n";
    input_text += "7) �������� ���� ������\n";
    input_text += "8) ��������� ����������� ������\n";
    input_text += "9) ��������� ������\n";
    while (current_command!=EXIT){
        current_command = input<int>([](int x){return EXIT<=x&&x<=REFILL;}, [](std::string str){return std::stoi(str);}, input_text, error);
        std::cout<<execute_command();
    }
}
