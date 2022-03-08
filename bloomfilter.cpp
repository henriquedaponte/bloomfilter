#include "bloomfilter.h"

// Compute the bloom filter size based on the false positive probability desired,
// and the expected number of strings to be inserted.
// Scale the computed size by c (for experimental purposes).
// p := probability of a false positive
// m := expected number of strings to be inserted
// c := scale factor of bloom filter size
int bloomFilterSize(int p , int m, int c){

    int n = -((m*log(p))/(pow(log(2),2)));

    return n*c;
}

// Compute the number of hash functions to use based on the bloom filter size,
// and the expected number of strings to be inserted.
// Scale the computed size by d (for experimental purposes).
// n := bloom filter size
// m := expected number of strings to be inserted
// d := scale factor of number of hash functions
int numHashFunctions(int n , int m, int d){

    int d0 = (n/m)*log(2);

    return d0*d;
}

// string to integer conversion.
// Needed for running the elements on the above hash function.
unsigned int strToInt(std::string element){

    size_t size = element.size();
    unsigned int x;

    // Prevent integer overflow
    // Do with justification

    for(size_t i = 0; i < size; i++){
        x += element[i]*(i+1);
    }

    return x;
}

// Family of hash functions
// The index specifies which hash function should be used
int hash(unsigned int element , int index){

    // Generating family of hash functions
    return element % 127*index;
}

// Main API of the bloom filter
// p := probability of a false positive
// m := expected number of strings to be inserted
// c := scale factor of bloom filter size
// d := scale factor of number of hash functions
BloomFilter::BloomFilter(float p , int m, float c , float d){
    this->p = p;
    this->m = m;
    this->c = c;
    this->d = d;

    this->bitArray = new int[bloomFilterSize(this->p, this->m, this->c)];
}

// Insert a string in to the bloom filter.
void BloomFilter::insert(std::string element){

    int bloomSize = bloomFilterSize(this->p, this->m, this->c);
    int hashNum = numHashFunctions(bloomSize, this->m, this->d);
    unsigned int elem = strToInt(element);


    for(int i = 0; i < hashNum; i++){
        (this->bitArray)[hash(elem, i+1)] = 1;
    }

}

// Delete an element from the bloom filter.
// This will use an auxiliary hash table. defined below.
void BloomFilter::remove(std::string element){

    (this->rem).insert(element);
}

// Return true if the element is in the bloom filter ,
// otherwise return false.
bool BloomFilter::find(std::string element){

    unsigned int elem = strToInt(element);

    if((this->bitArray)[hash(elem, 1)] == 1){
        return true;
    }else{
        return false;
    }
}

// Testing
void BloomFilter::print(){

}

// Separate Chaining Hash Table
// This will be used for your removed element s of the bloom filter.
// q := the size of the hash table (prime number)
HashTable::HashTable(int q){
    this->q = q;

    this->hashTable = new Node*[q];
}

// insert a string in to the hash table.
void HashTable::insert(std::string element){

    int x = strToInt(element);
    int index = hashSC(x);

    Node *newNode = new Node(element);

    if(hashTable[index]){

        Node* i = hashTable[index];

        while(i != NULL){
            i = i->next;
        }

        i->next = newNode;
    }else{

        hashTable[index] = newNode;
    }
}

// Delete an element from the hash table.
void HashTable::remove(std::string element){

    int x = strToInt(element);
    int index = hashSC(x);

    Node* temp = this->hashTable[index];
    Node* prev = NULL;

    while((temp != NULL) && (temp->data == element)){
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL)
        return;
 
    // Unlink the node from linked list
    prev->next = temp->next;
 
    // Free memory
    delete temp;
    
}

// Return true if the element is in the hash table ,
// otherwise return false.
bool HashTable::find(std::string element){

    int x = strToInt(element);
    int index = hashSC(x);

    for(Node* i = hashTable[index]; i != NULL; i = i->next){
        if(i->data == element){
            return true;
        }
    }

    return false;
}

// Destructor
BloomFilter::~BloomFilter(){
    delete [] bitArray;
}

// Destructor
HashTable::~HashTable(){
    delete [] hashTable;
}

// Default Constructor
HashTable::HashTable(){
    this->q = 1009;

    this->hashTable = new Node*[this->q];
}

// Print start message
void BloomFilter::printStart(){

    std::cout << "Experiment for values of:" << std::endl;
    std::cout << "c = " << this->c << std::endl;
    std::cout << "d = " << this->d << std::endl;
    std::cout << "q = " << "1009" << std::endl;
}