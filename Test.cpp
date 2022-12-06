//#include "LinearProbing.cpp"
#include "HashMapLP.cpp"
#include <iostream>

// Compile and run:
// g++ -O2 -Wall -std=c++17 LinearProbing.cpp Test.cpp -o test && ./test
// g++ -O2 -Wall -std=c++17 HashMapLP.cpp Test.cpp -o test && ./test
// g++ -O2 -Wall -std=c++11 HashMapLP.cpp Test.cpp -o test && ./test

void printHouse(House& house) {
    std::cout << house.zipCode << ", $" << house.price << ", " 
              << house.area << " sqft, " << house.address << "\n";
}

void printVector(std::vector<House> vec) {
    for (House h : vec)
        printHouse(h);
}

int main() {
    HashMapLP map(5);
    std::string address = "address";
    House h1(1,2,3,address);
    House h2(2,3,4,address);
    House h3(3,4,5,address);
    House h4(4,5,6,address);
    std::string h1s = "1", h2s = "6", h3s = "2";
    map.insert(h1s, h1);
    map.insert(h2s, h2);
    map.insert(h3s, h3);
    //table.insert(3, h4);
    //table.insert(11, h3);
    //Node* found = table.find(6);
    //if (found) printVector(found->value);
    printVector(map.find(h1s));
    return 0;
}