#include "QuadProbe.h"


QuadProbe::QuadProbe(int size){
        table_size = size;
        table = new string[table_size];
        for (int i = 0; i < table_size; i++) {
            table[i] = "";
        }
}

unsigned int QuadProbe::hashfunction(string &word){
    unsigned int key = 0;
    for (char ch : word){
        key = 37*key+ch;
    }
    
    return key % table_size;
}

void QuadProbe::insert(string word) {
    string lowercase_word = "";
    for (char c : word) {
        if (isalpha(c)) {
            lowercase_word += tolower(c);
        }
    }

    int index = hashfunction(lowercase_word);
        for (int i = 1; i < table_size; i++) {
            if (table[index] == "") {
                table[index] = word;
                break;
            } else {
                index = (index + i * i) % table_size;
            }
        }
}

string QuadProbe::search(string word){
    string lowercase_word = "";
    for (char c : word) {
        if (isalpha(c)) {
            lowercase_word += tolower(c);
        }
    }

    int index = hashfunction(lowercase_word);

    for (int i = 1; i < table_size; i++) {
        if (table[index] == "") {
            return "WNF";
        } else {
            // Convert table entry to lowercase and remove attached punctuation
            string lowercase_table_entry = "";
            for (char c : table[index]) {
                if (isalpha(c)) {
                    lowercase_table_entry += tolower(c);
                }
            }
            if (lowercase_table_entry == lowercase_word) {
                return table[index];
            } else {
                index = (index + i * i) % table_size;
            }
        }
    }
    return "WNF";
}
