#include <cstdlib>
#include "RaffleMachine.h"
#include <map>
#include <random>
#include <chrono>
#include <future>

unsigned long long MAX_ID = 100000000;

enum ACTION {
    REPEAT = 1, FIND_ID, FIND_PRIZE, FIND_FIELDS, CLOSE
};

ACTION ask_ACT();
void askAMOUNT(int &end);
void ask_NUM(unsigned long long min, unsigned long long max, unsigned long long &num);
void ask_YN(string &usr_ans);
void exiting(Container *my_pocket);
void find_by_id(FileManager &fm, RaffleMachine &rm, Container &pocket);
bool check_prize(Ticket &tic, unsigned long long prize, set<short> *);
bool check_filled_fields (Ticket &tic, unsigned long long lines_count, set<short> *kegs);
void printIDs(vector<unsigned long long> &IDs, Container &list, FileManager &fm);
void find_by_prize(FileManager &fm, RaffleMachine &rm, Container &pocket);
void find_by_fields(FileManager &fm, RaffleMachine &rm, Container &pocket);
void conductTour(RaffleMachine &rm, FileManager &fm, Container &pocket, int tour);


void askAMOUNT(int &end) {
    string usr_ans;
    while (true) {
        cout << ">>";
        std::getline(cin, usr_ans);
        try {
            int ans = stoi(usr_ans);
            if (ans < 1 or ans > 4) {
                cout << "Неверный ввод" << endl;
                continue;
            }
            if (ans == 1) {
                end = 2;
            } else {
                end = (ans - 1) * 15;
            }
        }
        catch (invalid_argument const& ex1)
        {
            std::cout << "Неверный ввод " << endl;
            continue;
        }
        catch(out_of_range const& ex2) {
            std::cout << "Неверный ввод " << endl;
            continue;
        }
        break;
    }
}

bool check_prize(Ticket &tic, unsigned long long int prize, set<short> *) {
    return tic.getPrize() == prize;
}

ACTION ask_ACT() {
    string usr_ans;
    ACTION act;
    while (true) {
        cout << ">>";
        std::getline(cin, usr_ans);
        try {
            int ans = stoi(usr_ans);
            if (ans < 1 or ans > 5) {
                continue;
            }
            act = ACTION(ans);
        }
        catch (invalid_argument const &ex1) {
            std::cout << "Неверный ввод " << endl;
            continue;
        }
        catch (out_of_range const &ex2) {
            std::cout << "Неверный ввод " << endl;
            continue;
        }
        break;
    }
    return act;
}

void ask_NUM(unsigned long long int min, unsigned long long int max, unsigned long long int &num) {
    string usr_ans;
    while (true) {
        cout << ">>";
        std::getline(cin, usr_ans);
        try {
            num = stoi(usr_ans);
            if (num < min or num > max) {
                std::cout << "Неверный ввод" << endl;
                continue;
            }
        }
        catch (invalid_argument const &ex1) {
            std::cout << "Неверный ввод" << endl;
            continue;
        }
        catch (out_of_range const &ex2) {
            std::cout << "Неверный ввод" << endl;
            continue;
        }
        break;
    }
}

bool check_filled_fields(Ticket &tic, unsigned long long int lines_count, set<short> *kegs) {
    unsigned long long lines = 0;
    for (auto &line: tic.getField()) {
        short cnt = 0;
        for (auto &num: line) {
            if (kegs->contains(num)) {
                cnt++;
            }
        }
        if (cnt == 5) {
            lines++;
        }
    }
    return lines == lines_count;
}

void ask_YN(string &usr_ans) {
    while (true) {
        cout << ">>";
        std::getline(cin, usr_ans);
        if (usr_ans == "Y" or usr_ans == "y" or usr_ans == "N" or usr_ans == "n") {
            break;
        }
        else {
            cout << "Неверный ввод" << endl;
        }
    }
}

void printIDs(vector<unsigned long long int> &IDs, Container &list, FileManager &fm) {
    string usr_ans;
    auto it = IDs.begin();
    while (true) {
        cout << "Вывести 10 найденных билетов? [Y/N]" << endl;
        ask_YN(usr_ans);
        if (usr_ans == "N" or usr_ans == "n") {
            return;
        }

        list.clear();
        int cnt = 0;
        while (it != IDs.end() and cnt != 10) {
            fm.findById(list, *it);
            it++;
            cnt++;
        }
        for (auto &l_it = list.begin(); l_it != list.end(); ++l_it) {
            (*l_it).info();
        }
        if (it == IDs.end()) {
            cout << "Выведены все билеты!" << endl;
            return;
        }

    }
}

void find_by_id(FileManager &fm, RaffleMachine &rm, Container &pocket) {
    unsigned long long ID;
    string usr_ans;
    while (true) {
        pocket.clear();
        cout << "Введите номер билета:" << endl;
        ask_NUM(1, MAX_ID, ID);
        if (rm.findById(pocket, ID, fm)) {
            cout << "Найденный билет" << endl;
            for (auto &it = pocket.begin(); it != pocket.end(); ++it) {
                (*it).info();
            }
        } else {
            cout << "Билет с таким номером в тираже не участвовал" << endl;
        }
        cout << "Повторить поиск? [Y/N]" << endl;
        ask_YN(usr_ans);
        if (usr_ans == "N" or usr_ans == "n") {
            cout << "Возврат в меню" << endl;
            return;
        }
    }
}

