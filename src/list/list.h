#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <map>
#include <string>

class List {
    private:
    struct Node {
        int value;
        Node* next, * prev;
        Node(int v, Node* n, Node* p ) : value(v), next(n), prev(p) {}

    };
    Node* head;
    Node* tail;

    void clear();
    public:
    List() {this->head = nullptr;  this->tail = nullptr;}
    ~List() { this->clear();}

    List(const List&) = delete;
    List& operator = (const List&) = delete;

    void push_front(int v);
    void push_back(int v);
    void push_index(int v, int index);

    void pop_front();
    void pop_back();
    void pop_index(int index);

    bool find(int v) const;
    void print() const;
    void save_to(std::ostream& out) const; 
    bool empty() const { return this->head == nullptr; }


};
std::map<std::string, List>& l_registry();
List& l_get_by_name(const std::string& name);




#endif 


