#include "SeparateChaining.h"
#include "LinearProbing.cpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

std::string FILE_NAME = "united_states_2022.csv";
void readFile(HashTableSC&, HashTableSC&, HashTableSC&, HashMapLP&, HashMapLP&, HashMapLP&);

int main()
{
    HashTableSC priceTableSC, locationTableSC, zipTableSC;
    HashMapLP priceTableLP, locationTableLP, zipTableLP;
    string cmd;
    cout << "Welcome to Home Seeker!\nBy Savannah Traub, Brandon Grunes, and Vraj Patel\n\n";
    cout << "Loading file into hashtables...\n";
    readFile(priceTableSC, locationTableSC, zipTableSC, priceTableLP, locationTableLP, zipTableLP);
    while(true)
    {
        cout << "Enter a Command: ";
        cin >> cmd;

        if (cmd == "price")
        {
            string price;
            cout << "\nWhat is your asking price? ";
            cin >> price;

            auto t1 = chrono::high_resolution_clock::now();
            vector<House> resultSC = priceTableSC.find(price);
            auto t2 = chrono::high_resolution_clock::now();
            auto duration1 = chrono::duration_cast<chrono::microseconds>(t2-t1).count();

            auto t3 = chrono::high_resolution_clock::now();
            vector<House> resultLP = priceTableLP.find(price);
            auto t4 = chrono::high_resolution_clock::now();
            auto duration2 = chrono::duration_cast<chrono::microseconds>(t4-t3).count();

            cout << "\nSeparate Chaining : " << duration1 << " ms\n";
            cout << "Linear Probing    : " << duration2 << " ms\n";

            cout << "\nHousing Details:\n";
            int length = resultSC.size();
            if (length == 0) {
                cout << "Sorry! No houses found!\n";
            }
            for (int i = 0; i < min(length, 10); i++) {
                resultSC[i].print();
                cout << '\n';
            }
        }
        else if (cmd == "location")
        {
            string city;

            cout << "\nEnter your city here (Ex: Gainesville): ";
            cin >> city;

            auto t1 = chrono::high_resolution_clock::now();
            vector<House> resultSC = locationTableSC.find(city);
            auto t2 = chrono::high_resolution_clock::now();
            auto duration1 = chrono::duration_cast<chrono::microseconds>(t2-t1).count();

            auto t3 = chrono::high_resolution_clock::now();
            vector<House> resultLP = locationTableLP.find(city);
            auto t4 = chrono::high_resolution_clock::now();
            auto duration2 = chrono::duration_cast<chrono::microseconds>(t4-t3).count();

            cout << "\nSeparate Chaining : " << duration1 << " ms\n";
            cout << "Linear Probing    : " << duration2 << " ms\n";

            cout << "\nHousing Details:\n";
            int length = resultSC.size();
            if (length == 0) {
                cout << "Sorry! No houses found!\n";
            }
            for (int i = 0; i < min(length, 10); i++) {
                resultSC[i].print();
                cout << '\n';
            }
        }
        else if (cmd == "zipcode") {
            string zip;

            cout << "\nEnter your zipcode here: ";
            cin >> zip;

            auto t1 = chrono::high_resolution_clock::now();
            vector<House> resultSC = zipTableSC.find(zip);
            auto t2 = chrono::high_resolution_clock::now();
            auto duration1 = chrono::duration_cast<chrono::microseconds>(t2-t1).count();

            auto t3 = chrono::high_resolution_clock::now();
            vector<House> resultLP = zipTableLP.find(zip);
            auto t4 = chrono::high_resolution_clock::now();
            auto duration2 = chrono::duration_cast<chrono::microseconds>(t4-t3).count();

            cout << "\nSeparate Chaining : " << duration1 << " ms\n";
            cout << "Linear Probing    : " << duration2 << " ms\n";

            cout << "\nHousing Details:\n";
            int length = resultSC.size();
            if (length == 0) {
                cout << "Sorry! No houses found!\n";
            }
            for (int i = 0; i < min(length, 10); i++) {
                resultSC[i].print();
                cout << '\n';
            }
        }
        else if (cmd == "help")
        {
            cout << "Commands List:\n";
            cout << "--------------\n";
            cout << "1. price\n";
            cout << "2. location\n";
            cout << "3. zipcode\n";
        }
        else if (cmd == "exit")
            return 0;
        else
            cout << "Unknown command, please type 'help' for command list\n";
    }
}

void readFile(HashTableSC& priceTableSC, HashTableSC& locationTableSC, HashTableSC& zipTableSC, HashMapLP& priceTableLP, HashMapLP& locationTableLP, HashMapLP& zipTableLP) {
    ifstream file;
    file.open(FILE_NAME);
    string spacer; //for column labels
    string price, address, addressCity, addressState, addressZipCode, area;
    getline(file, spacer);
    int count = 0;
    while (!file.eof())
    {
        count++;
        // Acquire all column data for each house
        getline(file, price, ',');
        getline(file, address, ',');
        getline(file, addressCity, ',');
        getline(file, addressState, ',');
        getline(file, addressZipCode, ',');
        getline(file, area, '\n');

        House newHouse(addressZipCode, price, area, addressCity, addressState, address);
        priceTableSC.insert(price, newHouse);
        priceTableLP.insert(price, newHouse);
        locationTableSC.insert(addressCity, newHouse);
        locationTableLP.insert(addressCity, newHouse);
        zipTableSC.insert(addressZipCode, newHouse);
        zipTableLP.insert(addressZipCode, newHouse);
    }
    file.close();
}