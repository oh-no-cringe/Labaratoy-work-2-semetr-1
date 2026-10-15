#ifndef ARRAY_H
#define ARRAY_H

#include <map>
#include <string>
#include <ostream>

class Array {
private:
    int* data;
    int  size;
    int  cap;

    void reserve(int new_cap);
    void clear();

public:
    Array() : data(nullptr), size(0), cap(0) {}
    ~Array() { this->clear(); }

    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    void push_back(int v);
    void push_index(int v, int index);
    int  get(int index) const;
    void set(int index, int v);
    void pop_index(int index);
    int  length() const { return this->size; }
    bool empty() const { return this->size == 0; }

    void print() const;
    void save_to(std::ostream& out) const;
};

std::map<std::string, Array>& a_registry();
Array& a_get_by_name(const std::string& name);

#endif