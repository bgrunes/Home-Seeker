#pragma once
#include <string>
#include <vector>
#include "House.cpp"

struct Node {
    Node* next;
    std::string key;
    std::vector<House> value;
    Node();
    Node(std::string&, std::vector<House>&, Node* = nullptr);
};

class HashTableSC {
private:
    int size, capacity;
    double load = 0.8;
    std::vector<Node*> table;
    void resize();
    int hash(std::string&);
    double getLoadFactor();
public:
    HashTableSC();
    HashTableSC(int);
    void insert(std::string&, House&);
    std::vector<House> find(std::string&);
};