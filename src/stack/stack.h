#include <iostream>
#include <map>
#include <string>

class Stack {
    private:

    struct Node {
        int value;
        Node* next;
        Node(int v, Node* n) : value(v), next(n) {}

    };
    Node* head;
    void clear();
    public:
    Stack() {this->head = nullptr;}
    ~Stack() {this->clear();}

    Stack(const Stack&) = delete;
    Stack& operator = (const Stack&) = delete;


    void push(int v);
    void pop();
    bool empty() {return this->head == nullptr;}

    void print() const;
    void save_to(std::ostream& out) const;


};

std::map<std::string, Stack>& s_registry();
Stack& s_get_by_name(const std::string& name);