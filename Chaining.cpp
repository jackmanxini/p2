#include "Chaining.h"



Chaining::Chaining(int size){
    table_size = size;

    table = new chain_node*[table_size];

    for (int i = 0; i < table_size; i++){
        table[i] = nullptr;
    }
}

unsigned int Chaining::hashfunction(string &word){
    unsigned int key = 0;
    for (char ch : word){
        key = 37*key+ch;
    }
    
    return key % table_size;
}

void Chaining::insert(string word){
    string lowercase_word = "";
    for (char c : word) {
        if (isalpha(c)) {
            lowercase_word += tolower(c);
        }
    }

    // Compute hash index for lowercase input word
    int index = hashfunction(lowercase_word);
    chain_node *insertNode = new chain_node();
    insertNode->word = word;
    insertNode->nPtr = table[index];
    table[index] = insertNode;
}

string Chaining::search(string word){
    string lowercase_word = "";
    for (char c : word) {
        if (isalpha(c)) {
            lowercase_word += tolower(c);
        }
    }

    // Compute hash index for lowercase input word
    int index = hashfunction(lowercase_word);
    
    // Traverse the chain at the hash index
    chain_node *temp = table[index];
    while(temp != nullptr){
        // Convert chain node word to lowercase and remove attached punctuation
        string lowercase_chain_node_word = "";
        for (char c : temp->word) {
            if (isalpha(c)) {
                lowercase_chain_node_word += tolower(c);
            }
        }
        
        if(lowercase_chain_node_word == lowercase_word){
            return temp->word;
        }
        temp = temp->nPtr;
    }
    return "WNF";
}
