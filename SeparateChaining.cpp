#include "SeparateChaining.h"
#include <cmath>

Node::Node() {
    key = "";
    value = std::vector<House>();
    next = nullptr;
}

Node::Node(std::string& k, std::vector<House>& v, Node* ptr) {
    key = k;
    value = v;
    next = ptr;
}

HashTableSC::HashTableSC() {
    size = 0;
    capacity = 10000;
    table.resize(capacity);
}

HashTableSC::HashTableSC(int cap) {
    size = 0;
    capacity = cap;
    table.resize(capacity);
}

void HashTableSC::insert(std::string& key, House& value) {
    // Increment size and check if table needs to be resized
    size++;
    if (getLoadFactor() >= load)
        resize();
    // Find the hash and the element at the corresponding hash index
    int index = hash(key);
    Node* head = table[index];
    // If key already exists, add value to the vector at that key
    while (head) {
        if (head->key == key) {
            head->value.push_back(value);
            return;
        }
        head = head->next;
    }
    // Otherwise create a vector containing that single element at that key
    std::vector<House> vec = {value};
    // Add (key-value) pair to table, and shift the linked list if necessary
    Node* nxt = table[index];
    table[index] = new Node(key, vec, nxt);
}

std::vector<House> HashTableSC::find(std::string& key) {
    // Find the hash and the element at the corresponding hash index
    int index = hash(key);
    Node* head = table[index];
    // Search through the linked list to find the specific key
    while (head) {
        if (head->key == key)
            return head->value;
        head = head->next;
    }
    return {};
}

int HashTableSC::hash(std::string& key) {
    // Hashes and reduces the given key for the table
    int hash = 0;
    for (int i = 0; i < key.size(); i++) {
        hash += key[i] * std::pow(31, i);
    }
    return hash % capacity;
}

double HashTableSC::getLoadFactor() {
    return (double)(size) / capacity;
}

void HashTableSC::resize() {
    // Resize capacity and move all elements into new table
    capacity *= 2;
    std::vector<Node*> vec(capacity);
    table.swap(vec);
    // Iterate through every single value in the table, and add it to new table
    for (Node* node : vec) {
        while (node) {
            for (House& house : node->value) {
                insert(node->key, house);
            }
            node = node->next;
        }
    }
}