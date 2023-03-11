//
// Created by Danon on 14.05.2022.
//

#ifndef COURSE_FA_RAFFLEMACHINE_H
#define COURSE_FA_RAFFLEMACHINE_H

#include "Generator.h"


class RaffleMachine {
    vector<short> basket;
    int first_tour_prize;
    int second_tour_prize;
    int third_tour_prize;
    size_t fourth_part, twice_fourth_part, thrice_fourth_part;
    set<short> kegs;
    void get_new_keg();
    bool check_tickets(Container &list, int tour);
    bool is_winning(Ticket &tic, int tour);
    bool checkDataFTour(FileManager &fm, int multiplier, Container &collection, int tour);
    int get_tour_prize(int tour);
    int get_tour_constant(int tour);
    int get_start_kegs_num(int tour);
    void help_find(future<void> &fut, vector<unsigned long long> &IDs, Container *list);
public:

    RaffleMachine(size_t f_p_f_a);

    void conductTheTour(FileManager &fm, Container &list, int tour);

    bool findById(Container &list, unsigned long long ID, FileManager &fm);
    bool findInData(Container &list, bool check(Ticket &tic, unsigned long long num, set<short> *), unsigned long long num, FileManager &fm, vector<unsigned long long> &IDs);

};


#endif //COURSE_FA_RAFFLEMACHINE_H
