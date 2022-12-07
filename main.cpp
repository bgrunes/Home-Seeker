#include "SeparateChaining.h"
#include "HashMapLP.cpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

HashTableSC createTable();
HashMapLP createMap();


int main()
{
    HashTableSC table;
    HashMapLP map;
    string cmd;
    
    table = createTable();
    map = createMap();

    cout << "Welcome to Home Seeker!\n By Savannah Traub, Brandon Grunes, and Vraj Patel\n\n";
    while(true)
    {
        cout << "Enter a Command: ";
        cin >> cmd;

        if (cmd == "price")
        {
            string price;
            cout << "\nWhat is your asking price?";
            cin >> price;

            //FIXME: Find functions
            auto t1 = chrono::high_resolution_clock::now();
            vector<House> resultTable = table.find(price);
            auto t2 = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(t2-t1).count();

            auto t3 = chrono::high_resolution_clock::now();
            vector<House> resultMap = map.find(price);
            auto t4 = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(t4-t3).count();

            cout << "Took table" << duration << " ms\n";
            cout << "Took map" << duration << "ms\n";

            cout << "Housing Details:\n";
            for (auto i : resultTable)
            {
                if (i.price != stod(price))
                    continue;
                else
                {
                    cout << "- ";
                    i.print();
                    cout << "\n";
                }
            }
        
        }
        else if (cmd == "location")
        {
            string city;
            string state;

            cout << "\nEnter your city and state here(Ex: Gainesville FL): ";
            cin >> city >> state;

            //FIXME: Find functions
            auto t1 = chrono::high_resolution_clock::now();
            vector<House> resultTable = table.find();
            auto t2 = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(t2-t1).count();

            auto t3 = chrono::high_resolution_clock::now();
            vector<House> resultMap = map.find();
            auto t4 = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(t4-t3).count();

            cout << "Took table" << duration << " ms\n";
            cout << "Took map" << duration << "ms\n";

            // Prints only the houses in the specific city and state
            for (auto i : resultTable)
            {
                if (i.city != city && i.state != state)
                    continue;
                else
                {
                    cout << "- ";
                    i.print();
                    cout << "\n";
                }
            }
        }
        else if (cmd == "help")
        {
            cout << "Commands List:\n";
            cout << "--------------\n";
            cout << "1. price\n";
            cout << "2. location\n";
        }
        else if (cmd == "exit")
            return 0;
        else
            cout << "Unknown command, please type 'help' for command list\n";
    }
}

HashTableSC createTable()
{
    ifstream file;
    HashTableSC table;
    string spacer; //for column labels
    string zpid,id,providerListingId,imgSrc,hasImage,detailUrl,statusType;
    string statusText,countryCurrency,price,unformattedPrice,address,addressStreet;
    string addressCity,addressState,addressZipcode,isUndisclosedAddress,beds,baths,area;
    string latLong,isZillowOwned,variableData,badgeInfo,hdpData,isSaved,isUserClaimingOwner;
    string isUserConfirmedClaim,pgapt,sgapt,zestimate,shouldShowZestimateAsPrice,has3DModel,hasVideo;
    string isHomeRec,info2String,brokerName,hasAdditionalAttributions,isFeaturedListing,availabilityDate;
    string list,relaxed,info3String,hasOpenHouse,openHouseStartDate,openHouseEndDate,openHouseDescription;
    string builderName,timeOfExtraction,extractionDate,homeType,daysOnZillow,isFeatured,datePriceChanged;
    string rentZestimate,priceReduction,isPreforclosureAuction,taxAssessedValue,lotAreaValue,lotAreaUnit;
    string priceReductionStr,lotAreaRaw,priceReductionRatio; // All column titles

    file.open("united_states_2022.csv");

    // Ignore 1st row of titles
    getline(file, spacer);
    
    while (!file.eof())
    {
        // Acquire all column data for each house
        getline(file, zpid, ',');
        getline(file, id, ',');
        getline(file, providerListingId, ',');
        getline(file, imgSrc, ',');
        getline(file, hasImage, ',');
        getline(file, detailUrl, ',');
        getline(file, statusType, ',');
        getline(file, statusText, ',');
        getline(file, countryCurrency, ',');
        getline(file, price, ',');
        getline(file, unformattedPrice, ',');
        getline(file, address, ',');
        getline(file, addressStreet, ',');
        getline(file, addressCity, ',');
        getline(file, addressState, ',');
        getline(file, addressZipcode, ',');
        getline(file, isUndisclosedAddress, ',');
        getline(file, beds, ',');
        getline(file, baths, ',');
        getline(file, area, ',');
        getline(file, latLong, ',');
        getline(file, isZillowOwned, ',');
        getline(file, variableData, ',');
        getline(file, badgeInfo, ',');
        getline(file, hdpData, ',');
        getline(file, isSaved, ',');
        getline(file, isUserClaimingOwner, ',');
        getline(file, isUserConfirmedClaim, ',');
        getline(file, pgapt, ',');
        getline(file, sgapt, ',');
        getline(file, zestimate, ',');
        getline(file, shouldShowZestimateAsPrice, ',');
        getline(file, has3DModel, ',');
        getline(file, hasVideo, ',');
        getline(file, isHomeRec, ',');
        getline(file, info2String, ',');
        getline(file, brokerName, ',');
        getline(file, hasAdditionalAttributions, ',');
        getline(file, isFeaturedListing, ',');
        getline(file, availabilityDate, ',');
        getline(file, list, ',');
        getline(file, relaxed, ',');
        getline(file, info3String, ',');
        getline(file, hasOpenHouse, ',');
        getline(file, openHouseStartDate, ',');
        getline(file, openHouseEndDate, ',');
        getline(file, openHouseDescription, ',');
        getline(file, builderName, ',');
        getline(file, timeOfExtraction, ',');
        getline(file, extractionDate, ',');
        getline(file, homeType, ',');
        getline(file, daysOnZillow, ',');
        getline(file, isFeatured, ',');
        getline(file, datePriceChanged, ',');
        getline(file, rentZestimate, ',');
        getline(file, priceReduction, ',');
        getline(file, isPreforclosureAuction, ',');
        getline(file, taxAssessedValue, ',');
        getline(file, lotAreaValue, ',');
        getline(file, lotAreaUnit, ',');
        getline(file, priceReductionStr, ',');
        getline(file, lotAreaRaw, ',');
        getline(file, priceReductionRatio, ',');

        House newHouse(stoi(addressZipcode), stod(price), stod(area), addressCity, addressState, address);
        table.insert(addressZipcode, newHouse);
    }
    
    file.close();
    return table;
}

