#pragma once
#include <string>

struct House {
    int zipCode;
    double area;
    double price;
    std::string city;
    std::string state;
    std::string address;
    House() {
        zipCode = 0;
        price = 0;
        area = 0;
        address = "";
    }
    House(int zipCode, double price, double area, std::string& addrCity, std::string& addrState, std::string& addr) {
        this->zipCode = zipCode;
        this->area = area;
        this->price = price;
        this->address = addr;
        this->city = addrCity;
        this->state = addrState;
    }

    void print()
    {
        cout << address << " " << zipCode << ", " << area << "sq. ft., " << "$" << price;
    }
};