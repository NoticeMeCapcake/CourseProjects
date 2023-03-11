//
// Created by Danon on 25.04.2022.
//

#ifndef COURSE_FA_CONTAINER_H
#define COURSE_FA_CONTAINER_H

#include <cstddef>
#include <forward_list>
#include "ticket.h"

using namespace std;

struct Node;
class BaseIterator;
class MyIterator;
class StlIterator;
class Container;
class Connected_list;
class Forward_list;

class BaseIterator {
public:
    virtual BaseIterator& operator++()=0;
    virtual bool operator==(BaseIterator &other)=0;
    virtual bool operator!=(BaseIterator &other)=0;
    virtual Ticket& operator*()=0;
};

class MyIterator: public BaseIterator {
private:
    Node* _node;
    friend class Connected_list;
public:
    MyIterator();

    MyIterator(MyIterator &it);
    BaseIterator &operator++() override;
    Ticket &operator*() override;
    bool operator!=(BaseIterator &other) override;
    bool operator==(BaseIterator &other) override;
};

class StlIterator: public BaseIterator {
private:
    forward_list<Ticket>::iterator iter;
    friend class Forward_list;
public:
    StlIterator() = default;
    explicit StlIterator(forward_list<Ticket>::iterator it);
    StlIterator(StlIterator &it);
    StlIterator& operator=(const StlIterator& it);
    BaseIterator &operator++() override;
    Ticket &operator*() override;
    bool operator!=(BaseIterator &other) override;
    bool operator==(BaseIterator &other) override;
};


class Container {
private:

public:
    virtual void insert_after(BaseIterator &it, Ticket &) = 0;
    virtual void erase_after(BaseIterator &it) = 0;
    virtual bool empty() = 0;
    virtual void clear() = 0;
    virtual void push_front(Ticket &) = 0;
    virtual void pop_front() = 0;
    virtual Ticket& front() = 0;
    virtual BaseIterator& begin() = 0;
    virtual BaseIterator& before_begin() = 0;
    virtual BaseIterator& end() = 0;
    virtual Container* get_pure_pointer() = 0;
    virtual ~Container() = default;
};

struct Node {
    Node();
private:
    Ticket data;
    Node *next;
    bool operator==(Node & other);
    bool operator!=(Node & other);
    friend class Connected_list;
    friend class MyIterator;
};


class Connected_list : public Container {
private:
    Node *head;

    MyIterator bef_beg_iter, beg_iter, end_iter;

    void insert_after(Node *elem, Ticket &tic);
    void erase_after(Node *elem);
public:
    Connected_list();
    void push_front(Ticket &ticket) override;
    void erase_after(BaseIterator &it) override;
    void insert_after(BaseIterator &it, Ticket &tic) override;
    void pop_front() override;
    bool empty() override;
    Ticket& front() override;
    void clear() override;
    BaseIterator& begin() override;
    BaseIterator& before_begin() override;
    BaseIterator& end() override;
    Container *get_pure_pointer() override;
    ~Connected_list() override;

};

class Forward_list : public Container {
private:
    forward_list<Ticket> list;
    StlIterator bef_beg_iter, beg_iter, end_iter;
public:
    void push_front(Ticket &ticket) override;
    void erase_after(BaseIterator &it) override;
    void insert_after(BaseIterator &it, Ticket &tic) override;
    void pop_front() override;
    bool empty() override;
    Ticket& front() override;
    void clear() override;
    BaseIterator& begin() override;
    BaseIterator& before_begin() override;
    BaseIterator& end() override;
    Container *get_pure_pointer() override;
    ~Forward_list() override;
};


#endif //COURSE_FA_CONTAINER_H
