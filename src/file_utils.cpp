#include "file_utils.hpp"
#include <fstream>
#include <sstream>

bool read_file(const string &path, string &out) {
    ifstream f(path);
    if (!f.is_open()) return false;
    stringstream ss;
    ss << f.rdbuf();
    out = ss.str();
    return true;
}

bool write_file(const string &path, const string &data) {
    ofstream f(path);
    if (!f.is_open()) return false;
    f << data;
    return true;
}
