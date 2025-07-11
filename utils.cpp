#include <fstream>
#include <string>

using namespace std;

string readFile(const string& path) {
    ifstream file(path, ios::binary);
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

void writeFile(const string& path, const string& data) {
    ofstream file(path, ios::binary);
    file.write(data.c_str(), data.size());
}