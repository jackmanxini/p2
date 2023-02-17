#include "QuadProbe.h"
#include "Chaining.h"
#include "DoubleHash.h"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std::chrono;

using namespace std;

bool isPrime(int n){
    if(n<=1){
        return false;
    }
    int upper_lim = sqrt(n);
    for (int i = 2; i <= upper_lim; i++){
        if (n % i == 0){
            return false;
        }
    }

    return true;
}

int nextPrime(int n){
    if (n < 2){
        return 2;
    }

    int prime = n;
    bool found = false;
    while(!found){
        prime++;
        if(isPrime(prime)){
            found = true;
        }
    }
    return prime;
}


//Beginning of Main Function

int main(int argc, const char * argv[]){

    ifstream quad_dictionary_file;
    ifstream quad_input_file;

    ifstream chaining_dictionary_file;
    ifstream chaining_input_file;

    ifstream double_dict_file;
    ifstream double_input_file;

    ifstream get_table_size;
    int table_size = 0;
    get_table_size.open(argv[1]);
    string num_words;
    while(get_table_size >> num_words){
        table_size ++;
    }
    table_size = 2*table_size;

    if(isPrime(table_size)){
        table_size = table_size;
    }
    else{
        table_size = nextPrime(table_size);
    }



    QuadProbe qp(table_size);
    Chaining c(table_size);
    DoubleHash dh(table_size);


    duration<double, nano> quad_hash_time;
    duration<double, nano> chaining_hash_time;
    duration<double, nano> double_hash_time;


    int chaining_num_wrong = 0;
    int quad_num_wrong = 0;
    int double_num_wrong = 0;

    quad_dictionary_file.open(argv[1]);
    quad_input_file.open(argv[2]);


    if(!quad_dictionary_file || !quad_input_file){
        cout << "Error opening dictionary file or Input File" << endl;
        return 0;
    }
    else{

    string quad_dict_word;
    auto quadStart = high_resolution_clock::now();
    while(quad_dictionary_file >> quad_dict_word){
        qp.insert(quad_dict_word);
    }
    auto quadEnd = high_resolution_clock::now();
    quad_hash_time = quadEnd - quadStart;


    string quad_check_word;
    while(quad_input_file >> quad_check_word){
        if(qp.search(quad_check_word) == "WNF"){
            quad_num_wrong++;
        }
        else{
            continue;
        }

    }
    }

    quad_dictionary_file.close();
    quad_input_file.close();

// END OF QUADRATIC PROBING FOR COLLISIONS

// BEGINNING OF CHAINING FOR COLLISIONS

    chaining_dictionary_file.open(argv[1]);
    chaining_input_file.open(argv[2]);

    if(!chaining_dictionary_file || !chaining_input_file){
        cout << "Error opening dictionary file or Input File" << endl;
        return 0;
    }
    else{

        string chaining_dict_word;
        auto chainingStart = high_resolution_clock::now();
        while(chaining_dictionary_file >> chaining_dict_word){
        c.insert(chaining_dict_word);
    }
        auto chainingEnd = high_resolution_clock::now();
        chaining_hash_time = chainingEnd - chainingStart;


    string chaining_check_word;
    while(chaining_input_file >> chaining_check_word){
        if(c.search(chaining_check_word) == "WNF"){
            chaining_num_wrong++;
        }
        else{
            continue;
        }

    }

    }
    //END OF CHAINING

    //START OF DOUBLE HASH
    double_dict_file.open(argv[1]);
    double_input_file.open(argv[2]);

    if(!double_dict_file || !double_input_file){
        cout << "Error opening dictionary file or Input File" << endl;
        return 0;
    }
    else{

        string double_dict_word;
        auto doubleStart = high_resolution_clock::now();
        while(double_dict_file >> double_dict_word){
        dh.insert(double_dict_word);
    }
        auto doubleEnd = high_resolution_clock::now();
        double_hash_time = doubleEnd - doubleStart;


    string double_search;
    while(double_input_file >> double_search){
        if(dh.search(double_search) == "WNF"){
            cout << double_search << endl;
            double_num_wrong++;
        }
        else{
            continue;
        }

    }

    }
    // END DOUBLE HASH

    double_dict_file.close();
    double_input_file.close();

    cout << "QUADRATIC PROBING FOUND : " << quad_num_wrong << " INCORRECTLY SPELLED WORDS \nTIME SPENT CREATING HASH TABLE (QUADRATIC PROBING): " << quad_hash_time.count() << endl << endl;
    cout << "CHAINING FOUND : " << chaining_num_wrong << " INCORRECTLY SPELLED WORDS \nTIME SPENT CREATING HASH TABLE (CHAINING) : " << chaining_hash_time.count() << endl << endl;
    cout << "DOUBLE HASHING FOUND : " << double_num_wrong << " INCORRECTLY SPELLED WORD \nTIME SPENT CREATING HASH TABLE (DOUBLE) : " << double_hash_time.count() << endl;

    chaining_dictionary_file.close();
    chaining_input_file.close();

return 0;
}