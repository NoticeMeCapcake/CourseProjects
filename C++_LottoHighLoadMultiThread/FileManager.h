//
// Created by Danon on 04.05.2022.
//

#ifndef COURSE_FA_FILEMANAGER_H
#define COURSE_FA_FILEMANAGER_H
#include "Container.h"
#include <experimental/filesystem>
#include <future>

namespace fs = std::experimental::filesystem;

class FileManager {
    string data_dir_name;
    size_t entries_in_one_file;
    string data_file_pre_name;

    void createDatabase();
public:
    FileManager();
    const string & get_pre_name() const;
    size_t get_pack_size() const;
    void readData(const string &path, Container &collection);
    void rewriteData(const string &path, Container &collection);

    string makeName(unsigned long long file_index);


    void readFileWithCheck(unsigned int indx, bool check(Ticket &tic, unsigned long long num, set<short> *), unsigned long long num, Container &list, set<short>*kegs);

    bool findById(Container &list, unsigned long long int ID);

    ~FileManager();
};


#endif //COURSE_FA_FILEMANAGER_H
