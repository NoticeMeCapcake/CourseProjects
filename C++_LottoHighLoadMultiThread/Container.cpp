//
// Created by Danon on 25.04.2022.
//

#include "Container.h"

MyIterator::MyIterator(MyIterator &it) {
    _node = it._node;
}


BaseIterator &MyIterator::operator++() {
    if (_node != nullptr)
        _node = _node->next;

    return *this;
}

Ticket &MyIterator::operator*() {
    return _node->data;
}

bool MyIterator::operator!=(BaseIterator &other) {
    return _node != dynamic_cast<MyIterator &>(other)._node;
}

bool MyIterator::operator==(BaseIterator &other) {
    return _node == dynamic_cast<MyIterator &>(other)._node;
}

MyIterator::MyIterator() {
    _node = nullptr;
}

Connected_list::Connected_list() {
    head = new Node;
    bef_beg_iter._node = head;
}

void Connected_list::push_front(Ticket &ticket) {
    insert_after(head, ticket);
}

void Connected_list::erase_after(Node *elem) {
    if (elem == nullptr) {
        return;
    }
    Node *tmp = elem->next;
    if (tmp == nullptr) {
        return;
    }
    elem->next = tmp->next;
    delete tmp;
}

void Connected_list::pop_front() {
    erase_after(head);
}

bool Connected_list::empty() {
    return head->next == nullptr;
}

Ticket &Connected_list::front() {
    if (!empty()) {
        return head->next->data;
    }
    return head->data;
}

void Connected_list::clear() {
    Node *curr = head->next;

    while (curr != nullptr) {
        Node *next = curr->next;
        delete curr;
        curr = next;
    }
    head->next = nullptr;
}

void Connected_list::insert_after(Node *elem, Ticket &tic) {
    if (elem == nullptr) {
        return;
    }
    Node *inserted = new Node;
    inserted->data = tic;
    inserted->next = elem->next;
    elem->next = inserted;
}

void Connected_list::erase_after(BaseIterator &it) {
    this->erase_after(dynamic_cast<MyIterator&>(it)._node);
}

void Connected_list::insert_after(BaseIterator &it, Ticket &tic) {
    this->insert_after(dynamic_cast<MyIterator&>(it)._node, tic);
}

BaseIterator &Connected_list::before_begin() {
    return bef_beg_iter;
}

BaseIterator &Connected_list::begin() {
    beg_iter._node = head->next;
    return beg_iter;
}

BaseIterator &Connected_list::end() {
    return end_iter;
}

Container *Connected_list::get_pure_pointer() {
    return new Connected_list();
}

Connected_list::~Connected_list() {
    this->clear();
    delete head;
}

Node::Node() {
    next = nullptr;
}

bool Node::operator==(Node &other) {
    return this == &other;
}

bool Node::operator!=(Node &other) {
    return this != &other;
}

BaseIterator & StlIterator::operator++() {
    iter++;
    return *this;
}

Ticket &StlIterator::operator*() {
    return *iter;
}

bool StlIterator::operator!=(BaseIterator &other) {
    return iter != dynamic_cast<StlIterator&>(other).iter;
}

bool StlIterator::operator==(BaseIterator &other) {
    return iter == dynamic_cast<StlIterator&>(other).iter;
}

StlIterator::StlIterator(forward_list<Ticket>::iterator it) {
    iter = it;
}

StlIterator::StlIterator(StlIterator &it) {
    iter = it.iter;
}

StlIterator &StlIterator::operator=(const StlIterator& it) {
    this->iter = it.iter;
    return *this;
}


void Forward_list::push_front(Ticket &ticket) {
    list.push_front(ticket);
}

void Forward_list::erase_after(BaseIterator &it) {
    list.erase_after(dynamic_cast<StlIterator&>(it).iter);
}

void Forward_list::pop_front() {
    list.pop_front();
}

Ticket &Forward_list::front() {
    return list.front();
}

bool Forward_list::empty() {
    return list.empty();
}

void Forward_list::clear() {
    list.clear();
}

void Forward_list::insert_after(BaseIterator &it, Ticket &tic) {
    list.insert_after(dynamic_cast<StlIterator&>(it).iter, tic);
}

BaseIterator &Forward_list::begin() {
    beg_iter = StlIterator(list.begin());
    return beg_iter;
}

BaseIterator &Forward_list::before_begin() {
    bef_beg_iter = StlIterator(list.before_begin());
    return bef_beg_iter;
}

BaseIterator &Forward_list::end() {
    end_iter = StlIterator(list.end());
    return end_iter;
}

Container *Forward_list::get_pure_pointer() {
    return new Forward_list();
}

Forward_list::~Forward_list() = default;
