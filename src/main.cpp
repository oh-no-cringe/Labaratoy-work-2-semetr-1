#include "cli/cli.h"
#include <iostream>
#include <exception>

using namespace std;

int main(int argc, char** argv) {
    try {
        return cli_run(argc, argv);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}