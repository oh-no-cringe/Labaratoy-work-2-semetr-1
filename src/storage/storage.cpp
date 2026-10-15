#include "storage/storage.h"
#include "forward_list/forward_list.h"
#include "list/list.h"
#include "stack/stack.h"
#include "queue/queue.h"
#include "array/array.h"
#include "tree/tree.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void storage_load(const string& path) {
    ifstream f(path);
    if (!f.is_open()) return;

    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string type, name;
        iss >> type >> name;
        if (type.empty() || name.empty()) continue;

        if (type == "FWD") {
            ForwardList& l = f_get_by_name(name);
            int v;
            while (iss >> v) l.push_back(v);
        }
        else if (type == "LST") {
            List& l = l_get_by_name(name);
            int v;
            while (iss >> v) l.push_back(v);
        }
        else if (type == "STK") {
            Stack& s = s_get_by_name(name);
            vector<int> vals;
            int v;
            while (iss >> v) vals.push_back(v);
            for (int x : vals) s.push(x);
        }
        else if (type == "QUE") {
            Queue& q = q_get_by_name(name);
            int v;
            while (iss >> v) q.push(v);
        }
        else if (type == "ARR") {
            Array& a = a_get_by_name(name);
            int v;
            while (iss >> v) a.push_back(v);
        }
        else if (type == "TRE") {
            Tree& t = t_get_by_name(name);
            int v;
            while (iss >> v) t.insert(v);
        }
    }
}

void storage_save(const string& path) {
    ofstream f(path, ios::trunc);
    if (!f.is_open()) return;

    for (auto& pair : f_registry()) {
        f << "FWD " << pair.first;
        pair.second.save_to(f);
        f << "\n";
    }

    for (auto& pair : l_registry()) {
        f << "LST " << pair.first;
        pair.second.save_to(f);
        f << "\n";
    }

    for (auto& pair : s_registry()) {
        f << "STK " << pair.first;
        pair.second.save_to(f);
        f << "\n";
    }

    for (auto& pair : q_registry()) {
        f << "QUE " << pair.first;
        pair.second.save_to(f);
        f << "\n";
    }

    for (auto& pair : a_registry()) {
        f << "ARR " << pair.first;
        pair.second.save_to(f);
        f << "\n";
    }

    for (auto& pair : t_registry()) {
        f << "TRE " << pair.first;
        pair.second.save_to(f);
        f << "\n";
    }
}