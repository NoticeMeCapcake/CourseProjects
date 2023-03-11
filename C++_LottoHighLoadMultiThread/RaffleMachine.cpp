//
// Created by Danon on 14.05.2022.
//

#include "RaffleMachine.h"

int RaffleMachine::get_start_kegs_num(int tour) {
    switch (tour) {
        case 1:
            return 4;
        case 2:
            return 14;
        case 3:
            return 29;
        default:
            return 0;
    }
}

void RaffleMachine::conductTheTour(FileManager &fm, Container &list, int tour) {
    while (kegs.size() < get_start_kegs_num(tour)) {
        get_new_keg();
    }

    bool is_someone_won = false;
    while (!is_someone_won) {
        get_new_keg();
        cout << "Вытянутые бочонки: ";
        for (auto el : kegs) {
            cout << el << " ";
        }
        cout << endl;
        future<bool> fut1 = async(launch::async, [&]{return checkDataFTour(fm, 0, list, tour);});
        future<bool> fut2 = async(launch::async, [&]{return checkDataFTour(fm, 1, list, tour);});
        future<bool> fut3 = async(launch::async, [&]{return checkDataFTour(fm, 2, list, tour);});
        future<bool> fut4 = async(launch::async, [&]{return checkDataFTour(fm, 3, list, tour);});

        bool a1 = fut1.get();
        bool a2 = fut2.get();
        bool a3 = fut3.get();
        bool a4 = fut4.get();

        is_someone_won = a1 or a2 or a3 or a4;

    }
}


bool RaffleMachine::checkDataFTour(FileManager &fm, int multiplier, Container &collection, int tour) {
    Container *list = collection.get_pure_pointer();
    bool is_someone_won = false;

    size_t shift = fourth_part * multiplier;
    for (size_t i = shift; i < fourth_part + shift; i++) {
        string path = fm.get_pre_name() + to_string(i);
        fm.readData(path, *list);
        if (check_tickets(*list, tour)) {
            is_someone_won = true;
            fm.rewriteData(path, *list);
        }
        list->clear();
    }
    delete list;
    return is_someone_won;
}

void RaffleMachine::get_new_keg() {
    if (kegs.size() == 90) return;
    short ind = rand() % basket.size();
    kegs.insert(basket[ind]);
    basket.erase(basket.begin() + ind);
}

bool RaffleMachine::is_winning(Ticket &tic, int tour_constant) {
    bool won = false;
    int counter = 0, walked = 0;
    int matches;
    for (auto & line : tic.numbers) {
        auto it = line.begin();
        walked++;
        matches = 0;
        while(it != line.end()) {
            if (kegs.contains(*it)) {
                matches++;
            }
            else {
                break;
            }
            it++;
        }
        if (matches == 5) {
            if ((++counter) == tour_constant and !(walked % tour_constant)) {
                cout << "Найден победитель с номером билета: " << tic.ticketID << endl;
                won = true;
            }
        }
        else {
            counter = 0;
        }
    }
    return won;
}

RaffleMachine::RaffleMachine(size_t f_p_f_a) {
    for (short i = 1; i < 91; i++) {
        basket.push_back(i);
    }
    first_tour_prize = 100;
    second_tour_prize = 1000;
    third_tour_prize = 10000;
    fourth_part = f_p_f_a;
    twice_fourth_part = fourth_part + fourth_part;
    thrice_fourth_part = twice_fourth_part + fourth_part;
}

bool RaffleMachine::check_tickets(Container &list, int tour) {
    bool is_data_changed = false;
    for (auto &it = list.begin(); it != list.end(); ++it) {
        if (is_winning(*it, get_tour_constant(tour))) {
            (*it).prize += get_tour_prize(tour);
            is_data_changed = true;
        }
    }
    return is_data_changed;
}

int RaffleMachine::get_tour_prize(int tour) {
    switch (tour) {
        case 1:
            return first_tour_prize;
        case 2:
            return second_tour_prize;
        case 3:
            return third_tour_prize;
        default:
            return 0;
    }
}

int RaffleMachine::get_tour_constant(int tour) {
    switch (tour) {
        case 1:
            return 1;
        case 2:
            return 3;
        case 3:
            return 6;
        default:
            return 0;
    }
}

bool RaffleMachine::findById(Container &list, unsigned long long int ID, FileManager &fm) {
    return fm.findById(list, ID);
}

void copyIDsToVec(vector<unsigned long long> &dst, Container *src) {
    for (auto &it = src->begin(); it != src->end(); ++it) {
        dst.push_back((*it).getID());
    }
}

bool RaffleMachine::findInData(Container &list, bool (*check)(Ticket &, unsigned long long, set<short>*),
                               unsigned long long num, FileManager &fm, vector<unsigned long long> &IDs) {
    Container *list1 = list.get_pure_pointer();
    Container *list2 = list.get_pure_pointer();
    Container *list3 = list.get_pure_pointer();
    Container *list4 = list.get_pure_pointer();

    for (int i = 0; i < fourth_part; i++) {
        future<void> fut1 = std::async(launch::async, [&]{return fm.readFileWithCheck(i, check, num, *list1, &kegs);});
        future<void> fut2 = std::async(launch::async, [&]{return fm.readFileWithCheck(i + fourth_part, check, num, *list2, &kegs);});
        future<void> fut3 = std::async(launch::async, [&]{return fm.readFileWithCheck(i + twice_fourth_part, check, num, *list3, &kegs);});
        future<void> fut4 = std::async(launch::async, [&]{return fm.readFileWithCheck(i + thrice_fourth_part, check, num, *list4, &kegs);});

        help_find(fut1, IDs, list1);
        help_find(fut2, IDs, list2);
        help_find(fut3, IDs, list3);
        help_find(fut4, IDs, list4);
    }

    delete list1;
    delete list2;
    delete list3;
    delete list4;

    return !IDs.empty();
}

void RaffleMachine::help_find(future<void> &fut, vector<unsigned long long int> &IDs, Container *list) {
    fut.get();
    copyIDsToVec(IDs, list);
    list->clear();
}

