//
// Created by MRV on 18.11.2021.
//

#include "Seller.h"
#include "Organization.h"

void Seller::change_popularity(int index, double cof) {
    if (0 <= index && index < number_items){
        cur_popularity[index] += cur_popularity[index] * cof;
        if (cur_involvement > cur_popularity) cur_involvement = cur_popularity;
    }
}

int Seller::get_employee() const {
    return employee;
}

std::string Seller::check_close() {
    double cur_balance = balance - 175*employee;
    for (int index = 0; index < number_items; index++){
        balance+=items[index].get_base_price()*balance_items[index]*0.5;
    }
    return "Общий баланс предприятия с учётом неустоек из-за увольнений и продажи товара за половину от себестоимости: " + to_string(
            my_round(cur_balance, 2));
}

std::string Seller::close() {
    double cur_balance = balance - 175*employee;
    for (int index = 0; index < number_items; index++){
        balance+=items[index].get_base_price()*balance_items[index]*0.5;
    }
    if (cur_balance > 0){
        while (number_items>0){
            remove_item(0);
        }
        dismiss_employees(employee);
        owner->recieve_money(cur_balance);
        balance = 0;
        return "Предприятие прекратило свою работу. Остаток денег переведён на счета компании: " + to_string(
                my_round(cur_balance, 2)) + "$";
    }
    else{
        if (owner->get_balance() + cur_balance > 0){
            receive_money(owner->take_money(cur_balance));
            while (number_items>0){
                remove_item(0);
            }
            dismiss_employees(employee);
            return "Предприятие прекратило свою работу. Для закрытия долгов предприятия были потрачены " + to_string(
                    my_round(abs(cur_balance), 2)) + "$";
        }
        else{
            return "Нам не хватает денег для покрытия долгов предприятия.";
        }
    }
}

const std::string &Seller::get_name() const {
    return name;
}

void Seller::set_name(const std::string &name) {
    Seller::name = name;
}

std::string Seller::switch_autorefill() {
    auto_refill = !auto_refill;
    std::string temp  = (!auto_refill)?"ы": "";
    return "Автопополнение теперь в" + temp + "ключено. ";
}

std::string Seller::get_info_about_item(int index) {
    std::string answer;
    if (0 <= index && index < number_items){
        answer = "Лот №" + to_string(index) + " " + items[index].get_name()+ "\n";
        answer += "Популярность: " + to_string(my_round(cur_popularity[index],2));
        answer += " Вовлеченность: " + to_string(my_round(cur_involvement[index],2)) + "\n";
        answer += "Текущая цена: " + to_string(price[index]);
        answer += " Базовая цена: " + to_string(items[index].get_base_price());
        answer += " Вместимость: " + std::to_string(capacity[index]);
        answer += " В наличии: " + std::to_string(balance_items[index]);
    }
    else "Некорректный номер товара.";
    return answer;
}

std::string Seller::get_info_about_items() {
    std::string answer;
    for (int index = 0; index < number_items; index++) answer += get_info_about_item(index) + '\n';
    return answer;
}

int Seller::get_number_items() const {
    return number_items;
}

double Seller::get_balance() const {
    return balance;
}

std::string Seller::refill(int index) {
    if (0<=index && index < number_items){
        double need = (capacity[index] - balance_items[index]) * items[index].get_base_price();
        if (balance > need) {
            balance_items[index] = capacity[index];
            return items[index].get_name() + " Мы пополнили успешно запасы. Потрачено " + std::to_string(need) + "$";
        }
        else return "У вас нет достаточного количества денег. Требуется не менее " + std::to_string(need) + "$ на счету предприятия.";
    }
    else return "Такого товара нет.";
}

std::string Seller::check_refill(int index) {
    std::string answer;
    if (0<=index && index < number_items){
        double need = (capacity[index] - balance_items[index]) * items[index].get_base_price();
        answer = "На пополнение данной позиции требуется " + to_string(my_round(need, 2)) + "$. На счету магазина: " + to_string(
                my_round(balance,2));
    }
    return answer;
}

std::string Seller::check_refill_all() {
    std::string answer;
    double need = 0;
    for (int index = 0; index < number_items; index++) need += (capacity[index] - balance_items[index]) * items[index].get_base_price();
    answer = "На пополнение всех позиций требуется " + to_string(my_round(need, 2)) + "$. На счету магазина: " + to_string(my_round(balance,2));
    return answer;
}

std::string Seller::refill_all() {
    double need = 0;
    for (int index = 0; index < number_items; index++) need += (capacity[index] - balance_items[index]) * items[index].get_base_price();
    if (balance >= need){
        for (int index = 0; index < number_items; index++) balance_items[index] = capacity[index];
        balance-=need;
        return "Вы пополнили запасы " + name + " за " + to_string(need) + "$";
    }
    else return "У Вас недостаточно денег для пополнение запасов " + name + ". Требуется не менее " + to_string(need) + "$" + " на счету предприятия.";
}

std::string Seller::check_remove_item(int index) {
    std::string answer;
    if (0 <= index && index < number_items){
        double plus = balance_items[index] * items[index].get_base_price() * 0.5;
        answer = "Вы избавитесь от " + items[index].get_name() + " в ассортименте и вернёте поставщику за половину стоимости  " + to_string(balance_items[index]) + "Таким образом, Вы получите " + to_string(
                my_round(plus, 2))  + "$";
    }
    else {
        answer = "Некорректный номер товара. ";
    }
    return answer;
}

std::string Seller::hire_employees(int number) {
    if (number * 300 <= balance){
        employee += number;
        balance -= number * 300;
        return "Вы успешно наняли сотрудников. Потрачено на первичные выплаты : " + to_string(number*300) + "$ ";
    }
    else return "Вы не можете позволить себе нанять сотрудников: требуется не менее " + to_string(number*300) + "$ на счету предприятия";
}

std::string Seller::check_hire_employees(int number) {
    std::string answer = "Нанять " + to_string(number) + " сотрудников стоит " + to_string(number*300) + "$. Ежедневная зарплата нанятых сотрудников: " + to_string(25*number) + " $";
    return answer;
}

std::string Seller::receive_money(double money) {
    if (money > 0){
        double from_owner = owner->take_money(money);
        balance += from_owner;
        if (from_owner > 0){
            return "Вы успешно перевели деньги со счета компании на счёт предприятия";
        }
        else return "Недостаточно денег на счету компании";
    }
    else return "Некорректная сумма для перевода";
}

std::string Seller::take_money(double money) {
    if (money > 0) {
        if (money <= balance){
            balance-=money;
            owner->recieve_money(money);
            return "Вы успешно перевели деньги со счета предприятия на счёт компании";
        }
        else return "Недостаточно денег на счету компании";
    }
    else return "Некорректная сумма для перевода";
}

double Seller::get_balance() {
    return balance;
}

std::string Seller::get_info_about_items_to_add(std::vector<Item> &base) {
    std::string answer;
    for (int index = 0; index < base.size(); index++){
        answer += base[index].get_info() + "\n";
    }
    return answer;
}

std::string Seller::change_price(int index, double new_price) {
    if (0 <= index && index < number_items){
        if (new_price>0){
            price[index] = new_price;
            return items[index].get_name() + " Вы изменили цену товара. Теперь он продаётся за " + to_string(new_price) + "$";
        }
        else return "Некорректная цена.";
    }
    else return "Такого товара не существует.";
}

void Seller::change_involvement(int index, double cof) {
    if (0 <= index && index < number_items){
        cur_involvement[index] += cur_involvement[index] * cof;
        if (cur_involvement > cur_popularity) cur_involvement = cur_popularity;
    }
}
