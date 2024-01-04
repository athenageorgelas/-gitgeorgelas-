// CSCI1300 Fall 2023 Project 2
// Author: Athena Georgelas
// Recitation: 102 - Athena Georgelas
//Date: Dec 5, 2023
#ifndef PLAYER2_H
#define PLAYER2_H

#include <iostream>
#include <string>
#include <vector>
#include "structs.h"

using namespace std;




struct Card{

    string color;

    bool is_double;

};

class GamePlayer{
    private:

        //name
        string player_name;

        string character_name;

        //character
        Character _choice;

        //current energy
        int _stamina;

        //current value of money
        double _gold;

        //name of current effect
        string _effect;

        int _player_position;

        int _prev_pos;


    public:
        bool robbers_repel;
        int immunity; 
        int _candy_amount;
        bool lose_turn = false; 
        bool lose_two_turn = false;
        const static int _MAX_CANDY_AMOUNT = 9;
        Candy _inventory[_MAX_CANDY_AMOUNT];

        GamePlayer();
        GamePlayer(Character choice, int stamina, double gold, string effect, Candy candy_array[], const int CANDY_ARR_SIZE);

        bool setPlayerPosition(int);

        void setPrevPos(int);
        int getPrevPos();

        int getPlayerPosition();


        void setPlayerName(string);
        void setCharacterName(string);
        string getPlayerName();
        string getCharacterName();
        int getStamina();
        void setStamina(int stamina);
        double getGold();
        void setGold(double gold);
        string getEffect();
        void setEffect(string effect);
        int getCandyAmount();
        bool validCandySelection(Candy);

        void printInventory();
        Candy findCandyInInventory(string candy_name);
        bool addCandyToInventory(Candy candy);
        bool removeCandyFromInventory(string candy_name);

        void printStats();

        void movePlayerBySpaces(int);
};

#endif