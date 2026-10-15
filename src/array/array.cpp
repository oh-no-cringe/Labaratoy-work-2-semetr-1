#include "array.h"
#include <iostream>
#include <stdexcept>

using namespace std;

void Array::reserve(int new_cap) {
    if (new_cap <= this->cap) return;
    int* nd = new int[new_cap];
    for (int i = 0; i < this->size; ++i) nd[i] = this->data[i];
    delete[] this->data;
    this->data = nd;
    this->cap  = new_cap;
}

void Array::push_back(int v) {
    if (this->size == this->cap) {
        this->reserve(this->cap == 0 ? 4 : this->cap * 2);
    }
    this->data[this->size++] = v;
}

void Array::push_index(int v, int index) {
    if (index < 0 || index > this->size)
        throw out_of_range("array index");
    if (this->size == this->cap) {
        this->reserve(this->cap == 0 ? 4 : this->cap * 2);
    }
    for (int i = this->size; i > index; --i) {
        this->data[i] = this->data[i - 1];
    }
    this->data[index] = v;
    ++this->size;
}

int Array::get(int index) const {
    if (index < 0 || index >= this->size)
        throw out_of_range("array index");
    return this->data[index];
}

void Array::set(int index, int v) {
    if (index < 0 || index >= this->size)
        throw out_of_range("array index");
    this->data[index] = v;
}

void Array::pop_index(int index) {
    if (index < 0 || index >= this->size) return;
    for (int i = index; i < this->size - 1; ++i) {
        this->data[i] = this->data[i + 1];
    }
    --this->size;
}

void Array::print() const {
    cout << "[";
    for (int i = 0; i < this->size; ++i) {
        if (i) cout << ", ";
        cout << this->data[i];
    }
    cout << "]\n";
}

void Array::save_to(ostream& out) const {
    for (int i = 0; i < this->size; ++i) {
        out << " " << this->data[i];
    }
}

void Array::clear() {
    delete[] this->data;
    this->data = nullptr;
    this->size = 0;
    this->cap  = 0;
}

map<string, Array>& a_registry() {
    static map<string, Array> reg;
    return reg;
}

Array& a_get_by_name(const string& name) {
    return a_registry()[name];
}