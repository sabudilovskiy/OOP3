//
// Created by MRV on 18.11.2021.
//
#include "Cargo.h"

Cargo::Cargo(Organization *owner, const std::string &name) {
    this->owner = owner;
    this->name = name;
}

std::string Cargo::add_item(Item item) {
    if (balance >= 200){
        items.push_back(item);
        cur_involvement.push_back(item.get_base_involvement());
        cur_popularity.push_back(item.get_base_popularity());
        capacity.push_back(2*item.get_capacity());
        balance_items.push_back(0);
        orders.push_back(0);
        balance-=200;
        number_items++;
        return "����� ������� ��������.";
    }
    else return "��� ���������� ������������ ��������� ����� �� ����� 200$ �� ����� ������.";
}

std::string Cargo::check_add_item() {
    std::string answer;
    if (balance >= 200){
        answer = "�� ������ ��������� ����������� �� 200$.";
    }
    else{
        answer = "�� �� ������ ��������� ����������� �� 200$: �� ����� ������ ��� ������������ ���������� �����.";
    }
    return answer;
}

std::string Cargo::buy(int index, int count) {
    if (0 <= index && index <= number_items){
        if (count <= balance_items[index] - orders[index]){
            balance_items[index] -= count;
            orders[index] += count;
            return items[index].get_name() + " ������� �������� " + to_string(count) + " ��. ";
        }
        else {
            change_popularity(index, my_random(0, 0.1));
            return items[index].get_name() + " ������ �� ��������� � �������. ������� ������������. ";
        }
    }
    else return "������ ������ ���. ";
}

std::string Cargo::remove_item(int index) {
    if (0 <= index && index < number_items){
        std::string answer = items[index].get_name() + " ����� ������������. �� �������� " + to_string(my_round(balance_items[index] * items[index].get_base_price() * 0.5, 2));
        balance += balance_items[index] * items[index].get_base_price() * 0.5;
        items.erase(items.cbegin() + index);
        cur_involvement.erase(cur_involvement.cbegin() + index);
        cur_popularity.erase(cur_popularity.cbegin() + index);
        price.erase(price.cbegin()+ index);
        capacity.erase(capacity.cbegin()+ index);
        balance_items.erase(balance_items.cbegin()+ index);
        orders.erase(orders.cbegin() + index);
        number_items--;
        return answer;
    }
    else return "������ ������ ���. ";
}

std::string Cargo::dismiss_employees(int number) {
    if (number > 0 && number <= employee){
        if (balance >= number * 175){
            employee-=number;
            balance-=number*175;
            return "�� ������� ��������� �������. �� ��������� " + to_string(number*175) + "$ ���������. ";
        }
        else return "� ��� ��� �����, ����� ��������� ��������� �������. ��������� " + to_string(number*175) + "$ �� ����� ������. ";
    }
    else return "������ ������ ���. ";
}

std::string Cargo::check_dismiss_employees(int number) {
    std::string answer;
    if (number > 0 && number <= employee) {
        answer = "�� ������ ������� " + to_string(number) +
                 " �����������. ��� ������� ��������� ��������� ��������� � ������� " +
                 to_string(number*75) + "$";
    }
    else {
        answer = "������������ ���������� �����������. ";
    }
    return answer;
}

std::string Cargo::promote_all() {
    double cost = 0;
    for (int index = 0; index < number_items; index++)
    {
        cost += pow(cur_popularity[index] / items[index].get_base_popularity(), 1.25) * 100;
    }
    if (balance >= cost){
        for (int index = 0; index < number_items; index++){
            change_popularity(index, my_random(0,1));
        }
        balance-=cost;
        return "�� ��������� " + to_string(cost) + " $ �� ������� ��������. ������������ ���� ������� �������. ";
    }
    else return "� ��� ��� ����� �� ���������� ��������� ��������. ��������� " + to_string(cost) +  "$";
}

std::string Cargo::check_promote_all() {
    double cost = 0;
    for (int index = 0; index < number_items; index++) {
        cost += pow(cur_popularity[index] / items[index].get_base_popularity(), 1.25) * 100;
    }
    std::string answer = "�������������� �������� ����� " + to_string(my_round(cost, 2)) +
                         "$ ��������� ������������ ���� �������. ";
    return answer;
}

std::string Cargo::promote_item(int index) {
    if (0 <= index && index < number_items){
        double cost = pow(cur_popularity[index] / items[index].get_base_popularity(), 1.25) * 100;
        if (cost <= balance){
            balance -= cost;
            change_popularity(index, my_random(0,1));
            return "�� ������� ��������� �������� ���������� " + to_string(cost)+ "$";
        }
        else return "� ��� ��� ����� �� ���������� ��������� ��������. ��������� " + to_string(cost) + "$";
    }
    else return "��� ������ ������.";
}

std::string Cargo::check_promote_item(int index) {
    std::string answer;
    if (0 <= index && index < number_items){
        double cost = pow(cur_popularity[index] / items[index].get_base_popularity(), 1.25) * 100;
        answer = "��������� ������� ��� ����� ������: " + to_string(my_round(cost, 2));
    }
    else answer = "������������ ����� ������. ";
    return answer;
}

std::string Cargo::day() {
    std::string answer = "����� " + name + '\n';
    if (balance > 0){
        for (int i = 8; i < 20; i++){
            answer += to_string(i) + ":00\n";
            for (int j = 0; j < number_items; j++){
                double x = price[i]/items[i].get_base_price();
                answer += buy(j, (int)((my_random(cur_involvement[j], cur_popularity[j])) * pow(16, log(1/x)))) + '\n';
            }
        }
        int free_employee = employee;
        for (int j = 0; j < number_items; j++){
            int order = ceil((double)orders[j]/ items[j].get_effectiveness());
            if (free_employee >= order){
                balance+=price[j]*orders[j];
                free_employee-=order;
                answer += items[j].get_name() + " �������� ����� �� " + to_string(orders[j]) + "��" + '\n';
            }
            else{
                int reject = orders[j] - free_employee;
                balance+= free_employee * items[j].get_effectiveness() * price[j];
                answer += items[j].get_name();
                if (free_employee > 0) answer += " �������� ����� �� " + to_string(orders[j]) + "��";
                change_popularity(j, my_random(-(double)(reject/order), 0));
                answer += " �� �������� ����� �� " + to_string(reject) + "��" + '\n';
                free_employee = 0;
            }
            orders[j] = 0;
        }
    }
    balance-=employee*25;
    answer += "�� ������ �������� ����������� ��������� " + to_string(employee*25) + "$\n";
    if (auto_refill) answer+=refill_all();
    return answer;
}

std::string Cargo::get_info_about_item(int index) {
    std::string answer;
    if (0 <= index && index < number_items) {
        answer = Seller::get_info_about_item(index);
        answer += "\n���� �������� ������ ������ : " + std::to_string(items[index].get_effectiveness());
    }
    else answer = "��� ������ ������.";
    return answer;
}
