//
// Created by Danon on 02.05.2022.
//

#ifndef COURSE_FA_GENERATOR_H
#define COURSE_FA_GENERATOR_H

#include "FileManager.h"
#include "ticket.h"
#include <random>


class Generator {
private:
    vector<unsigned char> basket;
    class Seller {
        int chance;
    public:
        Seller();
        void setChance(int unsold_percent);
        bool sellTicket(const Ticket &ticket, mt19937 &random) const;
    } merchant;
    void randomizeTicket(Ticket &ticket);
    Ticket generate_ticket(unsigned long long ID);
//    random_device rd;
    mt19937 mersenne;
public:
    Generator();
    void setChance(int unsold_percent);
    bool sell(Ticket &);
    Ticket generate_random_ticket(unsigned long long ID);

    friend bool generateTickets(Generator &, unsigned long long file_index, FileManager &fm);
};


#endif //COURSE_FA_GENERATOR_H
