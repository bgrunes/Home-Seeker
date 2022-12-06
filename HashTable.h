#pragma once
#include <string>
#include <vector>

struct House {
    int zipCode;
    double area;
    double price;
    std::string address;
    House();
    House(int, double, double, std::string&);
};

struct Node {
    int key;
    Node* next;
    std::vector<House> value;
    Node();
    Node(int, std::vector<House>&, Node* = nullptr);
};

class HashTable {
private:
    int size, capacity;
    double load = 0.8;
    std::vector<Node*> table;
    void resize();
    int hash(int);
    double getLoadFactor();
public:
    HashTable();
    HashTable(int);
    void insert(int, House);
    std::vector<House> find(int);
};