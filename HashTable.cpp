#include "HashTable.h"

House::House() {
    zipCode = 0;
    price = 0;
    area = 0;
    address = "";
}

House::House(int zip, double p, double sqFeet, std::string& location) {
    zipCode = zip;
    price = p;
    area = sqFeet;
    address = location;
}

Node::Node() {
    key = 0;
    value = std::vector<House>();
    next = nullptr;
}

Node::Node(int k, std::vector<House>& v, Node* ptr) {
    key = k;
    value = v;
    next = ptr;
}

HashTable::HashTable() {
    size = 0;
    capacity = 100;
}

HashTable::HashTable(int cap) {
    size = 0;
    capacity = cap;
    table.resize(capacity);
}

void HashTable::insert(int key, House value) {
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
    table[index] = new Node(key, vec, table[index]);
}

std::vector<House> HashTable::find(int key) {
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

int HashTable::hash(int key) {
    // Hashes and reduces the given key for the table
    int hash = key;
    return hash % capacity;
}

double HashTable::getLoadFactor() {
    return (double)(size) / capacity;
}

void HashTable::resize() {
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