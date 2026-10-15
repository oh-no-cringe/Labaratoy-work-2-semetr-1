#include "cli/cli.h"
#include "storage/storage.h"
#include "forward_list/forward_list.h"
#include "list/list.h"
#include "stack/stack.h"
#include "queue/queue.h"
#include "array/array.h"
#include "tree/tree.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

static int dispatch(const string& line) {
    istringstream iss(line);
    string cmd;
    iss >> cmd;
    if (cmd.empty()) throw runtime_error("empty query");

    if (cmd == "FPUSH") {
        string name; int v;
        iss >> name >> v;
        ForwardList& l = f_get_by_name(name);
        l.push_back(v);
        l.print();
        return 0;
    }

    if (cmd == "FDEL") {
        string name; int index;
        iss >> name >> index;
        ForwardList& l = f_get_by_name(name);
        l.pop_index(index);
        l.print();
        return 0;
    }

  
    if (cmd == "FGET") {
        string name; int v;
        iss >> name >> v;
        ForwardList& l = f_get_by_name(name);
        cout << (l.find(v) ? "TRUE" : "FALSE") << "\n";
        return 0;
    }


    if (cmd == "LPUSH") {
        string name; int v;
        iss >> name >> v;
        List& l = l_get_by_name(name);
        l.push_back(v);
        l.print();
        return 0;
    }

   
    if (cmd == "LDEL") {
        string name; int index;
        iss >> name >> index;
        List& l = l_get_by_name(name);
        l.pop_index(index);
        l.print();
        return 0;
    }

    
    if (cmd == "LGET") {
        string name; int v;
        iss >> name >> v;
        List& l = l_get_by_name(name);
        cout << (l.find(v) ? "TRUE" : "FALSE") << "\n";
        return 0;
    }


    if (cmd == "SPUSH") {
        string name; int v;
        iss >> name >> v;
        Stack& s = s_get_by_name(name);
        s.push(v);
        s.print();
        return 0;
    }

   
    if (cmd == "SPOP") {
        string name;
        iss >> name;
        Stack& s = s_get_by_name(name);
        s.pop();   
        return 0;
    }
    
    if (cmd == "QPUSH") {
        string name; int v;
        iss >> name >> v;
        Queue& q = q_get_by_name(name);
        q.push(v);
        q.print();
        return 0;
    }

    if (cmd == "QPOP") {
        string name;
        iss >> name;
        Queue& q = q_get_by_name(name);
        q.pop();
        return 0;
    }
    
       
    if (cmd == "MPUSH") {
        string name; int v;
        iss >> name >> v;
        Array& a = a_get_by_name(name);
        a.push_back(v);
        a.print();
        return 0;
    }

    
    if (cmd == "MDEL") {
        string name; int index;
        iss >> name >> index;
        Array& a = a_get_by_name(name);
        a.pop_index(index);
        a.print();
        return 0;
    }

    
    if (cmd == "MGET") {
        string name; int index;
        iss >> name >> index;
        Array& a = a_get_by_name(name);
        cout << a.get(index) << "\n";
        return 0;
    }


    if (cmd == "TINSERT") {
        string name; int v;
        iss >> name >> v;
        Tree& t = t_get_by_name(name);
        t.insert(v);
        t.print();
        return 0;
    }

   
    if (cmd == "TCHECK") {
        string name;
        iss >> name;
        Tree& t = t_get_by_name(name);
        cout << (t.is_complete() ? "TRUE" : "FALSE") << "\n";
        return 0;
    }

    
    if (cmd == "TGET") {
        string name; int v;
        iss >> name >> v;
        Tree& t = t_get_by_name(name);
        cout << (t.search(v) ? "TRUE" : "FALSE") << "\n";
        return 0;
    }
    
    

    if (cmd == "PRINT") {
        string name;
        iss >> name;

      
        auto& freg = f_registry();
        auto itf = freg.find(name);
        if (itf != freg.end()) { itf->second.print(); return 0; }

        auto& lreg = l_registry();
        auto itl = lreg.find(name);
        if (itl != lreg.end()) { itl->second.print(); return 0; }

        auto& sreg = s_registry();
        auto its = sreg.find(name);
        if (its != sreg.end()) { its->second.print(); return 0; }

        auto& qreg = q_registry();
        auto itq = qreg.find(name);
        if (itq != qreg.end()) { itq->second.print(); return 0; }

        auto& areg = a_registry();
        auto ita = areg.find(name);
        if (ita != areg.end()) { ita->second.print(); return 0; }

        auto& treg = t_registry();
        auto itt = treg.find(name);
        if (itt != treg.end()) { itt->second.print(); return 0; }

        throw runtime_error("no such container: " + name);
    }

    throw runtime_error("unknown command: " + cmd);
}

int cli_run(int argc, char** argv) {
    string file, query;

    for (int i = 1; i < argc; ++i) {
        string a = argv[i];
        if (a == "--file" && i + 1 < argc)       file  = argv[++i];
        else if (a == "--query" && i + 1 < argc) query = argv[++i];
        else throw runtime_error("unknown argument: " + a);
    }
    if (file.empty())  throw runtime_error("--file required");
    if (query.empty()) throw runtime_error("--query required");

    storage_load(file);
    int rc = dispatch(query);
    storage_save(file);
    return rc;
}