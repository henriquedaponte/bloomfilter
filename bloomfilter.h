#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <iostream>
#include <vector>
#include <cmath>

class HashTable{

    public:

    struct Node{

        public:

            // Constructor
            Node(std::string element){
                this->data = element;
                this->next = NULL;
            } 

            std::string data;
            Node* next;
        };

        HashTable(); // Default Constructor
        HashTable(int q); // Constructor
        ~HashTable(); // Destructor
        void insert(std::string element); // Insert a string in to the hash table
        void remove(std::string element); // Delete an element from the hash table
        bool find(std::string element); // Return true if the element is in the hash table, otherwise return false

        private:
        
        int q = 1009; // The size of the hash table (prime number)
        Node** hashTable; // Hash table using separate chaining
        

        // Hash function for separate chaining HashTable
        const int hashSC(int x){
            return x % this->q;
        }
    };

class BloomFilter{

    public:

    BloomFilter(float p , int m, float c , float d); // Constructor
    ~BloomFilter(); // Destructor
    void insert(std::string element); // Insert a string in to the bloom filter
    void remove(std::string element); // Delete an element from the bloom filter
    bool find(std::string element); // Return true if the element is in the bloom filter, otherwise return false
    void print(); // Testing
    void printStart(); // Print starting message
    void printEnd(); // Print ending message

    private:

    std::string key; // Word to be stored
    HashTable rem;

    

    float p; // Probability of a false positive
    int m; // Expected number of strings to be inserted
    float c = 1.0; // Scale factor of bloom filter size
    float d = 1.0; // Scale factor of number of hash functions

    int* bitArray; // Bit array hash table
    
};

#endif