//
// Created by Danon on 04.05.2022.
//

#include "FileManager.h"

void FileManager::createDatabase() {
    if (fs::exists(data_dir_name)) {
        fs::remove_all(data_dir_name);
    }
    fs::create_directory(data_dir_name);
}

FileManager::FileManager() {
    entries_in_one_file = 16384;
    data_dir_name = "database1";
    data_file_pre_name = data_dir_name + "/data";

    try {
        createDatabase();
    }
    catch(int &err) {
        return;
    }
}


FileManager::~FileManager() {

}

void FileManager::readData(const string &path, Container &collection) {

    ifstream data_file(path, ios_base::binary|ios_base::in);


    if (!data_file.is_open())
        return;

    for (int i = 0; i < entries_in_one_file and !data_file.eof(); i++) {
        Ticket cur;
        data_file >> cur;
        if (data_file.eof()) {
            data_file.close();
            return;
        }
        collection.push_front(cur);
    }
    data_file.close();
}


void FileManager::rewriteData(const string &path, Container &collection) {
    ofstream data_file(path, ios_base::binary|ios_base::trunc);

    if (!data_file.is_open()) {
        return;
    }
    for (auto &it = collection.begin(); it != collection.end(); ++it) {
        data_file << (*it);
    }
    data_file.close();
}


size_t FileManager::get_pack_size() const {
    return entries_in_one_file;
}

const string &FileManager::get_pre_name() const {
    return data_file_pre_name;
}


bool FileManager::findById(Container &list, unsigned long long int ID) {
    unsigned int number_of_file = ID / entries_in_one_file;
    ifstream fin(makeName(number_of_file), ios_base::binary);
    if (!fin.is_open()) {
        cout << "File with this ID is not existing" << endl;
        return false;
    }

    while (!fin.eof()) {
        Ticket tic;
        fin >> tic;
        if (fin.eof()) {
            break;
        }
        if (tic.getID() == ID) {
            list.push_front(tic);
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}


void FileManager::readFileWithCheck(unsigned int indx, bool (*check)(Ticket &, unsigned long long, set<short>*), unsigned long long  num, Container &collection, set<short>*kegs) {
    Container *list = collection.get_pure_pointer();
    readData(makeName(indx), *list);

    for (auto &it = list->begin(); it != list->end(); ++it) {
        if (check(*it, num, kegs)) {
            collection.push_front(*it);
        }
    }
    delete list;
}

string FileManager::makeName(unsigned long long int file_index) {
    return data_file_pre_name + to_string(file_index);
}
