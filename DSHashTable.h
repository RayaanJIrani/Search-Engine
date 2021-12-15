//
// Created by Saaketh Koka on 4/9/21.
//
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

template<class k, class v>
class DSHashTable{
private:
    struct pair{
        k key;
        v value;
        pair(const k& key, const v& value);
    };
    std::vector<std::vector<pair>> table;
    int numElements; //tracks the number of elements in the hashing table
    int tableSize;
    int hash(const k& key); //method hashes a given key input using the std::hash function
    void rehash(); //method (approx.) doubles the size of the hashmap whenever the numElements is equal to the size of the vector
    //const int near_primes TODO

public:
    /**
     * Default constructor.
     */
    DSHashTable(int size = 10);
    /**
     * Inserts a key-value pair into the hash table:
     * @param key
     * @param value
     */
    void insert(const k& key, const v& val);
    /**
     * Returns the value assigned to a certain key.
     * @param key
     * @return value
     */
    v* getVal(const k& key);
    /**
     * Checks to see if the hash map contains the Key
     * @param key
     * @return bool
     */
    bool contains(const k& key);

    /**
     * Returns the number of unique entries in the hash map
     * @return int - the number of unqiue entries in hash map
     */
    int getNumElememts();

    /**
     * Prints the content of the map based on hash value and input order respectivly
     */
    void printMap();

    /**
     * prints all of the elements in the hashmap to file with filename
     * @param fileName - the filename of the file which the hash map is being printed to.
     */
    void printTableToFile(std::string fileName);
};

template<class k, class v>
DSHashTable<k, v>::pair::pair(const k& key, const v& value) {
    this->key = key;
    this->value = value;
}

template<class k, class v>
DSHashTable<k, v>::DSHashTable(int size) : table(size){
    this->numElements = 0;
    this->tableSize = size;
}

template<class k, class v>
int DSHashTable<k, v>::hash(const k& key) {
    //Assumes that one key one value
    std::hash<k> hashFunc; //this creates the hash for the key
    //converts the output of the hashing function into an int value for the size
    return static_cast<unsigned long int>(hashFunc(key)) % static_cast<unsigned long int>(this->tableSize);
}

template<class k, class v>
void DSHashTable<k, v>::rehash() {
    std::vector<std::vector<pair>> newTable(this->tableSize * 2);
    this->tableSize *= 2;
    for(auto &c : table){ //iterates through all of the hashes in table
        for(auto &d : c){ //iterates through every value in each hash
            newTable[hash(d.key)].push_back(pair(d.key, d.value));
        }
    }
    table = newTable;
}

template<class k, class v>
void DSHashTable<k, v>::insert(const k& key, const v& val) {
    if(this->contains(key)){
        return;
    }
    if(numElements >= table.size()){ //checks if we should rehash
        rehash();
    }
    table[hash(key)].push_back(pair(key, val));
    numElements++;
}

template<class k, class v>
v* DSHashTable<k, v>::getVal(const k& key) {
    int index = hash(key);
    // Checks every key in the index produced by the hash:
    for(auto &c : table[index]){
        if(c.key == key){
            return &c.value;
        }
    }
    return nullptr;
}

template<class k, class v>
bool DSHashTable<k, v>::contains(const k& key) {
    int index = hash(key);
    // Checks every key in the index produced by the hash:
    for(auto &c : table[index]){
        if(c.key == key){
            return true;
        }
    }
    return false;
}

template<class k, class v>
void DSHashTable<k, v>::printMap() {
    for(auto &c : table){
        if(!c.empty()){
            for(auto d : c){
                std::cout << d.key << std::endl;
            }
        }
    }
}

template<class k, class v>
int DSHashTable<k, v>::getNumElememts() {
    return numElements;
}

template<class k, class v>
void DSHashTable<k, v>::printTableToFile(std::string filename) {
    std::fstream outfs(filename);
    for(auto &c : table){
        if(!c.empty()){
            for(auto d : c){
                outfs << d.key << " ";
                for(auto &a : d.value){
                    outfs << a->paper_id << " ";
                }
                outfs << std::endl;
            }
        }
    }
    outfs.close();
}
