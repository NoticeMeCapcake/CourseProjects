#ifndef TICKET_H
#define TICKET_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <set>


using namespace std;


class Ticket
{
private:
    friend class Generator;
    friend class RaffleMachine;
    unsigned long long ticketID;
    vector<vector<short>> numbers;
    unsigned long long prize;

public:
    Ticket();
    Ticket(const Ticket &);
    Ticket &operator=(const Ticket &);

    explicit Ticket(unsigned long long id);

    unsigned long long getID() const;
    unsigned long long getPrize() const;
    const vector<vector<short>> &getField() const;

    void info();
    friend ostream& operator<<(ostream &out, const Ticket &tic);
    friend istream& operator>>(istream &in, Ticket& tic);
};

#endif // TICKET_H
