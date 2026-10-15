#ifndef TREE_H
#define TREE_H

#include <map>
#include <string>
#include <ostream>
#include <vector>

class Tree {
private:
    struct Node {
        int   value;
        Node* left;
        Node* right;
        Node(int v) : value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void  clear(Node* n);
    void  collect_bfs(std::vector<int>& out) const;
    void print_bfs() const;
    bool  search_recursive(Node* n, int v) const;

public:
    Tree() : root(nullptr) {}
    ~Tree() { this->clear(this->root); }

    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&) = delete;

    void insert(int v);
    bool search(int v) const;
    bool is_complete() const;
    bool empty() const { return this->root == nullptr; }

    void print() const;
    void save_to(std::ostream& out) const;
};

std::map<std::string, Tree>& t_registry();
Tree& t_get_by_name(const std::string& name);

#endif