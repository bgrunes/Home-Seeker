#pragma once
#include <string>
#include <iostream>

struct House {
    std::string zipCode;
    std::string area;
    std::string price;
    std::string city;
    std::string state;
    std::string address;
    House() {
        zipCode = "";
        price = "";
        area = "";
        address = "";
        city = "";
        state = "";
    }
    House(std::string& zipCode, std::string& price, std::string& area, std::string& addrCity, std::string& addrState, std::string& addr) {
        this->zipCode = zipCode;
        this->area = area;
        this->price = price;
        this->address = addr;
        this->city = addrCity;
        this->state = addrState;
    }

    void print()
    {
        std::cout << "Address  : " << address << "\n" << "Zip Code : " << zipCode << "\n" << "Price    : $" << price << "\n";
    }
};