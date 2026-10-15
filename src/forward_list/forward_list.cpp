#include "forward_list.h"
#include <iostream>


using namespace std;



void ForwardList::push_front(int v) {
    this->head = new Node(v, this->head);
}

void ForwardList::push_back(int v) {
    Node* new_node = new Node(v, nullptr);
    if (!this->head) {
        this->head = new_node;
        return;
    }
    Node* current = this->head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
}

void ForwardList::push_index(int v, int index) {
    if (index <= 0) {
        this->push_front(v);
        return;
    }
    Node* current = this->head;
    for (int i = 0; i < index - 1 && current; ++i) {
        current = current->next;
    }
    if (!current) return;
    current->next = new Node(v, current->next);
}



void ForwardList::pop_front() {
    if (!this->head) return;
    Node* temp = this->head;
    this->head = temp->next;
    delete temp;
}

void ForwardList::pop_back() {
    if (!this->head) return;

    if (!this->head->next) {
        delete this->head;
        this->head = nullptr;
        return;
    }

    Node* current = this->head;
    while (current->next->next) {
        current = current->next;
    }
    delete current->next;
    current->next = nullptr;
}

void ForwardList::pop_index(int index) {
    if (!this->head) return;

    if (index == 0) {
        this->pop_front();
        return;
    }

    Node* current = this->head;
    for (int i = 0; i < index - 1 && current->next; ++i) {
        current = current->next;
    }
    if (!current->next) return;

    Node* temp = current->next;
    current->next = temp->next;
    delete temp;
}

bool ForwardList::find(int v) const {
    Node* current = this->head;
    while (current) {
        if (current->value == v) return true;
        current = current->next;
    }
    return false;
}

void ForwardList::print() const {
    cout << "[";
    bool first = true;
    Node* current = this->head;
    while (current) {
        if (!first) cout << ", ";
        cout << current->value;
        first = false;
        current = current->next;
    }
    cout << "]\n";
}

void ForwardList::clear() {
    while (this->head) {
        Node* temp = this->head;
        this->head = temp->next;
        delete temp;
    }
}


map<string, ForwardList>& f_registry() {
    static map<string, ForwardList> reg;
    return reg;
}

void ForwardList::save_to(ostream& out) const {
    Node* current = this->head;
    while (current) {
        out << " " << current->value;
        current = current->next;
    }
}

ForwardList& f_get_by_name(const string& name) {
    return f_registry()[name];
}