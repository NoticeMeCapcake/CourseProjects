#include "ticket.h"


Ticket::Ticket(unsigned long long id) {
    prize = 0;
    ticketID = id;

    for (int i = 0; i < 6; i++) {
        numbers.emplace_back();
    }
}

Ticket &Ticket::operator=(const Ticket &tic) = default;

Ticket::Ticket(const Ticket &tic) {
    ticketID = tic.ticketID;
    prize = tic.prize;
    numbers = tic.numbers;
}

void Ticket::info() {
    cout << "ID: " << ticketID << endl;
    cout << "Prize: " << prize << endl;
    cout << "Fields:" << endl;
    for (auto &line : numbers) {
        for (auto num : line) {
            cout << num << " ";
        }
        cout << endl;
    }
    cout << endl;

}

Ticket::Ticket() {
    ticketID = 0;
    prize = 0;

    for (int i = 0; i < 6; i++) {
        numbers.emplace_back();
//        numbers_const.emplace_back("");
    }
}

ostream &operator<<(ostream &out, const Ticket &tic) {
    out << tic.ticketID << endl;
    out << tic.prize << endl;
    for (char i = 0; i < 6; i++) {
        const vector<short> &line = tic.numbers[i];
        for (short num : line) {
            out << num << " ";
        }
        out << endl;
    }
    return out;
}

istream &operator>>(istream &in, Ticket &tic) {
    in >> tic.ticketID;
    in >> tic.prize;
    string nullifier;
    std::getline(in, nullifier);

    for (char i = 0; i < 6; i++) {
        vector<short> &keg_line = tic.numbers[i];
        string str_line;
        std::getline(in, str_line);
        short n = 0;
        for (char symbol_of_line : str_line) {
            if (symbol_of_line == ' ') {
                if (n) {
                    keg_line.push_back(n);
                    n = 0;
                }
                continue;
            }
            n *= 10;
            n += short(symbol_of_line) - '0';
        }
    }
    return in;
}

const vector<vector<short>> &Ticket::getField() const {
    return numbers;
}