void find_by_prize(FileManager &fm, RaffleMachine &rm, Container &pocket) {
    string usr_ans;
    vector<unsigned long long> IDs;
    unsigned long long prize;
    while (true) {
        pocket.clear();
        cout << "Введите размер выгрыша билета:" << endl;
        ask_NUM(100, 11100, prize);
        if (rm.findInData(pocket, check_prize, prize, fm, IDs)) {
            cout << "Найдено билетов: " << IDs.size() << endl;
            printIDs(IDs, pocket, fm);
            IDs.clear();
        } else {
            cout << "Ни один билет не нашёлся" << endl;
        }
        cout << "Повторить поиск? [Y/N]" << endl;
        ask_YN(usr_ans);
        if (usr_ans == "N" or usr_ans == "n") {
            cout << "Возврат в меню" << endl;
            return;
        }
    }
}

void find_by_fields(FileManager &fm, RaffleMachine &rm, Container &pocket) {
    string usr_ans;
    vector<unsigned long long> IDs;
    unsigned long long amount;
    while (true) {
        pocket.clear();
        cout << "Введите количество совпавших рядов в билете:" << endl;
        ask_NUM(1, 6, amount);
        if (rm.findInData(pocket, check_filled_fields, amount, fm, IDs)) {
            cout << "Найдено билетов: " << IDs.size() << endl;
            printIDs(IDs, pocket, fm);
            IDs.clear();
        } else {
            cout << "Ни один билет не нашёлся" << endl;
        }

        cout << "Повторить поиск? [Y/N]" << endl;
        ask_YN(usr_ans);
        if (usr_ans == "N" or usr_ans == "n") {
            cout << "Возврат в меню" << endl;
            return;
        }
    }
}

void conductTour(RaffleMachine &rm, FileManager &fm, Container &pocket, int tour) {
    cout << string("Начинаем розыгрыш ") + ((tour == 1)?"первого":(tour==2)?"второго":"третьего") + " тура" << endl;
    auto begin = std::chrono::steady_clock::now();

    rm.conductTheTour(fm, pocket, tour);

    auto end_t = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - begin);
    cout << string((tour == 1)?"Первый":(tour==2)?"второй":"третий") + " тур проведён за " << elapsed_ms.count() / 1000 << " сек" << endl;
}

void exiting(Container *my_pocket) {
        cout << "Завершение программы..." << endl;
        delete my_pocket;
        exit(0);
}

map<ACTION, void (*)(FileManager&, RaffleMachine&, Container&)> actions =
        {
        make_pair(FIND_ID, find_by_id),
        make_pair(FIND_PRIZE, find_by_prize),
        make_pair(FIND_FIELDS, find_by_fields)
        };


int main() {
    system("chcp 65001>nul");
    srand(time(nullptr));

    Container *my_pocket;

    while (true) {
        string usr_ans;
        cout << "Добро пожаловать в программу для проведения лоттереи." << endl;
        cout << "Хотите ли вы начать генерацию билетов? [Y/N]" << endl;
        ask_YN(usr_ans);


        cout << "Какое количество билетов будем генерировать?" << endl;
        cout << "1) 130 тысяч" << endl;
        cout << "2) 1 миллион" << endl;
        cout << "3) 2 миллиона" << endl;
        cout << "4) 3 миллиона" << endl;

        int end = 1;  // 60 == 4 миллиона, 45 == 3... 30 -- 2, 15 -- 1

        askAMOUNT(end);
        int end2 = end + end;
        int end3 = end2 + end;

        cout << "Производим генерацию билетов..." << endl;

        cout << "На какой коллекции сделаем?" << endl;
        cout << "1) Собственная реализация односвязного списка" << endl;
        cout << "2) std::forward_list" << endl;
        while (true) {
            cout << ">>";
            std::getline(cin, usr_ans);
            if (usr_ans == "1") {
                my_pocket = new Connected_list;

            } else if (usr_ans == "2"){
                my_pocket = new Forward_list;
            } else {
                std::cout << "Неверный ввод " << endl;
                continue;
            }
            break;
        }


        Generator gen;

        Container &pocket = *my_pocket;
        gen.setChance(5);
        auto begin = std::chrono::steady_clock::now();
        FileManager fm;
        for (int i = 0; i < end; i++) {
            future<bool> fut1 = std::async(launch::async, [&] { return generateTickets(gen, i, fm); });
            future<bool> fut2 = std::async(launch::async, [&] { return generateTickets(gen, i + end, fm); });
            future<bool> fut3 = std::async(launch::async, [&] { return generateTickets(gen, i + end2, fm); });
            future<bool> fut4 = std::async(launch::async, [&] { return generateTickets(gen, i + end3, fm); });

            fut1.get();
            fut2.get();
            fut3.get();
            fut4.get();
        }


        auto end_t = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - begin);
        cout << "Билеты сгенерированы за " << elapsed_ms.count() / 1000 << "сек" << endl;

        cout << "Начнём розыгрыш?[Y/N]" << endl;
        ask_YN(usr_ans);
        if (usr_ans == "N" or usr_ans == "n") {
            exiting(my_pocket);
        }

        RaffleMachine rm(end);

        conductTour(rm, fm, pocket, 1);
        conductTour(rm, fm, pocket, 2);
        conductTour(rm, fm, pocket, 3);

        pocket.clear();
        cout << "Розыгрыш проведён" << endl;
        while (true) {
            ACTION act;
            cout << "Что сделать дальше?" << endl;
            cout << "1) Повторить генерацию и розыгрыш" << endl;
            cout << "2) Найти билет с заданным номером" << endl;
            cout << "3) Найти все билеты по заданному размеру выигрыша" << endl;
            cout << "4) Найти все билеты, по заданному количеству совпавших рядов" << endl;
            cout << "5) Выйти из приложения" << endl;

            act = ask_ACT();
            if (act == CLOSE) {
                exiting(my_pocket);
            }
            else if (act == REPEAT) {
                break;
            }
            actions[act](fm, rm, pocket);

        }
        delete my_pocket;
    }

}

