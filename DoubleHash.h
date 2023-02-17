#include <iostream>
#include <cmath>
#include <cctype>
#include <regex>
#include <string>


using namespace std;

class DoubleHash{
    private:
        int table_size;
        string* table;
    public:
        DoubleHash(int);
        unsigned int hash1(string&);
        unsigned int hash2(string&);
        void insert(string);
        string search(string);
};

