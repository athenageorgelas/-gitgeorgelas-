// CSCI1300 Fall 2023 Project 2
// Author: Athena Georgelas
// Recitation: 102 - Athena Georgelas
//Date: Dec 5, 2023

#ifndef CANDY2_H
#define CANDY2_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "structs.h"
#include "Player2.h"

using namespace std;

class Store{

    private:


        const static int MAX_CANDIES = 4;
        int position;


    public:
        vector<Candy> candies;
        string store_name_;

        Store();
        Store(string store_name, int);
        void readCandy(string file_name);

        void displayCandiesInStore() const;
        int getPosition() const;
        void setPosition(int);

        GamePlayer sell(GamePlayer);
        GamePlayer substitution(GamePlayer);
        Candy findCandyInStore(string);

        void addCandyToStore(vector<Candy> cand);

        bool discount();
        bool unscramble();



};

#endif