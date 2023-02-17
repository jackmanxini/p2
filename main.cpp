#include "QuadProbe.h"
#include "Chaining.h"
#include "DoubleHash.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>

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

    duration<double, nano> quad_search_time;
    duration<double, nano> chaining_search_time;
    duration<double, nano> double_search_time;


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
   while (quad_dictionary_file >> quad_dict_word) {
    stringstream split_hyphen(quad_dict_word);
    string word;
    while (getline(split_hyphen, word, '-')) {
        qp.insert(word);
    }
}
    auto quadEnd = high_resolution_clock::now();
    quad_hash_time = quadEnd - quadStart;


string quad_check_word;
auto quad_search_start = high_resolution_clock::now();
while (quad_input_file >> quad_check_word) {
    stringstream split_hyphen(quad_check_word);
    string word;
    bool all_words_found = true;
    while (getline(split_hyphen, word, '-')) {
        if (qp.search(word) == "WNF") {
            all_words_found = false;
            break;
        }
    }
    if (!all_words_found) {
        quad_num_wrong++;
    }

}
auto quad_search_end = high_resolution_clock::now();
quad_search_time = quad_search_end - quad_search_start;

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
        while (chaining_dictionary_file >> chaining_dict_word) {
            stringstream split_hyphen(chaining_dict_word);
            string word;
            while (getline(split_hyphen, word, '-')) {
                c.insert(word);
            }
        }
            auto chainingEnd = high_resolution_clock::now();
            chaining_hash_time = chainingEnd - chainingStart;


        string chaining_check;
        auto chaining_search_start = high_resolution_clock::now();

        while (chaining_input_file >> chaining_check) {
            stringstream split_hyphen(chaining_check);
            string word;
            bool all_words_found = true;
            while (getline(split_hyphen, word, '-')) {
                if (c.search(word) == "WNF") {
                    all_words_found = false;
                    break;
                }
            }
            if (!all_words_found) {
                chaining_num_wrong++;
            }
        }
        auto chaining_search_end = high_resolution_clock::now();
        chaining_search_time = chaining_search_end - chaining_search_start;

        } // end elkse


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
        while (double_dict_file >> double_dict_word) {
            stringstream split_hyphen(double_dict_word);
            string word;
            while (getline(split_hyphen, word, '-')) {
                dh.insert(word);
            }
        }
            auto doubleEnd = high_resolution_clock::now();
            double_hash_time = doubleEnd - doubleStart;


        string double_check;
        auto double_search_start = high_resolution_clock::now();
        while (double_input_file >> double_check) {
            stringstream split_hyphen(double_check);
            string word;
            bool all_words_found = true;
            while (getline(split_hyphen, word, '-')) {
                if (dh.search(word) == "WNF") {
                    all_words_found = false;
                    break;
                }
            }
            if (!all_words_found) {
                double_num_wrong++;
            }
        }
        auto double_search_end = high_resolution_clock::now();
        double_search_time = double_search_end - double_search_start;

        }


    }
    // END DOUBLE HASH

    double_dict_file.close();
    double_input_file.close();

    cout << "QUADRATIC PROBING FOUND : " << quad_num_wrong << " INCORRECTLY SPELLED WORDS \nTme Creating Hash Table (Quadratic Probing): " << quad_hash_time.count() << endl;
    cout << "Time Searching (Quadratic Probing) : " << quad_search_time.count() << endl << endl;
    cout << "CHAINING FOUND : " << chaining_num_wrong << " INCORRECTLY SPELLED WORDS \nTime Spent Creating Hash Table (Chaining) : " << chaining_hash_time.count() << endl;
    cout << "Time Searching (Chaining) : " << chaining_search_time.count() << endl << endl;
    cout << "DOUBLE HASHING FOUND : " << double_num_wrong << " INCORRECTLY SPELLED WORD \nTime Spent Creating Hash Table (Double Hashing) : " << double_hash_time.count() << endl;
    cout << "Time Searching (Double Hashing) : " << double_search_time.count() << endl << endl;

    double min_hash = min({quad_hash_time.count(), chaining_hash_time.count() , double_hash_time.count() });
    
    if (min_hash == quad_hash_time.count()){cout << "Most Efficient Creating Hash Table Is Quadratic Probing\n";}
    else if(min_hash == chaining_hash_time.count()){cout << "Most Efficient Creating Hash Table Is Chaining\n";}
    else{cout << "Most Efficient Creating Hash Table is Double Hashing\n";}

    double min_search = min({quad_search_time.count(), chaining_search_time.count() , double_search_time.count() });
    if (min_search == quad_search_time.count()){cout << "Most Efficient Searching Hash Table Is Quadratic Probing\n";}
    else if(min_search == chaining_search_time.count()){cout << "Most Searching Creating Hash Table Is Chaining\n";}
    else{cout << "Most Searching Creating Hash Table is Double Hashing\n";}


    chaining_dictionary_file.close();
    chaining_input_file.close();

return 0;
}