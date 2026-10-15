#ifndef QUEUE_H
#define QUEUE_H

#include <map>
#include <string>
#include <ostream>

class Queue {
private:
    struct Node {
        int   value;
        Node* next;
        Node(int v, Node* n) : value(v), next(n) {}
    };

    Node* head;
    Node* tail;

    void clear();

public:
    Queue() : head(nullptr), tail(nullptr) {}
    ~Queue() { this->clear(); }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void push(int v);
    void pop();
    bool empty() const { return this->head == nullptr; }

    void print() const;
    void save_to(std::ostream& out) const;
};

std::map<std::string, Queue>& q_registry();
Queue& q_get_by_name(const std::string& name);

#endif