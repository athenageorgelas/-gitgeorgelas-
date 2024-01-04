// CSCI1300 Fall 2023 Project 2
// Author: Athena Georgelas
// Recitation: 102 - Athena Georgelas
//Date: Dec 5, 2023

#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>
#include <string>

using namespace std;

struct Character{

    string character_name;

    int stamina;

    double gold;

    vector<string> candies;

};

struct Candy{

    string name;

    string description;

    string effect_type;

    double effect_value;

    string candy_type;

    double price;
};

struct HiddenTreasure{
    string type;

    int pos;
};


#endif