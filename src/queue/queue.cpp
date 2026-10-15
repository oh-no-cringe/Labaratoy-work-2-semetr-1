#include "queue.h"
#include <iostream>

using namespace std;


void Queue::push(int v) {
    Node* new_node = new Node(v, nullptr);
    if (!this->head) {
        this->head = new_node;
        this->tail = new_node;
        return;
    }
    this->tail->next = new_node;
    this->tail = new_node;
}


void Queue::pop() {
    if (!this->head) {
        cout << "EMPTY\n";
        return;
    }
    cout << this->head->value << "\n";

    Node* temp = this->head;
    this->head = temp->next;
    if (!this->head) this->tail = nullptr;   // список стал пуст — обнуляем хвост
    delete temp;
}

void Queue::print() const {
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

void Queue::save_to(ostream& out) const {
    Node* current = this->head;
    while (current) {
        out << " " << current->value;
        current = current->next;
    }
}

void Queue::clear() {
    while (this->head) {
        Node* temp = this->head;
        this->head = temp->next;
        delete temp;
    }
    this->tail = nullptr;
}

map<string, Queue>& q_registry() {
    static map<string, Queue> reg;
    return reg;
}

Queue& q_get_by_name(const string& name) {
    return q_registry()[name];
}