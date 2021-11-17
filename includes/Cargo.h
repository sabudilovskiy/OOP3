//
// Created by MRV on 16.11.2021.
//
#include "Seller.h"
#ifndef CARGO_OOP3_H
#define CARGO_OOP3_H
class Cargo : public Seller{
protected:
    std::vector<int> orders;
public:
    Cargo(Organization* owner, const std::string& name) {
        this->owner = owner;
        this->name = name;
    }
    std::string add_item(Item item) override{
        if (balance >= 200){
            items.push_back(item);
            cur_involvement.push_back(item.get_base_involvement());
            cur_popularity.push_back(item.get_base_popularity());
            capacity.push_back(2*item.get_capacity());
            balance_items.push_back(0);
            orders.push_back(0);
            balance-=200;
            number_items++;
            return "Товар успешно добавлен.";
        }
        else return "Для расширения ассортимента требуется иметь не менее 200$ на счету склада.";
    }
    std::string check_add_item() override{
        std::string answer;
        if (balance >= 200){
            answer = "Вы можете расширить ассортимент за 200$.";
        }
        else{
            answer = "Вы не можете расширить ассортимент за 200$: на счету склада нет достаточного количества денег.";
        }
        return answer;
    }
    std::string buy(int index, int count) override{
        if (0 <= index && index <= number_items){
            if (count <= balance_items[index] - orders[index]){
                balance_items[index] -= count;
                orders[index] += count;
                return items[index].get_name() + " Клиенты заказали " + to_string(count) + " шт. ";
            }
            else {
                change_popularity(index, my_random(0, 0.1));
                return items[index].get_name() + " Товара не оказалось в наличии. Клиенты разочарованы. ";
            }
        }
        else return "Такого товара нет. ";
    }
    std::string remove_item(int index) override{
        if (0 <= index && index < number_items){
            std::string answer = items[index].get_name() + " Товар ликвидирован. Мы получили " + to_string(my_round(balance_items[index] * items[index].get_base_price() * 0.5, 2));
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
        else return "Такого товара нет. ";
    }
    std::string dismiss_employes(int number) override{
        if (number > 0 && number <= employee){
            if (balance >= number * 175){
                employee-=number;
                balance-=number*175;
                return "Мы успешно сократили рабочих. Мы заплатили " + to_string(number*175) + "$ неустойки. ";
            }
            else return "У нас нет денег, чтобы выплатить неустойку рабочим. Требуется " + to_string(number*175) + "$ на счету склада. ";
        }
        else return "Такого товара нет. ";
    }
    std::string check_dismiss_employes(int number) override{
        std::string answer;
        if (number > 0 && number <= employee) {
            answer = "Вы можете уволить " + to_string(number) +
                     " сотрудников. Вам придётся выплатить недельную неустойку в размере " +
                     to_string(number*75) + "$";
        }
        else {
            answer = "Некорректное количество сотрудников. ";
        }
    }
    std::string promote_all() override{
        double cost = 0;
        for (int index; index < number_items; index++)
        {
            cost += pow(cur_popularity[index] / items[index].get_base_popularity(), 1.25) * 100;
        }
        if (balance >= cost){
            for (int index; index < number_items; index++){
                change_popularity(index, my_random(0,1));
            }
            balance-=cost;
            return "Мы потратили " + to_string(cost) + " $ на рекламу магазина. Популярность всех товаров выросла. ";
        }
        else return "У нас нет денег на проведение рекламной кампании. Требуется " + to_string(cost) +  "$";
    }
    std::string check_promote_all() override {
        double cost = 0;
        for (int index; index < number_items; index++) {
            cost += pow(cur_popularity[index] / items[index].get_base_popularity(), 1.25) * 100;
        }
        std::string answer = "Рекламирование магазина стоит " + to_string(my_round(cost, 2)) +
                      "$ Повысится популярность всех товаров. ";
        return answer;
    }
    std::string promote_item(int index) override{
        if (0 <= index && index < number_items){
            double cost = pow(cur_popularity[index] / items[index].get_base_popularity(), 1.25) * 100;
            if (cost <= balance){
                balance -= cost;
                change_popularity(index, my_random(0,1));
                return "Мы провели рекламную кампанию стоимостью " + to_string(cost)+ "$";
            }
            else return "У нас нет денег на проведение рекламной кампании. Требуется " + to_string(cost) + "$";
        }
        else return "Нет такого товара.";
    }
    std::string check_promote_item(int index) override{
        std::string answer;
        if (0 <= index && index < number_items){
            double cost = pow(cur_popularity[index] / items[index].get_base_popularity(), 1.25) * 100;
            answer = "Стоимость рекламы для этого товара: " + to_string(my_round(cost, 2));
        }
        else answer = "Некорректный номер товара. ";
        return answer;
    }
    std::string day() override {
        std::string answer = "Склад " + name + '\n';
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
                int order = ceil((double)orders[j]/items[j].get_one_employee());
                if (free_employee >= order){
                    balance+=price[j]*orders[j];
                    free_employee-=order;
                    answer += items[j].get_name() + " Выполнен заказ на " + to_string(orders[j]) + "шт" + '\n';
                }
                else{
                    int reject = orders[j] - free_employee;
                    balance+=free_employee*items[j].get_one_employee()*price[j];
                    answer += items[j].get_name();
                    if (free_employee > 0) answer += " Выполнен заказ на " + to_string(orders[j]) + "шт";
                    change_popularity(j, my_random(-(double)(reject/order), 0));
                    answer += " Не выполнен заказ на " + to_string(reject) + "шт" + '\n';
                    free_employee = 0;
                }
                orders[j] = 0;
            }
        }
        balance-=employee*25;
        answer += "На оплату зарплаты сотрудников потрачено " + to_string(employee*25) + "$\n";
        if (auto_refill) answer+=refill_all();
        return answer;
    }
    std::string get_info_about_item(int index) override{
        std::string answer;
        if (0 <= index && index < number_items) {
            answer = Seller::get_info_about_item(index);
            answer += "\nОдин работник склада довезёт : " + std::to_string(items[index].get_one_employee());
        }
    }
};
#endif