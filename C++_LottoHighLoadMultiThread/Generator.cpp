//
// Created by Danon on 02.05.2022.
//

#include "Generator.h"

Ticket Generator::generate_random_ticket(unsigned long long ID) {
    Ticket ticket = generate_ticket(ID);
    randomizeTicket(ticket);
    return ticket;
}

Generator::Generator() {
    random_device rd;
    mersenne.seed(rd());
    for (short i = 1; i < 91; i++) {
        basket.push_back(i);
    }
}

Ticket Generator::generate_ticket(unsigned long long ID) {
    return Ticket(ID);
}

void Generator::setChance(int unsold_percent) {
    merchant.setChance(unsold_percent);
}

bool Generator::sell(Ticket &ticket) {
    return merchant.sellTicket(ticket, mersenne);
}

void Generator::randomizeTicket(Ticket &ticket) {
    vector<unsigned char> basket1(basket);
    int size = 90;
    for (auto &line : ticket.numbers)
        for (int j = 0; j < 5; j++)
        {
            unsigned int indx = mersenne() % size;
            size--;
            line.push_back(basket1[indx]);
            basket1.erase(basket1.begin() + indx);
        }
}

bool Generator::Seller::sellTicket(const Ticket &ticket, mt19937 &random) const {
    unsigned int sell_chance = random() % 100 + 1;
    return sell_chance > chance;

}

Generator::Seller::Seller() {
    chance = 0;
}

void Generator::Seller::setChance(int unsold_percent) {
    chance = unsold_percent;
}

bool generateTickets(Generator &gen, unsigned long long file_index, FileManager &fm) {
    forward_list<Ticket> my_pocket;
    size_t size = fm.get_pack_size();
    ofstream data_file(fm.makeName(file_index), ios_base::binary|ios_base::trunc);
    if (!data_file.is_open()) {
        return false;
    }
    for (size_t i = 0; i < size; i++) {
        Ticket tic = gen.generate_random_ticket(file_index*size + i);
        if (gen.sell(tic)) {
            data_file << tic;
        }
    }
    data_file.close();
    return true;
}

unsigned long long Ticket::getID() const {
    return ticketID;
}

unsigned long long Ticket::getPrize() const {
    return prize;
}