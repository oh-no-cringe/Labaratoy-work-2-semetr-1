#include "stack.h"
#include <iostream>
#include <vector>

using namespace std;

void Stack::push(int v) {
    Node* new_node = new Node(v, this->head);
    this->head = new_node;
}

void Stack::pop() {
    if (!this->head) {
        cout << "EMPTY\n";
        return;
    }
    cout << this->head->value << "\n";
    Node* temp = this->head;
    this->head = temp->next;
    delete temp;
}

void Stack::print() const {
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

void Stack::save_to(ostream& out) const {
    vector<int> vals;
    Node* current = this->head;
    while (current) {
        vals.push_back(current->value);
        current = current->next;
    }
    for (int i = (int)vals.size() - 1; i >= 0; --i)
        out << " " << vals[i];
}

void Stack::clear() {
    while (this->head) {
        Node* temp = this->head;
        this->head = temp->next;
        delete temp;
    }
}

map<string, Stack>& s_registry() {
    static map<string, Stack> reg;
    return reg;
}

Stack& s_get_by_name(const string& name) {
    return s_registry()[name];
}