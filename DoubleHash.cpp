#include "DoubleHash.h"


DoubleHash::DoubleHash(int size){
        table_size = size;
        table = new string[table_size];
        for (int i = 0; i < table_size; i++) {
            table[i] = "";
        }
}

unsigned int DoubleHash::hash1(string &word){
    unsigned int key = 0;
    for (char ch : word){
        key = 37*key+ch;
    }
    
    return key % table_size;
}

unsigned int DoubleHash::hash2(string &word){
    unsigned int key = 0;
    for (char ch : word){
        key = 37*key+ch;
    }
    
    return 953 - (key % 953);
}

void DoubleHash::insert(string word) {
    string lowercase_word = "";
    for (char c : word) {
        if (isalpha(c)) {
            lowercase_word += tolower(c);
        }
    }

    int index = hash1(lowercase_word);
    int second_hash = hash2(lowercase_word);
        for (int i = 1; i < table_size; i++) {
            if (table[index] == "") {
                table[index] = word;
                return;
            } else {
                index = (index + (i*second_hash)) % table_size;
            }
        }
}

string DoubleHash::search(string word){
    string lowercase_word = "";
    for (char c : word) {
        if (isalpha(c)) {
            lowercase_word += tolower(c);
        }
    }

    int index = hash1(lowercase_word);
    int second_hash = hash2(lowercase_word);
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
                index = (index + (i*second_hash)) % table_size;
            }
        }
    }
    return "WNF";
}