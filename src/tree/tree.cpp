#include "tree.h"
#include <iostream>

using namespace std;


void Tree::insert(int v) {
    Node* z = new Node(v);

    if (!this->root) {
        this->root = z;
        return;
    }


    vector<Node*> q;
    q.push_back(this->root);
    size_t i = 0;
    while (i < q.size()) {
        Node* cur = q[i++];

        if (!cur->left) { cur->left = z; return; }
        q.push_back(cur->left);

        if (!cur->right) { cur->right = z; return; }
        q.push_back(cur->right);
    }
}

bool Tree::search_recursive(Node* n, int v) const {
    if (!n) return false;
    if (n->value == v) return true;
    return search_recursive(n->left, v) || search_recursive(n->right, v);
}

bool Tree::search(int v) const {
    return search_recursive(this->root, v);
}

bool Tree::is_complete() const {
    if (!this->root) return true;

    vector<Node*> q;
    q.push_back(this->root);

    bool saw_gap = false;
    size_t i = 0;
    while (i < q.size()) {
        Node* cur = q[i++];

        if (cur->left) {
            if (saw_gap) return false;    // после "дырки" уже не может быть детей
            q.push_back(cur->left);
        } else {
            saw_gap = true;
        }

        if (cur->right) {
            if (saw_gap) return false;
            q.push_back(cur->right);
        } else {
            saw_gap = true;
        }
    }
    return true;
}

void Tree::print_bfs() const {
    cout << "[";
    if (this->root) {
        vector<Node*> q;
        q.push_back(this->root);
        size_t i = 0;
        bool first = true;
        while (i < q.size()) {
            Node* cur = q[i++];
            if (!first) cout << ", ";
            cout << cur->value;
            first = false;
            if (cur->left)  q.push_back(cur->left);
            if (cur->right) q.push_back(cur->right);
        }
    }
    cout << "]\n";
}

void Tree::print() const {
    print_bfs();
}


void Tree::collect_bfs(vector<int>& out) const {
    if (!this->root) return;

    vector<Node*> q;
    q.push_back(this->root);
    size_t i = 0;
    while (i < q.size()) {
        Node* cur = q[i++];
        out.push_back(cur->value);
        if (cur->left)  q.push_back(cur->left);
        if (cur->right) q.push_back(cur->right);
    }
}

void Tree::save_to(ostream& out) const {
    vector<int> vals;
    collect_bfs(vals);
    for (int v : vals) out << " " << v;
}

void Tree::clear(Node* n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

map<string, Tree>& t_registry() {
    static map<string, Tree> reg;
    return reg;
}

Tree& t_get_by_name(const string& name) {
    return t_registry()[name];
}