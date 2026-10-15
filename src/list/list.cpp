#include "list.h"
#include <iostream>

using namespace std;


void List::push_front(int v) {
    Node* new_node = new Node(v,this->head,nullptr);
    if(this->head != nullptr) {
        this->head->prev = new_node;

    }
    else {
        this->tail = new_node;

    }
    this->head = new_node;

}

void List::push_back(int v) {
    Node* new_node = new Node(v, nullptr, this->tail);
    if (this->tail != nullptr) {
        this->tail->next = new_node;
    } else {
        this->head = new_node;
    }
    this->tail = new_node;
}


void List::push_index(int v, int index) {
    if (index <= 0) {
        this->push_front(v);
        return;
    }

    Node* current = this->head;
    for (int i = 0; i < index - 1 && current; ++i) {
        current = current->next;
    }

    if (!current) {
        this->push_back(v);
        return;
    }

    Node* new_node = new Node(v, current->next, current);

    if (current->next) {
        current->next->prev = new_node;
    } else {
        this->tail = new_node;
    }

    current->next = new_node;
}


void List::pop_front() {
    if (!this->head) return;

    Node* temp = this->head;
    this->head = temp->next;

    if (this->head) {
        this->head->prev = nullptr;
    } else {
        this->tail = nullptr;
    }

    delete temp;
}

void List::pop_back() {
    if (!this->tail) return;

    Node* temp = this->tail;
    this->tail = temp->prev;

    if (this->tail) {
        this->tail->next = nullptr;
    } else {
        this->head = nullptr;
    }

    delete temp;
}

void List::pop_index(int index) {
    if (!this->head) return;
    if (index < 0)   return;

    if (index == 0) {
        this->pop_front();
        return;
    }

    Node* current = this->head;
    for (int i = 0; i < index && current; ++i) {
        current = current->next;
    }
    if (!current) return;

       if (current == this->tail) { 
        this->pop_back(); 
        return;
    }

    if (current->prev) {
        current->prev->next = current->next;
    }
    
    
    if (current->next) {
        current->next->prev = current->prev;
    }

   
    delete current;
}

bool List::find(int v) const {
    Node* current = this->head;
    while (current) {
        if (current->value == v) return true;
        current = current->next;
    }
    return false;
}

void List::print() const {
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

void List::save_to(ostream& out) const {
    Node* current = this->head;
    while (current) {
        out << " " << current->value;
        current = current->next;
    }
}

void List::clear() {
    while (this->head) {
        Node* temp = this->head;
        this->head = temp->next;
        delete temp;
    }
    this->tail = nullptr;
}


map<string, List>& l_registry() {
    static map<string, List> reg;
    return reg;
}

List& l_get_by_name(const string& name) {
    return l_registry()[name];
}
