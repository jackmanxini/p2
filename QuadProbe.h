#include <iostream>
#include <cmath>
#include <cctype>
#include <regex>
#include <string>


using namespace std;

class QuadProbe{
    private:
        int table_size;
        string* table;
    public:
        QuadProbe(int);
        unsigned int hashfunction(string&);
        void insert(string);
        string search(string);
};

