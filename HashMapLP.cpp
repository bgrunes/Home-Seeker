//LINEAR PROBING
#pragma once
#include <string>
#include <vector>
#include "House.cpp"
using std::vector;
using std::string;

//HashFunction(key) = Sum of key's ASCII characters
//Reduce(Hashcode) = Hashcode % TABLE_SIZE
//index if open (not determined by hash code)

struct HashNode {
    string key;
    vector<House> val;
    HashNode() {
        key = "";
        val = vector<House>();
    }
    HashNode(string& k, vector<House>& v){
        key = k;
        val = v;
    }
};

class HashMapLP {
    private:
        int capacity, size;
        double load = 0.8;
        void resize();
        double getLoadFactor();
        int hash(string&);

        //hash element map
        vector<HashNode*> map;
    public:
        HashMapLP(int capacity = 100);
        void insert(string&, House&);
        vector<House> find(string&);
};

HashMapLP::HashMapLP(int cap) {
    size = 0;
    capacity = cap;
    //map = vector<HashNode*>(capacity, nullptr);
    map.resize(capacity, nullptr);
}

void HashMapLP::insert(string& key, House& val){
    size++;
    if(getLoadFactor() >= load)
        resize();
        
    //find the hash of the key
    int index = hash(key);

    // If key is at expected location, add the house to the hashnode's vector
    if(map[index]->key == key && map[index]) {
        map[index]->val.push_back(val);
    }
    // Otherwise, use linear probing to resolve collision
    else {
        int shift = 1;
        while(shift < capacity) {
            if(map[(index+shift)%capacity] == nullptr){
                std::vector<House> vec = {map[index]->val};
                map[(index+shift)%capacity] = new HashNode(key, vec);
                return;
            }
            shift++;
        }
    }
}

std::vector<House> HashMapLP::find(string& key) {
    //find the hash of the key
    int index = hash(key);
    int shift = 1;

    //check if value is at index
    if(map[index]->key == key && map[index]) 
        return map[index]->val;
    while(shift < capacity) {
        int shiftedIndex = (index+shift)%capacity;
        if(map[shiftedIndex]->key == key && map[shiftedIndex])
            return map[shiftedIndex]->val;
        shift++;
    }
    //return map[0]->val;
    return {}; //idk if this works
}

int HashMapLP::hash(string& key) {
    // Hashes and reduces the given key for the table
    int hash = 0;
    for(char c : key) {
        hash += c;
    }
    return hash % capacity;
}

double HashMapLP::getLoadFactor() {
    return (double)(size) / capacity;
}

void HashMapLP::resize() {
    // Resize capacity and move all elements into new table
    capacity *= 2;
    vector<HashNode*> vec(capacity, nullptr);
    map.swap(vec);
    // Iterate through every single value in the table, and add it to new table
    for(HashNode* node : vec) {
        for(House& house : node->val) {
            insert(node->key, house);
        }
    }
}