HashMapLP createMap()
{
    ifstream file;
    HashMapLP map;
    bool works = false;
    string spacer; //for column labels
    string zpid,id,providerListingId,imgSrc,hasImage,detailUrl,statusType;
    string statusText,countryCurrency,price,unformattedPrice,address,addressStreet;
    string addressCity,addressState,addressZipcode,isUndisclosedAddress,beds,baths,area;
    string latLong,isZillowOwned,variableData,badgeInfo,hdpData,isSaved,isUserClaimingOwner;
    string isUserConfirmedClaim,pgapt,sgapt,zestimate,shouldShowZestimateAsPrice,has3DModel,hasVideo;
    string isHomeRec,info2String,brokerName,hasAdditionalAttributions,isFeaturedListing,availabilityDate;
    string list,relaxed,info3String,hasOpenHouse,openHouseStartDate,openHouseEndDate,openHouseDescription;
    string builderName,timeOfExtraction,extractionDate,homeType,daysOnZillow,isFeatured,datePriceChanged;
    string rentZestimate,priceReduction,isPreforclosureAuction,taxAssessedValue,lotAreaValue,lotAreaUnit;
    string priceReductionStr,lotAreaRaw,priceReductionRatio; // All column titles

    file.open("united_states_2022.csv");

    // Ignore 1st row of titles
    getline(file, spacer);
    
    while (!file.eof())
    {
        // Acquire all column data for each house
        getline(file, zpid, ',');
        getline(file, id, ',');
        getline(file, providerListingId, ',');
        getline(file, imgSrc, ',');
        getline(file, hasImage, ',');
        getline(file, detailUrl, ',');
        getline(file, statusType, ',');
        getline(file, statusText, ',');
        getline(file, countryCurrency, ',');
        getline(file, price, ',');
        getline(file, unformattedPrice, ',');
        getline(file, address, ',');
        getline(file, addressStreet, ',');
        getline(file, addressCity, ',');
        getline(file, addressState, ',');
        getline(file, addressZipcode, ',');
        getline(file, isUndisclosedAddress, ',');
        getline(file, beds, ',');
        getline(file, baths, ',');
        getline(file, area, ',');
        getline(file, latLong, ',');
        getline(file, isZillowOwned, ',');
        getline(file, variableData, ',');
        getline(file, badgeInfo, ',');
        getline(file, hdpData, ',');
        getline(file, isSaved, ',');
        getline(file, isUserClaimingOwner, ',');
        getline(file, isUserConfirmedClaim, ',');
        getline(file, pgapt, ',');
        getline(file, sgapt, ',');
        getline(file, zestimate, ',');
        getline(file, shouldShowZestimateAsPrice, ',');
        getline(file, has3DModel, ',');
        getline(file, hasVideo, ',');
        getline(file, isHomeRec, ',');
        getline(file, info2String, ',');
        getline(file, brokerName, ',');
        getline(file, hasAdditionalAttributions, ',');
        getline(file, isFeaturedListing, ',');
        getline(file, availabilityDate, ',');
        getline(file, list, ',');
        getline(file, relaxed, ',');
        getline(file, info3String, ',');
        getline(file, hasOpenHouse, ',');
        getline(file, openHouseStartDate, ',');
        getline(file, openHouseEndDate, ',');
        getline(file, openHouseDescription, ',');
        getline(file, builderName, ',');
        getline(file, timeOfExtraction, ',');
        getline(file, extractionDate, ',');
        getline(file, homeType, ',');
        getline(file, daysOnZillow, ',');
        getline(file, isFeatured, ',');
        getline(file, datePriceChanged, ',');
        getline(file, rentZestimate, ',');
        getline(file, priceReduction, ',');
        getline(file, isPreforclosureAuction, ',');
        getline(file, taxAssessedValue, ',');
        getline(file, lotAreaValue, ',');
        getline(file, lotAreaUnit, ',');
        getline(file, priceReductionStr, ',');
        getline(file, lotAreaRaw, ',');
        getline(file, priceReductionRatio, ',');
        
        House newHouse(stoi(addressZipcode), stod(price), stod(area), addressCity, addressState, address);
        map.insert(addressZipcode, newHouse);

    }

    file.close();
    return map;
}

