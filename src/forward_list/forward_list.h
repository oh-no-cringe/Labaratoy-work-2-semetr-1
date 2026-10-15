#ifndef FORWARD_LIST
#define FORWARD_LIST

#include <map>
#include <string>
#include <ostream>

class ForwardList {
private:
    struct Node {
        int   value;
        Node* next;
        Node(int v, Node* n) : value(v), next(n) {}
    };

    Node* head;

    void clear();

public:
    ForwardList() { this->head = nullptr; }
    ~ForwardList() { this->clear(); }

    ForwardList(const ForwardList&) = delete;
    ForwardList& operator=(const ForwardList&) = delete;

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

std::map<std::string, ForwardList>& f_registry();
ForwardList& f_get_by_name(const std::string& name);

#endif